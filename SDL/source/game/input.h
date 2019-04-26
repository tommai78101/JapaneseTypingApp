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
private:
	//Thread related functions
	void InputTask(char* value);

protected:
	std::set<std::string> hiragana;
	std::set<std::string> katakana;
	std::vector<SDL_Keycode> tokens;
	std::string tokenString;
	KeyCodeTrie hiraganaTrie;
	KeyCodeTrie katakanaTrie;
	bool isHiraganaInput = true;
	bool isDirty = true;
	bool isIncorrect = false;
	Game* game;

	//Inputbox properties
	int boxWidth;
	int boxHeight;
	SDL_Rect inputboxPosition;
	SDL_Rect tokensDestination;
	SDL_Rect glyphsDestination;
	SDL_Surface* tokenSurface = nullptr;
	SDL_Texture* tokenTexture = nullptr;
	SDL_Surface* glyphSurface = nullptr;
	SDL_Texture* glyphTexture = nullptr;

public:
	static const int MaxTokenSize = 4;

	Input(Game* game);
	~Input();

	bool HandleValidInputs(SDL_Keycode inputCode);
	void ConfirmToken();
	void ClearTokens();
	void Update();
	void Render();

	//Game related functions
	void UpdateTokens();
	void UpdateGlyphs(char* value);

	//Setters/Getters
	void SwapInputType();
	bool CheckInputType() const;
	std::set<std::string> GetCharacterGlyphs(bool isHiragana);

	std::vector<SDL_Keycode>* GetTokens();
};

#endif