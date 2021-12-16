#pragma once

#include "F7/Vec/Vec.h"

using namespace F7;

struct LightSource
{
	using value_type = float;

	Vec4_T<value_type> ambient{ 0,0,0,1 };	// 环境光
	Vec4_T<value_type> diffuse{ 1,1,1,1 };	// 漫反射
	Vec4_T<value_type> specular{ 1,1,1,1 };// 镜面反射
};

// 平行光
struct ParallelLight : public LightSource
{
	Vec3_T<value_type> direction{ 0,0,-1 };		// 方向
};

// 点光源
struct PointLight : public LightSource
{
	Vec3_T<value_type> position{ 0,0,3 };// 位置
	value_type constant{ 1 };//常数项
	value_type linear{ value_type(0.7) };//一次项
	value_type quadratic{ value_type(1.8f) };//二次项
};

// 聚光灯
struct SpotLight : public PointLight
{
	Vec3_T<value_type> direction{ 0,0,-1 };// 方向
	value_type cutOff{ value_type(0.91) };//内半角余弦
	value_type outerCutOff{ value_type(0.82) };//外半角余弦
};
