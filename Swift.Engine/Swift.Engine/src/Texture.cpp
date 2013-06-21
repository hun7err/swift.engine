#include "../include/Texture.h"
#include "../include/TextureManager.h"
#include <cstring>

namespace Swift {
	TexturePtr::TexturePtr() {
	}

	TexturePtr::TexturePtr(unsigned int _key) {
		key = _key;
	}

	Texture TexturePtr::operator*() {
		return TextureManager->getTexture(key);
	}

	Texture* TexturePtr::operator->() {
		return &(TextureManager->getTexture(key));
	}

	void TexturePtr::destroy() {
		TextureManager->destroy(*this);
	}

	Texture::Texture() {
		ilGenImages(1, &image);
		ilBindImage(image);
		ilDefaultImage();
	}

	Texture::Texture(const char *_name) {
		//printf("ilGenImages()\n");
		ilGenImages(1, &image);

		ILenum Error;
		Error = ilGetError();
		//printf("Error: %d\n", Error);
		//printf("image = %d\n", image);
		//printf("loadImage(%s)\n", _name);
		loadImage(_name);
	}

	Texture::~Texture() {
		destroy();
	}

	ILuint Texture::getImageID(void) {
		return image;
	}

	ILubyte* Texture::getImageData() {
		//printf("getImageData(), image = %d\n", image);
		ilBindImage(image);
		return ilGetData();
	}

	bool Texture::loadImage(const char *_name) {
		glGenTextures(1, &TexID);
		glBindTexture(GL_TEXTURE_2D, TexID);

		//printf("allocating memory block for name\n");
		name = (char*)malloc(strlen(_name)+1);
		//printf("copying name\n");
		strcpy(name, _name);
		//printf("binding image...\n");
		ilBindImage(image);
		//printf("done!\n");
		bool ret = ilLoadImage(name);
		//printf("image loaded\n");
		if(ret) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_BGR, GL_UNSIGNED_BYTE, getImageData());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_NEAREST
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		return ret;
	}

	void Texture::destroy() {
		ilDeleteImages(1, &image);
	}

	std::string Texture::getName() {
		return std::string(name);
	}

	bool TexturePtr::operator== (const TexturePtr& tex) {
		return tex.key == key;
	}

	bool TexturePtr::operator!= (const TexturePtr& tex) {
		return tex.key != key;
	}
}