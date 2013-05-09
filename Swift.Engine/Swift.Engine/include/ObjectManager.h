#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include "Light.h"
#include "Group.h"
#include "Singleton.h"

#define ObjectManager ObjectManagerC::getSingleton()

namespace Swift {
	class ObjectManagerClass/* : public Singleton<ObjectManagerClass>*/ {
		private:
			std::vector<Group*> groups;
			std::vector<Light*> lights;
		public:
			void add(Group* _group);
			void addLight(Light* light);
			void remove(std::string name);
			void removeAt(unsigned int index);
			std::vector<Group*>* getGroups();
			std::vector<Light*>* getLights();
		ObjectManagerClass();
		~ObjectManagerClass();
	};

	typedef Singleton<ObjectManagerClass> ObjectManagerC;
}


#endif // OBJECTMANAGER_H