//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "stb_image.h"
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include<iostream>
//#include"shader.h"
//
////���峣��
//float mixValue = 0.2f;
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
////�����ص�����
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
////���������˳�����
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//����Esc��Ϊ�˳���
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//	{
//		mixValue += 0.01f;
//		if (mixValue >= 1.0f)
//		{
//			mixValue = 1.0f;
//		}
//	}
//	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//	{
//		mixValue -= 0.01f;
//		if (mixValue <= 0.0f)
//		{
//			mixValue = 0.0f;
//		}
//	}
//}
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	//��������
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW Window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	//������ϵͳ��ص�opengl������ַ
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	//�����ӿ�
//	glViewport(0, 0, 800, 600);
//
//	//ע�ắ�������ػص���������Ϣ
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	//������������(����λ��,��ɫ����������)
//	float vertices[] = {
//		//---λ��---        ---��ɫ---         -����-
//		0.5f,  0.5f, 0.0f , 1.0f, 0.0f, 0.0f ,  1.0f, 1.0f,   // ����
//		0.5f, -0.5f, 0.0f , 0.0f, 1.0f, 0.0f ,  1.0f, 0.0f,   // ����
//		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  , 0.0f, 0.0f,   // ����
//		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f  , 0.0f, 1.0f    // ����
//	};
//	//������������
//	unsigned int indices[] = {
//	   0, 1, 3, // first triangle
//	   1, 2, 3  // second triangle
//	};
//	//**************************************************//
//	//����һ���ڴ�ռ�
//	unsigned int VBO, VAO, EBO;
//	//����VBO������
//	glGenBuffers(1, &VBO);
//	//����EBO������
//	glGenBuffers(1, &EBO);
//	//����VAO������
//	glGenVertexArrays(1, &VAO);
//	//��VAO
//	glBindVertexArray(VAO);//VAO�൱��һ��ָ��,����ָ��һ��VBO������
//	//ָ���������ɵ�VBO�������������涥�������е�����(ͬʱVBO�������ᱻ����һ��GL_ARRAY_BUFFER��ǩ,֮��ʹ�øñ�ǩ����ζ��ָ���˸û�����,���ڴ�ռ�,��������ͨ�������ǩ�Ի������е����ݽ�������)
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//ָ���������ɵ�EBO�����������������������е�����
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//�������������뵽ָ����VBO��������
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	//�������������뵽ָ����EBO��������
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	//������������
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//λ������
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//��ɫ����
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));//��������
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//	//****************************************************//
//	//VBO��һ�������洢��������Ļ�������EBO��һ�������洢��������Ļ���������VAO��һ�������洢�Ѿ����ú���ô�����������ݷ����Ļ�����
//	//��ȡ����Ķ�����������
//	int nrAtttributes;
//	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAtttributes);
//	std::cout << nrAtttributes << std::endl;
//
//	//������������ɫ������
//	Shader ourShader("vertex.glsl", "fragment.glsl");
//
//	//�����������������
//	//����һ���ڴ�ռ�
//	unsigned int texture1;
//	//������������
//	glGenTextures(1, &texture1);
//	//ָ���û�����������������(ͬʱ�û������ᱻ����GL_TEXTURE_2D�ı�ǩ��������ʹ�øñ�ǩ����ζ��ָ���˸û����������ڴ�ռ䣬��������ͨ�������ǩ����Ƭ�ڴ�ռ��е����ݽ�������)
//	glBindTexture(GL_TEXTURE_2D, texture1);
//	//���û��ƺ͹��˷�ʽ
//	//������uv���귶Χʱ,uv������ƽ�̵�
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//������Ŵ����Сʱ,pixel����β���texil
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//����ͼ��
//	int width, height, nrChannels;
//	//ͼ���width��height����������width��height,���᷵��ͼ���rgbֵ
//	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//	if (data)
//	{
//		//����֮ǰ���ص�ͼ������һ������,��������������������뵽��������
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//������Ҫ����ͼ������ݺ���������һЩ����
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	//����������󣬽����������ͼ�����������
//	stbi_image_free(data);
//
//	//ͬ����ڶ�������
//	unsigned int texture2;
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//��תy��
//	stbi_set_flip_vertically_on_load(true);
//	int width1, height1, nrChannels1;
//	data = stbi_load("awesomeface.png", &width1, &height1, &nrChannels1, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(data);
//
//	//�Ȱ�����������Ӧ������Ԫ��Ȼ�����ĸ�uniform��������Ӧ�ĸ�����Ԫ
//	//���ǻ�Ҫͨ��ʹ��glUniform1i����ÿ���������ķ�ʽ����OpenGLÿ����ɫ�������������ĸ�����Ԫ������ֻ��Ҫ����һ�μ��ɣ���������������Ⱦѭ����ǰ��
//	ourShader.use();
//	//֮��������ź�gluniform1i��ʵ��ÿ��uniform��������Ӧ����ȷ������Ԫ
//	ourShader.setInt("texture1", 0);
//	ourShader.setInt("texture2", 1);
//
//	//����
//	////����һ��4*4�ĵ�λ����
//	//glm::mat4 trans;
//	////��ת����
//	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//	////���ž���
//	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
//	//��Ⱦѭ��
//	while (!glfwWindowShouldClose(window))
//	{
//		//�ж��Ƿ�رմ���
//		processInput(window);
//
//		//��Ⱦָ��
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//���������Ļ���õ���ɫ
//		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ���������������������Ļ����ɫ�������ɫ������
//		//Ҫ��Ƭ����ɫ���е�sampler�������ǹ涨�õ�����,���ȼ�������Ԫ,����Ԫ���ȡ�������󶨺õ�����������ַ,������һ�����
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//		ourShader.setFloat("mixValue", mixValue);
//
//		//����
//		//trans*trans(translate)*trans(rotate):��������,��������������������
//		glm::mat4 trans= glm::mat4(1.0f);
//		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
//		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//
//		//������ɫ������
//		ourShader.use();
//		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
//		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
//		//����GPU����λ���
//		glBindVertexArray(VAO);//��VAO,���߶�����ɫ����ζ�ȡ���㻺����������
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//glDrawElements�������Զ��Ľ��������ݸ�ֵ��������
//		//glDrawArrays(GL_TRIANGLES, 0, 3);
//		//���
//		glBindVertexArray(0);
//		//������Ϣ�¼������������������Ӧ�Ļص����������Ӧ��ע�ắ��
//		glfwPollEvents();
//		//˫����
//		glfwSwapBuffers(window);//������һ֡����һ֡�Ļ�������
//	}
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//	glfwTerminate();
//	return 0;
//}
