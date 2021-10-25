#include "Triangle3.h"

Triangle3::Triangle3()
{
	vShader =
		"#version 330\n"
		"layout (location = 0) in vec3 pos;"
		"uniform mat4 model;"
		"void main()"
		"{"
		"	gl_Position = model * vec4(0.4*pos.x, 0.4*pos.y, pos.z, 1.0f);"
		"}";

	fShader = 
		"#version 330\n"
		"out vec4 color;"
		"void main()"
		"{"
		"	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);"
		"}";
	CreateObjects();
	CompileShader();
}

void Triangle3::CompileShader()
{
	shaderProgram = glCreateProgram();
	if (!shaderProgram)
	{
		printf("Error creating shader program!\n");
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
		printf("Error linking program: %s\n", eLog);
		return;
	}
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
		printf("Error validating program: %s\n", eLog);
		return;
	}
	uniformModel = glGetUniformLocation(shaderProgram, "model");

}

void Triangle3::AddShader(GLuint shaderProgram, const char* theCode, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	const GLchar* shaderCode[1];
	shaderCode[0] = theCode;
	GLint codeLength[1];
	codeLength[0] = strlen(theCode);

	glShaderSource(shader, 1, shaderCode, codeLength);
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

void Triangle3::CreateObjects()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Triangle3::Render()
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
	CompileShader();
	glUseProgram(shaderProgram);
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
	model = glm::rotate(model, i * toRadians, glm::vec3(1.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glUseProgram(0);
	i++;
}
