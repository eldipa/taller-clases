#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__
#include "Area.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class SdlWindow {
public:
    /**
     * Ctor para embeber en Qt
     */
    explicit SdlWindow(void* winId);
    /**
     * Ctor standalone
     */
    SdlWindow(int width, int height);
    ~SdlWindow();
    void renderTexture(SDL_Texture* textura_sdl,
        const Area& fuente,
        const Area& destino);
    void fill();
    void fill(int r, int g, int b, int alpha);
    void render();
    SDL_Renderer* getRenderer() const;
private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
