#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include"shader.h"

//���峣��
float mixValue = 0.2f;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
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
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.01f;
		if (mixValue >= 1.0f)
		{
			mixValue = 1.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.01f;
		if (mixValue <= 0.0f)
		{
			mixValue = 0.0f;
		}
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//��������
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

	//������������(����λ��,��ɫ����������)
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	//**************************************************//
	//����һ���ڴ�ռ�
	unsigned int VBO, VAO;
	//����VBO������
	glGenBuffers(1, &VBO);
	//����VAO������
	glGenVertexArrays(1, &VAO);
	//��VAO
	glBindVertexArray(VAO);//VAO�൱��һ��ָ��,����ָ��һ��VBO������
	//ָ���������ɵ�VBO�������������涥�������е�����(ͬʱVBO�������ᱻ����һ��GL_ARRAY_BUFFER��ǩ,֮��ʹ�øñ�ǩ����ζ��ָ���˸û�����,���ڴ�ռ�,��������ͨ�������ǩ�Ի������е����ݽ�������)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//�������������뵽ָ����VBO��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//������������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);//λ������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));//��������
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//****************************************************//
	//VBO��һ�������洢��������Ļ�������EBO��һ�������洢��������Ļ���������VAO��һ�������洢�Ѿ����ú���ô�����������ݷ����Ļ�����
	//��ȡ����Ķ�����������
	int nrAtttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAtttributes);
	std::cout << nrAtttributes << std::endl;

	//������������ɫ������
	Shader ourShader("vertex.glsl", "fragment.glsl");

	//�����������������
	//����һ���ڴ�ռ�
	unsigned int texture1;
	//������������
	glGenTextures(1, &texture1);
	//ָ���û�����������������(ͬʱ�û������ᱻ����GL_TEXTURE_2D�ı�ǩ��������ʹ�øñ�ǩ����ζ��ָ���˸û����������ڴ�ռ䣬��������ͨ�������ǩ����Ƭ�ڴ�ռ��е����ݽ�������)
	glBindTexture(GL_TEXTURE_2D, texture1);
	//���û��ƺ͹��˷�ʽ
	//������uv���귶Χʱ,uv������ƽ�̵�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//������Ŵ����Сʱ,pixel����β���texil
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//����ͼ��
	int width, height, nrChannels;
	//ͼ���width��height����������width��height,���᷵��ͼ���rgbֵ
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		//����֮ǰ���ص�ͼ������һ������,��������������������뵽��������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//������Ҫ����ͼ������ݺ���������һЩ����
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//����������󣬽����������ͼ�����������
	stbi_image_free(data);

	//ͬ����ڶ�������
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//��תy��
	stbi_set_flip_vertically_on_load(true);
	int width1, height1, nrChannels1;
	data = stbi_load("awesomeface.png", &width1, &height1, &nrChannels1, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//�Ȱ�����������Ӧ������Ԫ��Ȼ�����ĸ�uniform��������Ӧ�ĸ�����Ԫ
	//���ǻ�Ҫͨ��ʹ��glUniform1i����ÿ���������ķ�ʽ����OpenGLÿ����ɫ�������������ĸ�����Ԫ������ֻ��Ҫ����һ�μ��ɣ���������������Ⱦѭ����ǰ��
	ourShader.use();
	//֮��������ź�gluniform1i��ʵ��ÿ��uniform��������Ӧ����ȷ������Ԫ
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	//����view matrix:�ƶ���������
	glm::mat4 view= glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//����project matrix:���������ַ�ʽͶ�䵽��Ļ��
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//���������������,ÿ�������忴��������һ���ģ��������������������λ�ü���ת�ǶȲ�ͬ
	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//������Ȼ���:���ֵ�洢��ÿ��Ƭ������,����Ƭ����Ҫ���������ɫʱ,OpenGL�Ὣ�������ֵ����һ֡�����ֵ(��һ֡�����ֵ�ᱻ����z��������)���бȽ�.�����ǰ��Ƭ��������Ƭ��֮��,�����ᱻ����,���򽫻Ḳ��
	glEnable(GL_DEPTH_TEST);
	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		//�ж��Ƿ�رմ���
		processInput(window);

		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ���������������������Ļ����ɫ�������ɫ������
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����һ֡�����ֵ,Ȼ������һ֡�����ֵ,����ѭ��

		//Ҫ��Ƭ����ɫ���е�sampler�������ǹ涨�õ�����,���ȼ�������Ԫ,����Ԫ���ȡ�������󶨺õ�����������ַ,������һ�����
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//������ɫ������
		ourShader.use();
		ourShader.setFloat("mixValue", mixValue);

		glBindVertexArray(VAO);//��VAO,���߶�����ɫ����ζ�ȡ���㻺����������
		//����uniform����ֵ
		for (unsigned int i = 0; i < 10; i++)
		{
			
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(0.5f, 1.0f, 0.0f));
			ourShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		glad_glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
		glad_glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		//���
		glBindVertexArray(0);
		//������Ϣ�¼������������������Ӧ�Ļص����������Ӧ��ע�ắ��
		glfwPollEvents();
		//˫����
		glfwSwapBuffers(window);//������һ֡����һ֡�Ļ�������
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}
