#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>

namespace Swift {
	class Object {
		protected:
			glm::mat4 Model;
			glm::vec3 origin;
			GLuint VBO;
			GLuint VAO;
			GLuint normalbuffer;
			
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> uvs;
			std::vector<glm::vec3> normals;

			std::string name;
			Material* mtl;
			void destroy();
			void setup();
			void reload();
			bool visible;
		public:
			GLfloat* getVertices();
			Material* getMaterial();
			glm::mat4 getModelMatrix();
			glm::vec3 getPosition();
			glm::vec3 getOrigin();
			bool isVisible();
			void hide();
			void show();
			unsigned int getVertexCount();
			void rotate(const glm::vec3& axis, float angle);
			// jeszcze pitch, yaw, roll!
			void move(const glm::vec3& newPos);
			void scale(const glm::vec3& factor);
			// scale jeszcze!
			GLuint getVBO();
			GLuint getVAO();
			GLuint getNormalBuffer();

			void setName(std::string _name);
			void setMaterial(Material* _mtl);

			std::string getName();
		Object();
		// Object(vec3 pos)
		virtual ~Object();
	};
}

#endif // OBJECT_H