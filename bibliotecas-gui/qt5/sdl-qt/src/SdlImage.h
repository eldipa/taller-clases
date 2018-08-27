#ifndef __SDL_IMAGE_H__
#define __SDL_IMAGE_H__
#include <string>

class SDL_Texture;
class SDL_Renderer;

class SdlImage {
public:
	SdlImage(const std::string &filename, SDL_Renderer* renderer);
	~SdlImage();
	SDL_Texture* getTexture() const;
private:
	SDL_Texture* loadTexture(const std::string &filename);
	SDL_Renderer* renderer;
	SDL_Texture* texture;
};

#endif
