#ifndef MATHLIB_SWIZZLE_MACROS
#define MATHLIB_SWIZZLE_MACROS
#pragma once

#define DECLARE_SWIZZLES_2D(comp1, comp2) \
    SwizzleBase<T, Vector2<T>> comp1##comp2; \
    SwizzleBase<T, Vector2<T>> comp2##comp1; \
    SwizzleBase<T, Vector2<T>> comp1##comp1; \
    SwizzleBase<T, Vector2<T>> comp2##comp2;

#define INIT_SWIZZLES_2D(comp1, comp2) \
    comp1##comp2(comp1, comp2), \
    comp2##comp1(comp2, comp1), \
    comp1##comp1(comp1, comp1), \
    comp2##comp2(comp2, comp2)

#define DECLARE_SWIZZLES_3D_2COMP(comp1, comp2, comp3) \
    SwizzleBase<T, Vector2<T>> comp1##comp2; \
    SwizzleBase<T, Vector2<T>> comp1##comp3; \
    SwizzleBase<T, Vector2<T>> comp2##comp1; \
    SwizzleBase<T, Vector2<T>> comp2##comp3; \
    SwizzleBase<T, Vector2<T>> comp3##comp1; \
    SwizzleBase<T, Vector2<T>> comp3##comp2; \
    SwizzleBase<T, Vector2<T>> comp1##comp1; \
    SwizzleBase<T, Vector2<T>> comp2##comp2; \
    SwizzleBase<T, Vector2<T>> comp3##comp3;

#define DECLARE_SWIZZLES_3D_3COMP(comp1, comp2, comp3) \
    Swizzle3Base<T, Vector3<T>> comp1##comp2##comp3; \
    Swizzle3Base<T, Vector3<T>> comp1##comp3##comp2; \
    Swizzle3Base<T, Vector3<T>> comp2##comp1##comp3; \
    Swizzle3Base<T, Vector3<T>> comp2##comp3##comp1; \
    Swizzle3Base<T, Vector3<T>> comp3##comp1##comp2; \
    Swizzle3Base<T, Vector3<T>> comp3##comp2##comp1; \
    Swizzle3Base<T, Vector3<T>> comp1##comp1##comp1; \
    Swizzle3Base<T, Vector3<T>> comp2##comp2##comp2; \
    Swizzle3Base<T, Vector3<T>> comp3##comp3##comp3;

#define INIT_SWIZZLES_3D_2COMP(comp1, comp2, comp3) \
    comp1##comp2(comp1, comp2), \
    comp1##comp3(comp1, comp3), \
    comp2##comp1(comp2, comp1), \
    comp2##comp3(comp2, comp3), \
    comp3##comp1(comp3, comp1), \
    comp3##comp2(comp3, comp2), \
    comp1##comp1(comp1, comp1), \
    comp2##comp2(comp2, comp2), \
    comp3##comp3(comp3, comp3)

#define INIT_SWIZZLES_3D_3COMP(comp1, comp2, comp3) \
    comp1##comp2##comp3(comp1, comp2, comp3), \
    comp1##comp3##comp2(comp1, comp3, comp2), \
    comp2##comp1##comp3(comp2, comp1, comp3), \
    comp2##comp3##comp1(comp2, comp3, comp1), \
    comp3##comp1##comp2(comp3, comp1, comp2), \
    comp3##comp2##comp1(comp3, comp2, comp1), \
    comp1##comp1##comp1(comp1, comp1, comp1), \
    comp2##comp2##comp2(comp2, comp2, comp2), \
    comp3##comp3##comp3(comp3, comp3, comp3)

#define DECLARE_SWIZZLES_4D_2COMP(comp1, comp2, comp3, comp4) \
    SwizzleBase<T, Vector2<T>> comp1##comp2; \
    SwizzleBase<T, Vector2<T>> comp1##comp3; \
    SwizzleBase<T, Vector2<T>> comp1##comp4; \
    SwizzleBase<T, Vector2<T>> comp2##comp1; \
    SwizzleBase<T, Vector2<T>> comp2##comp3; \
    SwizzleBase<T, Vector2<T>> comp2##comp4; \
    SwizzleBase<T, Vector2<T>> comp3##comp1; \
    SwizzleBase<T, Vector2<T>> comp3##comp2; \
    SwizzleBase<T, Vector2<T>> comp3##comp4; \
    SwizzleBase<T, Vector2<T>> comp4##comp1; \
    SwizzleBase<T, Vector2<T>> comp4##comp2; \
    SwizzleBase<T, Vector2<T>> comp4##comp3; \
    SwizzleBase<T, Vector2<T>> comp1##comp1; \
    SwizzleBase<T, Vector2<T>> comp2##comp2; \
    SwizzleBase<T, Vector2<T>> comp3##comp3; \
    SwizzleBase<T, Vector2<T>> comp4##comp4;

#define INIT_SWIZZLES_4D_2COMP(comp1, comp2, comp3, comp4) \
    comp1##comp2(comp1, comp2), \
    comp1##comp3(comp1, comp3), \
    comp1##comp4(comp1, comp4), \
    comp2##comp1(comp2, comp1), \
    comp2##comp3(comp2, comp3), \
    comp2##comp4(comp2, comp4), \
    comp3##comp1(comp3, comp1), \
    comp3##comp2(comp3, comp2), \
    comp3##comp4(comp3, comp4), \
    comp4##comp1(comp4, comp1), \
    comp4##comp2(comp4, comp2), \
    comp4##comp3(comp4, comp3), \
    comp1##comp1(comp1, comp1), \
    comp2##comp2(comp2, comp2), \
    comp3##comp3(comp3, comp3), \
    comp4##comp4(comp4, comp4)

#endif //MATHLIB_SWIZZLE_MACROS