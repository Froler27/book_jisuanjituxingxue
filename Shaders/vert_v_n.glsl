#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 normal_v;
out vec4 color_v;

uniform mat4 proj_view_world_matrix;
uniform vec4 color_u;

void main(void)
{
	gl_Position = proj_view_world_matrix * vec4(position, 1.0);
	normal_v = normal;
	color_v = color_u;
}
