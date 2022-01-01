#version 460 core
// out vec4 FragColor;

in vec3 color;
in vec2 TexCoord;

uniform sampler2D  aTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//	gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);k


//	gl_FragColor = texture(aTexture, TexCoord);
//	gl_FragColor = texture(aTexture, TexCoord) * vec4(color, 1.0f);
	
//	gl_FragColor = texture(texture1, TexCoord);
	gl_FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}