#version 430

struct PositionalLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
};

struct Material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform Material material;
uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 position_v;// �Ӿ��ռ��еĶ���λ��
out vec3 normal_v;// �Ӿ��ռ��еķ���
out vec3 lightDir_v;// ָ���Դ������
out vec3 halfVector_v;


void main(void)
{
	position_v = (view_matrix * world_matrix * vec4(position, 1)).xyz;
	lightDir_v = normalize((view_matrix*vec4(light.position,1)).xyz - position_v);
	normal_v = (view_matrix * world_matrix * vec4(normal, 0)).xyz;
	halfVector_v = lightDir_v - normalize(position_v);// L + V; V = -P; ==> L - P

	gl_Position = proj_matrix * vec4(position_v,1);
}
