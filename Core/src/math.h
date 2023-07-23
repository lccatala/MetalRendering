#pragma once

#include <simd/simd.h>

namespace Math 
{
    inline constexpr simd::float3 add(const simd::float3& a, const simd::float3& b) 
    {
        return { a.x+b.x, a.y+b.y, a.z+b.z };
    }

    inline constexpr simd_float4x4 Identity() 
    {
        using simd::float4;
        return (simd_float4x4) {
            (float4) {1.0f, 0.0f, 0.0f, 0.0f},
            (float4) {0.0f, 1.0f, 0.0f, 0.0f},
            (float4) {0.0f, 0.0f, 1.0f, 0.0f},
            (float4) {0.0f, 0.0f, 0.0f, 1.0f},
        };
    }

    inline simd::float4x4 Perspective(float fovRadians, float aspectRatio, float zNear, float zFar)
    {
        using simd::float4;

        float ys = 1.0f / tanf(fovRadians * 0.5f);
        float xs = ys / aspectRatio;
        float zs = zFar / (zNear - zFar);

        return simd_matrix_from_rows(
            (float4){ xs, 0.0f, 0.0f, 0.0f },
            (float4){ 0.0f, ys, 0.0f, 0.0f },
            (float4){ 0.0f, 0.0f, zs, zNear * zs },
            (float4){ 0.0f, 0.0f, -1.0f, 0.0f }
        );
    }

    inline simd::float4x4 RotationX(float radians) 
    {
        using simd::float4;
        return simd_matrix_from_rows(
            (float4){ 1.0f, 0.0f, 0.0f, 0.0f },
            (float4){ 0.0f, cosf(radians), sinf(radians), 0.0f },
            (float4){ 0.0f, -sinf(radians), cosf(radians), 0.0f },
            (float4){ 0.0f, 0.0f, 0.0f, 1.0f }
        );
    }

    inline simd::float4x4 RotationY(float radians)
    {
        using simd::float4;
        return simd_matrix_from_rows(
            (float4){ cosf(radians), 0.0f, sinf(radians), 0.0f },
            (float4){ 0.0f, 1.0f, 0.0f, 0.0f },
            (float4){ -sinf(radians), 0.0f, cosf(radians), 0.0f },
            (float4){ 0.0f, 0.0f, 0.0f, 1.0f }
        );
    }

    simd::float4x4 RotationZ(float radians)
    {
        using simd::float4;
        return simd_matrix_from_rows(
            (float4){ cosf(radians), sinf(radians), 0.0f, 0.0f },
            (float4){ -sinf(radians), cosf(radians), 0.0f, 0.0f },
            (float4){ 0.0f, 0.0f, 1.0f, 0.0f },
            (float4){ 0.0f, 0.0f, 0.0f, 1.0f }
        );
    }

    simd::float4x4 Translate(const simd::float3& v)
    {
        using simd::float4;

        const float4 col0 = {1.0f, 0.0f, 0.0f, 0.0f};
        const float4 col1 = {0.0f, 1.0f, 0.0f, 0.0f};
        const float4 col2 = {0.0f, 0.0f, 1.0f, 0.0f};
        const float4 col3 = {v.x, v.y, v.z, 1.0f};

        return simd_matrix(col0, col1, col2, col3);
    }

    simd::float4x4 Scale(const simd::float3& v) 
    {
        using simd::float4;
        return simd_matrix((float4){v.x, 0.0f, 0.0f, 0.0f},
                           (float4){0.0f, v.y, 0.0f, 0.0f},
                           (float4){0.0f, 0.0f, v.z, 0.0f},
                           (float4){0.0f, 0.0f, 0.0f, 1.0f});
    }
}
