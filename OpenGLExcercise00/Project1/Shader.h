#pragma once
#include <string>
class Shader
{
public:
	Shader(const char * vertexPath, const char * fragmentPath);
	//~Shader();
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	int vertexShader , fragmentShader , shaderProgram;
	void Use();

private:
	void CheckComileErrors(int shaderProgram,std::string type);
};

