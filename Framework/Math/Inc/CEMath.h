#pragma once

#include "Common.h"

namespace CASTLEEngine::CEMath
{
    template <typename T> inline T Min(T a, T b) { return (a > b) ? b : a; }
    template <typename T> inline T Max(T a, T b) { return (a < b) ? b : a; }
    template <typename T> inline T Abs(T value) { return (value >= 0) ? value : -value; }
    template <typename T> inline T Clamp(T value, T min, T max) { return Max(min, Min(max, value)); }

    inline float Sign(float value)
    {
        return (value >= 0.0f) ? 1.0f : -1.0f;
    }

    inline float Sqr(float value)
    {
        return value * value;
    }

    inline float Sqrt(float value)
    {
        return std::sqrtf(value);
    }

    inline bool Compare(float a, float b, float epsilon = FLT_MIN)
    {
        return Abs(a - b) <= epsilon;
    }

    inline bool IsZero(float value)
    {
        return Compare(value, 0.0f);
    }

    inline bool IsZero(const Vector2& v)
    {
        return IsZero(v.x) && IsZero(v.y);
    }

    inline bool IsZero(const Vector3& v)
    {
        return IsZero(v.x) && IsZero(v.y) && IsZero(v.z);
    }

    inline bool IsZero(const Vector4& v)
    {
        return IsZero(v.x) && IsZero(v.y) && IsZero(v.z) && IsZero(v.w);
    }

    // Vector Operations
    inline float MagnitudeSqr(const Vector2& v)
    {
        return (v.x * v.x) + (v.y * v.y);
    }

    inline float MagnitudeSqr(const Vector3& v)
    {
        return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    }

    inline float MagnitudeSqr(const Vector4& v)
    {
        return (v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w);
    }

    inline float Magnitude(const Vector2& v)
    {
        return std::sqrt(MagnitudeSqr(v));
    }

    inline float Magnitude(const Vector3& v)
    {
        return std::sqrt(MagnitudeSqr(v));
    }

    inline float Magnitude(const Vector4& v)
    {
        return std::sqrtf(MagnitudeSqr(v));
    }

    inline Vector2 Normalize(const Vector2& v)
    {
        return v / Magnitude(v);
    }

    inline Vector3 Normalize(const Vector3& v)
    {
        return v / Magnitude(v);
    }

    inline Vector4 Normalize(const Vector4& v)
    {
        return v / Magnitude(v);
    }

    inline float DistanceSqr(const Vector2& v1, const Vector2& v2)
    {
        return MagnitudeSqr(v1 - v2);
    }

    inline float DistanceSqr(const Vector3& v1, const Vector3& v2)
    {
        return MagnitudeSqr(v1 - v2);
    }

    inline float DistanceSqr(const Vector4& v1, const Vector4& v2)
    {
        return MagnitudeSqr(v1 - v2);
    }

    inline float Distance(const Vector2& v1, const Vector2& v2)
    {
        return Sqrt(DistanceSqr(v1, v2));
    }

    inline float Distance(const Vector3& v1, const Vector3& v2)
    {
        return Sqrt(DistanceSqr(v1, v2));
    }

    inline float Distance(const Vector4& v1, const Vector4& v2)
    {
        return Sqrt(DistanceSqr(v1, v2));
    }

    inline float Dot(const Vector2& v1, const Vector2& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }

    inline float Dot(const Vector3& v1, const Vector3& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    }

    inline float Dot(const Vector4& v1, const Vector4& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
    }

    inline Vector3 Cross(const Vector3& v1, const Vector3& v2) // Returns vector perpendicular to the 2 vectors
    {
        return Vector3((v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x));
    }

    inline Vector2 Project(const Vector2& v, const Vector2& n)
    {
        return n * (Dot(v, n) / Dot(n, n));
    }

    inline Vector3 Project(const Vector3& v, const Vector3& n)
    {
        return n * (Dot(v, n) / Dot(n, n));
    }

    inline Vector4 Project(const Vector4& v, const Vector4& n)
    {
        return n * (Dot(v, n) / Dot(n, n));
    }

    inline Vector2 Reflect(const Vector2& v, const Vector2& normal)
    {
        return v - (normal * Dot(v, normal) * 2.0f);
    }

    inline Vector3 Reflect(const Vector3& v, const Vector3& normal)
    {
        return v - (normal * Dot(v, normal) * 2.0f);
    }

    inline Vector4 Reflect(const Vector4& v, const Vector4& normal)
    {
        return v - (normal * Dot(v, normal) * 2.0f);
    }

    inline Vector2 GetTranslation(const Matrix3& m)
    {
        return Vector2(m._31, m._32);
    }

    inline Vector3 GetTranslation(const Matrix4& m)
    {
        return Vector3(m._41, m._42, m._43);
    }

