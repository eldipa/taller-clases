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
        Area destArea(100, 100, 300, 300);
        im.render(srcArea, destArea);
        window.render();
        SDL_Delay(3000);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
