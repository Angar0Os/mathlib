#ifndef MATHLIB_VECTOR_PROPERTIES
#define MATHLIB_VECTOR_PROPERTIES
#pragma once

#include <iostream>
#include <functional>

template<typename T>
class VectorProperty
{
private:
    T* valuePtr;
    std::function<T(const T&)> getter;
    std::function<void(const T&)> setter;

public:
    VectorProperty(T* ptr,
        std::function<T(const T&)> getterFunc = [](const T& v) { return v; },
        std::function<void(const T&)> setterFunc = [](const T& v) {})
        : valuePtr(ptr), getter(getterFunc), setter(setterFunc) {
    }

    operator T() const
    {
        return getter(*valuePtr);
    }

    VectorProperty<T>& operator=(const T& newValue)
    {
        *valuePtr = newValue;
        setter(newValue);
        return *this;
    }
};

#endif //MATHLIB_VECTOR_PROPERTIES