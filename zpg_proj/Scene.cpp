#include "Scene.h"

float Scene::RandomFloat(float min, float max)
{
	// this  function assumes max > min, you may want 
	// more robust error checking for a non-debug build
	assert(max > min);
	float random = ((float)rand()) / (float)RAND_MAX;

	// generate (in your case) a float between 0 and (4.5-.78)
	// then add .78, giving you a float between .78 and 4.5
	float range = max - min;
	return (random * range) + min;
}

void Scene::createShader(const char* vShaderPath, const char* fShaderPath)
{
	Shader* shader = new Shader();
	shader->createFromFiles(vShaderPath, fShaderPath);
	shaderList.push_back(shader);
}

void Scene::calculateDeltaTime()
{
	GLfloat now = (GLfloat)glfwGetTime();
	deltaTime = now - lastTime;
	if (deltaTime < 0.0167f)
		deltaTime = 0.0167f;
	else if (deltaTime > 0.1f)
		deltaTime = 0.1f;
	lastTime = now;
}

Scene::Scene()
{
	lastTime = 0.0f;
	deltaTime = 0.0f;
	vShader = "";
	fShader = "";
	this->window = new Window(1280, 720);
	transform = Transform();

	createShader("Shaders/vertex_phong.shader", "Shaders/frag_phong.shader");
	createShader("Shaders/vertex_shader.shader", "Shaders/fragment_shader.shader");
	createShader("Shaders/vertex_lambert.shader", "Shaders/frag_lambert.shader");
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.8f, 0.3f);
	projection = glm::perspective(glm::radians(60.0f), (GLfloat)this->window->getBufferWidth() / (GLfloat)this->window->getBufferHeight(), 0.1f, 100.0f);
}

Scene::~Scene()
{
}

