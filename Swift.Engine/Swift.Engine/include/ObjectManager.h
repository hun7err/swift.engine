#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include "Group.h"
#include "Singleton.h"

#define ObjectManager ObjectManagerC::getSingleton()

namespace Swift {
	class ObjectManagerClass/* : public Singleton<ObjectManagerClass>*/ {
		private:
			std::vector<Group*> groups;
		public:
			void add(Group* _group);
			void remove(std::string name);
			void removeAt(unsigned int index);
			std::vector<Group*>* getGroups();
		ObjectManagerClass();
		~ObjectManagerClass();
	};

	typedef Singleton<ObjectManagerClass> ObjectManagerC;
}


#endif // OBJECTMANAGER_H