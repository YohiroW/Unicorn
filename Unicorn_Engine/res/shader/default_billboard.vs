#version 330 core
//
layout (location = 0) in vec3 quadVertices;
//
out vec2 UV;
//
uniform vec3 billboardPosition_WS;
uniform mat4 VP;
uniform vec2 scaleFactor;
uniform int isFixed;

void main()
{
	gl_Position = VP* vec4(billboardPosition_WS, 1.0);
	if(isFixed == 1)
	{
		gl_Position /= gl_Position.w;
	}
	gl_Position.xy = gl_Position.xy + quadVertices.xy* vec2(scaleFactor.x, scaleFactor.y);

	UV = quadVertices.xy+ vec2(0.5,0.5);
}
