#include "Renderer.h"
#include "math.h"

MyAppDelegate::~MyAppDelegate()
{
    m_View->release();
    m_Window->release();
    m_Device->release();

    delete m_ViewDelegate;
}

NS::Menu* MyAppDelegate::CreateMenuBar()
{
    using NS::StringEncoding::UTF8StringEncoding;

    NS::Menu* mainMenu = NS::Menu::alloc()->init();
    NS::MenuItem* appMenuItem = NS::MenuItem::alloc()->init();
    NS::Menu* appMenu = NS::Menu::alloc()->init(NS::String::string("Appname", UTF8StringEncoding));

    NS::String* appName = NS::RunningApplication::currentApplication()->localizedName();
    NS::String* quitItemName = NS::String::string("Quit ", UTF8StringEncoding)->stringByAppendingString(appName);
    SEL quitCb = NS::MenuItem::registerActionCallback("appQuit", 
            [](void*, SEL, const NS::Object* sender) 
            {
                auto app = NS::Application::sharedApplication();
                app->terminate(sender);
            });

    NS::MenuItem* appQuitItem = appMenu->addItem(quitItemName, quitCb, NS::String::string("q", UTF8StringEncoding));
    appQuitItem->setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);
    appMenuItem->setSubmenu(appMenu);

    NS::MenuItem* windowMenuItem = NS::MenuItem::alloc()->init();
    NS::Menu* windowMenu = NS::Menu::alloc()->init(NS::String::string("Window", UTF8StringEncoding));
    SEL closeWindowCb = NS::MenuItem::registerActionCallback(
            "windowClose",
            [](void*, SEL, const NS::Object*)
            {
                auto app = NS::Application::sharedApplication();
                app->windows()->object<NS::Window>(0)->close();
            }
            );
    NS::MenuItem* closeWindowItem = windowMenu->addItem(
            NS::String::string("Close window", UTF8StringEncoding),
            closeWindowCb,
            NS::String::string("*", UTF8StringEncoding)
            );
    closeWindowItem->setKeyEquivalentModifierMask( NS::EventModifierFlagCommand );

    windowMenuItem->setSubmenu(windowMenu);

    mainMenu->addItem(appMenuItem);
    mainMenu->addItem(windowMenuItem);

    appMenuItem->release();
    windowMenuItem->release();
    appMenu->release();
    windowMenu->release();

    return mainMenu->autorelease();
}

void MyAppDelegate::applicationWillFinishLaunching(NS::Notification* notification)
{
    NS::Menu* menu = CreateMenuBar();
    NS::Application* app = reinterpret_cast<NS::Application*>(notification->object());
    app->setMainMenu(menu);
    app->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
}

void MyAppDelegate::applicationDidFinishLaunching(NS::Notification* notification)
{
    CGRect frame = (CGRect){ { 100.0, 100.0 }, { 1024.0, 1024.0 } };

    m_Window = NS::Window::alloc()->init(
            frame,
            NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled,
            NS::BackingStoreBuffered,
            false
            );

    m_Device = MTL::CreateSystemDefaultDevice();

    m_View = MTK::View::alloc()->init(frame, m_Device);
    m_View->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    m_View->setClearColor(MTL::ClearColor::Make(0.1, 0.1, 0.1, 0.1));
    m_View->setDepthStencilPixelFormat(MTL::PixelFormat::PixelFormatDepth16Unorm);
    m_View->setClearDepth(1.0f);

    // Set a delegate object to issue commands to Metal
    m_ViewDelegate = new MyMTKViewDelegate(m_Device);
    m_View->setDelegate(m_ViewDelegate);

    m_Window->setContentView(m_View);
    m_Window->setTitle(NS::String::string(
                "Test app", 
                NS::StringEncoding::UTF8StringEncoding
                ));

    m_Window->makeKeyAndOrderFront(nullptr);

    NS::Application* app = reinterpret_cast<NS::Application*>(notification->object());
    app->activateIgnoringOtherApps(true);
}

