#pragma once


#include "../../depend/glad/include/glad/glad.h"
#include <string>
#include <iostream>
#include "loading.h"
#include "Texture.h"
#include <vector>
#include <string>
#include <utility>


class ShaderProgram
{
private:
	GLuint programID;
public:
	ShaderProgram(std::string name);
	~ShaderProgram();
	GLuint getID();
	void use();
};

