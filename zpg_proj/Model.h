#ifndef _MODEL_H_
#define _MODEL_H_
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Objects/Mesh.h"
#include "Texture.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Model
{
public:
	Model(const char* path, const char* texture, glm::vec3 position);

	void loadModel(const std::string& fileName);
	void renderModel();
	~Model();
	glm::vec3 getPosition();

private:
	GLuint VBO, VAO;
	Texture texture;
	int vertexCount;
	glm::vec3 position;
};
#endif

