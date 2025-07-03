#ifndef MATHLIB_SWIZZLE
#define MATHLIB_SWIZZLE
#pragma once

#include <vector/vector2.h>

template<typename T>
class Swizzle
{
public:
    VectorProperty<T>& x;
    VectorProperty<T>& y;

    Swizzle(VectorProperty<T>& xRef, VectorProperty<T>& yRef) : x(xRef), y(yRef) {}

    operator Vector2<T>() const {
        return Vector2<T>(static_cast<T>(x), static_cast<T>(y));
    }

    Swizzle<T>& operator=(const Vector2<T>& vec) {
        x = vec.x;
        y = vec.y;
        return *this;
    }
};

#endif //MATHLIB_SWIZZLE
