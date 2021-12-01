#ifndef _SCENE_H_
#define _SCENE_H_
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
#include <iostream>
#include "Transform.h"


class Scene
{
public:
	Scene();
	~Scene();
	virtual void PrepareScene() = 0;
protected:
	Window* window;
	std::vector<Mesh*> meshList;
	std::vector<Shader*> shaderList;
	Camera camera;
	Transform transform;
	void createShader(const char* vShaderPath, const char* fShaderPath);
	const char* fShader;
	const char* vShader;
	GLfloat deltaTime;
	GLfloat lastTime;
	glm::mat4 projection;
	void calculateDeltaTime();
	float RandomFloat(float min, float max);
};
#endif

