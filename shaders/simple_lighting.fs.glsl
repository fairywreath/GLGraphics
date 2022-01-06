#version 460 core

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;


/* phong lighting */
void main()
{
	// ambient calculation
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse calculation
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);		// get angle between normal and light direction
	vec3 diffuse = diff * lightColor;

	// specular calculation
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);	// get angle between viewpos and reflected lightdir, then power it to shininess value
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
}