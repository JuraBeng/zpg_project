#pragma once
#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	void createMesh(GLfloat *vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void createMesh(GLfloat* vertices, unsigned int numOfVertices);
	void render();
	void clearMesh();
	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
	GLsizei vertexCount;
	GLsizei bufferSize;
};
