#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "ObjectPart.h"

namespace Swift {
	class Object {
		protected:
			std::string name;
			glm::vec3 origin;
			std::vector<ObjectPart> parts;
		public:
			GLfloat* getVertices();
			glm::vec3 getOrigin();
			unsigned int getVertexCount();
			ObjectPart& getPart(std::string alias);
			ObjectPart& getPartAt(unsigned int pos);

			void setName(std::string _name);
			unsigned int getPartCount();
			void setMaterial(MaterialPtr _mtl);
			void hide();
			void show();
			bool isVisible(void);

			std::string getName();

			void rotate(const glm::vec3& axis, float angle);
			// jeszcze pitch, yaw, roll!
			void move(const glm::vec3& newPos);
			void scale(const glm::vec3& factor);
		Object();
		virtual ~Object();
	};
}

#endif // OBJECT_H