#include "Group.h"

namespace Swift {
	void Group::add(Object* obj) {
		objects.push_back(obj);
	}

	void Group::remove(std::string _name) {
		for(std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
			if((*it)->getName() == _name) {
				objects.erase(it);
				break;
			}
		}
	}

	void Group::removeAt(unsigned int index) {
		std::vector<Object*>::iterator it = objects.begin();
		objects.erase(it+index);
	}

	void Group::setName(std::string _name) {
		name = _name;
	}

	std::string Group::getName() {
		return name;
	}

	Object* Group::getObject(std::string _name) {
		for(std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
			if((*it)->getName() == _name) {
				return (*it);
				break;
			}
		}
	}

	Object* Group::getObjectAt(unsigned int index) {
		return objects[index];
	}
	
	std::vector<Object*>* Group::getObjects() {
		return &objects;
	}

	Group::Group() {}
	Group::Group(Object* obj) {
		objects.push_back(obj);
	}
	Group::~Group() {
		for(std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
			delete *it;
		}
	}
}