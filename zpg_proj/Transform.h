#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
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
#include <iostream>
#include <vector>
#include "Shaders/Shader.h"
#include "Camera.h"

class Transform
{

public:
	Transform();
	~Transform();
	void applyTransform(glm::vec3 position, float rotateAngle, glm::vec3 rotateAxis, glm::vec3 scale, glm::mat4 projection, Shader &shader, Camera *camera);


private:
	glm::mat4 model;


};
#endif

