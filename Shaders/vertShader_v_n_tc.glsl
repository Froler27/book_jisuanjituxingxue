#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec4 color_v;
out vec2 texCoord_v;

uniform mat4 proj_view_world_matrix;

void main(void)
{
	gl_Position = proj_view_world_matrix * vec4(position, 1.0);
	color_v = vec4(position, 1.0)*0.5 + vec4(0.5, 0.5, 0.5, 0.5);
	texCoord_v = texCoord;
}
