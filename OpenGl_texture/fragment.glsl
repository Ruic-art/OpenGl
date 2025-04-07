#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//Ƭ����ɫ������ݶ�������������ÿ�����ؽ��в�ֵ����,ʹÿ�����ص����ĵ�����������ϵ��Ҳ�ж�Ӧ����������
	//Ȼ��ͨ��uniform����һ��ȫ�ֱ���,���ⲿ��������
	//֮��ͨ��texture����,����ȡ������ɫ
	FragColor=mix(texture(texture1,TexCoord),texture(texture2,TexCoord),0.2);
}
