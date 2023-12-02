#pragma once

namespace CASTLEEngine::CEMath
{
    struct Vector2
    {
        float x, y;

        constexpr Vector2() noexcept : Vector2{0.0f} {};
        explicit constexpr Vector2(float f) noexcept : Vector2{ f,f } {};
        constexpr Vector2(float x, float y) noexcept : x{ x }, y{ y } {};

        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 XAxis;
        static const Vector2 YAxis;

        constexpr Vector2 operator-() const
        {
            return Vector2(-x, -y);
        }

        constexpr Vector2 operator+(const Vector2& rhs) const
        {
            return Vector2(x + rhs.x, y + rhs.y);
        }

        constexpr Vector2 operator-(const Vector2& rhs) const
        {
            return Vector2(x - rhs.x, y - rhs.y);
        }

        constexpr Vector2 operator*(float s) const
        {
            return Vector2(x * s, y * s);
        }

        constexpr Vector2 operator/(float s) const
        {
            return Vector2(x / s, y / s);
        }

        constexpr Vector2& operator+=(const Vector2& rhs)
        {
            x += rhs.x;
            y += rhs.y;

            return *this;
        }

        constexpr Vector2& operator-=(const Vector2& rhs)
        {
            x -= rhs.x;
            y -= rhs.y; return *this;
        }

        constexpr Vector2& operator*=(float s)
        {
            x *= s; y *= s; return *this;
        }

        constexpr Vector2& operator/=(float s)
        {
            x /= s; y /= s; return *this;
        }
    };
}