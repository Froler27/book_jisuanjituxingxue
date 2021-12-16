#pragma once

#include "Vec.hpp"

namespace F7
{

	template class Vec2_T<int>		;	typedef Vec2_T<int>		Vec2i;
	template class Vec2_T<float>	;	typedef Vec2_T<float>	Vec2f;
	template class Vec2_T<double>	;	typedef Vec2_T<double>	Vec2d;

	template class Vec3_T<int>		;	typedef Vec3_T<int>		Vec3i;
	template class Vec3_T<float>	;	typedef Vec3_T<float>	Vec3f;
	template class Vec3_T<double>	;	typedef Vec3_T<double>	Vec3d;

	template class Vec4_T<int>		;	typedef Vec4_T<int>		Vec4i;
	template class Vec4_T<float>	;	typedef Vec4_T<float>	Vec4f;
	template class Vec4_T<double>	;	typedef Vec4_T<double>	Vec4d;

	template class Color_T<float>	;	typedef Color_T<float>	Colorf;
	template class Color_T<double>	;	typedef Color_T<double>	Colord;

	typedef Vec2f Vec2;
	typedef Vec3f Vec3;
	typedef Vec4f Vec4;
	typedef Colorf Color;
	class Color255;
}