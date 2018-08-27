#include "SdlImage.h"
#include <string>
#include <SDL2/SDL_image.h>

SdlImage::SdlImage(const std::string &filename, SDL_Renderer* renderer)
    : renderer(renderer) {
	this->texture = loadTexture(filename);
}

SdlImage::~SdlImage() {
	// TODO LIBERAR MEMORIA
}

SDL_Texture* SdlImage::getTexture() const {
	return this->texture;
}

SDL_Texture* SdlImage::loadTexture(const std::string &filename) {
	SDL_Texture* texture = IMG_LoadTexture(this->renderer,
										   filename.c_str());
	if (!texture) {
		throw "IMG_LoadTexture: No se pudo cargar la imagen ";
	}
	return texture;
}
