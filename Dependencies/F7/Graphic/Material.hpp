#pragma once

#include "F7/Vec/Vec.h"

using namespace F7;

struct Material
{
	using value_type = float;

	Vec4_T<value_type> ambient;	// ������
	Vec4_T<value_type> diffuse;	// ������
	Vec4_T<value_type> specular;// ���淴��
	value_type shininess;		// ����
}; 

// �ƽ�
const Material MaterialGold{
	{0.24725f, 0.1995f, 0.0745f, 1},
	{0.75164f, 0.60648f, 0.22648f, 1},
	{0.62828f, 0.5558f, 0.36607f, 1},
	51.2f
};

// ����
const Material MaterialSilver{
	{0.19225f, 0.19225f, 0.19225f, 1},
	{0.50754f, 0.50754f, 0.50754f, 1},
	{0.50827f, 0.50827f, 0.50827f, 1},
	51.2f
};
// ��ͭ
const Material MaterialSi{
	{0.2125f, 0.1275f, 0.0540f, 1},
	{0.7140f, 0.4284f, 0.1814f, 1},
	{0.3936f, 0.2719f, 0.1667f, 1},
	25.6f
};