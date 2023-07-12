#include "Model.h"

#define TINYOBJLOADER_IMPLEMENTATION // Prevent linker error
#include <tinyobjloader.h>


Model::Model(MTL::Device* device, const NS::String* texturePathString, const std::string& modelPath)
{

    NS::Error* error;
    NS::URL* texturePathUrl;
    texturePathUrl->initFileURLWithPath(texturePathString);
    m_TextureLoader->init(device);
    Texture = m_TextureLoader->newTexture(texturePathUrl, nullptr, &error);
    __builtin_printf("Texture dimensions %lux%lux%lu\n", Texture->width(), Texture->height(), Texture->depth());
    __builtin_printf("Gets here");
    exit(-1);
    if (!Texture)
    {
        __builtin_printf("%s", error->localizedFailureReason()->utf8String());
        assert(false);
    }


    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath.c_str()))
    {
        __builtin_printf("%s %s", warn.c_str(), err.c_str());
        assert(false);
    }

    for (const auto& shape : shapes) 
    {
        for (const auto& index : shape.mesh.indices)
        {
            Vertex vertex{};
            vertex.Position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.TextureCoordinates = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.Color = {1.0f, 1.0f, 1.0f, 1.0f};

            Vertices.push_back(vertex);
            Indices.push_back(Indices.size());
        }
    }
    __builtin_printf("%lu", Vertices.size());
}
