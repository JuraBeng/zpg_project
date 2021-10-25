#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>

class Rectangle {
public:
    Rectangle(float vertices[4][2][4], int size);
    void applyShaders(const char* vertex_shader, const char* fragment_shader);
    void render(int x, int y, int z, float velocity);
private:
    GLuint VAO, VBO;
    GLuint shaderProgram;
};