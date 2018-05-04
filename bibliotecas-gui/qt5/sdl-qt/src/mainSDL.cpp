#include <SDL2/SDL.h>
#include "SdlWindow.h"
#include "SdlImage.h"

int main(int argc, char** argv){
	SdlWindow window(400,400);
	window.fill();
	SDL_Renderer* renderer = window.getRenderer();
	SdlImage im("cat.gif", renderer);
    Area srcArea(0, 0, 300, 300);
	Area destArea(50, 50, 300, 300);
	window.renderTexture(im.getTexture(), srcArea, destArea);
	window.render();
	SDL_Delay(3000);
}
