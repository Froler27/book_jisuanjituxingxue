#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 varyingColor;
out vec2 TexCoord;

mat4 buildRotateX(float rad);
mat4 buildRotateY(float rad);
mat4 buildRotateZ(float rad);
mat4 buildTranslate(float x, float y, float z);

void main(void)
{
	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
	varyingColor = vec4(position, 1.0)*0.5 + vec4(0.5, 0.5, 0.5, 0.5);
	TexCoord = aTexCoord;
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