#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
}

void Shader::createFromFiles(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexString = readFile(vertexPath);
	std::string fragmentString = readFile(fragmentPath);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("Failed to read %s! File doesnt exist.", fileLocation);
		return "";
	}
	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}


void Shader::useShader()
{
	glUseProgram(shaderID);
}

void Shader::usePhongShader(glm::vec3 eyePos, glm::vec3 lightPos, GLfloat shininess)
{
		setVec3f("light.position", lightPos);
		setVec3f("viewPos", eyePos);
		setVec3f("light.ambient", glm::vec3(1.f, 1.0f, 1.0f));
		setVec3f("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		setVec3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		setVec3f("material.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		setVec3f("material.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		setVec3f("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		set1f("material.shininess", shininess);
}

void Shader::useLambertShader(glm::vec3 lightPos)
{
	setVec3f("light.position", lightPos);
	setVec3f("objectColor", glm::vec3(0.5f, 0.5f, 0.1f));
	setVec3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
}

void Shader::clearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
	}
}

void Shader::setMat4f(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3f(const std::string& name, const glm::vec3 vec)
{
	glUniform3f(glGetUniformLocation(shaderID, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::set1f(const std::string& name, const GLfloat val)
{
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), val);
}

Shader::~Shader()
{
	clearShader();
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();
	if (!shaderID)
	{
		printf("Error creating shader program\n");
		return;
	}
	
	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: %s", eLog);
		return;
	}
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: %s", eLog);
		return;
	}
}


void Shader::addShader(GLuint shaderProgram, const char* shaderCode, GLenum shaderType)
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
