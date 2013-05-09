#include "../include/Object.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Swift {
	/*glm::vec3 Object::getPosition() {
		glm::vec4 pos = Model * glm::vec4(origin,1);
		return glm::vec3(pos.x, pos.y, pos.z);
	}*/
	unsigned int Object::getVertexCount() {
		unsigned int ret = 0;
		for(int i = 0; i < parts.size(); i++)
			ret += parts[i].getVertexCount();

		return ret;
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

	unsigned int Object::getPartCount() {
		return parts.size();
	}

	ObjectPart& Object::getPart(std::string alias) {
		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			if( (*it).getAlias() == alias)
				return *it;
	}

	void Object::hide() {
		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			(*it).hide();
	}

	void Object::show() {
		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			(*it).show();
	}

	ObjectPart& Object::getPartAt(unsigned int pos) {
		return parts[pos];
	}

	void Object::setMaterial(MaterialPtr _mtl) {
		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			(*it).setMaterial(_mtl);
	}

	void Object::rotate(const glm::vec3& axis, float angle) {
		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			(*it).rotate(axis, angle);
	}
	void Object::move(const glm::vec3& newPos) {
		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			(*it).move(newPos);
	}
	void Object::scale(const glm::vec3& factor){
		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			(*it).scale(factor);
	}

	Object::Object() {
	}

	Object::~Object() {
	}
}