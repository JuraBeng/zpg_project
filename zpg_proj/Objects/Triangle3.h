#pragma once
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <cmath>
#include <stdlib.h>

class Triangle3 {
public: 
	Triangle3();
	void CompileShader();
	void AddShader(GLuint shaderProgram, const char* theCode, GLenum shaderType);
	void CreateObjects();
	void Render();
private:
	GLuint VAO = 0, VBO = 0;
	GLuint shaderProgram, uniformModel;
	bool direction = false;
	int i = 0;
	float triIncrement = 0.008f;
	float triOffset = 0.0f;
	float triMaxOffset = 0.7f;
	const char* vShader;
	const char* fShader;
	const float toRadians = 3.14159265358979323846f / 180.0f;
	bool sizeDirection = true;
	float curSize = 0.4f;
	float maxSize = 0.8f;
	float minSize = 0.1f;
};