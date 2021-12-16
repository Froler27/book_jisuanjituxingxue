#pragma once

#include "Mat.hpp"

namespace F7
{

	template class Mat4_T<float>;		using Mat4f = Mat4_T<float>;
	template class Mat4_T<double>;		using Mat4d = Mat4_T<double>;
	template class Mat4_T<long double>;	using Mat4ld = Mat4_T<long double>;

	using Mat4 = Mat4f;
}