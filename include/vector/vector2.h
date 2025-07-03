#ifndef MATHLIB_VECTOR_2
#define MATHLIB_VECTOR_2
#pragma once

#include <utils.h>
#include <vector.h>
#include <vector_properties.h>
#include <swizzle.h>
#include <swizzle_macro.h>

template<typename T>
class Vector2 : public Vector<T, 2>
{
public:

    VectorProperty<T> x;
    VectorProperty<T> y;

    Vector2() : Vector<T, 2>(),
        x(INIT_VECTOR_PROPERTY(0)),
        y(INIT_VECTOR_PROPERTY(1))
    {
    }

    Vector2(T arg1, T arg2) : Vector<T, 2>({ arg1, arg2 }),
        x(INIT_VECTOR_PROPERTY(0)),
        y(INIT_VECTOR_PROPERTY(1))
    {
    }

};



#endif //MATHLIB_VECTOR_2