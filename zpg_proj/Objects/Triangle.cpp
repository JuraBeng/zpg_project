#include "Triangle.h"

float rotate_triangle = 0;

Triangle::Triangle(float vertices[4][2][4], int size)
{
	this->shaderProgram = 0;

	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO);	  //generate the VAO
	glBindVertexArray(VAO);		  //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(b[0]), (GLvoid*)0);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(b[0]), (GLvoid*)(4 * sizeof(GL_FLOAT)));
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(4 * sizeof(GL_FLOAT)));

	glBindVertexArray(VAO);
}

void Triangle::applyShaders(const char* vertex_shader, const char* fragment_shader)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	// global shader program
	this->shaderProgram = shaderProgram;

	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		throw(1);
	}
	glUseProgram(shaderProgram);
}

void Triangle::render(int x, int y, int z, float velocity)
{

	glm::mat4 M = glm::mat4(1.0f);

	rotate_triangle += velocity;
	M = glm::rotate(M, rotate_triangle, glm::vec3(x, y, z));

	// uniformni promena
	GLint idModelTransform = glGetUniformLocation(this->shaderProgram, "modelMatrix");
	glUseProgram(this->shaderProgram);
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
