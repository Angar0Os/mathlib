#ifndef MATHLIB_VECTOR_3
#define MATHLIB_VECTOR_3
#pragma once

#include <utils.h>
#include <swizzle.h>
#include <vector.h>
#include <vector/vector2.h>
#include <vector_properties.h>

template <typename T>
class Vector3 : public Vector<T, 3>
{
public:
    VectorProperty<T> x;
    VectorProperty<T> y;
    VectorProperty<T> z;

    Swizzle<T> xy;

    Vector3() : Vector<T, 3>(),
        x(INIT_VECTOR_PROPERTY(0)),
        y(INIT_VECTOR_PROPERTY(1)),
        z(INIT_VECTOR_PROPERTY(2)),
        xy(x, y)
    {
    }

    Vector3(T arg1, T arg2, T arg3) : Vector<T, 3>({ arg1, arg2, arg3 }),
        x(INIT_VECTOR_PROPERTY(0)),
        y(INIT_VECTOR_PROPERTY(1)),
        z(INIT_VECTOR_PROPERTY(2)),
        xy(x, y)
    {
    }

};



#endif //MATHLIB_VECTOR_3