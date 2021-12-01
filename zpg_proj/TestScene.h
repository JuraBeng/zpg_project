#ifndef __TESTSCENE_H__
#define __TESTSCENE_H__
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
#include "Scene.h"
#include "Transform.h"
#include "Texture.h"
#include "Model.h"
#include "Skybox.h"

class TestScene : public Scene
{
public:
	void PrepareScene();
};
#endif

