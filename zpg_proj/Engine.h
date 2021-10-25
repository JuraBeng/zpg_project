#pragma once
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
#include "Objects/Rectangle.h"
#include "Objects/Triangle.h"
#include "Objects/Triangle1.h"
#include "Objects/Triangle2.h"
#include "Objects/Triangle3.h"

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <math.h>
#include <vector>
#include "Objects/Mesh.h"
#include "Shaders/Shader.h"

class Engine
{
public:
	Engine(const Engine&) = delete;
	static Engine& Get()
	{
		return s_Instance;
	}
	static void Render() { return Get().IRender(); };
private:
	void IRender();
	Engine(){
		this->window = new Window(1280, 720);
	}
	static Engine s_Instance;
	Window* window;
	std::vector<Mesh*> meshList;
	std::vector<Shader> shaderList;
	void CreateShader();
	const char* fShader;
	const char* vShader;
};

