#include "../include/ObjectPart.h"
#include <glm/ext.hpp>

namespace Swift {
	ObjectPart::ObjectPart() {
		origin = glm::vec3(0.0f);
	}
	ObjectPart::~ObjectPart() {}

	GLuint ObjectPart::getVAO() {
		return VAO;
	}

	GLuint ObjectPart::getVBO() {
		return VBO;
	}

	GLuint ObjectPart::getNormalBuffer() {
		return normalbuffer;
	}

	GLuint ObjectPart::getUVbuffer() {
		return uvbuffer;
	}

	void ObjectPart::setup() {
		origin = glm::vec3(0.0f);
		//printf("origin = %f %f %f\n", origin.x, origin.y, origin.z);
		Model = glm::translate(glm::mat4(1.0f), origin);
		visible = true;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
	}

	void ObjectPart::destroy() {
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &normalbuffer);
		glDeleteBuffers(1, &uvbuffer);
		glDeleteVertexArrays(1, &VAO);

		vertices.clear();
		normals.clear();
		uvs.clear();
	}

	glm::mat4 ObjectPart::getModelMatrix() {
		return Model;
	}

	void ObjectPart::reload() {
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);

		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_DYNAMIC_DRAW);

		glGenBuffers(1, &normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_DYNAMIC_DRAW);
	}

	bool ObjectPart::isVisible() {
		return visible;
	}

	void ObjectPart::hide() {
		visible = false;
	}

	void ObjectPart::show() {
		visible = true;
	}

	std::string ObjectPart::getAlias() {
		return alias;
	}

	void ObjectPart::setAlias(std::string _alias) {
		alias = _alias;
	}

	MaterialPtr ObjectPart::getMaterial() {
		return mtl;
	}

	void ObjectPart::setMaterial(MaterialPtr _mtl) {
		mtl = _mtl; // tu siê wywala z access violation
	}

	glm::vec3 ObjectPart::getOrigin() {
		return origin;
	}

	unsigned int ObjectPart::getVertexCount() {
		return vertices.size();
	}
	
	void ObjectPart::rotate(const glm::vec3& axis, float angle) {
		Model = glm::rotate(Model, angle, axis);
	}

	void ObjectPart::move(const glm::vec3& newPos) {
		glm::vec4 pos = Model * glm::vec4(origin,1);
		glm::vec3 curPos(pos.x, pos.y, pos.z);

		Model = glm::translate(Model, glm::vec3(newPos.x - curPos.x, newPos.y - curPos.y, newPos.z - curPos.z));
	}

	void ObjectPart::scale(const glm::vec3& factor) {
		Model = glm::scale(Model, factor);
	}
}