bool MyAppDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application* sender)
{
    return true;
}

MyMTKViewDelegate::MyMTKViewDelegate(MTL::Device* device)
    : MTK::ViewDelegate(), m_Renderer(new Renderer(device))
{}

MyMTKViewDelegate::~MyMTKViewDelegate()
{
    delete m_Renderer;
}

void MyMTKViewDelegate::drawInMTKView(MTK::View* view)
{
    m_Renderer->Draw(view);
}

Renderer::Renderer(MTL::Device* device)
    : m_Device(device->retain()), m_Angle(0.0f), m_Frame(0)
{
    m_CommandQueue = m_Device->newCommandQueue();

    BuildShaders();
    BuildDepthStencilStates();
    BuildBuffers();
    /* BuildFrameData(); */

    // Use a semaphore to explicitly syncrhonize buffer updates
    // This ensures the CPU isn't updating the same buffer the GPU reads from
    m_Semaphore = dispatch_semaphore_create(k_MaxFramesInFlight);
}

Renderer::~Renderer()
{
    m_ShaderLibrary->release();
    m_VertexDataBuffer->release();
    m_DepthStencilState->release();
    /* m_ArgBuffer->release(); */
    /* m_VertexPositionsBuffer->release(); */
    /* m_VertexColorsBuffer->release(); */
    for (int i = 0; i < k_MaxFramesInFlight; ++i)
    {
        /* m_FrameData[i]->release(); */
        m_InstanceDataBuffer[i]->release();
        m_CameraDataBuffer[i]->release(); // TODO: check why the sample does this in separate loops
    }
    m_IndexBuffer->release();
    m_RenderPipelineState->release();
    m_CommandQueue->release();
    m_Device->release();
}

// Structs for passing instance transform and color
// and perspective and world transform matrices to the GPU
namespace ShaderTypes
{
    struct VertexData
    {
        simd::float3 Position;
        simd::float3 Normal;
    };

    struct InstanceData
    {
        simd::float4x4 InstanceTransform;
        simd::float3x3 InstanceNormalTransform;
        simd::float4   InstanceColor;
    };

    struct CameraData
    {
        simd::float4x4 PerspectiveTransform;
        simd::float4x4 WorldTransform;
        simd::float3x3 WorldNormalTransform;
    };
}

std::string Renderer::ReadFile(const std::string& filepath)
{
    std::string result;

    std::ifstream file(filepath, std::ios::in);
    if (!file)
    {
        __builtin_printf("File %s not found", filepath.c_str());
        assert(false);
    }
    else
    {
        file.seekg(0, std::ios::end); // Pointing at the end of the file
        result.resize(file.tellg()); // Resize output string to file size
        file.seekg(0, std::ios::beg); // Move to the beggining of the file
        file.read(&result[0], result.size());
        file.close();
    }

    return result;
}

void Renderer::BuildShaders() 
{
    using NS::StringEncoding::UTF8StringEncoding;

    const std::string shaderSrc = ReadFile("Core/resources/shader.metal");
    NS::Error* error = nullptr;
    MTL::Library* library = m_Device->newLibrary(
            NS::String::string(shaderSrc.c_str(), UTF8StringEncoding), 
            nullptr,
            &error
            );
    if (!library) 
    {
        __builtin_printf("%s", error->localizedDescription()->utf8String());
        assert(false);
    }

    // Extract one object per function from the library (shader)
    MTL::Function* vertexFunction = library->newFunction(
            NS::String::string("vertexMain", UTF8StringEncoding));
    MTL::Function* fragmentFunction = library->newFunction(
            NS::String::string("fragmentMain", UTF8StringEncoding));

    // Use the RenderPipelineDescriptor to configure what shaders the render pipeline should use
    MTL::RenderPipelineDescriptor* descriptor =
        MTL::RenderPipelineDescriptor::alloc()->init();
    descriptor->setVertexFunction(vertexFunction);
    descriptor->setFragmentFunction(fragmentFunction);
    descriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    descriptor->setDepthAttachmentPixelFormat(MTL::PixelFormat::PixelFormatDepth16Unorm);

    // When creating a render pipeline state, it's configured to convert the fragment shader's 
    // output into the render target's pixel format. If we wanted to use another pixel format, 
    // we'd have to create a different pipeline state object. Shaders can be reused between state objects.
    // This is an expensive operation, so only do it on startup or when loading is expected.

    m_RenderPipelineState = m_Device->newRenderPipelineState(descriptor, &error);
    if (!m_RenderPipelineState)
    {
        __builtin_printf("%s", error->localizedDescription()->utf8String());
        assert(false);
    }

    vertexFunction->release();
    fragmentFunction->release();
    descriptor->release();
    m_ShaderLibrary = library;
}

