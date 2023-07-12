#include <metal_stdlib>

using namespace metal;

#include "../../Core/src/Vertex.h"

struct RasterizedData
{
    // The [[position]] attribute of this member indicates that this value
    // is the clip space position of the vertex when this structure is
    // returned from the vertex function.
    float4 position [[position]];

    // Since this member does not have a special attribute, the rasterizer
    // interpolates its value with the values of the other triangle vertices
    // and then passes the interpolated value to the fragment shader for each
    // fragment in the triangle.
    float4 color;
};

vertex RasterizedData vertexShader(uint vertexID[[vertex_id]],
                                   constant Vertex *vertices [[buffer(VertexInputIndexVertices)]],
                                   constant vector_uint2 *viewportSizePointer [[buffer(VertexInputIndexViewportSize)]])
{
    RasterizedData out;

    float2 pixelSpacePosition = vertices[vertexID].Position.xy;
    vector_float2 viewportSize = vector_float2(*viewportSizePointer);

    out.position = vector_float4(0.0, 0.0, 0.0, 1.0);
    out.position.xy = pixelSpacePosition / (viewportSize / 2.0);
    out.color = vertices[vertexID].Color;

    return out;
}

fragment float4 fragmentShader(RasterizedData in [[stage_in]]) // Receives the same parameters that were declared in the vertex shaders output
{
    return in.color;
}
