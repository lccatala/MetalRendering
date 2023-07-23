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

v2f vertex vertexMain(device const VertexData* vertexData [[buffer(0)]],
                      device const InstanceData* instanceData [[buffer(1)]],
                      uint                     vertexId   [[vertex_id]],
                      uint                     instanceId [[instance_id]]) // Value of the instance provided by runtime
{
    v2f o;

    // Determine what instance each vertex belongs to and retrieve its specific data
    float4 pos = float4(vertexData[vertexId].position, 1.0);
    o.position = instanceData[instanceId].InstanceTransform * pos;
    o.color = half3(instanceData[instanceId].InstanceColor.rgb);

    return o;
}

half4 fragment fragmentMain(v2f in [[stage_in]])
{
    return half4(in.color, 1.0);
}
