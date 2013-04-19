#include "Supervisor.h"
#include <GL/glew.h>
#include <cstdio>

namespace Swift {
	////// GPU INFO START
	std::string SupervisorClass::getRenderer() {
		const GLubyte* temp = glGetString(GL_RENDERER);
		std::string ret = temp ? (const char*)temp : "";
		//delete temp;
		return ret;
	}

	std::string SupervisorClass::getVendor() {
		const GLubyte* temp = glGetString(GL_VENDOR);
		std::string ret = temp ? (const char*)temp : "";
		//delete temp;
		return ret;
	}
	
	std::string SupervisorClass::getShaderLanguageVersion() {
		const GLubyte* temp = glGetString(GL_SHADING_LANGUAGE_VERSION);
		std::string ret = temp ? (const char*)temp : "";
		//delete temp;
		return ret;
	}
	
	std::string SupervisorClass::getOpenGLversion() {
		const GLubyte* temp = glGetString(GL_VERSION);
		std::string ret = temp ? (const char*)temp : "";
		//delete temp;
		return ret;
	}

	SupervisorClass::SupervisorClass() {}

	SupervisorClass::~SupervisorClass() {}

	//SupervisorClass::SupervisorClass() {}
	//SupervisorClass::~SupervisorClass() {}

	////// GPU INFO END
}