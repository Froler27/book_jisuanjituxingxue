#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 normal_v;
out vec4 color_v;

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
//uniform mat4 norm_matrix;

void main(void)
{
	mat4 view_world_matrix = view_matrix * world_matrix;
	vec4 P = view_world_matrix * vec4(position, 1);
	vec3 N = normalize( (view_world_matrix * vec4(normal, 0)).xyz );
	vec3 L = normalize( (view_matrix*vec4(light.position,1)).xyz - P.xyz );
	vec3 V = normalize(-P.xyz);
	vec3 R = reflect(-L, N);

	vec3 ambient = ((globalAmbient + light.ambient)*material.ambient).xyz;
	vec3 diffuse = light.diffuse.xyz * material.diffuse.xyz * max(dot(N,L), 0);
	vec3 specular = material.specular.xyz * light.specular.xyz * pow(max(dot(R,V),0), material.shininess);

	color_v = vec4(ambient+diffuse+specular, 1);
	gl_Position = proj_matrix * P;
}
