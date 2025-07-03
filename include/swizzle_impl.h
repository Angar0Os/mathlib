#ifndef MATHLIB_SWIZZLE_IMPL
#define MATHLIB_SWIZZLE_IMPL
#pragma once

#include <swizzle.h>
#include <vector/vector2.h>
#include <vector/vector3.h>

// Implémentations des opérateurs de conversion et d'assignation pour Swizzle
template<typename T>
Swizzle<T>::operator Vector2<T>() const {
    return Vector2<T>(static_cast<T>(x), static_cast<T>(y));
}

template<typename T>
Swizzle<T>& Swizzle<T>::operator=(const Vector2<T>& vec) {
    x = vec.x;
    y = vec.y;
    return *this;
}

// Implémentations des opérateurs de conversion et d'assignation pour Swizzle3
template<typename T>
Swizzle3<T>::operator Vector3<T>() const {
    return Vector3<T>(static_cast<T>(x), static_cast<T>(y), static_cast<T>(z));
}

template<typename T>
Swizzle3<T>& Swizzle3<T>::operator=(const Vector3<T>& vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

#endif //MATHLIB_SWIZZLE_IMPL
