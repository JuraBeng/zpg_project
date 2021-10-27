#pragma once
#define STB_IMAGE_IMPLEMENTATION
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
#include "Window.h"
//#include "sphere.h"

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <math.h>
#include <vector>
#include "Objects/Mesh.h"
#include "Shaders/Shader.h"
#include "Camera.h"


class Engine
{
public:
	Engine(const Engine&) = delete;
	static Engine& get()
	{
		return sInstance;
	}
	static void render() { return get().iRender(); };
private:
	void iRender();
	Engine(){
		lastTime = 0.0f;
		deltaTime = 0.0f;
		vShader = "";
		fShader = "";
		this->window = new Window(1280, 720);
	}
	static Engine sInstance;
	Window* window;
	std::vector<Mesh*> meshList;
	std::vector<Shader> shaderList;
	Camera camera;
	void createShader();
	const char* fShader;
	const char* vShader;
	GLfloat deltaTime;
	GLfloat lastTime;
	void calculateDeltaTime();
};

