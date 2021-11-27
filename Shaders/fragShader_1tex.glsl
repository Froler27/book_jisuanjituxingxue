#version 430

in vec4 color_v;
in vec2 texCoord_v;
out vec4 color_f;

uniform sampler2D texture0;

void main(void)
{
	color_f = texture(texture0, texCoord_v);
}