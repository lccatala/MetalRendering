#include <metal_stdlib>

using namespace metal;

struct v2f
{
    float4 position [[position]];
    half3 color;
};

struct VertexData
{
    float3 position;
    //device float3* positions[[id(0)]];
    //device float3* colors[[id(1)]];
};

struct InstanceData
{
    float4x4 InstanceTransform;
    float4 InstanceColor;
};

struct CameraData
{
    simd::float4x4 PerspectiveTransform;
    simd::float4x4 WorldTransform;
};

v2f vertex vertexMain(device const VertexData*   vertexData   [[buffer(0)]],
                      device const InstanceData* instanceData [[buffer(1)]],
                      device const CameraData*    cameraData   [[buffer(2)]],
                      uint                     vertexId   [[vertex_id]],
                      uint                     instanceId [[instance_id]]) // Value of the instance provided by runtime
{
    v2f o;

    // Determine what instance each vertex belongs to and retrieve its specific data
    float4 pos = float4(vertexData[vertexId].position, 1.0);
    pos = instanceData[instanceId].InstanceTransform * pos;
    pos = cameraData->PerspectiveTransform * cameraData->WorldTransform * pos;
    o.position = pos;

    o.color = half3(instanceData[instanceId].InstanceColor.rgb);

    return o;
}

half4 fragment fragmentMain(v2f in [[stage_in]])
{
    return half4(in.color, 1.0);
}
