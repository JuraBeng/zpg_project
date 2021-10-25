#include "Triangle1.h"

Triangle1::Triangle1()
{
	vShader = "													\n\
		#version 330											\n\
																\n\
		layout (location = 0) in vec3 pos;						\n\
																\n\
		void main()												\n\
		{														\n\
				gl_Position = vec4(0.4*pos.x, 0.4*pos.y, pos.z, 1.0);	\n\
		}";

// fragment shader
	fShader = "									\n\
		#version 330							\n\
												\n\
		out vec4 color;							\n\
												\n\
		void main()								\n\
		{										\n\
			color = vec4(1.0, 0.0, 0.0, 1.0);	\n\
		}";
}

void Triangle1::CompileShader()
{
	shaderProgram = glCreateProgram();
	if (!shaderProgram)
	{
		printf("Error creating shader program\n");
		return;
	}

	AddShader(shaderProgram, vShader, GL_VERTEX_SHADER);
	AddShader(shaderProgram, fShader, GL_FRAGMENT_SHADER);
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}
}


void Triangle1::AddShader(GLuint shaderProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(shader, 1, theCode, codeLength);
	glCompileShader(shader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}
	glAttachShader(shaderProgram, shader);
	return;
}

void Triangle1::CreateObjects()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	// it defines space in memory for your 1 vertex array
	// and gives it id
	// if you wanna access that point of memory, you have to pass the id 
	// that has been stored in VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Triangle1::Render()
{
	glBindVertexArray(VAO);
	CompileShader();
	glUseProgram(shaderProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glUseProgram(0);
}
