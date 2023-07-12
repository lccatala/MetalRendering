#pragma once

#include "Vertex.h"

#include <vector>
#include <string>

#include <AppKit/AppKit.hpp>
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

class Model
{
public:
    Model(MTL::Device* device, const NS::String* texturePathString, const std::string& modelPath);

    std::vector<Vertex> Vertices;
    std::vector<int> Indices;
    MTL::Texture* Texture;

private:
    MTK::TextureLoader* m_TextureLoader;
};
