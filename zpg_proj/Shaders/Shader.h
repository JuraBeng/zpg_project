#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	void CreateFromFiles(const char* vertexPath, const char* fragmentPath);
	std::string ReadFile(const char* fileLocation);
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	void UseShader();
	void ClearShader();
	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel;
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint shaderProgram, const char* shaderCode, GLenum shaderType);
};

