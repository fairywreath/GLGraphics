#version 460 core
out vec4 FragColor;

/* phong lighting */

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material {
	sampler2D diffuse;		// ambient color is equal to difuse color. 
//	vec3 specular;
	sampler2D specular;		// use specular map
	sampler2D emission;
	float shininess;
};

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


void main()
{
	// ambient calculation
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	// diffuse calculation
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);		// get angle between normal and light direction
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	// specular calculation
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);	// get angle between viewpos and reflected lightdir, then power it to shininess value
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	// emission
    vec3 emission = texture(material.emission, TexCoords).rgb;

	vec3 result = ambient + diffuse + specular + emission;
	FragColor = vec4(result, 1.0);
}