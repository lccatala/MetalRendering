#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

#include <simd/simd.h>
#include <fstream>
#include <string>
#include <cassert>

class Renderer
{
    public:
        Renderer(MTL::Device* device);
        ~Renderer();
        void BuildShaders();
        void BuildBuffers();
        void Draw(MTK::View* view);
    private:
        std::string ReadFile(const std::string& filepath);

        MTL::Device* m_Device;
        MTL::CommandQueue* m_CommandQueue;
        MTL::Library* m_ShaderLibrary;
        MTL::RenderPipelineState* m_RenderPipelineState;
        MTL::Buffer* m_ArgBuffer;
        MTL::Buffer* m_VertexPositionsBuffer;
        MTL::Buffer* m_VertexColorsBuffer;
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
