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
			GLuint VBO;
			GLuint VAO;
			std::vector<GLfloat> vertices;
			std::string name;
			Material* mtl;
			void destroy();
			void setup();
		public:
			GLfloat* getVertices();
			Material* getMaterial();
			glm::mat4 getModelMatrix();
			glm::vec3 getPosition();
			unsigned int getVertexCount();
			void rotate(glm::vec3 axis, float angle);
			// jeszcze pitch, yaw, roll!
			void move(const glm::vec3& offset);
			// scale jeszcze!
			GLuint getVBO();
			GLuint getVAO();

			void setName(std::string _name);
			void setMaterial(Material* _mtl);

			std::string getName();
		Object();
		// Object(vec3 pos)
		virtual ~Object();
	};
}

#endif // OBJECT_H