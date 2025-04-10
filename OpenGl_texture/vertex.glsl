#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aTexCoord;//输入每个顶点在纹理坐标系下所对应的坐标

out vec3 ourColor;
out vec2 TexCoord;//输出纹理坐标

void main()
{
	gl_Position = vec4(aPos.x,aPos.y,aPos.z, 1.0);
	ourColor=aColor;
	TexCoord=aTexCoord;
}