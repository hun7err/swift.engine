#ifndef MATERIAL_H
#define MATERIAL_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
//#include <GL/gl.h>

namespace Swift {
	class Material {
		private:
			GLuint shader;
			// Texture* diffuseMap
			glm::vec4 diffuse;
			// Color diffuse
			// Texture* specularMap
			// Color specular
			glm::vec4 specular;
			glm::vec4 ambient;
			float phongExponent;
			// Texture* bumpMap
			// Texture* normalMap
			// float phongExponent
			// float fresnel
			// float IOR
			// float opacity
			// Color ambient

		public:
			void setShader(std::string name);
			GLuint getShaderID();
		Material();
		Material(std::string shaderName);
		~Material();
	};
}

#endif // MATERIAL_H