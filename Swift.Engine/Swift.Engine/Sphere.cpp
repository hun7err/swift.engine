#include "Sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace Swift {
	Sphere::Sphere(double radius, int segments, int rings, glm::vec3 center) {
		Model = glm::mat4(1.0f);

		double  r_f = M_PI/(rings+1),
				s_f = 2*M_PI/segments;

		//std::cout << "Sphere points:" << std::endl;

		//std::ofstream out("points.txt");

		//out << "0, -5, 0" << std::endl << std::endl;
		const int vertex_count = 2 + rings*segments;
		glm::vec3 *gl_vertices = new glm::vec3[vertex_count];

		//printf("vertex count:\t%d\n", vertex_count);
		//vcount = vertex_count;

		int cur_pos = 0;
		gl_vertices[cur_pos] = glm::vec3(0.0f + center.x, (-1)*radius + center.z, 0.0f + center.y);
		cur_pos++;
		for(int r = 1/*1*/; r < rings+1; r++) {
			for(int s = 0; s < segments; s++) {
				GLfloat x = radius * cos(s_f * s) * cos(-M_PI_2 + r_f * r) + center.x;
				GLfloat y = radius * sin(s_f * s) * cos(-M_PI_2 + r_f * r) + center.y;
				GLfloat z = radius * sin(-M_PI_2 + r_f * r) + center.z;
				//GLfloat y = sin( -M_PI_2 + M_PI * r_f * r);
				//GLfloat x = cos(2*M_PI * s_f * s) * sin(M_PI * r_f * r);
				//GLfloat z = sin(2*M_PI*s_f*s) * sin(M_PI*r_f*r);
				//printf("%f %f %f\n", x, z, y);

				gl_vertices[cur_pos] = glm::vec3(x, z, y);
			
				cur_pos++;
				//out << x << ", " << z << ", " << y << std::endl;
			}
			//out << std::endl;
		}
		//out.close();
		gl_vertices[vertex_count-1] = glm::vec3(0 + center.x, radius + center.z, 0 + center.y);

		/*printf("gl_vertices_BEGIN\n");
		for(int i = 0; i < vertex_count; i++) {
			printf("%d: %f %f %f\n", i, gl_vertices[i].x, gl_vertices[i].y, gl_vertices[i].z);
		}

		printf("gl_vertices_END\n");*/

		int vcount = 3 * 6 * rings * segments/*3*6*vertex_count*/;
		vertices.resize(vcount);

		cur_pos = 0;
		for(int i = 1; i <= segments; i++) {
			//printf("cur_pos = %d\n", cur_pos);
			vertices[cur_pos] = gl_vertices[0].x;
			vertices[cur_pos+1] = gl_vertices[0].y;
			vertices[cur_pos+2] = gl_vertices[0].z;
			//printf("0 ");
			vertices[cur_pos+3] = gl_vertices[i].x;
			vertices[cur_pos+4] = gl_vertices[i].y;
			vertices[cur_pos+5] = gl_vertices[i].z;
			//printf("%d ", i);
			vertices[cur_pos+6] = gl_vertices[i + 1 > segments ? 1 : i+1].x;
			vertices[cur_pos+7] = gl_vertices[i + 1 > segments ? 1 : i+1].y;
			vertices[cur_pos+8] = gl_vertices[i + 1 > segments ? 1 : i+1].z;
			//printf("%d\n", i + 1 > segments ? 1 : i+1);
			cur_pos += 9;
		}

		for(int i = 1; i <= (rings-1)*segments /* 1? */; i++) {
				int t1 = i, t2 = i + segments, t3 = i % segments > 0 ? i+segments+1 : i+1/*i%segments+segments+1 : (rings-1)*segments + 1*/;
				// trójk¹t 1
				vertices[cur_pos] = gl_vertices[t1].x;
				vertices[cur_pos+1] = gl_vertices[t1].y;
				vertices[cur_pos+2] = gl_vertices[t1].z;
			
				vertices[cur_pos+3] = gl_vertices[t2].x;
				vertices[cur_pos+4] = gl_vertices[t2].y;
				vertices[cur_pos+5] = gl_vertices[t2].z;

				vertices[cur_pos+6] = gl_vertices[t3].x;
				vertices[cur_pos+7] = gl_vertices[t3].y;
				vertices[cur_pos+8] = gl_vertices[t3].z;
				// trójk¹t 2
				vertices[cur_pos+9] = gl_vertices[t1].x;
				vertices[cur_pos+10] = gl_vertices[t1].y;
				vertices[cur_pos+11] = gl_vertices[t1].z;

				t2 = i % segments == 0 ? i+1-segments : i+1;
				vertices[cur_pos+12] = gl_vertices[t2].x;
				vertices[cur_pos+13] = gl_vertices[t2].y;
				vertices[cur_pos+14] = gl_vertices[t2].z;

				vertices[cur_pos+15] = gl_vertices[t3].x;
				vertices[cur_pos+16] = gl_vertices[t3].y;
				vertices[cur_pos+17] = gl_vertices[t3].z;
			
				cur_pos += 18;
			}

		int diff = vertex_count - segments - 1;
		for(int i = 0; i < segments; i++) {
			//printf("cur_pos = %d\n", cur_pos);
			vertices[cur_pos] = gl_vertices[vertex_count-1].x;
			vertices[cur_pos+1] = gl_vertices[vertex_count-1].y;
			vertices[cur_pos+2] = gl_vertices[vertex_count-1].z;
			//printf("%d ", vertex_count-1);
		
			vertices[cur_pos+3] = gl_vertices[diff+i].x;
			vertices[cur_pos+4] = gl_vertices[diff+i].y;
			vertices[cur_pos+5] = gl_vertices[diff+i].z;
			//printf("%d ", diff+i);

			vertices[cur_pos+6] = gl_vertices[i-1 == segments ? vertex_count-1-segments : vertex_count-segments+i].x;
			vertices[cur_pos+7] = gl_vertices[i-1 == segments ? vertex_count-1-segments : vertex_count-segments+i].y;
			vertices[cur_pos+8] = gl_vertices[i-1 == segments ? vertex_count-1-segments : vertex_count-segments+i].z;
			//printf("%d\n", i+1 == segments ? vertex_count-1-segments : vertex_count-segments+i);

			cur_pos += 9;
		}
		//for(int i = 0; i < vertices.size()-3; i++)
		//	printf("%f %f %f\n", vertices[i], vertices[i+1], vertices[i+2]);
		//printf("Sfera: vertices[n-1] = vertices[%d] = %f\n", vertices.size()-1, vertices[vertices.size()-1]);
		delete gl_vertices;
		setup();
	}
	Sphere::~Sphere() {
		destroy();
	}
}