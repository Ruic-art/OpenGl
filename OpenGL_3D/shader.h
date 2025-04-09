#pragma once
#ifndef SHADER_H// #ifndef A_H��if not define a.h��,��˼�����û��a_h
#define SHADER_H//���û��a_h,����a_h

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
	//�������캯��
	Shader(const char* vertexPath, const char* fragmentPath)//����Ĳ���Ϊ������ɫ����Ƭ����ɫ�����ļ���·��
	{
		//�����ַ���,��������Դ����
		std::string vertexCode;
		std::string fragmentCode;
		//��������������,Ϊ�˺����ܶ�������ɫ����Ƭ����ɫ�����ļ���
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		//ȷ�������������ܹ��׳��쳣
		//std::exception�������쳣��Ļ���,������һ�����Ա����what(),���ø��麯����Ա�����Ի�ȡ���쳣��Ϣ
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			//���ļ���
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			//����stringstream����(���������ַ�������������)
			std::stringstream vShaderStream, fShaderStream;
			//��������ɫ����Ƭ����ɫ����Դ�������뵽stringstream������
			//�����õ�rdbuf(), rdbuf()����ʵ��һ��������ָ�����������һ�������������,��ifstream�����ȡ���������뵽stringstream������
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//�������ر��ļ���
			vShaderFile.close();
			fShaderFile.close();
			//Ȼ��д��stringstream�����е��ַ����������ǰ��������������Դ������ַ�������
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)//ʹ�� std::ios_base::failure �쳣�������ļ���ʧ�ܵ����
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		}
		//ִ�� try ���е���䣬���ִ�еĹ�����û���쳣��������ôִ������ִ�����һ�� catch ��������䣬���� catch ���е���䶼���ᱻִ�У�
		//��� try ��ִ�еĹ����В������쳣����ô�����쳣��������ת����һ�����쳣���͡��͒������쳣����ƥ��� catch ����ִ�У������쳣���� catch �顰���񡱣���ִ���������ת�����һ�� catch ��������ִ�С�
		//��ν���쳣������bad_typeid,bad_cast,bad_alloc,ios::base::failure,logic_error��
		//��try����ֻ���ļ��򿪴�������ֻ��Ҫһ��catch��
		const char* vShaderCode = vertexCode.c_str(); //c_str���ڽ� std::string ����ת��Ϊ C �����ַ���
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;
		//ָ�����ڴ�ռ��������涥����ɫ��
		vertex = glCreateShader(GL_VERTEX_SHADER);
		//��Դ���������ȥ
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		//����Դ����
		glCompileShader(vertex);
		//�������Ƿ�ɹ�
		checkCompileErrors(vertex, "VERTEX");
		//ָ�����ڴ�ռ���������Ƭ����ɫ��
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		//��Դ���������ȥ
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		//����Դ����
		glCompileShader(fragment);
		//�������Ƿ�ɹ�
		checkCompileErrors(fragment, "FRAGMENT");
		//������ɫ������
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		//�������Ƿ�ɹ�
		checkCompileErrors(ID, "PROGRAM");
		//���������ɫ��ɾ����
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	//������ɫ������
	void use()
	{
		glUseProgram(ID);//���캯����Ŀ���Ǵ�����ɫ������
	}
	//����uniform����
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
#endif//�����a_h�����ö���
