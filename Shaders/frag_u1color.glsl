#version 430

in vec4 color_v;
out vec4 color_f;

//uniform vec4 color_u;

void main(void)
{
	color_f = color_v;
}