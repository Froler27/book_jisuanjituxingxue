#version 430

in vec4 varyingColor;
in vec2 TexCoord;
out vec4 color;

uniform sampler2D ourTexture;


void main(void)
{
	color = varyingColor;
	color = texture(ourTexture, TexCoord);
}