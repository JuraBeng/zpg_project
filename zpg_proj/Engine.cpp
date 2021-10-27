#include "Engine.h"
#include "sphere.h"
#include "plain.h"
#include "suzi_smooth.h"
#include "tree.h"
Engine Engine::sInstance;

void Engine::iRender()
{
	GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0;
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.8f, 0.3f);
	deltaTime = 0.0f;
	lastTime = 0.0f;
	unsigned int indices[] =
	{
		/*0, 3, 1,
		2, 3, 1,
		0, 3, 2,
		0, 2, 1*/
		0, 4, 2,
		2, 4, 3,
		3, 1, 4,
		1, 4, 0,
		0, 3, 1,
		2, 0, 3
	};

	GLfloat vertices[] = {
		/*-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f*/
		-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	GLfloat cubeVertices[] = {
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 0.2f, 0.5f, 1.0f,
		1.0f, 1.0f, -1.0f, 0.3f, 0.1f, 0.5f,
		-1.0, 1.0f, -1.0f, 0.4f, 1.0f, 0.5f
	};

	unsigned int cubeIndices[]{
		0, 2, 1,
		0, 3, 2,
		3, 6, 2,
		3, 6, 5,
		5, 7, 6,
		5, 7, 4,
		0, 7, 1,
		0, 7, 4,
		3, 4, 0,
		3, 4, 5,
		2, 7, 1,
		2, 7, 6,
	};

	createShader();

	Mesh* obj = new Mesh();
	Mesh* obj1 = new Mesh();
	Mesh* obj2 = new Mesh();
	Mesh* obj3 = new Mesh();
	Mesh* obj4 = new Mesh();
	Mesh* obj5 = new Mesh();
	obj->createMesh(vertices, indices, 5, 18);
	obj1->createMesh(vertices, indices, 5, 18);
	obj2->createMesh(cubeVertices, cubeIndices, 8, 36);
	obj3->createMesh(sphere, 2880);
	obj4->createMesh(suziSmooth, 2904);
	obj5->createMesh(tree, 92814);

	meshList.push_back(obj);
	meshList.push_back(obj1);
	meshList.push_back(obj2);
	meshList.push_back(obj3);
	meshList.push_back(obj4);
	meshList.push_back(obj5);
	int j = 0;
	while (!this->window->getShouldClose())
	{
		calculateDeltaTime();
		// get and handle user input events
		glfwPollEvents();
		camera.keyControl(window->getKeys(), deltaTime);
		camera.mouseControl(window->getXChange(), window->getYChange());

		glClearColor(.0f, .0f, .0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		for (size_t i = 0; i < meshList.size(); i++)
		{
			shaderList[0].useShader();
			glm::mat4 model(1.0f);
			glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->window->getBufferWidth() / (GLfloat)this->window->getBufferHeight(), 0.1f, 100.0f);

			model = glm::translate(model, glm::vec3((GLfloat)i*2-4.5f, 0.0f, -2.5f));
			model = glm::rotate(model, j * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, .4f));

			shaderList[0].setMat4f("model", model);
			shaderList[0].setMat4f("view", camera.calculateViewMatrix());
			shaderList[0].setMat4f("projection", projection);

			meshList[i]->render();
			glUseProgram(0);
		}
		
		/*shaderList[0].UseShader();

		glm::mat4 model(1.0f);
		glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->window->GetBufferWidth() / (GLfloat)this->window->GetBufferHeight(), 0.1f, 100.0f);
		
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::rotate(model,  i * 3.14159265359f/180.0f, glm::vec3(.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, .4f));
		
		shaderList[0].setMat4f("model", model);
		shaderList[0].setMat4f("view", camera.calculateViewMatrix());
		shaderList[0].setMat4f("projection", projection);

		obj->RenderIndexed();*/
		// a poradi tady
		glfwSwapBuffers(this->window->getWindow());
		j++;
	}
	glfwDestroyWindow(this->window->getWindow());
	glfwTerminate();
	exit(EXIT_SUCCESS);

}

void Engine::createShader()
{
	Shader* shader = new Shader();
	shader->createFromFiles("Shaders/vertex_shader.shader", "Shaders/fragment_shader.shader");
	shaderList.push_back(*shader);
}

void Engine::calculateDeltaTime()
{
	GLfloat now = (GLfloat)glfwGetTime();
	deltaTime = now - lastTime;
	if (deltaTime < 0.0167f)
		deltaTime = 0.0167f;
	else if (deltaTime > 0.1f)
		deltaTime = 0.1f;
	lastTime = now;
}
