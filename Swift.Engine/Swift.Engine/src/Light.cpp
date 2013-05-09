#include "../include/Light.h"
#include "../include/MaterialManager.h"

namespace Swift {
	LightStruct Light::getStruct() {
		light.pos = parts[0].origin;
		light.model = parts[0].Model;
		return light;
	}

	LightStruct* Light::getStructPtr() {
		light.pos = origin;
		light.model = parts[0].Model;
		return &light;
	}

	Light::Light() {
		parts.resize(1);
		light.pos = glm::vec3(0.0f);
		parts[0].origin = light.pos;
		light.color = glm::vec3(1.0f);
		light.intensity = 1.0f;
		MaterialManager->loadShaders("pointlight");
		Material _mtl("pointlight");
		MaterialPtr m = MaterialManager->addMaterial(_mtl);
		parts[0].mtl = m;
	}

	Light::Light(glm::vec3 _color, glm::vec3 _pos, float _intensity) {
		parts.resize(1);

		origin = _pos;
		light.color = _color;
		light.pos = _pos;
		light.intensity = _intensity;
		MaterialManager->loadShaders("pointlight");
		Material _mtl("pointlight");
		MaterialPtr m = MaterialManager->addMaterial(_mtl);
		parts[0].mtl = m;
	}

	Light::~Light() {}
}