#include "../include/Sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace Swift {
	Sphere::Sphere(double _radius, int _segments, int _rings, glm::vec3 center) {
		parts.resize(1);
		origin = center;
		segments = _segments;
		rings = _rings;
		radius = _radius;
		
		//printf("przed setup()\n");
		parts[0].setup();
		//printf("po setup\n");

		calculateVertices();
	}

	void Sphere::calculateVertices() {
		double  r_f = M_PI/(rings+1),
				s_f = 2*M_PI/segments;

		const int vertex_count = 2 + rings*segments;
		glm::vec3 *gl_vertices = new glm::vec3[vertex_count];

		parts.resize(1);
		parts[0].vertices.clear();

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
		parts[0].vertices.resize(vcount);
		parts[0].normals.clear();
		parts[0].normals.resize(vcount);

		cur_pos = 0;
		for(int i = 1; i <= segments; i++) {
			parts[0].vertices[cur_pos] = gl_vertices[0];
			parts[0].vertices[cur_pos+1] = gl_vertices[i];
			parts[0].vertices[cur_pos+2] = gl_vertices[i+1 > segments ? 1 : i+1];

			cur_pos += 3;
		}

		for(int i = 1; i <= (rings-1)*segments; i++) {
				int t1 = i, t2 = i + segments, t3 = i % segments > 0 ? i+segments+1 : i+1;
				// trójk¹t 1
				parts[0].vertices[cur_pos] = gl_vertices[t1];
				parts[0].vertices[cur_pos+1] = gl_vertices[t2];
				parts[0].vertices[cur_pos+2] = gl_vertices[t3];
				// trójk¹t 2
				parts[0].vertices[cur_pos+3] = gl_vertices[t1];
				t2 = i % segments == 0 ? i+1-segments : i+1;
				parts[0].vertices[cur_pos+4] = gl_vertices[t2];
				parts[0].vertices[cur_pos+5] = gl_vertices[t3];

				cur_pos += 6;
			}

		int diff = vertex_count - segments - 1;
		for(int i = 0; i < segments; i++) {
			parts[0].vertices[cur_pos] = gl_vertices[vertex_count-1];
			parts[0].vertices[cur_pos+1] = gl_vertices[diff+i];
			parts[0].vertices[cur_pos+2] = gl_vertices[i+1 == segments ? vertex_count-segments-1 : vertex_count-segments+i];
			cur_pos += 3;
		}

		for(unsigned int i = 0; i < parts[0].vertices.size(); i++) {
			parts[0].normals[i] = glm::normalize(parts[0].vertices[i] - origin);
		}
		
		delete gl_vertices;

		parts[0].reload();
	}

	int Sphere::getSegmentCount(){
		return segments;
	}
	
	double Sphere::getRadius(){
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

	void Sphere::setRadius(double _radius) {
		radius = _radius;
		calculateVertices();
	}

	Sphere::~Sphere() {
		parts[0].destroy();
	}
}