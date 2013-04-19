#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

/*
	pomys³:
	Swift::Supervisor z MaterialManagerem, ObjectManagerem itp.
	konstruktor np. Swift::Supervisor(new Camera(), new ObjectManager(), new MaterialManager())

	Swift::Supervisor
		setDefaultCamera()
		getDefaultCamera()
		objectManager()
		setObjectManager()
		addMaterial()
		addObject() -> wywo³uje ObjectManager::add()
		getObject() -> wywo³uje ObjectManager::get()
		setProperty()
		getPropertyValue()
		void renderLoop() -> tu bêdzie w pêtli wywo³ywane rysowanie na ekranie obiektów z ObjectManagera przez
			domyœlny renderer z domyœlnej kamery (Renderer powinien do metody render() pobieraæ Camera*
			z którego ma renderowaæ)
*/
// local
#include "Material.h"
// STL
#include <map>
#include <string>
// platform-specific
#ifdef _WIN32
	#include <Windows.h>
#endif // _WIN32
// OpenGL
#include <GL/GL.h>
#include "Singleton.h"

#define MaterialManager MaterialManagerC::getSingleton()

namespace Swift {
	class MaterialManagerClass/* : public Singleton<MaterialManager>*/ {
		private:
			std::map<std::string, Material*> materials;
			std::map<std::string, GLuint> shaders;
			// (lista shaderów jakaœ)
		public:
			// Material* get(std::string name)
			// void add(Material* mtl)
			// loadShader(vertex_shader_name, pixel_shader_name)
			void loadShader(std::string shader_name, std::string vertex_shader_name, std::string pixel_shader_name);
			unsigned int getShader(std::string name);
		MaterialManagerClass();
		~MaterialManagerClass();
	};

	typedef Singleton<MaterialManagerClass> MaterialManagerC;
}

#endif // MATERIALMANAGER_H