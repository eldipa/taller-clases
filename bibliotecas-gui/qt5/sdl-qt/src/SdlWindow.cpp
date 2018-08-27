#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "SdlWindow.h"
#include <iostream>

SdlWindow::SdlWindow(void* winId) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    //int errCode = SDL_VideoInit(nullptr);
    if (errCode) {
        std::cerr << "Error en la inicialización: " << SDL_GetError() << std::endl;
    }
    this->window = SDL_CreateWindowFrom(winId);
    if (!this->window) {
        std::cerr << "Error en createWindow:" << SDL_GetError() << std::endl;
    }
    this->renderer = SDL_CreateRenderer(
        this->window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->renderer) {
        std::cerr << "Error en createRenderer:" << SDL_GetError() << std::endl;
    }
    std::cout << "Window: " << this->window << std::endl;
    std::cout << "Renderer: " << this->renderer << std::endl;
}

SdlWindow::SdlWindow(int width, int height) :
        width(width), height(height) {
    SDL_CreateWindowAndRenderer(width,
                                height,
                                SDL_RENDERER_SOFTWARE,
                                &this->window,
                                &this->renderer);
}


SdlWindow::~SdlWindow() {
    std::cout << "Destruyendo" << std::endl;
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
}

void SdlWindow::renderTexture(SDL_Texture* textura_sdl,
    const Area& fuente,
    const Area& destino) {
    SDL_Rect sdlSrc = {
            fuente.getX(), fuente.getY(),
            fuente.getWidth(), fuente.getHeight()
    };
    SDL_Rect sdlDest = {
            destino.getX(), destino.getY(),
            destino.getWidth(), destino.getHeight()
    };

    SDL_RenderCopy(this->renderer,
                   textura_sdl,
                   &sdlSrc,
                   &sdlDest);
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer,
                           r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() {
    this->fill(0x33,0x33,0x33,0xFF);
}

void SdlWindow::render() {
    SDL_RenderPresent(this->renderer);
}


SDL_Renderer* SdlWindow::getRenderer() const {
    return this->renderer;
}
