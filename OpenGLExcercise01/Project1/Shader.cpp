#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Shader::Shader(const char* vertexPath,const char* fragmentPath)
{
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw std::exception("Open File Error");
		}
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		printf(vertexSource);
		printf(fragmentSource);

		

		
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}

	//顶点着色器
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	CheckComileErrors(vertexShader,"VERTEXSHADER");
	//像素着色器
	
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	CheckComileErrors(fragmentShader, "FRAGMENTSHADER");

	//link在一起
	
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	CheckComileErrors(shaderProgram, "PROGRAMSHADER");
	//link之后删除掉
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
}

void Shader::Use()
{
	//使用这个shader进行染色
	glUseProgram(shaderProgram);
	//glUniform1i(glGetUniformLocation());
}

void Shader::CheckComileErrors(int shaderProgram, std::string type)
{
	int success;
	char infoLog[512];
	if (type !="PROGRAMSHADER")
	{
		glGetShaderiv(shaderProgram,GL_COMPILE_STATUS,&success);
		if (!success)
		{
			glGetShaderInfoLog(shaderProgram,512,NULL,infoLog);
			std::cout << "shader compile error: " << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram,1024,NULL,infoLog);
			std::cout << "shader linking error: " << infoLog << std::endl;
		}
	}
}





//Shader::~Shader()
//{
//}
