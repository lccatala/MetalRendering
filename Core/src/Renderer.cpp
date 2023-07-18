#include "Renderer.h"

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
    CGRect frame = (CGRect){{100.0, 100.0}, {512.0, 512.0}};

    m_Window = NS::Window::alloc()->init(
            frame,
            NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled,
            NS::BackingStoreBuffered,
            false
            );

    m_Device = MTL::CreateSystemDefaultDevice();

    m_View = MTK::View::alloc()->init(frame, m_Device);
    m_View->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    m_View->setClearColor(MTL::ClearColor::Make(0.2, 0.6, 0.8, 1.0));

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
    BuildBuffers();
    BuildFrameData();

    // Use a semaphore to explicitly syncrhonize buffer updates
    // This ensures the CPU isn't updating the same buffer the GPU reads from
    m_Semaphore = dispatch_semaphore_create(k_MaxFramesInFlight);
}

Renderer::~Renderer()
{
    m_ShaderLibrary->release();
    m_ArgBuffer->release();
    m_VertexPositionsBuffer->release();
    m_VertexColorsBuffer->release();
    for (int i = 0; i < k_MaxFramesInFlight; ++i)
    {
        m_FrameData[i]->release();
    }
    m_RenderPipelineState->release();
    m_CommandQueue->release();
    m_Device->release();
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

void Renderer::BuildBuffers()
{
    const size_t numVertices = 3;

    simd::float3 positions[numVertices] = {
        { -0.8f,  0.8f, 0.0f },
        {  0.0f, -0.8f, 0.0f },
        {  0.8f,  0.8f, 0.0f }
    };

    simd::float3 colors[numVertices] = {
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f }
    };

    constexpr size_t dataSize = numVertices * sizeof(simd::float3);

    MTL::Buffer* vertexPositionsBuffer = m_Device->newBuffer(dataSize, MTL::ResourceStorageModeManaged);
    MTL::Buffer* vertexColorsBuffer = m_Device->newBuffer(dataSize, MTL::ResourceStorageModeManaged);

    // TODO: This is how they do it in the official sample code,
    // try assigning directly to the class members
    m_VertexPositionsBuffer = vertexPositionsBuffer;
    m_VertexColorsBuffer = vertexColorsBuffer;

    memcpy(m_VertexPositionsBuffer->contents(), positions, dataSize);
    memcpy(m_VertexColorsBuffer->contents(), colors, dataSize);

    // Indicate to Metal the CPU has copied data over to the buffers
    m_VertexPositionsBuffer->didModifyRange(
            NS::Range::Make(0, m_VertexPositionsBuffer->length()));
    m_VertexColorsBuffer->didModifyRange(
            NS::Range::Make(0, m_VertexColorsBuffer->length()));

    using NS::StringEncoding::UTF8StringEncoding;
    
    assert(m_ShaderLibrary);

    MTL::Function* vertexFunction = m_ShaderLibrary->newFunction(
            NS::String::string("vertexMain", UTF8StringEncoding));
    MTL::ArgumentEncoder* argEncoder = vertexFunction->newArgumentEncoder(0);
    MTL::Buffer* argBuffer = m_Device->newBuffer(
            argEncoder->encodedLength(),
            MTL::ResourceStorageModeManaged);
    m_ArgBuffer = argBuffer; // TODO: why not set it up directly on the member??

    // Specify destination to which the encoder writes object references
    argEncoder->setArgumentBuffer(m_ArgBuffer, 0);
    argEncoder->setBuffer(m_VertexPositionsBuffer, 0, 0);
    argEncoder->setBuffer(m_VertexColorsBuffer, 0, 1);

    m_ArgBuffer->didModifyRange(NS::Range::Make(0, m_ArgBuffer->length()));

    vertexFunction->release();
    argEncoder->release();
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
    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();

    // Use a different buffer each time to avoid race conditions between CPU and GPU
    m_Frame = (m_Frame + 1) % k_MaxFramesInFlight;
    MTL::Buffer* frameDataBuffer = m_FrameData[m_Frame];

    MTL::CommandBuffer* commandBuffer = m_CommandQueue->commandBuffer();

    // Force CPU to wait if the GPU hasn't finished reading the next buffer in the cycle
    dispatch_semaphore_wait(m_Semaphore, DISPATCH_TIME_FOREVER);

    // The renderer receives a notification that the GPU has finished processing each command buffer via a completed handler closure
    // (invoked by Metal)
    Renderer* renderer = this;
    commandBuffer->addCompletedHandler(^void(MTL::CommandBuffer* commandBuffer) {
        dispatch_semaphore_signal(renderer->m_Semaphore);
    });

    // Overwrite buffer contents with a new value once it's safe to do so
    reinterpret_cast<FrameData*>(frameDataBuffer->contents())->angle = m_Angle += 0.01f;
    frameDataBuffer->didModifyRange(NS::Range::Make(0, sizeof(FrameData)));
    // Describes render targets and how they should be processed at the start and end of a render pass.
    MTL::RenderPassDescriptor* descriptor = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* encoder = commandBuffer->renderCommandEncoder(descriptor);
    // No arguments to set for fragment, since it uses the output from the vertex stage
    encoder->setRenderPipelineState(m_RenderPipelineState);

    // Make argument buffer available in the vertex shader, since it indirectly
    // uses the vertex buffers through the vertexData argument buffer
    encoder->setVertexBuffer(m_ArgBuffer, 0, 0);
    encoder->useResource(m_VertexPositionsBuffer, MTL::ResourceUsageRead);
    encoder->useResource(m_VertexColorsBuffer, MTL::ResourceUsageRead);
    encoder->setVertexBuffer(frameDataBuffer, 0, 1);
    encoder->drawPrimitives(
            MTL::PrimitiveType::PrimitiveTypeTriangle,
            NS::UInteger(0),
            NS::UInteger(3));

    encoder->endEncoding();

    // We could encode more commands with the same set of steps.
    // The final image is rendered as if the commands were processed
    // in the order they were specified, even though they might not be
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();

    pool->release();
}
