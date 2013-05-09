#include "../include/MaterialManager.h"
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

	Material& MaterialManagerClass::getMaterial(unsigned int key) {
		return materials[key];
	}

	MaterialManagerClass::MaterialManagerClass() {}
	MaterialManagerClass::~MaterialManagerClass() {
		for(std::map<std::string, GLuint>::iterator it = programs.begin(); it != programs.end(); ++it)
			glDeleteProgram((*it).second);
	}
}