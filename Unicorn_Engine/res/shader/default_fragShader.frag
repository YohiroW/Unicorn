#version 330 core

in vec2 TexCoords;
out vec4 color;
uniform vec3 viewPosition;
uniform sampler2D diffTex;

in vec3 FragPos;
in vec3 Normal;

#define INVAILD_TEXTURE 32

void main()
{    
	// vec3 lightColor = vec3(1,1,1);
	// vec3 lightPosition = viewPosition;
	// vec3 modelColor = vec3(0.75f,0.75f,0.75f);
	// //ambient
	// vec3 ambient = 0.05f * lightColor;

	//diffuse
	// vec3 diff = vec3(texture(diffTex, TexCoords));
	// vec3 lightDir = normalize(lightPosition - FragPos);
	// vec3 normal = normalize(Normal);
	// vec3 diffuse = diff* max(dot(lightDir, normal),0.0f);

	//specular
	// vec3 viewDir = normalize(viewPosition - FragPos);
	// vec3 viewReflector = reflect(-lightDir,normal);
	// float specPoint = pow(max(dot(viewReflector,viewDir),0.0f),32.0f);
	// vec3 specular = 0.5f* specPoint* lightColor;


	// vec3 final = (ambient + diffuse);
	// color = vec4(final, 1.0);
	color = texture2D(diffTex, TexCoords);
}