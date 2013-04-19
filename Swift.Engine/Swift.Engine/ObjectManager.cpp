#include "ObjectManager.h"

namespace Swift {
	void ObjectManagerClass::add(Group* group) {
		groups.push_back(group);
	}

	void ObjectManagerClass::remove(std::string name) {
		for(std::vector<Group*>::iterator it = groups.begin(); it != groups.end(); ++it)
			if((*it)->getName() == name) {
				groups.erase(it);
				break;
			}
	}

	void ObjectManagerClass::removeAt(unsigned int index) {
		std::vector<Group*>::iterator start = groups.begin();
		groups.erase(start+index);
	}

	std::vector<Group*>* ObjectManagerClass::getGroups() {
		return &groups;
	}

	ObjectManagerClass::ObjectManagerClass(){
		//printf("Konstruktor ObjectManager()\n");
	}
	ObjectManagerClass::~ObjectManagerClass() {
		//printf("Destruktor ObjectManager()\n");
		for(std::vector<Group*>::iterator it = groups.begin(); it != groups.end(); ++it)
			delete (*it);
	}
}