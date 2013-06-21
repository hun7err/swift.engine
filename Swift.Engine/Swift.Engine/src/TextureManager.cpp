#include "../include/TextureManager.h"

namespace Swift {
	TexturePtr TextureManagerClass::load(const char *name) {
		Texture tex(name);
		textures.push_back(tex);
		return TexturePtr(textures.size()-1);
	}

	void TextureManagerClass::destroy(TexturePtr tex) {
		unsigned int key = tex.key;
		textures[key].destroy();
		textures.erase(textures.begin()+key);
	}

	Texture TextureManagerClass::getTexture(unsigned int key) {
		//printf("key = %d\n", key);
		return textures[key];
	}

	TexturePtr TextureManagerClass::addTexture(Texture tex) {
		textures.push_back(tex);
		return TexturePtr(textures.size()-1);
	}

	TextureManagerClass::TextureManagerClass() {
	}
	TextureManagerClass::~TextureManagerClass() {
		for(int i = 0; i < textures.size(); i++) {
			textures[i].destroy();
		}
		textures.clear();
	}
}