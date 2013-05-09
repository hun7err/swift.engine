#ifdef English_doc
/**
	\file Supervisor.h
	\brief Contains a definition of the supervisor class that gives access to most important headers and to some most important functions that could not be located anywhere else
*/
#endif
#ifdef Polski_doc
/**
	\file Supervisor.h
	\brief Zawiera definicję klasy nadzorcy która daje dostęp do najważniejszych nagłówków i najważniejszych funkcji, których nie dało się wrzucić nigdzie indziej
*/
#endif

#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "Camera.h"
#include "Object.h"
#include "Material.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "MaterialManager.h"
#include "Singleton.h"

namespace Swift {


	#ifdef Polski_doc
	/**
		\class Supervisor
		\brief Klasa-singleton, która pozwala na dostęp do funkcji ogólnych (sprawdzenie wersji itp.) + daje dostęp do innych singletonów (ObjectManager, MaterialManager itp.) 
	*/
	#endif

	class SupervisorClass {
		public:			
			// GPU info
			#ifdef Polski_doc
			/** Zwraca renderer (czyli najczęściej nazwę GPU) jako std::string */
			#endif
			std::string getRenderer();
			
			#ifdef Polski_doc
			/** Zwraca wersję OpenGL jako std::string */
			#endif
			std::string getOpenGLversion();
			
			#ifdef Polski_doc
			/** Zwraca producenta GPU jako std::string */
			#endif
			std::string getVendor();

			#ifdef Polski_doc
			/** Zwraca wersję języka shaderów OpenGL (GLSL) jako std::string */
			#endif
			std::string getShaderLanguageVersion();

		#ifdef Polski_doc
		/** Domyślny konstruktor klasy (w sumie to nie robi nic, ale może kiedyś coś będzie robił) */
		#endif
		SupervisorClass();
		
		#ifdef Polski_doc
		/** Domyślny destruktor klasy (zastosowanie jak konstruktora - póki co żadne) */
		#endif
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