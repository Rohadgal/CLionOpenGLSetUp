#pragma once

#include "external/glew-2.1.0/include/GL/glew.h"
#include "external/glfw-3.4/include/GLFW/glfw3.h"
// Reading files
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


class Shader {
private:
	std::string vertexCode, fragmentCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;
	std::stringstream vertexShaderStream, fragmentShaderStream;
	const char* vertexShaderData, *fragmentShaderData;
	unsigned int vertex, fragment;
public:
	GLuint ID;

	// Constructor
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	// Utility uniforms
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;

};
