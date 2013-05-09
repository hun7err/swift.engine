#include "../include/Cube.h"

namespace Swift {
	Cube::Cube(int _a, const glm::vec3& _pos, int _segs) {
		a = _a;
		origin = _pos;
		segs = _segs;
		parts.resize(1);

		parts[0].setup();
		calculateVertices();
	}

	void Cube::calculateVertices() {
		// base wall
		const double off = a / (double)segs;
		double	xstart = origin.x - a/2,
				ystart = origin.y - a/2,
				zstart = origin.z - a/2;

		parts[0].vertices.clear();

		for(int i = 0; i < segs; i++) {
			for(int j = 0; j < segs; j++) {
				glm::vec3	p0(xstart, ystart + i*off, zstart + j*off),
							p1(xstart, ystart + (i+1)*off, zstart + j*off),
							p2(xstart, ystart + (i+1)*off, zstart + (j+1)*off),
							p3(xstart, ystart + i*off, zstart + (j+1)*off);

				// first triangle
				parts[0].vertices.push_back(p0);
				parts[0].vertices.push_back(p1);
				parts[0].vertices.push_back(p3);
				// second triangle

				parts[0].vertices.push_back(p1);
				parts[0].vertices.push_back(p2);
				parts[0].vertices.push_back(p3);



				parts[0].vertices.push_back(glm::vec3(p0.x+a, p0.y, p0.z));
				parts[0].vertices.push_back(glm::vec3(p1.x+a, p1.y, p1.z));
				parts[0].vertices.push_back(glm::vec3(p3.x+a, p3.y, p3.z));

				// second triangle
				parts[0].vertices.push_back(glm::vec3(p1.x+a, p1.y, p1.z));
				parts[0].vertices.push_back(glm::vec3(p2.x+a, p2.y, p2.z));
				parts[0].vertices.push_back(glm::vec3(p3.x+a, p3.y, p3.z));

				p0 = glm::vec3(xstart+j*off, ystart + i*off, zstart);
				p1 = glm::vec3(xstart+j*off, ystart + (i+1)*off, zstart);
				p2 = glm::vec3(xstart+(j+1)*off, ystart + (i+1)*off, zstart);
				p3 = glm::vec3(xstart+(j+1)*off, ystart + i*off, zstart);
				// first triangle
				parts[0].vertices.push_back(p0);
				parts[0].vertices.push_back(p1);
				parts[0].vertices.push_back(p3);
				// second triangle

				parts[0].vertices.push_back(p1);
				parts[0].vertices.push_back(p2);
				parts[0].vertices.push_back(p3);



				parts[0].vertices.push_back(glm::vec3(p0.x, p0.y, p0.z+a));
				parts[0].vertices.push_back(glm::vec3(p1.x, p1.y, p1.z+a));
				parts[0].vertices.push_back(glm::vec3(p3.x, p3.y, p3.z+a));

				// second triangle
				parts[0].vertices.push_back(glm::vec3(p1.x, p1.y, p1.z+a));
				parts[0].vertices.push_back(glm::vec3(p2.x, p2.y, p2.z+a));
				parts[0].vertices.push_back(glm::vec3(p3.x, p3.y, p3.z+a));


				p0 = glm::vec3(xstart+j*off, ystart, zstart+i*off);
				p1 = glm::vec3(xstart+j*off, ystart, zstart+(i+1)*off);
				p2 = glm::vec3(xstart+(j+1)*off, ystart, zstart+(i+1)*off);
				p3 = glm::vec3(xstart+(j+1)*off, ystart, zstart+i*off);
				// first triangle
				parts[0].vertices.push_back(p0);
				parts[0].vertices.push_back(p1);
				parts[0].vertices.push_back(p3);
				// second triangle

				parts[0].vertices.push_back(p1);
				parts[0].vertices.push_back(p2);
				parts[0].vertices.push_back(p3);



				parts[0].vertices.push_back(glm::vec3(p0.x, p0.y+a, p0.z));
				parts[0].vertices.push_back(glm::vec3(p1.x, p1.y+a, p1.z));
				parts[0].vertices.push_back(glm::vec3(p3.x, p3.y+a, p3.z));

				// second triangle
				parts[0].vertices.push_back(glm::vec3(p1.x, p1.y+a, p1.z));
				parts[0].vertices.push_back(glm::vec3(p2.x, p2.y+a, p2.z));
				parts[0].vertices.push_back(glm::vec3(p3.x, p3.y+a, p3.z));
			}
		}
		parts[0].reload();
	}

	int Cube::getSegCount() {
		return segs;
	}

	Cube::~Cube() {
		parts[0].destroy();
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