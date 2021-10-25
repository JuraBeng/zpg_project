#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>
#include <string.h>

class Triangle1 {
public:
    Triangle1();
    void CompileShader();
    void AddShader(GLuint shaderProgram, const char* shaderCode, GLenum shaderType);
    void CreateObjects();
    void Render();
private:
    GLuint VAO=0, VBO=0;
    GLuint shaderProgram;
    const char* vShader;
    const char* fShader;
};
