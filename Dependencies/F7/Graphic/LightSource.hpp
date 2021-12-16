#pragma once

#include "F7/Vec/Vec.h"

using namespace F7;

struct LightSource
{
	using value_type = float;

	Vec4_T<value_type> ambient{ 0,0,0,1 };	// ������
	Vec4_T<value_type> diffuse{ 1,1,1,1 };	// ������
	Vec4_T<value_type> specular{ 1,1,1,1 };// ���淴��
};

// ƽ�й�
struct ParallelLight : public LightSource
{
	Vec3_T<value_type> direction{ 0,0,-1 };		// ����
};

// ���Դ
struct PointLight : public LightSource
{
	Vec3_T<value_type> position{ 0,0,3 };// λ��
	value_type constant{ 1 };//������
	value_type linear{ value_type(0.7) };//һ����
	value_type quadratic{ value_type(1.8f) };//������
};

// �۹��
struct SpotLight : public PointLight
{
	Vec3_T<value_type> direction{ 0,0,-1 };// ����
	value_type cutOff{ value_type(0.91) };//�ڰ������
	value_type outerCutOff{ value_type(0.82) };//��������
};
