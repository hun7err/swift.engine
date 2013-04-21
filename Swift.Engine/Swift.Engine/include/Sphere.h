#ifndef SPHERE_H
#define SPHERE_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Object.h"

namespace Swift {
	class Sphere : public Object {
		private:
			int segments; // segment count
			int radius; // radius
			int rings; // ring count
			void calculateVertices();
		public:
			int getSegmentCount();
			int getRadius();
			int getRingCount();
			void setSegmentCount(int _segments);
			void setRingCount(int _rings);
			void setRadius(int _radius);
		Sphere(double _radius, int _segments, int _rings, glm::vec3 center);
		~Sphere();
	};
}

#endif // SPHERE_H