// Ensure pixels closest to the camera are visible, 
// independently of draw order
void Renderer::BuildDepthStencilStates() 
{
    MTL::DepthStencilDescriptor* descriptor = MTL::DepthStencilDescriptor::alloc()->init();

    // Only draw fragments that are closer to the camera
    descriptor->setDepthCompareFunction(MTL::CompareFunction::CompareFunctionLess);

    // Update each pixel's depth value for future comparisons
    descriptor->setDepthWriteEnabled(true);

    m_DepthStencilState = m_Device->newDepthStencilState(descriptor);
    descriptor->release();
}

void Renderer::BuildBuffers()
{
    using simd::float3;

    const float s = 0.5f;

    ShaderTypes::VertexData verts[] = {
        //   Positions          Normals
        { { -s, -s, +s }, { 0.f,  0.f,  1.f } },
        { { +s, -s, +s }, { 0.f,  0.f,  1.f } },
        { { +s, +s, +s }, { 0.f,  0.f,  1.f } },
        { { -s, +s, +s }, { 0.f,  0.f,  1.f } },

        { { +s, -s, +s }, { 1.f,  0.f,  0.f } },
        { { +s, -s, -s }, { 1.f,  0.f,  0.f } },
        { { +s, +s, -s }, { 1.f,  0.f,  0.f } },
        { { +s, +s, +s }, { 1.f,  0.f,  0.f } },

        { { +s, -s, -s }, { 0.f,  0.f, -1.f } },
        { { -s, -s, -s }, { 0.f,  0.f, -1.f } },
        { { -s, +s, -s }, { 0.f,  0.f, -1.f } },
        { { +s, +s, -s }, { 0.f,  0.f, -1.f } },

        { { -s, -s, -s }, { -1.f, 0.f,  0.f } },
        { { -s, -s, +s }, { -1.f, 0.f,  0.f } },
        { { -s, +s, +s }, { -1.f, 0.f,  0.f } },
        { { -s, +s, -s }, { -1.f, 0.f,  0.f } },

        { { -s, +s, +s }, { 0.f,  1.f,  0.f } },
        { { +s, +s, +s }, { 0.f,  1.f,  0.f } },
        { { +s, +s, -s }, { 0.f,  1.f,  0.f } },
        { { -s, +s, -s }, { 0.f,  1.f,  0.f } },

        { { -s, -s, -s }, { 0.f, -1.f,  0.f } },
        { { +s, -s, -s }, { 0.f, -1.f,  0.f } },
        { { +s, -s, +s }, { 0.f, -1.f,  0.f } },
        { { -s, -s, +s }, { 0.f, -1.f,  0.f } },
    };

    uint16_t indices[] = {
        0,  1,  2,  2,  3,  0, // Front
        4,  5,  6,  6,  7,  4, // Right
        8,  9, 10, 10, 11,  8, // Back
        12, 13, 14, 14, 15, 12, // Left
        16, 17, 18, 18, 19, 16, // Top
        20, 21, 22, 22, 23, 20, // Bottom
    };

    const size_t vertexDataSize = sizeof(verts);
    const size_t indexDataSize  = sizeof(indices);

    MTL::Buffer* vertexBuffer = m_Device->newBuffer(vertexDataSize, MTL::ResourceStorageModeManaged);
    MTL::Buffer* indexBuffer = m_Device->newBuffer(indexDataSize, MTL::ResourceStorageModeManaged);

    m_VertexDataBuffer = vertexBuffer;
    m_IndexBuffer = indexBuffer;

    memcpy(m_VertexDataBuffer->contents(), verts, vertexDataSize);
    memcpy(m_IndexBuffer->contents(), indices, indexDataSize);

    m_VertexDataBuffer->didModifyRange(NS::Range::Make(0, m_VertexDataBuffer->length()));
    m_IndexBuffer->didModifyRange(NS::Range::Make(0, m_IndexBuffer->length()));

    const size_t instanceDataSize = k_MaxFramesInFlight * k_NumInstances * sizeof(ShaderTypes::InstanceData);

    // Initialize buffers for each instance
    for (size_t i = 0; i < k_MaxFramesInFlight; ++i)
    {
        m_InstanceDataBuffer[i] = m_Device->newBuffer(instanceDataSize, MTL::ResourceStorageModeManaged);
    }

    const size_t cameraDataSize = k_MaxFramesInFlight * sizeof(ShaderTypes::CameraData);
    for (size_t i = 0; i < k_MaxFramesInFlight; ++i)
    {
        m_CameraDataBuffer[i] = m_Device->newBuffer(cameraDataSize, MTL::ResourceStorageModeManaged);
    }
}

