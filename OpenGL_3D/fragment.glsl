#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
	//片段着色器会根据顶点的纹理坐标对每个像素进行插值运算,使每个像素的中心点在纹理坐标系下也有对应的纹理坐标
	//然后通过uniform创建一个全局变量,从外部导入纹理
	//之后通过texture函数,来读取纹理颜色
	FragColor=mix(texture(texture1,TexCoord),texture(texture2,TexCoord),mixValue);
}
