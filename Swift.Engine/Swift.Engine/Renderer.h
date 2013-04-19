#ifndef RENDERER_H
#define RENDERER_H
#include "Camera.h"
#include "ObjectManager.h"

#define SW_WIREFRAME 0
#define SW_SOLID 1

namespace Swift {
	class Renderer {
		private:
			Camera* cam;
			//ObjectManager* objManager;
		public:
			void render();
			void setCamera(Camera* c);
			void setRenderMode(unsigned int mode);
			void clearColor(double r, double g, double b, double a);
		Renderer();
		//Renderer(ObjectManager* obj);
		~Renderer();
	};
}

#endif // RENDERER_H