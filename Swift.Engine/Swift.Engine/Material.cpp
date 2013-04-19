#include "Material.h"
#include "MaterialManager.h"

namespace Swift {
	Material::Material() {}

	void Material::setShader(std::string name) {
		shader = MaterialManager->getShader(name);
	}

	GLuint Material::getShaderID() {
		return shader;
	}

	Material::Material(std::string shaderName) {
		setShader(shaderName);
	}

	Material::~Material() {}
}