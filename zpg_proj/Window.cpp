#include "Window.h"

Window::Window(int width, int height)
{
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	this->height = height;
	this->width = width;
	if (!glfwInit())
	{
		printf("GLFW Initialisation failed!");
		glfwTerminate();
		return;
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
	window = glfwCreateWindow(this->width, this->height, "TEST ZPG", NULL, NULL);

	if (!window)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return;
	}

	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	// Lets GLEW know that everything we draw should be drawn into our window
	glfwMakeContextCurrent(window);

	createCallbacks();

	glewExperimental = GL_TRUE;


	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}
	glEnable(GL_DEPTH_TEST);
	// setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	
	glfwSetWindowUserPointer(window, this);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

int Window::GetWidth()
{
	return this->width;
}

int Window::GetHeight()
{
	return this->height;
}

GLFWwindow* Window::GetWindow()
{
	return this->window;
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(window, handleKeys);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			printf("pressed %d\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			printf("released %d\n", key);
		}
	}
}
