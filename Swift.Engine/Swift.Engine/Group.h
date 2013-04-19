#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <glm/glm.hpp>
#include "Object.h"

namespace Swift {
	class Group {
		private:
			std::string name;
			std::vector<Object*> objects;
		public:
			void add(Object* obj);
			void remove(std::string _name);
			void removeAt(unsigned int index);
			std::vector<Object*>* getObjects();
			// rotate
			// pitch
			// yaw
			// roll
			// move

			void setName(std::string _name);

			std::string getName();
			Object* getObject(std::string _name);
			Object* getObjectAt(unsigned int index);
		Group();
		Group(Object* obj);
		~Group();
	};
}

#endif // GROUP_H