#version 430

layout (location = 0) in vec3 position;

uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float tf;

out vec4 varyingColor;

mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

void main(void)
{ 
	float i = gl_InstanceID + tf;
	float a = sin(0.35*i)*8.0;
	float b = sin(0.52*i)*8.0;
	float c = sin(0.7*i)*8.0;

	float k = 1.75f;
	mat4 localRotX = buildRotateX(k*i);
	mat4 localRotY = buildRotateY(k*i);
	mat4 localRotZ = buildRotateZ(k*i);
	mat4 localTrans = buildTranslate(a,b,c);

	mat4 newM_matrix = m_matrix * localTrans *localRotY *localRotZ;
	mat4 mv_matrix = v_matrix * newM_matrix;

	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
	varyingColor = vec4(position, 1.0)*0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}

mat4 buildTranslate(float x, float y, float z)
{
	return mat4(1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				x,y,z,1);
}

mat4 buildRotateX(float rad)
{
	float value_cos = cos(rad);
	float value_sin = sin(rad);
	return mat4(1, 0, 0, 0,
				0, value_cos, value_sin, 0,
				0, -value_sin, value_cos, 0,
				0, 0, 0, 1);
}

mat4 buildRotateY(float rad)
{
	float value_cos = cos(rad);
	float value_sin = sin(rad);
	return mat4(value_cos, 0, -value_sin, 0,
				0, 1, 0, 0,
				value_sin, 0, value_cos, 0,
				0, 0, 0, 1);
}

mat4 buildRotateZ(float rad)
{
	float value_cos = cos(rad);
	float value_sin = sin(rad);
	return mat4(value_cos, value_sin, 0, 0,
				-value_sin, value_cos, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
}