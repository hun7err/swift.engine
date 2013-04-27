#include "../include/Mesh.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>

namespace Swift {
	Mesh::Mesh(const glm::vec3& pos) {
		origin = pos;
		setup();
	}

	Mesh::Mesh(const char *filename, const glm::vec3& pos) {
		origin = pos;
		std::string fname(filename);
		std::string type = fname.substr(fname.find('.')+1, fname.length()-fname.find('.')-1);
		
		if(type == "obj")
			loadObj(filename);
		else if (type == "3ds")
			load3DS(filename);
		else if (type == "blend")
			loadBlend(filename);
	}

	Mesh::~Mesh() {
		destroy();
	}

	void Mesh::loadObj(const char* filename) {
		std::ifstream in(filename);

		std::string line("");
		std::vector<glm::vec3> gl_vertices;
		std::vector<glm::vec2> gl_uv;
		std::vector<glm::vec3> gl_normals;

		vertices.clear();
		
		while(std::getline(in, line)) {
			std::string st = line.substr(0, line.find(' '));
			line = line.substr(line.find(' ')+1, line.length()-line.find(' ')-1);

			float xyz[3] = {0.0f, 0.0f, 0.0f};
			int i = 0;

			if(st == "v" || st == "vn" || st == "vt" || st == "f")
			while(1) {
				std::string part = line.substr(0, line.find(' '));

				if (st == "v" || st == "vn" || st == "vt") {
					xyz[i] = atof(part.c_str());
					i++;
				} else if(st == "f") {
					int	v,
						t = -1,
						n = -1;
					const size_t pos = part.find('/'),
									rpos = part.rfind('/');

					if(pos == std::string::npos) {
						v = atoi(part.c_str());
						vertices.push_back(gl_vertices[v-1]);
					} else {
						v = atoi(part.substr(0, pos).c_str());

						std::string temp = part.substr(pos+1, rpos-pos-1);

						if(temp == "")
							t = -1;
						else
							t = atoi(temp.c_str());
						temp = part.substr(rpos+1, part.length()-rpos-1);
						if(temp == "")
							n = -1;
						else
							n = atoi(temp.c_str());
						vertices.push_back(gl_vertices[v-1]);
						if(n != -1) normals.push_back(gl_normals[n-1]);
						if(t != -1) uvs.push_back(gl_uv[t-1]);
					}
				}
				if(line.find(' ') == std::string::npos) break;
				line = line.substr(line.find(' ')+1, line.length()-line.find(' ')-1);
			}

			if(st == "v") {
				gl_vertices.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
			} else if(st == "vt") {
				gl_uv.push_back(glm::vec2(xyz[0], xyz[1]));
			} else if(st == "vn") {
				gl_normals.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
			}
		}
		gl_vertices.clear();

		reload();
	}
	
	void Mesh::load3DS(const char *filename) {
	}
	
	void Mesh::loadBlend(const char *filename) {
	}
}