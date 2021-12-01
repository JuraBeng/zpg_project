#ifndef _WINDOW_H_
#define _WINDOW_H_
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <GLFW/glfw3.h>
class Window
{
public:
	Window(int width, int height);
	~Window();
	int getWidth();
	int getHeight();
	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }
	GLFWwindow *getWindow();
	bool getShouldClose() { return glfwWindowShouldClose(window); }
	bool* getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

private:
	int height, width;
	GLFWwindow *window;
	GLint bufferWidth, bufferHeight;
	bool keys[1024];
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;
	void createCallbacks();
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
};
#endif

