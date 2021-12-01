#ifndef _ENGINE_H_
#define _ENGINE_H_
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <math.h>
#include <vector>
#include "Objects/Mesh.h"
#include "Shaders/Shader.h"
#include "Camera.h"
//#include "MainScene.h"
#include "TestScene.h"
#include <iostream>
#include "Transform.h"


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
	Engine() {
		scene = new TestScene();
	}
	static Engine sInstance;
	TestScene* scene;
};
#endif