#pragma once
#include <simd/simd.h>

typedef enum VertexInputIndex
{
    VertexInputIndexVertices     = 0,
    VertexInputIndexViewportSize = 1,
} VertexInputIndex;

struct Vertex
{
    simd::float3 Position;
    simd::float4 Color;
    simd::float2 TextureCoordinates;
};
