#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D colorMap;

void main()
{
	color = texture2D(colorMap, UV);
	if(color.r >= 0.95f && color.g >= 0.95f && color.b >= 0.95f){
		discard;
	}
}