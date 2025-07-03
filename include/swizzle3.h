#ifndef MATHLIB_SWIZZLE3
#define MATHLIB_SWIZZLE3
#pragma once

#include <vector/vector3.h>

template<typename T>
class Swizzle3
{
public:
    VectorProperty<T>& x;
    VectorProperty<T>& y;
    VectorProperty<T>& z;

    Swizzle3(VectorProperty<T>& xRef, VectorProperty<T>& yRef, VectorProperty<T>& zRef)
        : x(xRef), y(yRef), z(zRef) {
    }

    operator Vector3<T>() const {
        return Vector3<T>(static_cast<T>(x), static_cast<T>(y), static_cast<T>(z));
    }

    Swizzle3<T>& operator=(const Vector3<T>& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }
};

#endif //MATHLIB_SWIZZLE3
