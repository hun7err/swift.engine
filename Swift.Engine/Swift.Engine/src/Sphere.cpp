#include "../include/Sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace Swift {
	Sphere::Sphere(double _radius, int _segments, int _rings, glm::vec3 center) {
		origin = center;
		segments = _segments;
		rings = _rings;
		radius = _radius;
		
		calculateVertices();
	}

	void Sphere::calculateVertices() {
		double  r_f = M_PI/(rings+1),
				s_f = 2*M_PI/segments;

		const int vertex_count = 2 + rings*segments;
		glm::vec3 *gl_vertices = new glm::vec3[vertex_count];

		vertices.clear();

		int cur_pos = 0;
		gl_vertices[cur_pos] = glm::vec3(0.0f + origin.x, (-1)*radius + origin.y, 0.0f + origin.z);
		cur_pos++;
		for(int r = 1; r < rings+1; r++) {
			for(int s = 0; s < segments; s++) {
				GLfloat x = radius * cos(s_f * s) * cos(-M_PI_2 + r_f * r) + origin.x;
				GLfloat y = radius * sin(-M_PI_2 + r_f * r) + origin.y;
				GLfloat z = radius * sin(s_f * s) * cos(-M_PI_2 + r_f * r) + origin.z;

				gl_vertices[cur_pos] = glm::vec3(x, y, z);
			
				cur_pos++;
			}
		}
		gl_vertices[vertex_count-1] = glm::vec3(0 + origin.x, radius + origin.y, 0 + origin.z);

		int vcount = 6 * rings * segments;
		vertices.resize(vcount);

		cur_pos = 0;
		for(int i = 1; i <= segments; i++) {
			vertices[cur_pos] = gl_vertices[0];
			vertices[cur_pos+1] = gl_vertices[i];
			vertices[cur_pos+2] = gl_vertices[i+1 > segments ? 1 : i+1];

			cur_pos += 3;
		}

		for(int i = 1; i <= (rings-1)*segments; i++) {
				int t1 = i, t2 = i + segments, t3 = i % segments > 0 ? i+segments+1 : i+1;
				// trójk¹t 1
				vertices[cur_pos] = gl_vertices[t1];
				vertices[cur_pos+1] = gl_vertices[t2];
				vertices[cur_pos+2] = gl_vertices[t3];
				// trójk¹t 2
				vertices[cur_pos+3] = gl_vertices[t1];
				t2 = i % segments == 0 ? i+1-segments : i+1;
				vertices[cur_pos+4] = gl_vertices[t2];
				vertices[cur_pos+5] = gl_vertices[t3];

				cur_pos += 6;
			}

		int diff = vertex_count - segments - 1;
		for(int i = 0; i < segments; i++) {
			vertices[cur_pos] = gl_vertices[vertex_count-1];
			vertices[cur_pos+1] = gl_vertices[diff+i];
			vertices[cur_pos+2] = gl_vertices[i+1 == segments ? vertex_count-segments-1 : vertex_count-segments+i];
			cur_pos += 3;
		}

		delete gl_vertices;

		setup();
	}

	int Sphere::getSegmentCount(){
		return segments;
	}
	
	int Sphere::getRadius(){
		return radius;
	}
	
	int Sphere::getRingCount(){
		return rings;
	}
	
	void Sphere::setSegmentCount(int _segments){
		segments = _segments;
		calculateVertices();
	}
	
	void Sphere::setRingCount(int _rings){
		rings = _rings;
		calculateVertices();
	}

	void Sphere::setRadius(int _radius) {
		radius = _radius;
		calculateVertices();
	}

	Sphere::~Sphere() {
		destroy();
	}


}