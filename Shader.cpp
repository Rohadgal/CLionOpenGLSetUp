#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open files
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);

		// Read files
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		// Close files
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// Read as a string
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cerr << "FAILED::FILES::TO::READ: " << vertexPath << " or " << fragmentPath << "\n";
		std::cerr << "Exception: " << e.what() << std::endl;
		glfwTerminate();
		return;
	}

	// catch (std::ifstream::failure e)
	// {
	// 	std::cout << "FAILED::FILES::TO::READ\n";
	// 	glfwTerminate();
	// 	return;
	// }

	// Read as Const Char
	vertexShaderData = vertexCode.c_str();
	fragmentShaderData = fragmentCode.c_str();

	/* Shader */
   // Vertex Shader
	this->vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderData, NULL);
	glCompileShader(vertex);

	int success;
	char infolog[1024];

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertex, 1024, NULL, infolog);
		printf("Failed vertex shader");
		printf(infolog);
		printf("\n");
	}


	// Fragment Shader
	this->fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderData, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragment, 1024, NULL, infolog);
		printf("Failed fragment shader");
		printf(infolog);
		printf("\n");
	}

	// Program
	this->ID = glCreateProgram();

	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(ID, 1024, NULL, infolog);
		printf("Failed program");
		printf(infolog);
		printf("\n");
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(this->ID);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
