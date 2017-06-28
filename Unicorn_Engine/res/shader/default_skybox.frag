#version 330 core
in vec3 TexCoords;
out vec4 color;

//根据纹理坐标当作输入去采样
uniform samplerCube skybox;

void main()
{
    color = texture(skybox, TexCoords);
}