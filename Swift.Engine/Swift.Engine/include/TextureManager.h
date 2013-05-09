#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Texture.h"
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

#define TextureManager TextureManagerC::getSingleton()

namespace Swift {
	class TextureManagerClass {
		private:
			std::vector<Texture> textures;
		public:
			TexturePtr load(const char *name);
			void destroy(TexturePtr tex);
			Texture getTexture(unsigned int key);
			TexturePtr addTexture(Texture tex);
		TextureManagerClass();
		~TextureManagerClass();
	};

	typedef Singleton<TextureManagerClass> TextureManagerC;
}

#endif // TEXTUREMANAGER_H