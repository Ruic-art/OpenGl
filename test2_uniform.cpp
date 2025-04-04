//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include<iostream>
//
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
//		glfwWindowShouldClose(window) == 1;
//	}
//}
////*******************************************//
////��д������ɫ��Դ�룬����(ÿ����ɫ����Ҫ��һ����������)
//const char* vertexShadersource = "#version 330 core\n"
//"layout(location=0) in vec3 aPos;\n"//Ϊ������ɫ�����붥������,��ʶ��layout(location=0)�������൱��glGetAttribLocation,����Ҫ�ڶ�����ɫ����ָ�����������(����Ϊλ�ã���ɫ�����ߵ�),��Ϊ������ɫ����������ֱ�Ӷ�ȡ���㻺�����е����ݣ���������Ҫ��ȷ���������
//"void main()\n"
//"{\n"
//"gl_Position=vec4(aPos,1.0f);\n"
//"}\n";
////*******************************************//
////��дƬ����ɫ��Դ�룬���
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"uniform vec4 outColor;\n"//uniform��ȫ�ֱ���,�����ǿ��Բ�������ɫ���ж�����ɫ����������ɫ���ⶨ����ɫ������uniform����һֱ���������ֱ���������Ļ�����
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
//	//��������
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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
//	//������������
//	float vertices[] = {
//		0.5f, 0.5f, 0.0f,   // ���Ͻ�
//		0.5f, -0.5f, 0.0f,  // ���½�
//		-0.5f, 0.5f, 0.0f   // ���Ͻ�
//	};
//	//**************************************************//
//	//����һ���ڴ�ռ�
//	unsigned int VBO, VAO;
//	//����VBO������
//	glGenBuffers(1, &VBO);
//	//����VAO������
//	glGenVertexArrays(1, &VAO);
//	//��VAO
//	glBindVertexArray(VAO);
//	//ָ��VBO�������������涥������
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//�������������뵽ָ����VBO��������
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	//������������
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//�����Ķ������ݶ�Ϊλ������
//	glEnableVertexAttribArray(0);
//	//****************************************************//
//	//VBO��һ�������洢��������Ļ�������EBO��һ�������洢��������Ļ���������VAO��һ�������洢�Ѿ����ú���ô�����������ݷ����Ļ�����
//	//****************************************************//
//		//��д������ɫ����Ƭ����ɫ��
//		//����һ���ڴ�ռ�
//	unsigned int vertexShader;
//	//ָ�����ڴ�ռ��������涥����ɫ��Դ��
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	//��������ɫ����Դ���������ȥ������ȥ
//	glShaderSource(vertexShader, 1, &vertexShadersource, NULL);
//	//Ȼ�����
//	glCompileShader(vertexShader);
//
//	//����һ���ڴ�ռ�
//	unsigned int fragmentShader;
//	//ָ�����ڴ�ռ���������Ƭ����ɫ��
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	//��������ɫ����Դ���������ȥ������ȥ
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	//Ȼ�����
//	glCompileShader(fragmentShader);
//
//	//��������ɫ�����ӵ�һ��
//	//������ɫ������
//	//����һ���ڴ�ռ�
//	unsigned int shaderProgram;
//	//ָ�����ڴ�ռ�����������ɫ������
//	shaderProgram = glCreateProgram();
//	//����ɫ�����ӵ���ɫ��������
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	//****************************************************//
//		//����Ƿ����ɹ�
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
//	//����Ƿ����ӳɹ�
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	//***********************************************//
//	//������Ϊ������ɫ��
//	//��������Ҫ������ɫ������(���仰˵��Ϊopengl������ɫ������,������״̬��ʹshaderProgram�����Ӷ����Ƭ����ɫ���Ĺ���)
//	glUseProgram(shaderProgram);
//	//���Ҫ�����ɫ�����ڴ�ռ�
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//	//**********************************************//
//	//����unifom������
//	float timeValue = glfwGetTime();//��ȡʱ��(��һ�ε��������������һ�ε�������������õ�ʱ��)
//	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;//������ɫֵ
//	int vertexColorLocation = glGetUniformLocation(shaderProgram, "outColor");//��ȡuniform��λ��
//	glUseProgram(shaderProgram);//ͬ��ʹshaderProgram�в���unifomd�Ĺ���
//	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);//����unifom������
//	//��������������״̬
//
//	//��ȡ����Ķ�����������
//	int nrAtttributes;
//	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAtttributes);
//	std::cout << nrAtttributes << std::endl;
//
//	//��Ⱦѭ��
//	while (!glfwWindowShouldClose(window))
//	{
//		//�ж��Ƿ�رմ���
//		processInput(window);
//
//		//��Ⱦָ��
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//���������Ļ���õ���ɫ
//		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ���������������������Ļ����ɫ�������ɫ������
//		glUseProgram(shaderProgram);//������ɫ��
//		float timeValue = glfwGetTime();//��ȡʱ��(��һ�ε��������������һ�ε�������������õ�ʱ��)
//		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;//������ɫֵ
//		int vertexColorLocation = glGetUniformLocation(shaderProgram, "outColor");//��ȡuniform��λ��
//		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);//����unifom������
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		//������Ϣ�¼������������������Ӧ�Ļص����������Ӧ��ע�ắ��
//		glfwPollEvents();
//		//˫����
//		glfwSwapBuffers(window);//������һ֡����һ֡�Ļ�������
//	}
//	glfwTerminate();
//	return 0;
//}