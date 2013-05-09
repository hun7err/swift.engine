#ifndef MESH_H
#define MESH_H

#include "Object.h"

namespace Swift {
	class Mesh : public Object {
		public:
			int loadObj(const char *filename);
			void load3DS(const char *filename);
			void loadBlend(const char *filename);
		Mesh(const glm::vec3& pos = glm::vec3(0,0,0));
		Mesh(const char *filename, const glm::vec3& pos = glm::vec3(0,0,0));
		~Mesh();
	};
}

#endif // MESH_H