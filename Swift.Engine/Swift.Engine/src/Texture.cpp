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

	Texture TexturePtr::operator->() {
		return TextureManager->getTexture(key);
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
		ilGenImages(1, &image);
		loadImage(_name);
	}

	Texture::~Texture() {
		destroy();
	}

	ILubyte* Texture::getImageData() {
		ilBindImage(image);
		return ilGetData();
	}

	bool Texture::loadImage(const char *_name) {
		strcpy(name, _name);
		ilBindImage(image);
		bool ret = ilLoadImage(name);
		return ret;
	}

	void Texture::destroy() {
		ilDeleteImages(1, &image);
	}

	std::string Texture::getName() {
		return std::string(name);
	}
}