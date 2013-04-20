#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "Camera.h"
#include "Object.h"
#include "Material.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "MaterialManager.h"
#include "Singleton.h"

//#define Supervisor SupervisorClass::getSingleton()

namespace Swift {
	class SupervisorClass/* : public Singleton<SupervisorClass>*/ {
		private:
			Camera* cam;
			//ObjectManager* objMan;
			//MaterialManager* matMan;
		public:
			Camera* getDefaultCamera();
			void setCamera(Camera* newCam);
			Object* getObject();
			void addObject(Object* obj);
			
			// GPU info
			std::string getRenderer();
			std::string getOpenGLversion();
			std::string getVendor();
			std::string getShaderLanguageVersion();
		SupervisorClass();
		//Supervisor(Camera* newCam, ObjectManager* newObjMan, MaterialManager* newMatMan);
		~SupervisorClass();
	};

	/*
		I know, I'm gonna buuuuurn soooo long in Hell for this. But I can't do it the other way, sorry ;_;
		Blame the Devil, not me.
	*/
	typedef Singleton<SupervisorClass> SupervisorC;
	#define Supervisor SupervisorC::getSingleton()


}

#endif // SUPERVISOR_H