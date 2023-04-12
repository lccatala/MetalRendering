#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#include "MetalKit/MTKView.hpp"
#include <Foundation/Foundation.hpp>
#include <AppKit/AppKit.hpp>

#include "Renderer.h"


int main() {
    NS::AutoreleasePool* autoreleasePool = NS::AutoreleasePool::alloc()->init();
    
    MyAppDelegate appDelegate;
    NS::Application* sharedApplication = NS::Application::sharedApplication();
    sharedApplication->setDelegate(&appDelegate);
    sharedApplication->run();
    /*  */
    autoreleasePool->release();
}
