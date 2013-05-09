#include "../include/Mesh.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>
#include <map>

namespace Swift {
	Mesh::Mesh(const glm::vec3& pos) {
		origin = pos;

		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			(*it).setup();
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
		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			(*it).destroy();
	}

	int Mesh::loadObj(const char* filename) {
		printf("Mesh - loadObj\n");
		std::ifstream in(filename);
		if(!in.is_open()) return SW_FAILURE;

		std::string line("");
		std::vector<glm::vec3> gl_vertices;
		std::vector<glm::vec2> gl_uv;
		std::vector<glm::vec3> gl_normals;

		ObjectPart obj;
		std::map<std::string, Material> materials;
		Material mtl;

		std::string lastst = "";

		int lc = 1;

		while(std::getline(in, line)) {
			std::string st = line.substr(0, line.find(' '));
			line = line.substr(line.find(' ')+1, line.length()-line.find(' ')-1);

			float xyz[3] = {0.0f, 0.0f, 0.0f};
			int i = 0;

			if(st == "v" || st == "vn" || st == "vt" || st == "f")
			while(1) {
				//printf("while(1), cutting line\n");
				std::string part = line.substr(0, line.find(' '));

				if (st == "v" || st == "vn" || st == "vt") {
					//printf("v | vn | vt\n");
					xyz[i] = atof(part.c_str());
					i++;
				} else if(st == "f") {
					//printf("f - index\n");
					unsigned int	v,
									t = 0,
									n = 0;
					const size_t pos = part.find('/'),
									rpos = part.rfind('/');

					if(pos == std::string::npos) {
						//printf("just vertex, pushing. Line %d\n", lc);
						v = atoi(part.c_str());
						obj.vertices.push_back(gl_vertices[v-1]);
					} else {
						v = atoi(part.substr(0, pos).c_str());

						std::string temp = part.substr(pos+1, rpos-pos-1);

						if(temp != "")
							t = atoi(temp.c_str());
						temp = part.substr(rpos+1, part.length()-rpos-1);
						if(temp != "")
							n = atoi(temp.c_str());
						obj.vertices.push_back(gl_vertices[v-1]);
						if(n != 0) obj.normals.push_back(gl_normals[n-1]);
						if(t != 0) obj.uvs.push_back(gl_uv[t-1]);
					}
				} else if(st == "mtllib") {
					printf("mtllib %s\n", line.c_str());
				} else if(st == "usemtl") {
					// przypisz mtl dla obj
				}
				if(line.find(' ') == std::string::npos) break;
				line = line.substr(line.find(' ')+1, line.length()-line.find(' ')-1);
			}

			if(st == "v") {
				//printf("pushing vertex\n");
				gl_vertices.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
			} else if(st == "vt") {
				//printf("pushing uv\n");
				gl_uv.push_back(glm::vec2(xyz[0], xyz[1]));
			} else if(st == "vn") {
				//printf("pushing normal\n");
				gl_normals.push_back(glm::vec3(xyz[0], xyz[1], xyz[2]));
			}
			if(st == "v" && lastst == "f") {
				parts.push_back(obj);
				//printf("destroying obj\n");
				obj.destroy();
				obj.setup();
			}

			lastst = st;
			//printf("lastst = |%s|\n", lastst.c_str());

			lc++;
		}
		if(lastst == "f") {
			//printf("last part\n");
			parts.push_back(obj);

			obj.destroy();
		}
		gl_vertices.clear();
		gl_normals.clear();
		gl_uv.clear();

		printf("setup\n");
		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			(*it).setup();
		for(std::vector<ObjectPart>::iterator it = parts.begin(); it != parts.end(); ++it)
			(*it).reload();
		return SW_SUCCESS;
	}
	
	void Mesh::load3DS(const char *filename) {
	}
	
	void Mesh::loadBlend(const char *filename) {
	}
}