#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include"shader.h"

//创建回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//创建窗口退出函数
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//设置Esc键为退出键
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

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//加载与系统相关的opengl函数地址
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//创建视口
	glViewport(0, 0, 800, 600);

	//注册函数，返回回调函数的消息
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//创建顶点数据(包括位置和颜色)
	float vertices[] = {
		0.5f, 0.5f, 0.0f  , 1.0f,0.0f,0.0f,  // 右上角
		0.5f, -0.5f, 0.0f , 0.0f,1.0f,0.0f,  // 右下角
		-0.5f, 0.5f, 0.0f , 0.0f,0.0f,1.0f  // 左上角
	};
	//**************************************************//
	//开辟一处内存空间
	unsigned int VBO, VAO;
	//生成VBO缓冲区
	glGenBuffers(1, &VBO);
	//生成VAO缓冲区
	glGenVertexArrays(1, &VAO);
	//绑定VAO
	glBindVertexArray(VAO);
	//指定VBO缓冲区用来储存顶点数组
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//将顶点数据输入到指定的VBO缓冲区中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//解析顶点数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//解析的顶点数据都为位置数据
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//****************************************************//
	//VBO是一个用来存储顶点数组的缓冲区，EBO是一个用来存储索引数组的缓冲区，而VAO是一个用来存储已经配置好怎么解析顶点数据方法的缓冲区
	
	//获取输入的顶点属性上限
	int nrAtttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAtttributes);
	std::cout << nrAtttributes << std::endl;

	//创建和链接着色器程序
	Shader ourShader("vertex.glsl","fragment.glsl");

	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//判断是否关闭窗口
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓冲区，并用设置清空屏幕的颜色来填充颜色缓冲区
		//启用着色器程序
		ourShader.use();
		//告诉GPU该如何绘制
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//处理消息事件，这个函数会调用相对应的回调函数和相对应的注册函数
		glfwPollEvents();
		//双缓冲
		glfwSwapBuffers(window);//交换上一帧和新一帧的绘制内容
	}
	glfwTerminate();
	return 0;
}