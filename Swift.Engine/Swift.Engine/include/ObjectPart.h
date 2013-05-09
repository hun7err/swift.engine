#ifndef OBJECTPART_H
#define OBJECTPART_H

#include "Texture.h"
#include "Material.h"
#include <vector>
#include <glm/glm.hpp>

namespace Swift {
	class ObjectPart {
		public:
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> uvs;
			std::vector<glm::vec3> normals;

			MaterialPtr mtl;
			glm::mat4 Model;
			glm::vec3 origin;
			GLuint VBO;
			GLuint VAO;
			GLuint normalbuffer;
			GLuint uvbuffer;

			bool visible;
			std::string alias;

			void destroy();
			void setup();
			void reload();

			GLuint getVBO();
			GLuint getVAO();
			GLuint getNormalBuffer();
			glm::vec3 getOrigin();

			bool isVisible();
			void hide();
			void show();
			GLuint getUVbuffer();

			TexturePtr DiffuseMap;
			TexturePtr SpecularMap;
			TexturePtr AmbientMap;
			TexturePtr NormalMap;
			TexturePtr BumpMap;

			unsigned int getVertexCount();

			std::string getAlias();
			void setAlias(std::string _alias);

			glm::mat4 getModelMatrix();

			MaterialPtr getMaterial();
			void setMaterial(MaterialPtr _mtl);

			void rotate(const glm::vec3& axis, float angle);
			// jeszcze pitch, yaw, roll!
			void move(const glm::vec3& newPos);
			void scale(const glm::vec3& factor);
		ObjectPart();
		~ObjectPart();
	};
}

#endif // OBJECTPART_H