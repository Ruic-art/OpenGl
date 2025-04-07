#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include"shader.h"

//�����ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//���������˳�����
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//����Esc��Ϊ�˳���
	{
		glfwSetWindowShouldClose(window,true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//������ϵͳ��ص�opengl������ַ
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//�����ӿ�
	glViewport(0, 0, 800, 600);

	//ע�ắ�������ػص���������Ϣ
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//������������(����λ�ú���ɫ)
	float vertices[] = {
		0.5f, 0.5f, 0.0f  , 1.0f,0.0f,0.0f,  // ���Ͻ�
		0.5f, -0.5f, 0.0f , 0.0f,1.0f,0.0f,  // ���½�
		-0.5f, 0.5f, 0.0f , 0.0f,0.0f,1.0f  // ���Ͻ�
	};
	//**************************************************//
	//����һ���ڴ�ռ�
	unsigned int VBO, VAO;
	//����VBO������
	glGenBuffers(1, &VBO);
	//����VAO������
	glGenVertexArrays(1, &VAO);
	//��VAO
	glBindVertexArray(VAO);
	//ָ��VBO�������������涥������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//�������������뵽ָ����VBO��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//������������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//�����Ķ������ݶ�Ϊλ������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//****************************************************//
	//VBO��һ�������洢��������Ļ�������EBO��һ�������洢��������Ļ���������VAO��һ�������洢�Ѿ����ú���ô�����������ݷ����Ļ�����
	
	//��ȡ����Ķ�����������
	int nrAtttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAtttributes);
	std::cout << nrAtttributes << std::endl;

	//������������ɫ������
	Shader ourShader("vertex.glsl","fragment.glsl");

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		//�ж��Ƿ�رմ���
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ���������������������Ļ����ɫ�������ɫ������
		//������ɫ������
		ourShader.use();
		//����GPU����λ���
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//������Ϣ�¼������������������Ӧ�Ļص����������Ӧ��ע�ắ��
		glfwPollEvents();
		//˫����
		glfwSwapBuffers(window);//������һ֡����һ֡�Ļ�������
	}
	glfwTerminate();
	return 0;
}