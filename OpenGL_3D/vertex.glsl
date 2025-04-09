#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aTexCoord;//输入每个顶点在纹理坐标系下所对应的坐标

out vec2 TexCoord;//输出纹理坐标

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position =projection*view*model*vec4(aPos, 1.0f);
	TexCoord=aTexCoord;
}