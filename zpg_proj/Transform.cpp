#include "Transform.h"

Transform::Transform()
{
	model = glm::mat4(1.0f);
}

Transform::~Transform()
{
}

void Transform::applyTransform(glm::vec3 position, float rotateAngle, glm::vec3 rotateAxis, glm::vec3 scale, glm::mat4 projection, Shader &shader, Camera *camera)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, rotateAngle, rotateAxis);
	model = glm::scale(model, scale);

	shader.setMat4f("model", model);
	shader.setMat4f("view", camera->calculateViewMatrix());
	shader.setMat4f("projection", projection);
}

