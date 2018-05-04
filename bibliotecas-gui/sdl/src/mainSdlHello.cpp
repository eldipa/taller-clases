#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include "SdlWindow.h"
#include "SdlTexture.h"

int main(int argc, char** argv){
    try {
        SdlWindow window(800, 600);
        window.fill();
        // Usar factory
        SdlTexture im("cat.gif", window);
        Area srcArea(0, 0, 300, 300);
        window.renderTexture(im.getTexture(), srcArea, destArea);
        window.render();
        SDL_Delay(3000);
}
