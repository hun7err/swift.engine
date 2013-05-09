#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include "Object.h"

namespace Swift {
	typedef struct LightStruct {
		glm::vec3 pos;
		glm::vec3 color;
		float intensity;
		glm::mat4 model;
	} LightStruct;

	class Light : public Object {
		private:
			LightStruct light;
		public:
			LightStruct getStruct();
			LightStruct* getStructPtr();
		Light();
		Light(glm::vec3 _color, glm::vec3 _pos = glm::vec3(0.0f), float _intensity = 1.0f);
		~Light();
	};
}

#endif // LIGHT_H