struct FrameData
{
    float angle;
};
void Renderer::BuildFrameData()
{
    // Pass 3 versions of FrameData to GPU using multiple buffers.
    // This is typically used when passing larger ammounts of data
    // In this case we could simply use setVertexBytes()
    for (int i = 0; i < k_MaxFramesInFlight; ++i)
    {
        m_FrameData[i] = m_Device->newBuffer(sizeof(FrameData), MTL::ResourceStorageModeManaged);
    }
}

void Renderer::Draw(MTK::View* view)
{
    using simd::float3;
    using simd::float4;
    using simd::float4x4;

    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();

    // Use a different buffer each time to avoid race conditions between CPU and GPU
    m_Frame = (m_Frame + 1) % k_MaxFramesInFlight;
    MTL::Buffer* instanceDataBuffer = m_InstanceDataBuffer[m_Frame];

    MTL::CommandBuffer* commandBuffer = m_CommandQueue->commandBuffer();

    // Force CPU to wait if the GPU hasn't finished reading the next buffer in the cycle
    dispatch_semaphore_wait(m_Semaphore, DISPATCH_TIME_FOREVER);

    // The renderer receives a notification that the GPU has finished processing each command buffer via a completed handler closure
    // (invoked by Metal)
    Renderer* renderer = this;
    commandBuffer->addCompletedHandler(^void(MTL::CommandBuffer* commandBuffer) {
        dispatch_semaphore_signal(renderer->m_Semaphore);
    });

    m_Angle += 0.02f;

    const float scale = 0.2f;

    // Update position and color of every instance
    ShaderTypes::InstanceData* instanceData = reinterpret_cast<ShaderTypes::InstanceData*>(instanceDataBuffer->contents());

    float3 objectPosition = { 0.0f, 0.0f, -10.0f };

    // Update instance positions
    float4x4 rt = Math::Translate(objectPosition);

    float4x4 rr0 = Math::RotationY(-m_Angle);
    float4x4 rr1 = Math::RotationY(m_Angle * 0.5);
    float4x4 rtInv = Math::Translate({ -objectPosition.x, -objectPosition.y, -objectPosition.z });
    float4x4 fullObjectRotation = rt * rr1 * rr0 * rtInv;

    size_t ix = 0;
    size_t iy = 0;
    size_t iz = 0;
    for (size_t i = 0; i < k_NumInstances; ++i)
    {
        if (ix == k_InstanceRows)
        {
            ix = 0;
            ++iy;
        }
        if (iy == k_InstanceRows)
        {
            iy = 0;
            ++iz;
        }

        // 3D transform of instance
        float4x4 scaleMatrix = Math::Scale((float3){scale, scale, scale});
        float4x4 rotationMatrixZ = Math::RotationZ(m_Angle * sinf((float)ix));
        float4x4 rotationMatrixY = Math::RotationY(m_Angle * cosf((float)iy));

        float x = ((float)ix - (float)k_InstanceRows/2.0f) * (2.0f * scale) + scale;
        float y = ((float)iy - (float)k_InstanceCols/2.0f) * (2.0f * scale) + scale;
        float z = ((float)iz - (float)k_InstanceDepth/2.0f) * (2.0f * scale) + scale;
        float4x4 translationMatrix = Math::Translate(Math::add(objectPosition, { x, y, z }));

        instanceData[i].InstanceTransform = fullObjectRotation * translationMatrix * rotationMatrixY * rotationMatrixZ * scaleMatrix;
        instanceData[i].InstanceNormalTransform = Math::DiscardTranslation(instanceData[i].InstanceTransform);

        float iDivNumInstances = i / (float)k_NumInstances;

        float r = iDivNumInstances;
        float g = 1.0f - r;
        float b = sinf(M_PI * 2.0f * iDivNumInstances);

        instanceData[i].InstanceColor = (float4){ r, g, b, 1.0f };

        ++ix;
    }

    instanceDataBuffer->didModifyRange(NS::Range::Make(0, instanceDataBuffer->length()));

    // Update camera state
    MTL::Buffer* cameraDataBuffer = m_CameraDataBuffer[m_Frame];
    ShaderTypes::CameraData* cameraData = reinterpret_cast<ShaderTypes::CameraData*>(cameraDataBuffer->contents());

    // Apply perspective projection
    cameraData->PerspectiveTransform = Math::Perspective(45.0f * M_PI / 180.0f, 1.0f, 0.03f, 500.0f);
    cameraData->WorldTransform = Math::Identity();
    cameraData->WorldNormalTransform = Math::DiscardTranslation(cameraData->WorldTransform);
    cameraDataBuffer->didModifyRange(NS::Range::Make(0, sizeof(ShaderTypes::CameraData)));

    // Begin render pass

    // Describes render targets and how they should be processed at the start and end of a render pass.
    MTL::RenderPassDescriptor* descriptor = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* encoder = commandBuffer->renderCommandEncoder(descriptor);
    encoder->setRenderPipelineState(m_RenderPipelineState);

    // Set depth stencil state and pass updated camera matrices to vertex shader
    encoder->setDepthStencilState(m_DepthStencilState);
    encoder->setVertexBuffer(m_VertexDataBuffer, 0, 0);
    encoder->setVertexBuffer(instanceDataBuffer, 0, 1);
    encoder->setVertexBuffer(cameraDataBuffer, 0, 2);

    // Enable back face culing and set polygon winding order
    // This avoids drawing the interior of geometry 
    encoder->setCullMode(MTL::CullModeBack);
    encoder->setFrontFacingWinding(MTL::Winding::WindingCounterClockwise);

    encoder->drawIndexedPrimitives(
            MTL::PrimitiveTypeTriangle,
            6 * 6, 
            MTL::IndexType::IndexTypeUInt16,
            m_IndexBuffer,
            0,
            // Draw the object 32 times (or whatever the value in k_NumInstances is)
            k_NumInstances); 


    encoder->endEncoding();

    // We could encode more commands with the same set of steps.
    // The final image is rendered as if the commands were processed
    // in the order they were specified, even though they might not be
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();

    pool->release();
}
