#pragma once

namespace CASTLEEngine::CEMath
{
    struct Vector4
    {
        union { float x; float r; };
        union { float y; float g; };
        union { float z; float b; };
        union { float w; float a; };

        constexpr Vector4() noexcept : Vector4{0.0f} {}
        explicit constexpr Vector4(float n) noexcept : Vector4{ n, n, n, n } {}
        constexpr Vector4(float x, float y, float z, float w) noexcept : x{ x }, y{ y }, z{ z }, w{ w } {}

        static const Vector4 Zero;
        static const Vector4 One;
        static const Vector4 XAxis;
        static const Vector4 YAxis;
        static const Vector4 ZAxis;
        static const Vector4 WAxis;

        constexpr Vector4 operator-() const
        {
            return Vector4(-x, -y, -z, -w);
        }

        constexpr Vector4 operator+(const Vector4& rhs) const
        {
            return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
        }

        constexpr Vector4 operator-(const Vector4& rhs) const
        {
            return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
        }

        constexpr Vector4 operator*(const float s) const
        {
            return Vector4(x * s, y * s, z * s, w * s);
        }

        constexpr Vector4 operator/(const float s) const
        {
            return Vector4(x / s, y / s, z / s, w / s);
        }

        constexpr Vector4& operator+=(const Vector4& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;

            return *this;
        }

        constexpr Vector4& operator-=(const Vector4& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;

            return *this;
        }

        constexpr Vector4& operator*=(const float s)
        {
            x *= s;
            y *= s;
            z *= s;
            w *= s;

            return *this;
        }

        constexpr Vector4& operator/=(const float s)
        {
            x /= s;
            y /= s;
            z /= s;
            w /= s;

            return *this;
        }
    };
}