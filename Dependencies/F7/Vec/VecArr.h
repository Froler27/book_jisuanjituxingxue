#pragma once

#include "VecArr.hpp"

namespace F7
{
	template int* vector2ptr<int>(const std::vector<int>&);
	template float* vector2ptr<float>(const std::vector<float>&);
	template double* vector2ptr<double>(const std::vector<double>&);

	template class VecArr_T<int,	Vec2_T<int>>	; using Vec2iArr = VecArr_T<int,	Vec2_T<int>		>;
	template class VecArr_T<float,	Vec2_T<float>>	; using Vec2fArr = VecArr_T<float,	Vec2_T<float>	>;
	template class VecArr_T<double, Vec2_T<double>>	; using Vec2dArr = VecArr_T<double,	Vec2_T<double>	>;

	template class VecArr_T<int,	Vec3_T<int>>	; using Vec3iArr = VecArr_T<int,	Vec3_T<int>		>;
	template class VecArr_T<float,	Vec3_T<float>>	; using Vec3fArr = VecArr_T<float,	Vec3_T<float>	>;
	template class VecArr_T<double, Vec3_T<double>>	; using Vec3dArr = VecArr_T<double,	Vec3_T<double>	>;

	template class VecArr_T<int,	Vec4_T<int>>	; using Vec4iArr = VecArr_T<int,	Vec4_T<int>		>;
	template class VecArr_T<float,	Vec4_T<float>>	; using Vec4fArr = VecArr_T<float,	Vec4_T<float>	>;
	template class VecArr_T<double, Vec4_T<double>>	; using Vec4dArr = VecArr_T<double,	Vec4_T<double>	>;

	using Vec2Arr = Vec2dArr;
	using Vec3Arr = Vec3dArr;
	using Vec4Arr = Vec3dArr;


}