    inline Vector3 GetRight(const Matrix4& m)
    {
        return Vector3(m._11, m._12, m._13);
    }

    inline Vector3 GetUp(const Matrix4& m)
    {
        return Vector3(m._21, m._22, m._23);;
    }

    inline Vector3 GetForward(const Matrix4& m)
    {
        return Vector3(m._31, m._32, m._33);
    }

    inline Vector3 GetScale(const Matrix4& m)
    {
        return Vector3(m._11, m._22, m._33);
    }

    inline Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
    {
        float x = v.x * m._11 + v.y * m._21 + v.z * m._31 + m._41;
        float y = v.x * m._12 + v.y * m._22 + v.z * m._32 + m._42;
        float z = v.x * m._13 + v.y * m._23 + v.z * m._33 + m._43;

        return { x, y, z };
    }

    inline Vector3 TransformNormal(const Vector3& v, const Matrix4& m)
    {
        float x = v.x * m._11 + v.y * m._21 + v.z * m._31;
        float y = v.x * m._12 + v.y * m._22 + v.z * m._32;
        float z = v.x * m._13 + v.y * m._23 + v.z * m._33;

        return { x, y, z };
    }

    inline Vector2 Lerp(const Vector2& v0, const Vector2& v1, float t)
    {
        return v0 + ((v1 - v0) * t);
    }

    inline Vector3 Lerp(const Vector3& v0, const Vector3& v1, float t)
    {
        return v0 + ((v1 - v0) * t);
    }

    inline Vector4 Lerp(const Vector4& v0, const Vector4& v1, float t)
    {
        return v0 + ((v1 - v0) * t);
    }

    // Matrix Operations
    inline float Determinant(const Matrix3& m)
    {
        float det = 0.0f;
        det = (m._11 * (m._22 * m._33 - m._23 * m._32));
        det -= (m._12 * (m._21 * m._33 - m._23 * m._31));
        det += (m._13 * (m._21 * m._32 - m._22 * m._31));
        return det;
    }

    inline float Determinant(const Matrix4& m)
    {
        float det = 0.0f;
        det += (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
        det -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
        det += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
        det -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
        return det;
    }

    inline Matrix3 Adjoint(const Matrix3& m)
    {
        return Matrix3
        (
            (m._22 * m._33 - m._23 * m._32),
            -(m._12 * m._33 - m._13 * m._32),
            (m._12 * m._23 - m._13 * m._22),

            -(m._21 * m._33 - m._23 * m._31),
            (m._11 * m._33 - m._13 * m._31),
            -(m._11 * m._23 - m._13 * m._21),

            (m._21 * m._32 - m._22 * m._31),
            -(m._11 * m._32 - m._12 * m._31),
            (m._11 * m._22 - m._12 * m._21)
        );
    }

    inline Matrix4 Adjoint(const Matrix4& m)
    {
        return Matrix4
        (
            (m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
            -(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
            (m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
            -(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),

            -(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
            (m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
            -(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
            (m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),

            (m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
            -(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
            (m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
            -(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),

            -(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
            (m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
            -(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
            (m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))
        );
    }

    inline Matrix3 Inverse(const Matrix3& m)
    {
        const float determinant = Determinant(m);
        const float invDet = 1.0f / determinant;
        return Adjoint(m) * invDet;
    }

    inline Matrix4 Inverse(const Matrix4& m)
    {
        const float determinant = Determinant(m);
        const float invDet = 1.0f / determinant;
        return Adjoint(m) * invDet;
    }

    inline Matrix3 Transpose(const Matrix3& m)
    {
        return Matrix3
        (
            m._11, m._21, m._31,
            m._12, m._22, m._32,
            m._13, m._23, m._33
        );
    }

    inline Matrix4 Transpose(const Matrix4& m)
    {
        return Matrix4
        (
            m._11, m._21, m._31, m._41,
            m._12, m._22, m._32, m._42,
            m._13, m._23, m._33, m._43,
            m._14, m._24, m._34, m._44
        );
    }

    inline Matrix4 Matrix4::RotationAxis(const Vector3& axis, float rad)
    {
        // Normalize located in CEMath
        const Vector3 u = Normalize(axis);
        const float x = u.x;
        const float y = u.y;
        const float z = u.z;
        const float s = sin(rad);
        const float c = cos(rad);

        return {
             c + (x * x * (1.0f - c)),
             x * y * (1.0f - c) + z * s,
             x * z * (1.0f - c) - y * s,
             0.0f,

            x * y * (1.0f - c) - z * s,
             c + (y * y * (1.0f - c)),
             y * z * (1.0f - c) + x * s,
             0.0f,

            x * z * (1.0f - c) + y * s,
             y * z * (1.0f - c) - x * s,
             c + (z * z * (1.0f - c)),
             0.0f,

            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
}