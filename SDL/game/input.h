#pragma once

#ifndef __INPUT_H__
#	define __INPUT_H__

#include "common.h"

/*
	Input system that holds the logic of determining the input SDL_Keycodes, piecing them
	together so the tokens maps up to the corresponding Japanese character.
*/

class Game;

class Input {
protected:
	std::vector<SDL_Keycode> tokens;
	//std::map<std::vector<SDL_Keycode>, char*> glyphMap;
	Trie glyphMap;
	Game* game;

public:
	static const int MaxTokenSize = 4;

	Input(Game* game);
	~Input();

	void HandleValidInputs(SDL_Keycode inputCode);
	void ConfirmToken();
	void ClearTokens();
};

#endif