#include "../include/Material.h"
#include "../include/MaterialManager.h"

namespace Swift {
	Material::Material() {}

	void Material::setShader(std::string name) {
		shader = MaterialManager->getProgram(name);
	}

	GLuint Material::getProgramID() {
		return shader;
	}

	Material MaterialPtr::operator*() {
		return MaterialManager->getMaterial(key);
	}

	MaterialPtr::MaterialPtr() {
		key = -1;
	}

	void MaterialPtr::setKey(unsigned int _key) {
		key = _key;
	}

	Material* MaterialPtr::operator->() {
		return &(MaterialManager->getMaterial(key));
	}

	MaterialPtr::MaterialPtr(unsigned int _key) {
		key = _key;
	}

	Material::Material(std::string shaderName, glm::vec3 _DiffuseColor, glm::vec3 _SpecularColor, glm::vec3 _AmbientColor, float _PhongExponent) {
		DiffuseColor = _DiffuseColor;
		SpecularColor = _SpecularColor;
		AmbientColor = _AmbientColor;
		PhongExponent = _PhongExponent;
		setShader(shaderName);
	}

	Material::~Material() {}
}