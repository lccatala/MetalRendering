#include <metal_stdlib>

using namespace metal;

struct v2f
{
    float4 position [[position]];
    float3 normal; // The normal for each fragment is interpolated across each triangle
    half3 color;
};

struct VertexData
{
    float3 position;
    float3 normal;
    //device float3* positions[[id(0)]];
    //device float3* colors[[id(1)]];
};

struct InstanceData
{
    float4x4 InstanceTransform;
    float3x3 InstanceNormalTransform;
    float4 InstanceColor;
};

struct CameraData
{
    simd::float4x4 PerspectiveTransform;
    simd::float4x4 WorldTransform;
    simd::float3x3 WorldNormalTransform;
};

v2f vertex vertexMain(device const VertexData*   vertexData   [[buffer(0)]],
                      device const InstanceData* instanceData [[buffer(1)]],
                      device const CameraData*    cameraData   [[buffer(2)]],
                      uint                     vertexId   [[vertex_id]],
                      uint                     instanceId [[instance_id]]) // Value of the instance provided by runtime
{
    v2f o;
    const device VertexData& vd = vertexData[vertexId];

    // Determine what instance each vertex belongs to and retrieve its specific data
    float4 pos = float4(vd.position, 1.0);
    pos = instanceData[instanceId].InstanceTransform * pos;
    pos = cameraData->PerspectiveTransform * cameraData->WorldTransform * pos;
    o.position = pos;

    // Normal 
    float3 normal = instanceData[instanceId].InstanceNormalTransform * vd.normal;
    normal = cameraData->WorldNormalTransform * normal;
    o.normal = normal;

    o.color = half3(instanceData[instanceId].InstanceColor.rgb);

    return o;
}

// Use the interpolated normal to calculate the lit 
// color of the fragment via Lambert illumination
half4 fragment fragmentMain(v2f in [[stage_in]])
{
    // We assume the light is coming from front-top-right
    float3 l = normalize(float3(1.0, 1.0, 0.8));
    float3 n = normalize(in.normal);

    float ndotl = saturate(dot(n, l));

    return half4(in.color * 0.1 + in.color * ndotl, 1.0);
}
