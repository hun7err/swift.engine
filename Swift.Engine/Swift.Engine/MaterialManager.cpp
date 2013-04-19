#include "MaterialManager.h"
#include <fstream>
#include <vector>
#include <GL/glew.h>

namespace Swift {
	void MaterialManagerClass::loadShader(std::string shader_name, std::string vertex_shader_name, std::string pixel_shader_name) {
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_shader_name, std::ios::in);
		if(VertexShaderStream.is_open()) {
			std::string Line = "";
			while(getline(VertexShaderStream, Line))
				VertexShaderCode += "\n" + Line;
			VertexShaderStream.close();
		}
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(pixel_shader_name, std::ios::in);
		if(FragmentShaderStream.is_open()) {
			std::string Line = "";
			while(getline(FragmentShaderStream, Line))
				FragmentShaderCode += "\n" + Line;
			FragmentShaderStream.close();
		}
		GLint Result = GL_FALSE;
		int InfoLogLength;

		printf("Compiling shader: %s\n", vertex_shader_name.c_str());
		const char * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

		printf("Compiling shader: %s\n", pixel_shader_name.c_str());
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
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)));
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		fprintf(stdout, "shader ID: %d\n", ProgramID);
		shaders.insert(std::pair<std::string, GLuint>(shader_name, ProgramID));
	}
	unsigned int MaterialManagerClass::getShader(std::string name) {
		return shaders[name];
	}

	MaterialManagerClass::MaterialManagerClass() {}
	MaterialManagerClass::~MaterialManagerClass() {
		for(std::map<std::string, GLuint>::iterator it = shaders.begin(); it != shaders.end(); ++it)
			glDeleteProgram((*it).second);
	}
}