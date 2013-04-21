#include "../include/Cube.h"

namespace Swift {
	Cube::Cube(int _a, const glm::vec3& _pos, int _segs) {
		a = _a;
		origin = _pos;
		segs = _segs;

		calculateVertices();
	}

	void Cube::calculateVertices() {
		// base wall
		const double off = a / (double)segs;
		double	xstart = origin.x - a/2,
				ystart = origin.y - a/2,
				zstart = origin.z - a/2;

		vertices.clear();

		for(int i = 0; i < segs; i++) {
			for(int j = 0; j < segs; j++) {
				glm::vec3	p0(xstart, ystart + i*off, zstart + j*off),
							p1(xstart, ystart + (i+1)*off, zstart + j*off),
							p2(xstart, ystart + (i+1)*off, zstart + (j+1)*off),
							p3(xstart, ystart + i*off, zstart + (j+1)*off);

				vertices.push_back(p0.x);
				vertices.push_back(p0.y);
				vertices.push_back(p0.z);
				
				vertices.push_back(p1.x);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z);

				vertices.push_back(p3.x);
				vertices.push_back(p3.y);
				vertices.push_back(p3.z);
				// second triangle
				vertices.push_back(p1.x);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z);

				vertices.push_back(p2.x);
				vertices.push_back(p2.y);
				vertices.push_back(p2.z);

				vertices.push_back(p3.x);
				vertices.push_back(p3.y);
				vertices.push_back(p3.z);



				vertices.push_back(p0.x+a);
				vertices.push_back(p0.y);
				vertices.push_back(p0.z);
				
				vertices.push_back(p1.x+a);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z);

				vertices.push_back(p3.x+a);
				vertices.push_back(p3.y);
				vertices.push_back(p3.z);
				// second triangle
				vertices.push_back(p1.x+a);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z);

				vertices.push_back(p2.x+a);
				vertices.push_back(p2.y);
				vertices.push_back(p2.z);

				vertices.push_back(p3.x+a);
				vertices.push_back(p3.y);
				vertices.push_back(p3.z);

				p0 = glm::vec3(xstart+j*off, ystart + i*off, zstart);
				p1 = glm::vec3(xstart+j*off, ystart + (i+1)*off, zstart);
				p2 = glm::vec3(xstart+(j+1)*off, ystart + (i+1)*off, zstart);
				p3 = glm::vec3(xstart+(j+1)*off, ystart + i*off, zstart);


				
				vertices.push_back(p0.x);
				vertices.push_back(p0.y);
				vertices.push_back(p0.z);
				
				vertices.push_back(p1.x);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z);

				vertices.push_back(p3.x);
				vertices.push_back(p3.y);
				vertices.push_back(p3.z);
				// second triangle
				vertices.push_back(p1.x);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z);

				vertices.push_back(p2.x);
				vertices.push_back(p2.y);
				vertices.push_back(p2.z);

				vertices.push_back(p3.x);
				vertices.push_back(p3.y);
				vertices.push_back(p3.z);



				vertices.push_back(p0.x);
				vertices.push_back(p0.y);
				vertices.push_back(p0.z+a);
				
				vertices.push_back(p1.x);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z+a);

				vertices.push_back(p3.x);
				vertices.push_back(p3.y);
				vertices.push_back(p3.z+a);
				// second triangle
				vertices.push_back(p1.x);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z+a);

				vertices.push_back(p2.x);
				vertices.push_back(p2.y);
				vertices.push_back(p2.z+a);

				vertices.push_back(p3.x);
				vertices.push_back(p3.y);
				vertices.push_back(p3.z+a);


				p0 = glm::vec3(xstart+j*off, ystart, zstart+i*off);
				p1 = glm::vec3(xstart+j*off, ystart, zstart+(i+1)*off);
				p2 = glm::vec3(xstart+(j+1)*off, ystart, zstart+(i+1)*off);
				p3 = glm::vec3(xstart+(j+1)*off, ystart, zstart+i*off);


				
				vertices.push_back(p0.x);
				vertices.push_back(p0.y);
				vertices.push_back(p0.z);
				
				vertices.push_back(p1.x);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z);

				vertices.push_back(p3.x);
				vertices.push_back(p3.y);
				vertices.push_back(p3.z);
				// second triangle
				vertices.push_back(p1.x);
				vertices.push_back(p1.y);
				vertices.push_back(p1.z);

				vertices.push_back(p2.x);
				vertices.push_back(p2.y);
				vertices.push_back(p2.z);

				vertices.push_back(p3.x);
				vertices.push_back(p3.y);
				vertices.push_back(p3.z);



				vertices.push_back(p0.x);
				vertices.push_back(p0.y+a);
				vertices.push_back(p0.z);
				
				vertices.push_back(p1.x);
				vertices.push_back(p1.y+a);
				vertices.push_back(p1.z);

				vertices.push_back(p3.x);
				vertices.push_back(p3.y+a);
				vertices.push_back(p3.z);
				// second triangle
				vertices.push_back(p1.x);
				vertices.push_back(p1.y+a);
				vertices.push_back(p1.z);

				vertices.push_back(p2.x);
				vertices.push_back(p2.y+a);
				vertices.push_back(p2.z);

				vertices.push_back(p3.x);
				vertices.push_back(p3.y+a);
				vertices.push_back(p3.z);
			}
		}
		setup();

	}

	int Cube::getSegCount() {
		return segs;
	}

	Cube::~Cube() {
		destroy();
	}

	void Cube::setSegCount(int count) {
		segs = count;
		calculateVertices();
	}
	
	void Cube::setSide(int _a) {
		a = _a;
		calculateVertices();
	}
}