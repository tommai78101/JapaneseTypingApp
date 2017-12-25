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
	std::string tokenString;
	Trie hiraganaTrie;
	Trie katakanaTrie;
	bool isHiraganaInput = true;
	Game* game;

	//Inputbox properties
	int boxWidth;
	int boxHeight;
	SDL_Rect inputboxPosition;
	SDL_Rect tokensDestination;
	SDL_Surface* tokenGlyph;
	SDL_Texture* tokenTexture;
	bool isDirty;
	bool isIncorrect;

public:
	static const int MaxTokenSize = 4;

	Input(Game* game);
	~Input();

	void HandleValidInputs(SDL_Keycode inputCode);
	void ConfirmToken();
	void ClearTokens();
	void Update();
	void Render();

	//Setters/Getters
	void SwapInputType();
	bool CheckInputType() const;

	std::vector<SDL_Keycode>* GetTokens();
};

#endif