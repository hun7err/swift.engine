#include "../include/Object.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Swift {
	GLfloat* Object::getVertices() {
		return &vertices[0];
	}

	Material* Object::getMaterial() {
		return mtl;
	}

	glm::mat4 Object::getModelMatrix() {
		return Model;
	}

	unsigned int Object::getVertexCount() {
		return vertices.size();
	}

	void Object::setMaterial(Material* _mtl) {
		mtl = _mtl;
	}

	void Object::rotate(const glm::vec3& axis, float angle) {
		Model = glm::rotate(Model, angle, axis);
	}

	void Object::move(const glm::vec3& newPos) {
		glm::vec3 curPos = getPosition();
		Model = glm::translate(Model, glm::vec3(newPos.x - curPos.x, newPos.y - curPos.y, newPos.z - curPos.z));
	}

	glm::vec3 Object::getPosition() {
		glm::vec4 pos = Model * glm::vec4(origin,1);
		return glm::vec3(pos.x, pos.y, pos.z);
	}

	glm::vec3 Object::getOrigin() {
		return origin;
	}

	void Object::setName(std::string _name) {
		name = _name;
	}

	std::string Object::getName() {
		return name;
	}

	GLuint Object::getVAO() {
		return VAO;
	}

	GLuint Object::getVBO() {
		return VBO;
	}

	void Object::setup() {
		Model = glm::mat4(1.0f);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	}

	void Object::destroy() {
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}

	Object::Object() {
		setup();
	}
	Object::~Object() {
		destroy();
	}
}