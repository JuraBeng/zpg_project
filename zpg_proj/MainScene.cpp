/*#include "MainScene.h"
#include "sphere.h"
#include "suzi_smooth.h"
#include "tree.h"
#include "bushes.h"
#include "plain.h"
#include "suzi_flat.h"

void MainScene::PrepareScene()
{
	const int sphereNum = 4;
	const int treeNum = 20;
	const int bushNum = treeNum * 4;
	std::vector<glm::vec3> spherePos =
	{
		glm::vec3(-2.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -2.0f),
		glm::vec3(0.0f, 0.0f, 2.0f),
		glm::vec3(2.0f, 0.0f, 0.0f)
	};

	std::vector<glm::vec3> bushPos =
	{
		glm::vec3(-0.2f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, -0.2f),
		glm::vec3(0.0f, 0.0f, 0.2f),
		glm::vec3(0.2f, 0.0f, 0.0f)
	};



	Mesh* objSphere = new Mesh();
	Mesh* objTree = new Mesh();
	Mesh* objBush = new Mesh();
	Mesh* objPlain = new Mesh();
	Mesh* objMonke = new Mesh();

	objSphere->createMesh(sphere, 2880);

	meshList.push_back(objSphere);


	objTree->createMesh((GLfloat*)tree, 92814);
	meshList.push_back(objTree);

	objBush->createMesh((GLfloat*)bushes, 8730);
	meshList.push_back(objBush);

	objPlain->createMesh((GLfloat*)plain, 6);
	meshList.push_back(objPlain);

	objMonke->createMesh((GLfloat*)suziSmooth, 2904);
	meshList.push_back(objMonke);

	int rotate = 0;

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

		for (size_t i = 0; i < spherePos.size() - 1; i++)
		{
			shaderList[0]->useShader();
			transform.applyTransform(spherePos[i], 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f), projection, *shaderList[0], &camera
			);
			shaderList[0]->usePhongShader(camera.getCameraPosition(), glm::vec3(0.0f, 0.0f, 0.0f), 32.0f);

			meshList[0]->render();
			glUseProgram(0);
		}

		shaderList[2]->useShader();
		transform.applyTransform(spherePos[3], 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f), projection, *shaderList[2], &camera
		);

		shaderList[2]->useLambertShader(glm::vec3(0.0f, 0.0f, 0.0f));

		meshList[0]->render();
		glUseProgram(0);

		for (size_t j = 0; j < 5; j++)
		{

			for (size_t i = 0; i < 4; i++)
			{
				shaderList[2]->useShader();
				glm::mat4 model(1.0f);
				glm::mat4 projection = glm::perspective(-80.0f, (GLfloat)this->window->getBufferWidth() / (GLfloat)this->window->getBufferHeight(), 0.1f, 100.0f);

				model = glm::translate(model, glm::vec3(40 + (i * 8), 0.0f, (j * 5)));
				model = glm::rotate(model, 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

				shaderList[2]->setMat4f("model", model);
				shaderList[2]->setMat4f("view", camera.calculateViewMatrix());
				shaderList[2]->setMat4f("projection", projection);
				shaderList[2]->useLambertShader(glm::vec3(40.0f, 40.0f, -60.0f));

				meshList[1]->render();



				for (size_t k = 0; k < 4; k++)
				{
					glm::mat4 model(1.0f);
					glm::mat4 projection = glm::perspective(-80.0f, (GLfloat)this->window->getBufferWidth() / (GLfloat)this->window->getBufferHeight(), 0.1f, 100.0f);
					model = glm::translate(model, glm::vec3(bushPos[k].x + 40 + (i * 8), bushPos[k].y, bushPos[k].z + (j * 5)));
					//model = glm::translate(model, glm::vec3(10 + (i * 8), 0.0f, (j * 5)));
					model = glm::rotate(model, 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f));
					model = glm::scale(model, glm::vec3(1.0f, 1.0f, RandomFloat(1.0f, 1.2f)));

					shaderList[2]->setMat4f("model", model);
					shaderList[2]->setMat4f("view", camera.calculateViewMatrix());
					shaderList[2]->setMat4f("projection", projection);
					shaderList[2]->useLambertShader(glm::vec3(40.0f, 50.0f, -60.0f));
					meshList[2]->render();
				}
			}
			glUseProgram(0);
		}

		shaderList[2]->useShader();
		glm::mat4 model(1.0f);
		glm::mat4 projection = glm::perspective(-80.0f, (GLfloat)this->window->getBufferWidth() / (GLfloat)this->window->getBufferHeight(), 0.1f, 100.0f);

		model = glm::translate(model, glm::vec3(51, 0.00002f, 10.f));
		model = glm::rotate(model, 0 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(18.0f, 1.0f, 25.0f));

		shaderList[2]->setMat4f("model", model);
		shaderList[2]->setMat4f("view", camera.calculateViewMatrix());
		shaderList[2]->setMat4f("projection", projection);
		shaderList[2]->useLambertShader(glm::vec3(40.0f, 50.0f, -60.0f));

		meshList[3]->render();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(51, 2.0f, 10.f));
		model = glm::rotate(model, 180 * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

		shaderList[2]->setMat4f("model", model);
		shaderList[2]->setMat4f("view", camera.calculateViewMatrix());
		shaderList[2]->setMat4f("projection", projection);
		shaderList[2]->useLambertShader(glm::vec3(40.0f, 50.0f, -60.0f));
		meshList[4]->render();

		glUseProgram(0);
		shaderList[1]->useShader();

		model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(40.0f, 50.0f, -60.0f));
		model = glm::rotate(model, rotate * 3.14159265359f / 180.0f, glm::vec3(.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));

		shaderList[1]->setMat4f("model", model);
		shaderList[1]->setMat4f("view", camera.calculateViewMatrix());
		shaderList[1]->setMat4f("projection", projection);

		meshList[0]->render();
		glUseProgram(0);

		glfwSwapBuffers(this->window->getWindow());
		rotate++;
	}
	glfwDestroyWindow(this->window->getWindow());
	glfwTerminate();
	exit(EXIT_SUCCESS);

}*/
