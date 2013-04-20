#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

/*
	pomys�:
	Swift::Supervisor z MaterialManagerem, ObjectManagerem itp.
	konstruktor np. Swift::Supervisor(new Camera(), new ObjectManager(), new MaterialManager())

	Swift::Supervisor
		setDefaultCamera()
		getDefaultCamera()
		objectManager()
		setObjectManager()
		addMaterial()
		addObject() -> wywo�uje ObjectManager::add()
		getObject() -> wywo�uje ObjectManager::get()
		setProperty()
		getPropertyValue()
		void renderLoop() -> tu b�dzie w p�tli wywo�ywane rysowanie na ekranie obiekt�w z ObjectManagera przez
			domy�lny renderer z domy�lnej kamery (Renderer powinien do metody render() pobiera� Camera*
			z kt�rego ma renderowa�)
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
			// (lista shader�w jaka�)
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