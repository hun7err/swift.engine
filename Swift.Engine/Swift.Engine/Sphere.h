#ifndef SPHERE_H
#define SPHERE_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Object.h"

namespace Swift {
	class Sphere : public Object {
		public:
		Sphere(double radius, int segments, int rings, glm::vec3 center);
		~Sphere();
	};
}

#endif // SPHERE_H