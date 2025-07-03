#ifndef MATHLIB_UTILS
#define MATHLIB_UTILS
#pragma once

#define INIT_VECTOR_PROPERTY(index) \
	& this->values[index], \
	[](const T& v) { return v; }, \
	[](const T& v) {}

#endif //MATHLIB_UTILS