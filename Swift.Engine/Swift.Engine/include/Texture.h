#ifndef TEXTURE_H
#define TEXTURE_H

#include <IL/il.h>
#include "Defines.h"
#include <string>

namespace Swift {
	class Texture {
		private:
			ILuint image;
			char *name;
		public:
			std::string getName();
			bool loadImage(const char *_name);
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
			Texture operator-> ();
			void destroy();
		TexturePtr(unsigned int _key);
		TexturePtr();
	};
}

#endif // TEXTURE_H