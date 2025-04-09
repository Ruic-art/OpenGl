#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include"shader.h"

//定义常数
float mixValue = 0.2f;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
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

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

	//创建顶点数据(包括位置,颜色和纹理坐标)
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
	//开辟一处内存空间
	unsigned int VBO, VAO;
	//生成VBO缓冲区
	glGenBuffers(1, &VBO);
	//生成VAO缓冲区
	glGenVertexArrays(1, &VAO);
	//绑定VAO
	glBindVertexArray(VAO);//VAO相当于一个指针,它会指向一个VBO缓冲区
	//指定上述生成的VBO缓冲区用来储存顶点数组中的数据(同时VBO缓冲区会被赋予一个GL_ARRAY_BUFFER标签,之后使用该标签就意味这指向了该缓冲区,即内存空间,后续可以通过这个标签对缓冲区中的数据进行设置)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//将顶点数据输入到指定的VBO缓冲区中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//解析顶点数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);//位置数据
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));//纹理数据
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//****************************************************//
	//VBO是一个用来存储顶点数组的缓冲区，EBO是一个用来存储索引数组的缓冲区，而VAO是一个用来存储已经配置好怎么解析顶点数据方法的缓冲区
	//获取输入的顶点属性上限
	int nrAtttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAtttributes);
	std::cout << nrAtttributes << std::endl;

	//创建和链接着色器程序
	Shader ourShader("vertex.glsl", "fragment.glsl");

	//创建纹理和链接纹理
	//开辟一块内存空间
	unsigned int texture1;
	//生成纹理缓冲区
	glGenTextures(1, &texture1);
	//指定该缓冲区用来储存纹理(同时该缓冲区会被贴上GL_TEXTURE_2D的标签，当后续使用该标签就意味着指向了该缓冲区，即内存空间，后续可以通过这个标签对这片内存空间中的数据进行设置)
	glBindTexture(GL_TEXTURE_2D, texture1);
	//设置环绕和过滤方式
	//当超出uv坐标范围时,uv是怎样平铺的
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//当纹理放大或缩小时,pixel是如何采样texil
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//加载图像
	int width, height, nrChannels;
	//图像的width和height会填充纹理的width和height,最后会返回图像的rgb值
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		//利用之前加载的图像生成一张纹理,并把这张纹理的数据输入到缓冲区中
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//这里需要传入图像的数据和输出纹理的一些设置
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//创建完纹理后，将导入进来的图像数据清理掉
	stbi_image_free(data);

	//同理导入第二张纹理
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//翻转y轴
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

	//先绑定两个纹理到对应的纹理单元，然后定义哪个uniform采样器对应哪个纹理单元
	//我们还要通过使用glUniform1i设置每个采样器的方式告诉OpenGL每个着色器采样器属于哪个纹理单元。我们只需要设置一次即可，所以这个会放在渲染循环的前面
	ourShader.use();
	//之后利用序号和gluniform1i来实现每个uniform采样器对应着正确的纹理单元
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	//创建view matrix:移动整个场景
	glm::mat4 view= glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	//创建project matrix:物体以哪种方式投射到屏幕上
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//创建更多的立方体,每个立方体看起来都是一样的，区别在于它们在世界的位置及旋转角度不同
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

	//开启深度缓冲:深度值存储在每个片段里面,当新片段想要输出它的颜色时,OpenGL会将它的深度值和上一帧的深度值(上一帧的深度值会被放入z缓冲区中)进行比较.如果当前的片段在其它片段之后,它将会被丢弃,否则将会覆盖
	glEnable(GL_DEPTH_TEST);
	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//判断是否关闭窗口
		processInput(window);

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓冲区，并用设置清空屏幕的颜色来填充颜色缓冲区
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除上一帧的深度值,然后保留这一帧的深度值,反复循环

		//要想片段着色器中的sampler采样我们规定好的纹理,首先激活纹理单元,纹理单元会获取接下来绑定好的纹理缓冲区地址,并返回一个序号
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//启用着色器程序
		ourShader.use();
		ourShader.setFloat("mixValue", mixValue);

		glBindVertexArray(VAO);//绑定VAO,告诉顶点着色器如何读取顶点缓冲区的数据
		//设置uniform矩阵值
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
		
		//解绑
		glBindVertexArray(0);
		//处理消息事件，这个函数会调用相对应的回调函数和相对应的注册函数
		glfwPollEvents();
		//双缓冲
		glfwSwapBuffers(window);//交换上一帧和新一帧的绘制内容
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}
