#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader();
	void createFromFiles(const char* vertexPath, const char* fragmentPath);
	std::string readFile(const char* fileLocation);
	void createFromString(const char* vertexCode, const char* fragmentCode);
	void useShader();
	void usePhongShader(glm::vec3 eyePos, glm::vec3 lightPos, GLfloat shininess);
	void useLambertShader(glm::vec3 lightPos);
	void clearShader();
	void setMat4f(const std::string& name, const glm::mat4& mat);
	void setVec3f(const std::string& name, const glm::vec3 vec);
	void set1f(const std::string& name, const GLfloat val);
	~Shader();

private:
	GLuint shaderID;
	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint shaderProgram, const char* shaderCode, GLenum shaderType);
};


