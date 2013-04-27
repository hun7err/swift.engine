#include "../include/Object.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Swift {
	GLfloat* Object::getVertices() {
		return &(vertices[0].x);
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

	void Object::scale(const glm::vec3& factor) {
		Model = glm::scale(Model, factor);
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

	void Object::hide() {
		visible = false;
	}

	void Object::show() {
		visible = true;
	}

	bool Object::isVisible() {
		return visible;
	}

	GLuint Object::getVBO() {
		return VBO;
	}


	GLuint Object::getNormalBuffer() {
		return normalbuffer;
	}

	void Object::setup() {
		Model = glm::translate(glm::mat4(1.0f), origin);
		visible = true;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		
		glGenBuffers(1, &normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_DYNAMIC_DRAW);
		reload();
	}

	void Object::reload() {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);
	
	}

	void Object::destroy() {
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &normalbuffer);
		glDeleteVertexArrays(1, &VAO);

		vertices.clear();
	}

	Object::Object() {
		setup();
	}
	Object::~Object() {
		destroy();
	}
}