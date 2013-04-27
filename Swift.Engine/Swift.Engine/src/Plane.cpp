#include "../include/Plane.h"

namespace Swift {
	Plane::Plane(double _width, double _height, const glm::vec3& pos, int heightSegments, int widthSegments) {
		width = _width;
		height = _height;
		origin = pos;
		heightSegs = heightSegments;
		widthSegs = widthSegments;

		//move(pos);

		calculateVertices();
	}

	Plane::~Plane() {
		destroy();
	}

	void Plane::calculateVertices() {
		//std::vector<GLfloat> vertex_data;
		const double	xoff = width / (double)widthSegs,
						zoff = height / (double)heightSegs;
		double	xstart = origin.x - width/2,
				zstart = origin.z - height/2;

		vertices.clear();

		for (int i = 0; i < widthSegs; i++) {
			for(int j = 0; j < heightSegs; j++) {
				glm::vec3	p0(xstart + i*xoff, origin.y, zstart + j*zoff),
							p1(xstart + (i+1)*xoff, origin.y, zstart + j*zoff),
							p2(xstart + (i+1)*xoff, origin.y, zstart + (j+1)*zoff),
							p3(xstart + i*xoff, origin.y, zstart + (j+1)*zoff);
				// vertices are oriented CW (clockwise)
				
				// first triangle
				vertices.push_back(p0);
				vertices.push_back(p1);
				vertices.push_back(p3);
				
				// second triangle
				vertices.push_back(p1);
				vertices.push_back(p2);
				vertices.push_back(p3);
			}
		}
		setup();
	}
	
	int Plane::getHeightSegCount() {
		return heightSegs;
	}

	int Plane::getWidthSegCount(){
		return widthSegs;
	}
	
	int Plane::getWidth(){
		return width;
	}
	
	int Plane::getHeight(){
		return height;
	}
	
	void Plane::setHeightSegCount(int count){
		heightSegs = count;
		calculateVertices();
	}
	
	void Plane::setWidthSegCount(int count){
		widthSegs = count;
		calculateVertices();
	}
}