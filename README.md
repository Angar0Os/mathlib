# MathLib — Modern C++ Math Library

**BEFORE ALL | This library is a learning project that I mainly use to refresh my math knowledge.**

**MathLib** is a modern, header-only mathematics library for C++.  
It provides a complete foundation for 2D and 3D applications: linear algebra, geometry, transformations, and rotation handling.

MathLib is entirely independent from any graphics API or engine.  
It can be used in game engines, physics simulations, rendering tools, or any project that requires a reliable and efficient mathematical core.

---

## Key Features

- Generic types: `Vec2`, `Vec3`, `Vec4`, `Mat2`, `Mat3`, `Mat4`, `Quaternion`
- Complete vector and matrix operations
- 3D transformations: `Translate`, `Rotate`, `Scale`, `LookAt`, `Perspective`, `Ortho`
- Quaternion-based rotations and conversions (Euler ↔ Matrix ↔ Quaternion)
- Fully `constexpr` and header-only (no dependencies)
- Window / MSBuild Only 
- SIMD-ready (SSE, AVX, NEON)
- Inspired by GLM

---

## Project Structure

```
math/
 ├── common.hpp       # Base types and utilities
 ├── vector.hpp       # Generic vectors (Vec2, Vec3, Vec4)
 ├── matrix.hpp       # Matrix types (Mat2, Mat3, Mat4)
 ├── quaternion.hpp   # Rotations and interpolation
 ├── transform.hpp    # Transformations and camera matrices
 └── math.hpp         # Global include header
```

---

## Example Usage

```cpp
#include <math/math.hpp>
using namespace math;

int main()
{
    Vec3 position = { 0, 0, 5 };
    Vec3 target   = { 0, 0, 0 };
    Vec3 up       = { 0, 1, 0 };

    Mat4 view = LookAt(position, target, up);
    Mat4 proj = Perspective(DegToRad(70.0f), 16.0f / 9.0f, 0.1f, 100.0f);

    Vec4 worldPos = { 1, 2, 3, 1 };
    Vec4 clipPos  = proj * view * worldPos;

    return 0;
}
```

---

## Roadmap

### Phase 1 — Core Mathematics
- [x] Implementation of `Vec`, `Mat`, `Quaternion`, and `Transform`
- [x] Base functions (`Dot`, `Cross`, `Lerp`, `Clamp`, etc.)
- [x] Matrix operations (multiplication, transpose, inverse, determinant)

### Phase 2 — SIMD and Performance
- [ ] SIMD implementation (SSE2, AVX, NEON)
- [ ] Optimized vector and matrix operations

### Phase 3 — Advanced Math and Geometry
- [ ] Geometric types: `Ray`, `Plane`, `AABB`, `OBB`, `Sphere`
- [ ] Intersection tests: `RayPlane`, `RaySphere`, `AABB-AABB`, etc.
- [ ] Analytical functions: `Barycentric`, `Reflect`, `Refract`, `Project`
- [ ] Statistical helpers: `Average`, `Variance`, `Min`, `Max`
- [ ] Curves and interpolation: `CubicBezier`, `CatmullRom`, `Hermite`

### Phase 4 — Optional Modules
- [ ] `math::color` (RGB, HSV, conversions)
- [ ] `math::noise` (Perlin, Simplex, Worley)
- [ ] `math::random` (random distributions)
- [ ] `math::geometry` (normals, tangents)
- [ ] `math::spline` (NURBS, B-Spline)

### Phase 5 — Testing, Packaging, and Documentation
- [ ] Complete unit test coverage
- [ ] Doxygen documentation 
- [ ] Example projects under `examples/`

### Phase 6 — Maintenance and Community
- [ ] Semantic versioning (`v1.0.0`)
- [ ] Contribution guidelines and PR templates
- [ ] Compatibility checks (GLM, Eigen, DirectXMath)

---

## Compatibility

- Language: **C++20** or higher  
- Platforms: **Windows**  
- Dependencies: **None**

---

## Integration

Simply include the library headers in your project:

```cpp
#include "math/math.hpp"
```

## License

MIT License  
Free to use, modify, and distribute.

---

## Reference

- [GLM (OpenGL Mathematics)](https://github.com/g-truc/glm)  

---

MathLib aims to provide a clear, performant, and durable mathematical foundation for any modern 3D or simulation project.
