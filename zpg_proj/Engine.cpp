#include "Engine.h"
Engine Engine::s_Instance;

void Engine::IRender()
{
	GLuint uniformModel = 0, uniformProjection = 0;

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
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};
	CreateShader();

	Mesh* obj = new Mesh();
	obj->CreateMesh(vertices, indices, 15, 18);
	meshList.push_back(obj);
	int i = 0;
	while (!this->window->getShouldClose())
	{
		// get and handle user input events
		glfwPollEvents();

		glClearColor(.0f, .0f, .0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		glm::mat4 model(1.0f);
		glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->window->GetBufferWidth() / (GLfloat)this->window->GetBufferHeight(), 0.1f, 100.0f);
		model = glm::translate(model, glm::vec3(0.7f, 0.0f, -2.5f));
		model = glm::rotate(model,  i * 3.14159265359f/180.0f, glm::vec3(.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, .4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		obj->Render();



		glUseProgram(0);
		glfwSwapBuffers(this->window->GetWindow());
		i++;
	}

	glfwDestroyWindow(this->window->GetWindow());
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Engine::CreateShader()
{
	Shader* shader = new Shader();
	shader->CreateFromFiles("Shaders/vertex_shader.shader", "Shaders/fragment_shader.shader");
	shaderList.push_back(*shader);
}
