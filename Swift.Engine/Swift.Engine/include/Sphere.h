#ifndef SPHERE_H
#define SPHERE_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Object.h"

namespace Swift {
	class Sphere : public Object {
		private:
			int segments; // segment count
			double radius; // radius
			int rings; // ring count
			void calculateVertices();
		public:
			int getSegmentCount();
			double getRadius();
			int getRingCount();
			void setSegmentCount(int _segments);
			void setRingCount(int _rings);
			void setRadius(double _radius);
		Sphere(double _radius, int _segments, int _rings, glm::vec3 center = glm::vec3(0,0,0));
		~Sphere();
	};
}

#endif // SPHERE_H