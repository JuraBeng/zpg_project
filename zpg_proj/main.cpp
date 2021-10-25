#define _USE_MATH_DEFINES
//Remake into objects
//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Shaders/FragmentShader.h"
#include "Shaders/VertexShader.h"
#include "Objects/Rectangle.h"
#include "Objects/Triangle.h"
#include "Objects/Triangle1.h"
#include "Objects/Triangle2.h"

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <math.h>

int rotate = 1;
float rotateX = 1.f;
float rotateY = 0.f;
float rotateZ = 0.f;


static void error_callback(int error, const char* description) { fputs(description, stderr); }

/*static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		rotate *= -1;
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		rotate *= -1;
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		rotateX = 1.f;
		rotateY = 0.f;
		rotateZ = 0.f;
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		rotateX = 0.f;
		rotateY = 0.f;
		rotateZ = 1.f;
	}
	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		rotateX = 0.f;
		rotateY = 1.f;
		rotateZ = 0.f;
	}
}*/

/*static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}*/



//GLM test

// Projection matrix : 45deg Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
/*glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);*/

//Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader, uniformModel;
bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 0.7f;
float triIncrement = 0.008f;
const float toRadians = M_PI / 180.0f;

// vertex shader
static const char* vShader = "						\n\
#version 330										\n\
													\n\
layout (location = 0) in vec3 pos;					\n\
													\n\
uniform mat4 model;									\n\
													\n\
void main()											\n\
{													\n\
	gl_Position = model * vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);	\n\
}";

// fragment shader
static const char* fShader = "						\n\
#version 330										\n\
													\n\
out vec4 color;										\n\
													\n\
void main()											\n\
{													\n\
	color = vec4(1.0, 1.0, 0.0, 1.0);	\n\
}";

void CreateTriangle()
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
	// binds our vertex array with VAO
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void AddShader(GLuint program, const char* shaderCode, GLenum shaderType)
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
	glAttachShader(program, shader);
	return;
}

void CompileShaders() {
	shader = glCreateProgram();
	if (!shader)
	{
		printf("Error creating shader program\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}
	uniformModel = glGetUniformLocation(shader, "model");
}

int main(void)
{
	// Initialise GLFW
	// Throw it in if to see if it fails
	if (!glfwInit())
	{
		printf("GLFW Initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Window properties
	// OpenGL version
	// Sets major version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// Sets minor version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Profile is saying how opengl is gonna treat the code
	// Core profile means it wont allow older versions and deprecated code
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Window creation
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "TEST ZPG", NULL, NULL);

	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get buffer size info, meaning size of window viewport
	// where things get drawn to
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	// Lets GLEW know that everything we draw should be drawn into our window
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initianlisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	//CreateTriangle();
	//CompileShaders();

	// loop until window closed
	int i = 0;
	Triangle2* t2 = new Triangle2();
	//t2->CreateObjects();
	//t2->CompileShader();
	while (!glfwWindowShouldClose(mainWindow))
	{
		// get and handle user input events
		glfwPollEvents();
		/*if (direction)
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}
		if (abs(triOffset) >= triMaxoffset)
		{
			direction = !direction;
		}*/

		// clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// clears all colors
		glClear(GL_COLOR_BUFFER_BIT);
		t2->Render();


		//glUseProgram(shader);
		//glm::mat4 model(1.0f);
		//model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
		//model = glm::rotate(model, i * toRadians, glm::vec3(1.0f, 0.4f, 0.9f));
		//glUniform1f(uniformModel, triOffset);
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);
		//glUseProgram(0);



		glfwSwapBuffers(mainWindow);
		//i++;
	}
	/*GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	float vertices[4][2][4] = {
	{ { -.1f, .7f, .3f, 1 }, { 1, 0, 0, 1 } },
	{ { -.1f, .0f, .3f, 1 }, { 0, 0, 1, 1 } },
	{ { -.7f, .0f, .3f, 1 }, { 0, 1, 0, 1 } },
	{ { .7f, -.0f, .3f, 1 }, { 0, 1, 0, 1 } },
	};
	float vertices2[4][2][4] = {
		{ { .1f, .7f, .3f, 1 }, { 1, 1, 0, 1 } },
		{ { .1f, .0f, .3f, 1 }, { 1, 0, 1, 1 } },
		{ { .7f, .0f, .3f, 1 }, { 0, 1, 1, 1 } },
		{ { .7f, .0f, .3f, 1 }, { 0, 0, 1, 1 } },
	};
	float vertices3[4][2][4] = {
	{ { .1f, .7f, .3f, 1 }, { 0, 1, 0, 1 } },
	{ { .1f, .0f, .3f, 1 }, { 1, 0, 1, 1 } },
	{ { .7f, .0f, .3f, 1 }, { 0, 1, 1, 1 } },
	{ { .7f, .0f, .3f, 1 }, { 1, 1, 1, 1 } },
	};

	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Triangle* t = new Triangle(vertices, sizeof(vertices));
		t->applyShaders(vertex_shader, fragment_shader);
		t->render(1, 1, 1, 0.01f);

		Triangle* t2 = new Triangle(vertices2, sizeof(vertices2));
		t2->applyShaders(vertex_shader, fragment_shader);
		t2->render(1, 0, 0, 0.01f);

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we�ve been drawing onto the display
		glfwSwapBuffers(window);
	}*/

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}