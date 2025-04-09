#pragma once
#ifndef SHADER_H// #ifndef A_H“if not define a.h”,意思是如果没有a_h
#define SHADER_H//如果没有a_h,则定义a_h

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	unsigned int ID;
	//创建构造函数
	Shader(const char* vertexPath, const char* fragmentPath)//放入的参数为顶点着色器和片段着色器的文件夹路径
	{
		//创建字符串,用来储存源代码
		std::string vertexCode;
		std::string fragmentCode;
		//创建输入流对象,为了后续能读顶点着色器和片段着色器的文件夹
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		//确保输入流对象能够抛出异常
		//std::exception是所有异常类的基类,它返回一个虚成员函数what(),利用该虚函数成员，可以获取出异常信息
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			//打开文件夹
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			//创建stringstream对象(用来处理字符串的输入和输出)
			std::stringstream vShaderStream, fShaderStream;
			//将顶点着色器和片段着色器的源代码输入到stringstream对象中
			//这里用到rdbuf(), rdbuf()可以实现一个流对象指向的内容用另一个流对象来输出,即ifstream对象读取的数据输入到stringstream对象中
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//输入完后关闭文件夹
			vShaderFile.close();
			fShaderFile.close();
			//然后将写入stringstream对象中的字符串赋予给先前创建好用来储存源代码的字符串对象
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)//使用 std::ios_base::failure 异常来捕获文件打开失败的情况
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		}
		//执行 try 块中的语句，如果执行的过程中没有异常拋出，那么执行完后就执行最后一个 catch 块后面的语句，所有 catch 块中的语句都不会被执行；
		//如果 try 块执行的过程中拋出了异常，那么拋出异常后立即跳转到第一个“异常类型”和拋出的异常类型匹配的 catch 块中执行（称作异常被该 catch 块“捕获”），执行完后再跳转到最后一个 catch 块后面继续执行。
		//所谓的异常类型有bad_typeid,bad_cast,bad_alloc,ios::base::failure,logic_error等
		//在try块中只有文件打开错误，所以只需要一个catch块
		const char* vShaderCode = vertexCode.c_str(); //c_str用于将 std::string 对象转换为 C 风格的字符串
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;
		//指定该内存空间用来储存顶点着色器
		vertex = glCreateShader(GL_VERTEX_SHADER);
		//将源代码输入进去
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		//编译源代码
		glCompileShader(vertex);
		//检测编译是否成功
		checkCompileErrors(vertex, "VERTEX");
		//指定该内存空间用来储存片段着色器
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		//将源代码输入进去
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		//编译源代码
		glCompileShader(fragment);
		//检测编译是否成功
		checkCompileErrors(fragment, "FRAGMENT");
		//创建着色器程序
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		//检测编译是否成功
		checkCompileErrors(ID, "PROGRAM");
		//链接完后将着色器删除掉
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	//调用着色器成序
	void use()
	{
		glUseProgram(ID);//构造函数的目的是创建着色器程序
	}
	//创建uniform数组
	void setBool(const std::string& name, bool value)const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value)const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value)const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setMat4(const std::string& name, glm::mat4 matrix)const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()),1,GL_FALSE, glm::value_ptr(matrix));
	}
private:
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINK_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};
#endif//如果有a_h，则不用定义
