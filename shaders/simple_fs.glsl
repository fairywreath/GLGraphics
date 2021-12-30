#version 460 core
// out vec4 FragColor;

in vec3 color;
in vec2 TexCoord;

uniform sampler2D  aTexture;

void main()
{
	gl_FragColor = texture(aTexture, TexCoord);
}