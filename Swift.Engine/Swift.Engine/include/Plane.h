#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

namespace Swift {
	class Plane : public Object { // a plane
		protected:
			int heightSegs;
			int widthSegs;
			double width;
			double height;
			void calculateVertices();	// recalculates vertices based on hSegs and wSegs
		public:
			int getHeightSegCount();
			int getWidthSegCount();
			double getWidth();
			double getHeight();
			void setHeightSegCount(int count);
			void setWidthSegCount(int count);
		Plane(double _width, double _height, const glm::vec3& pos = glm::vec3(0,0,0),  int heightSegments = 1, int widthSegments = 1);
		~Plane();
	};
}
#endif // PLANE_H