#pragma once
#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
class Renderer
{
    public:
        Renderer(MTL::Device* device);
        ~Renderer();
        void Draw(MTK::View* view);
    private:
        MTL::Device* m_Device;
        MTL::CommandQueue* m_CommandQueue;
};

class MyMTKViewDelegate : public MTK::ViewDelegate 
{
    public:
        MyMTKViewDelegate(MTL::Device* device);
        virtual ~MyMTKViewDelegate() override;
        virtual void drawInMTKView(MTK::View* view) override;
    private:
        Renderer* m_Renderer;
};

class MyAppDelegate : public NS::ApplicationDelegate 
{
    public:
        ~MyAppDelegate();

        NS::Menu* CreateMenuBar();

        virtual void applicationWillFinishLaunching(NS::Notification* notification) override;
        virtual void applicationDidFinishLaunching(NS::Notification* notification) override;
        virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application* sender) override;

    private:
        NS::Window* m_Window;
        MTK::View* m_View;
        MTL::Device* m_Device;
        MyMTKViewDelegate* m_ViewDelegate = nullptr;
};
