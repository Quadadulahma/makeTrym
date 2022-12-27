#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(std::string name)
{
	std::string vertexShaderString = loadFile("shaders/"+name+".vertex");
	
	const char* vertexShaderCharPtr = vertexShaderString.c_str();
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCharPtr, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[1024];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
		std::cout << "ERROR:: Vertex Shader compilation: " << name << " \n" << infoLog << "\n ----------------------------------------------------- -- " << std::endl;
	}
	else 
	{
		std::cout << "vertex shader compiled: " << name << std::endl;
	}

	std::string fragmentShaderString = loadFile("shaders/" + name + ".fragment");
	const char* fragmentShaderCharPtr = fragmentShaderString.c_str();
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCharPtr, NULL);
	glCompileShader(fragmentShader);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
		std::cout << "ERROR:: Fragment Shader compilation: \n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	}
	else {
		std::cout << "fragment shader compiled: " << name << std::endl;
	}
	programID = glCreateProgram();
	std::cout << "this is the shader id " << programID << std::endl;
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 1024, NULL, infoLog);
		std::cout << "ERROR linking error :\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	}
	else {
		std::cout << "program linked correctly: "<< name << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programID);
}

GLuint ShaderProgram::getID()
{
	return programID;
}

void ShaderProgram::use()
{
	glUseProgram(programID);
}
