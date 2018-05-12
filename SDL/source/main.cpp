#include "game/common.h"

//#ifndef __SWITCH__
//#	ifdef _WIN32
//#		undef main
//#	endif
//#endif

int main(int c, char* v[]) {
#ifndef __SWITCH__
	try
	{
#endif
	//Allocate the program on the stack, so it is guaranteed to be cleared
	//The Game class constructor handles game-specific variable initializations.
	//600 = width of playing field
	//400 = 300 of playing field + 100 UI at the top.
	Game game(600, 400, "Hello world");

	//We need to initialize the thread here.
	game.InitializeThread();

	//Start the game loop.
	/*while (appletMainLoop()) {
		if (game.GameLoopTick())
			break;
	}*/
	game.GameEventLoop();
	//game.GameLoop();

#ifndef __SWITCH__
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		system("pause");
		return -1;
	}
#endif
	return 0;
}

//