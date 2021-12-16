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

in vec3 position_v;// 视觉空间中的顶点位置
in vec3 normal_v;// 视觉空间中的法线
in vec3 lightDir_v;// 指向光源的向量
out vec4 color_f;

void main(void)
{
	vec3 N = normalize(normal_v);
	vec3 L = normalize(lightDir_v);
	vec3 V = normalize(-position_v);
	vec3 H = normalize(L + V);

	vec3 ambient = ((globalAmbient + light.ambient)*material.ambient).xyz;
	vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(N,L), 0);
	//vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(2*pow(dot(H,N),2)-1,0), material.shininess);
	vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(dot(H,N),0), material.shininess*3);

	color_f = vec4(ambient+diffuse+specular, 1);
}