#pragma once

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

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
        void BuildFrameData();
        void BuildDepthStencilStates();
        void BuildTextures();
        void Draw(MTK::View* view);
    private:
        static constexpr int k_MaxFramesInFlight = 3;
        static constexpr size_t k_InstanceRows = 10;
        static constexpr size_t k_InstanceCols = 10;
        static constexpr size_t k_InstanceDepth = 10;
        static constexpr size_t k_NumInstances = k_InstanceRows * k_InstanceCols * k_InstanceDepth;

        std::string ReadFile(const std::string& filepath);

        MTL::Device* m_Device;
        MTL::CommandQueue* m_CommandQueue;
        MTL::Library* m_ShaderLibrary;
        MTL::RenderPipelineState* m_RenderPipelineState;
        MTL::DepthStencilState* m_DepthStencilState;
        MTL::Texture* m_Texture;

        MTL::Buffer* m_InstanceDataBuffer[k_NumInstances];
        MTL::Buffer* m_VertexDataBuffer;
        MTL::Buffer* m_IndexBuffer;
        MTL::Buffer* m_CameraDataBuffer[k_MaxFramesInFlight];
        /* MTL::Buffer* m_ArgBuffer; */
        /* MTL::Buffer* m_VertexPositionsBuffer; */
        /* MTL::Buffer* m_VertexColorsBuffer; */

        MTL::Buffer* m_FrameData[3];
        float m_Angle;
        int m_Frame;
        dispatch_semaphore_t m_Semaphore;

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
