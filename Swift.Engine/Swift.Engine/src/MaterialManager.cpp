#include "../include/MaterialManager.h"
#include "../include/TextureManager.h"
#include <fstream>
#include <vector>
#include <GL/glew.h>

namespace Swift {
	int MaterialManagerClass::loadShaders(std::string shader_name) {
		int ret = 0;
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		//GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(shader_name+".vxshader", std::ios::in);
		if(VertexShaderStream.is_open()) {
			std::string Line = "";
			while(getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		} else ret |= SW_NOVXSHADER;

		/*std::string GeometryShaderCode;
		std::ifstream GeometryShaderStream(shader_name+".gmshader", std::ios::in);
		if(GeometryShaderStream.is_open()) {
			std::string Line = "";
			while(getline(GeometryShaderStream, Line))
				GeometryShaderCode += "\n" + Line;
			GeometryShaderStream.close();
		} else ret |= SW_NOGMSHADER;*/

		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(shader_name+".pxshader", std::ios::in);
		printf("Opening shader: %s\n", (shader_name+".pxshader").c_str());
		if(FragmentShaderStream.is_open()) {
			std::string Line = "";
			while(getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		} else ret |= SW_NOPXSHADER;

		GLint Result = GL_FALSE;
		int InfoLogLength;

		printf("Compiling shader: %s\n", (shader_name+".vxshader").c_str());
		const char * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

		/*printf("Compiling shader: %s\n", (shader_name+".gmshader").c_str());
		const char * GeometrySourcePointer = GeometryShaderCode.c_str();
		glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, NULL);
		glCompileShader(GeometryShaderID);

		glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(GeometryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> GeometryShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(GeometryShaderID, InfoLogLength, NULL, &GeometryShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &GeometryShaderErrorMessage[0]);*/

		printf("Compiling shader: %s\n", (shader_name+".pxshader").c_str());
		const char * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

		fprintf(stdout, "Linking program\n");
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		//glAttachShader(ProgramID, GeometryShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)));
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

		glDeleteShader(VertexShaderID);
		//glDeleteShader(GeometryShaderID);
		glDeleteShader(FragmentShaderID);

		fprintf(stdout, "shader ID: %d\n", ProgramID);
		programs.insert(std::pair<std::string, GLuint>(shader_name, ProgramID));

		return ret;
	}
	unsigned int MaterialManagerClass::getProgram(std::string name) {
		return programs[name];
	}

	MaterialPtr MaterialManagerClass::addMaterial(Material mtl) {
		materials.push_back(mtl);
		return MaterialPtr(materials.size()-1);
	}

	Material MaterialManagerClass::getMaterial(unsigned int key) {
		return materials[key];
	}

	MaterialPtr MaterialManagerClass::getMaterialByName(std::string name) {
		//printf("name = %s\n", name.c_str());
		for(int key = 0; key < materials.size(); key++) {
			//printf("available: %s\n", materials[key].name.c_str());
			if(materials[key].name == name) {
				//printf("Found!\n");
				return MaterialPtr(key);
			}
		}
		//printf("dammit, nothing ;_;\n");
		return MaterialPtr(666666);
	}

	unsigned int MaterialManagerClass::getMaterialCount(void) {
		return materials.size();
	}

	int MaterialManagerClass::loadMtl(const char *filename) {
		//printf("loadMtl(%s)\n", filename);

		std::ifstream in(filename);
		if(!in.is_open()) return SW_FAILURE;
		
		Material *m = NULL;
		std::string line, name;

		int linec = 1;

		while(std::getline(in, line)) {

			std::string st = line.substr(0, line.find(' '));
			std::string temp(line);
			
			float xyz[3];
			int i = 0;

			while(temp != "" && temp != " " && temp.find(' ') != std::string::npos) {

				if(st == "Ka" || st == "Ks" || st == "Kd") {
					xyz[i] = ::atof(temp.substr(0, temp.find(' ')).c_str());
					i++;
				}
				temp = temp.substr(temp.find(' ')+1, temp.length()-temp.find(' ')-1);
			}
			
			glm::vec3 col(xyz[0], xyz[1], xyz[2]);
			std::string arg = line.substr(line.find(' ')+1, line.length()-line.find(' ')-1);
			if(st == "newmtl") { // nie ustawia nazw, wtf
				//printf("newmtl\n");
				if(m != NULL) {
					//printf("addMaterial\n");
					m->name = name;
					//if(m->PhongExponent < 0 || m->PhongExponent > 1000) m->PhongExponent = 50;
					addMaterial(*m);
					//printf("delete m\n");
					delete m;
				}
				m = new Material("phongblinn");
				m->PhongExponent = 50;
				m->DiffuseMap = SW_TEXTURE_EMPTY;
				m->AmbientMap = SW_TEXTURE_EMPTY;
				m->SpecularMap = SW_TEXTURE_EMPTY;

				name = arg;
			} else if (st == "Ns") {
				float phong = ::atof(arg.c_str());
				m->PhongExponent = phong;
				//printf("Phong exponent: %f\n", m->PhongExponent);
			} else if (st == "Ka") {
				m->AmbientColor = col;
				//printf("Ambient color: %f %f %f\n", m->AmbientColor.r, m->AmbientColor.g, m->AmbientColor.b);
			} else if (st == "Ks") {
				m->SpecularColor = col;
				//printf("Specular color: %f %f %f\n", m->SpecularColor.r, m->SpecularColor.g, m->SpecularColor.b);
			} else if (st == "Kd") {
				m->DiffuseColor = col;
				//printf("Diffuse color: %f %f %f\n", m->DiffuseColor.r, m->DiffuseColor.g, m->DiffuseColor.b);
			} else if (st == "map_Kd") {
				const char *tex_name = arg.c_str();

				Texture tex(tex_name);

				//printf("Adding diffuse texture\n");
				m->DiffuseMap = TextureManager->addTexture(tex);
				//printf("diffuse tex - done!\n");
			} else if (st == "map_Ka") {
				const char *tex_name = arg.c_str();

				Texture tex(tex_name);

				m->AmbientMap = TextureManager->addTexture(tex);
			} else if (st == "map_Ks") {
				const char *tex_name = arg.c_str();
				Texture tex(tex_name);

				m->SpecularMap = TextureManager->addTexture(tex);
			} else if (st == "map_bump" || st == "bump") {
				const char *tex_name = arg.c_str();

				Texture tex(tex_name);

				m->SpecularMap = TextureManager->addTexture(tex);
			}
			linec++;
		}
		
		m->name = name;
		addMaterial(*m);
		delete m;
		
		//printf("success!\n");
		return SW_SUCCESS;
	}

	MaterialManagerClass::MaterialManagerClass() {}
	MaterialManagerClass::~MaterialManagerClass() {
		for(std::map<std::string, GLuint>::iterator it = programs.begin(); it != programs.end(); ++it)
			glDeleteProgram((*it).second);
	}
}