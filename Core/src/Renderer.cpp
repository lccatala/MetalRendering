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
    m_View->setClearColor(MTL::ClearColor::Make(1.0, 0.0, 0.0, 1.0));

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
    : m_Device(device->retain())
{
    m_CommandQueue = m_Device->newCommandQueue();
}

Renderer::~Renderer()
{
    m_CommandQueue->release();
    m_Device->release();
}

void Renderer::Draw(MTK::View* view)
{
    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer* commandBuffer = m_CommandQueue->commandBuffer();
    MTL::RenderPassDescriptor* descriptor = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* encoder = commandBuffer->renderCommandEncoder(descriptor);
    encoder->endEncoding();
    commandBuffer->presentDrawable(view->currentDrawable());
    commandBuffer->commit();

    pool->release();
}
