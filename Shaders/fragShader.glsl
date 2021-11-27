#version 430

in vec4 color_v;
in vec2 texCoord_v;
out vec4 color_f;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main(void)
{
	color_f = mix(texture(texture0, texCoord_v), texture(texture1, texCoord_v), 0.25);
}