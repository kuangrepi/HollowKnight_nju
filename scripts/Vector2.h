#ifndef HOLLOWKNIGHT_DEMO_VECTOR2_H
#define HOLLOWKNIGHT_DEMO_VECTOR2_H

#include <cmath>

class Vector2
{
public:
    float x;
    float y;

    Vector2() = default;
    ~Vector2() = default;
    Vector2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vector2 operator+(const Vector2& vec) const {
        return Vector2(x + vec.x, y + vec.y);
    }

    void operator+=(const Vector2& vec) {
        x += vec.x, y += vec.y;
    }

    void operator-=(const Vector2& vec) {
        x -= vec.x, y -= vec.y;
    }

    Vector2 operator-(const Vector2& vec) const {
        return Vector2(x - vec.x, y - vec.y);
    }
    float operator*(const Vector2& vec) const {
        return x * vec.x + y * vec.y;
    }

    Vector2 operator*(float val) const {
        return Vector2(x * val, y * val);
    }

    void operator*=(float val) {
        x *= val, y *= val;
    }

    Vector2 normalize() {
        float len = length();
        if (len == 0)
            return Vector2(0, 0);
        return Vector2(x / len, y / len);
    }

    float length();

};

#endif //HOLLOWKNIGHT_DEMO_VECTOR2_H