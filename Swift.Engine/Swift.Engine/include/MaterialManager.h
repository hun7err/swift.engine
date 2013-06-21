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
#include <vector>
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
			std::vector<Material> materials;
			std::map<std::string, GLuint> programs;
		public:
			int loadMtl(const char *filename);
			int loadShaders(std::string shader_name);
			unsigned int getProgram(std::string name);
			unsigned int getMaterialCount(void);
			Material getMaterial(unsigned int key);
			MaterialPtr getMaterialByName(std::string name);
			MaterialPtr addMaterial(Material mtl);
		MaterialManagerClass();
		~MaterialManagerClass();
	};

	typedef Singleton<MaterialManagerClass> MaterialManagerC;
}

#endif // MATERIALMANAGER_H