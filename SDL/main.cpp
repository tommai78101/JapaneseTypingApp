#include <SDL.h>
#include <iostream>
#include <Windows.h>

#include "game/game.h"


#if _WIN32
#  undef main
#endif

int main(int c, char* v[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	Game game;
	game.Initialize("Hello world.");
	game.GameLoop();
	return 0;
}