#ifndef MATERIAL_H
#define MATERIAL_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "Texture.h"
//#include <GL/gl.h>

namespace Swift {
	class Material {
		private:
			GLuint shader;
			// float fresnel
			// float IOR
			// float opacity

			// ILuint -> tekstura
		public:
			glm::vec3 DiffuseColor;
			glm::vec3 SpecularColor;
			glm::vec3 AmbientColor;

			float PhongExponent;
			void setShader(std::string name);
			GLuint getProgramID();
			std::string name;

			TexturePtr DiffuseMap;
			TexturePtr SpecularMap;
			TexturePtr AmbientMap;
			TexturePtr NormalMap;
			TexturePtr BumpMap;
		Material();
		Material(std::string shaderName, glm::vec3 _DiffuseColor = glm::vec3(1.0f), glm::vec3 _SpecularColor = glm::vec3(0.7f), glm::vec3 _AmbientColor = glm::vec3(0.3f), float _PhongExponent = 50.0f);
		~Material();
	};

	class MaterialPtr {
		public:
			unsigned int key;
			Material operator* ();
			Material* operator->();
			void setKey(unsigned int _key);
		MaterialPtr();
		MaterialPtr(unsigned int _key);
	};
}

#endif // MATERIAL_H