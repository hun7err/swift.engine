#ifndef CUBE_H
#define CUBE_H

#include "Object.h"

namespace Swift {
	class Cube : public Object {
		protected:
			int segs; // width/height segment count
			int a; // length of the cube's side
			void calculateVertices();
		public:
			int getSegCount();
			void setSegCount(int count);
			void setSide(int _a);
		Cube(int _a, const glm::vec3& _pos, int _segs = 1);
		~Cube();
	};
}

#endif // CUBE_H