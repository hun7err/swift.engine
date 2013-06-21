#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#ifdef _WIN32
	#include <Windows.h>
#endif // _WIN32
// OpenGL
#include <GL/GL.h>

#include <IL/il.h>
#include "Defines.h"
#include <string>

#define SW_TEXTURE_EMPTY TexturePtr(-1)

namespace Swift {
	class Texture {
		private:
			ILuint image;
			char *name;
		public:
			GLuint TexID;
			std::string getName();
			bool loadImage(const char *_name);
			ILuint getImageID(void);
			ILubyte* getImageData();
			void destroy();
		Texture();
		Texture(const char *_name);
		~Texture();
	};
	
	class TexturePtr {
		public:
			unsigned int key;
			Texture operator* ();
			Texture* operator-> ();
			bool operator== (const TexturePtr& tex);
			bool operator!= (const TexturePtr& tex);
			void destroy();
		TexturePtr(unsigned int _key);
		TexturePtr();
	};
}

#endif // TEXTURE_H