#include "TestScene.h"
#include "sphere.h"
#include "suzi_smooth.h"
#include "tree.h"
#include "bushes.h"
#include "plain.h"
#include "suzi_flat.h"

void TestScene::PrepareScene()
{
	Model zombie = Model("zombie.obj", "zombie.png", glm::vec3(-13.0f, 0.0f, 5.f));
	Model tree = Model("tree.obj", "./Textures/tree.png", glm::vec3(10.0f, 0.0f, 5.f));
	Model tree1 = Model("tree.obj", "./Textures/tree.png", glm::vec3(-10.0f, 0.0f, 5.f));
	Model house = Model("model.obj", "model.png", glm::vec3(0.0f, 0.0f, 0.0f));
	Model teren = Model("teren.obj", "./Textures/grass.png", glm::vec3(0.0f, 0.0f, 0.0f));

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");
	Skybox skybox;
	skybox = Skybox(skyboxFaces);
	/*Model plane;
	plane = Model();
	plane.loadModel("teren.obj");*/
	/*Model house;
	house = Model();
	house.loadModel("house.obj");*/



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
				skybox.DrawSkybox(camera.calculateViewMatrix(), projection);


		shaderList[0]->useShader();
		transform.applyTransform(zombie.getPosition(), 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f), projection, *shaderList[0], &camera
		);
		shaderList[0]->usePhongShader(camera.getCameraPosition(), glm::vec3(20.0f, 20.0f, 40.0f), 32.0f);

		zombie.renderModel();

		transform.applyTransform(tree.getPosition(), 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f), projection, *shaderList[0], &camera
		);

		tree.renderModel();

		transform.applyTransform(tree1.getPosition(), 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.5f, 1.0f), projection, *shaderList[0], &camera
		);

		tree1.renderModel();

		transform.applyTransform(house.getPosition(), 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f), projection, *shaderList[0], &camera
		);

		house.renderModel();

		transform.applyTransform(teren.getPosition(), 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f),
			glm::vec3(.8f, 0.8f, .8f), projection, *shaderList[0], &camera
		);

		teren.renderModel();
		glUseProgram(0);



		/*shaderList[0]->useShader();
		transform.applyTransform(glm::vec3(-10.0f, 0.0f, 5.f), 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f),
			glm::vec3(20.0f, 0.5f, 20.0f), projection, *shaderList[0], &camera
		);
		shaderList[0]->usePhongShader(camera.getCameraPosition(), glm::vec3(0.0f, 0.0f, 0.0f), 32.0f);

		plane.renderModel();
		glUseProgram(0);*/

		/*shaderList[0]->useShader();
		transform.applyTransform(glm::vec3(5.0f, 0.0f, 5.f), 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f), projection, *shaderList[0], &camera
		);
		shaderList[0]->usePhongShader(camera.getCameraPosition(), glm::vec3(0.0f, 0.0f, 0.0f), 32.0f);

		tree.renderModel();
		glUseProgram(0);*/

		/*shaderList[0]->useShader();
		transform.applyTransform(glm::vec3(15.0f, 0.0f, 0.f), 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f), projection, *shaderList[0], &camera
		);
		shaderList[0]->usePhongShader(camera.getCameraPosition(), glm::vec3(0.0f, 0.0f, 0.0f), 32.0f);

		house.renderModel();
		glUseProgram(0);*/


		glfwSwapBuffers(this->window->getWindow());
	}
	glfwDestroyWindow(this->window->getWindow());
	glfwTerminate();
	exit(EXIT_SUCCESS);

}
