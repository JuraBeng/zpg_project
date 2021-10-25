#include "Triangle2.h"

Triangle2::Triangle2()
{
	vShader = "													\n\
		#version 330											\n\
																\n\
		layout (location = 0) in vec3 pos;						\n\
																\n\
		uniform mat4 model;										\n\
		uniform mat4 projection;								\n\
																\n\
		out vec4 vCol;											\n\
																\n\
		void main()												\n\
		{														\n\
			gl_Position = projection * model * vec4(pos, 1.0);	\n\
			vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);			\n\
		}";

	fShader = "												\n\
		#version 330										\n\
															\n\
		in vec4 vCol;										\n\
															\n\
		out vec4 color;										\n\
															\n\
		void main()											\n\
		{													\n\
			color = vCol;									\n\
		}";
	CreateObjects();
	CompileShader();
}

void Triangle2::CompileShader()
{
	shaderProgram = glCreateProgram();
	if (!shaderProgram)
	{
		printf("Error creating shader program\n");
		return;
	}

	AddShader(shaderProgram, GL_VERTEX_SHADER, vShader);
	AddShader(shaderProgram, GL_FRAGMENT_SHADER, fShader);
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
		printf("Error linking program: %s", eLog);
		return;
	}
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
		printf("Error validating program: %s", eLog);
		return;
	}
	uniformModel = glGetUniformLocation(shaderProgram, "model");
	uniformProjection = glGetUniformLocation(shaderProgram, "projection");
}

void Triangle2::AddShader(GLuint shaderProgram, GLenum shaderType, const char* shaderCode)
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
		printf("Error compiling the %d shader: %s", shaderType, eLog);
		return;
	}
	glAttachShader(shaderProgram, shader);
	return;
}

void Triangle2::CreateObjects()
{
	unsigned int indices[] =
	{
		/*0, 3, 1,
		2, 3, 1,
		0, 3, 2,
		0, 2, 1*/
		0, 4, 2,
		2, 4, 3,
		3, 1, 4,
		1, 4, 0,
		0, 3, 1,
		2, 0, 3
	};

	GLfloat vertices[] = {
		/*-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f*/
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Triangle2::Render()
{
	if (!direction)
	{
		triOffset += triIncrement;
	}
	else
	{
		triOffset -= triIncrement;
	}
	if (abs(triOffset) >= triMaxOffset)
	{
		direction = !direction;
	}
	if (i >= 360)
	{
		i = 0;
	}
	if (sizeDirection)
	{
		curSize += 0.01f;;
	}
	else
	{
		curSize -= 0.01f;
	}
	if (curSize >= maxSize || curSize <= minSize)
	{
		sizeDirection = !sizeDirection;
	}
	CompileShader();
	glUseProgram(shaderProgram);
	glm::mat4 model(1.0f);
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)800/(GLfloat)600, 0.1f, 100.0f);
	model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.5f));
	//model = glm::rotate(model, i * toRadians, glm::vec3(.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	i+=1;
}
