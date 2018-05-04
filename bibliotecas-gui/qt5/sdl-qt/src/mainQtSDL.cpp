#include <QApplication>
#include <iostream>
#include "MainWindow.h"
#include "SdlWindow.h"
#include "SdlImage.h"

class SDL_Renderer;
class SDL_Texture;

int main(int argc, char *argv[]) {
    // Clase que contiene el loop principal
    QApplication app(argc, argv);
    // Instancio la ventana principal
    MainWindow window;
    window.show();
    unsigned int winId = window.getWinId();
    std::cout << "WinId: " << winId << std::endl;
    if (!winId) {
        return -1;
    }
    // HOLY SHIT, SDL!
    SdlWindow sdlWindow((void*) &winId);
    sdlWindow.fill(0x33,0x66,0x99, 0xFF);
    sdlWindow.render();
    SDL_Renderer* renderer = sdlWindow.getRenderer();
    try {
        SdlImage im("cat.gif", renderer);
        Area srcArea(0, 0, 300, 300);
        Area destArea(50, 50, 300, 300);
        sdlWindow.renderTexture(im.getTexture(), srcArea, destArea);
        sdlWindow.render();
    } catch (const char* e) {
        std::cout << "Reventó SDL: " << e << std::endl;
    }
    // Arranca el loop de la UI
    return app.exec();
}

