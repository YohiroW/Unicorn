#version 330 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;

void main()
{    
	vec3 lightColor = vec3(0.85f);
	vec3 normal = normalize(Normal);

	//only diffuse 
	vec3 diffTexture = texture(texture_diffuse1, TexCoords).rgb;
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffLight = diff* diffTexture* lightColor;

	// vec3 viewPos = lightPos;
	// vec3 viewDir = normalize(viewPos - FragPos);
	// vec3 halfWayDir = normalize(viewDir + lightDir);
	// float spec = pow(max(dot(halfWayDir, normal), 0.0f),16.0f);
	// vec3 specLight = spec * lightColor;

    color = vec4(0.2f* diffTexture + diffLight, 1.0f);
}