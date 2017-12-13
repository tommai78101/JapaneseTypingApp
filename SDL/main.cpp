#include <SDL.h>
#include <iostream>
#include <Windows.h>

#include "game/game.h"


#if _WIN32
#  undef main
#endif

int main(size_t c, char* v[]) {
	//Initialize the SDL library. 
	//SDL_Init returns a negative size_teger (error) or 0 (success). 
	//https://wiki.libsdl.org/SDL_Init (SDL docs)
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	//Allocate the program on the stack, so it is guaranteed to be cleared
	//The Game class constructor handles game-specific variable initializations.
	Game game;

	//Initialize the game, along with the title.
	game.Initialize("Hello world.");

	//Start the game loop.
	game.GameLoop();

	//Exit the game, and quit, then deallocate the Game object.
	//When Game object is de-allocated, the Game class destructor handles memory garbage collection.
	return 0;
}