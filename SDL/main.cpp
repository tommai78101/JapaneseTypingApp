#include "game/game.h"

#if _WIN32
#  undef main
#endif

int main(size_t c, char* v[]) {
	try {
		//Allocate the program on the stack, so it is guaranteed to be cleared
		//The Game class constructor handles game-specific variable initializations.
		Game game;

		//Initialize the game, along with the title.
		game.Initialize("Hello world.");

		//Start the game loop.
		game.GameLoop();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	//Exit the game, and quit, then deallocate the Game object.
	//When Game object is de-allocated, the Game class destructor handles memory garbage collection.
	return 0;
}