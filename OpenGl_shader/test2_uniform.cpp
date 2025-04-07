//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include<iostream>
//
////创建回调函数
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
////创建窗口退出函数
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//设置Esc键为退出键
//	{
//		glfwWindowShouldClose(window) == 1;
//	}
//}
////*******************************************//
////编写顶点作色器源码，输入(每个着色器都要有一个输入和输出)
//const char* vertexShadersource = "#version 330 core\n"
//"layout(location=0) in vec3 aPos;\n"//为顶点着色器输入顶点数据,标识符layout(location=0)的作用相当于glGetAttribLocation,但需要在顶点着色器中指定顶点的属性(比如为位置，颜色，法线等),因为顶点着色器的输入是直接读取顶点缓冲区中的数据，所以两边要明确顶点的属性
//"void main()\n"
//"{\n"
//"gl_Position=vec4(aPos,1.0f);\n"
//"}\n";
////*******************************************//
////编写片段着色器源码，输出
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"uniform vec4 outColor;\n"//uniform是全局变量,即我们可以不用在着色器中定义颜色，可以在着色器外定义颜色，并且uniform可以一直保存变量，直到变量更改或重置
//"void main()\n"
//"{\n"
//"FragColor = outColor;\n"
//"}\n";
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	//创建窗口
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW Window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	//加载与系统相关的opengl函数地址
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	//创建视口
//	glViewport(0, 0, 800, 600);
//
//	//注册函数，返回回调函数的消息
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	//创建顶点数据
//	float vertices[] = {
//		0.5f, 0.5f, 0.0f,   // 右上角
//		0.5f, -0.5f, 0.0f,  // 右下角
//		-0.5f, 0.5f, 0.0f   // 左上角
//	};
//	//**************************************************//
//	//开辟一处内存空间
//	unsigned int VBO, VAO;
//	//生成VBO缓冲区
//	glGenBuffers(1, &VBO);
//	//生成VAO缓冲区
//	glGenVertexArrays(1, &VAO);
//	//绑定VAO
//	glBindVertexArray(VAO);
//	//指定VBO缓冲区用来储存顶点数组
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//将顶点数据输入到指定的VBO缓冲区中
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	//解析顶点数据
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//解析的顶点数据都为位置数据
//	glEnableVertexAttribArray(0);
//	//****************************************************//
//	//VBO是一个用来存储顶点数组的缓冲区，EBO是一个用来存储索引数组的缓冲区，而VAO是一个用来存储已经配置好怎么解析顶点数据方法的缓冲区
//	//****************************************************//
//		//编写顶点着色器和片段着色器
//		//开辟一处内存空间
//	unsigned int vertexShader;
//	//指定该内存空间用来储存顶点着色器源码
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	//将顶点着色器的源代码输入进去或附着上去
//	glShaderSource(vertexShader, 1, &vertexShadersource, NULL);
//	//然后编译
//	glCompileShader(vertexShader);
//
//	//开辟一处内存空间
//	unsigned int fragmentShader;
//	//指定该内存空间用来储存片段着色器
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	//将顶点着色器的源代码输入进去或附着上去
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	//然后编译
//	glCompileShader(fragmentShader);
//
//	//将两个着色器链接到一起
//	//创建着色器程序
//	//开辟一处内存空间
//	unsigned int shaderProgram;
//	//指定该内存空间用来储存着色器程序
//	shaderProgram = glCreateProgram();
//	//将着色器链接到着色器程序上
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	//****************************************************//
//		//检测是否编译成功
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	//检测是否链接成功
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	//***********************************************//
//	//上续都为配置着色器
//	//接下来就要启动着色器程序(换句话说是为opengl配置着色器程序,即配置状态，使shaderProgram有链接顶点和片段着色器的功能)
//	glUseProgram(shaderProgram);
//	//最后要清空着色器的内存空间
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//	//**********************************************//
//	//设置unifom的数据
//	float timeValue = glfwGetTime();//获取时间(上一次调用这个函数到下一次调用这个函数所用的时间)
//	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;//设置颜色值
//	int vertexColorLocation = glGetUniformLocation(shaderProgram, "outColor");//获取uniform的位置
//	glUseProgram(shaderProgram);//同理使shaderProgram有查找unifomd的功能
//	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);//更改unifom的数据
//	//上续都是在配置状态
//
//	//获取输入的顶点属性上限
//	int nrAtttributes;
//	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAtttributes);
//	std::cout << nrAtttributes << std::endl;
//
//	//渲染循环
//	while (!glfwWindowShouldClose(window))
//	{
//		//判断是否关闭窗口
//		processInput(window);
//
//		//渲染指令
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清空屏幕所用的颜色
//		glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓冲区，并用设置清空屏幕的颜色来填充颜色缓冲区
//		glUseProgram(shaderProgram);//启动着色器
//		float timeValue = glfwGetTime();//获取时间(上一次调用这个函数到下一次调用这个函数所用的时间)
//		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;//设置颜色值
//		int vertexColorLocation = glGetUniformLocation(shaderProgram, "outColor");//获取uniform的位置
//		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);//更改unifom的数据
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		//处理消息事件，这个函数会调用相对应的回调函数和相对应的注册函数
//		glfwPollEvents();
//		//双缓冲
//		glfwSwapBuffers(window);//交换上一帧和新一帧的绘制内容
//	}
//	glfwTerminate();
//	return 0;
//}