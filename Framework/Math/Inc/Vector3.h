#pragma once

namespace CASTLEEngine::CEMath
{
    struct Vector3
    {
        union
        {
            struct { float x, y, z; };
            std::array<float, 3> v;
        };

        // if you set up smth that will be constant, the compiler will create it at compile time
        // noexcept is an optimization that teels the compiler to choose when to create it, runtime or compile time
        // explicit to constrain the parameters and constructors for the struct
        constexpr Vector3() noexcept : Vector3{ 0.0f } {};
        explicit constexpr Vector3(float f) noexcept : Vector3{ f, f, f } {};
        constexpr Vector3(float x, float y, float z) noexcept : x{ x }, y{ y }, z{ z } {};

        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 XAxis;
        static const Vector3 YAxis;
        static const Vector3 ZAxis;

        constexpr Vector3 operator-() const
        {
            return Vector3(-x, -y, -z);
        }

        constexpr Vector3 operator+(const Vector3& rhs) const
        {
            return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        constexpr Vector3 operator-(const Vector3& rhs) const
        {
            return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        constexpr Vector3 operator*(const float s) const
        {
            return Vector3(x * s, y * s, z * s);
        }

        constexpr Vector3 operator/(const float s) const
        {
            return Vector3(x / s, y / s, z / s);
        }

        constexpr Vector3& operator+=(const Vector3& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;

            return *this;
        }

        constexpr Vector3& operator-=(const Vector3& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;

            return *this;
        }

        constexpr Vector3& operator*=(const float s)
        {
            x *= s;
            y *= s;
            z *= s;

            return *this;
        }

        constexpr Vector3& operator/=(const float s)
        {
            x /= s;
            y /= s;
            z /= s;

            return *this;
        }

        constexpr bool operator==(const Vector3& rhs)
        {
            if (rhs.x == x && rhs.y == y && rhs.z == z)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };
}