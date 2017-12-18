#include "input.h"

void InitializeGlyphMap(std::map<std::vector<SDL_Keycode>, char*>& glyphMap) {
	//Length of key determines the paired value.
	std::vector<SDL_Keycode> key1;
	std::vector<SDL_Keycode> key2;
	std::vector<SDL_Keycode> key3;

	//あ
	key1.push_back(SDLK_a);
	glyphMap.insert(std::pair<std::vector<SDL_Keycode>, char*>(key1, u8"あ"));
	key1.clear();

	//い
	key1.push_back(SDLK_i);
	glyphMap.insert(std::pair<std::vector<SDL_Keycode>, char*>(key1, u8"い"));
	key1.clear();

	//う
	key1.push_back(SDLK_u);
	glyphMap.insert(std::pair<std::vector<SDL_Keycode>, char*>(key1, u8"う"));
	key1.clear();

	//え
	key1.push_back(SDLK_e);
	glyphMap.insert(std::pair<std::vector<SDL_Keycode>, char*>(key1, u8"え"));
	key1.clear();

	//お
	key1.push_back(SDLK_o);
	glyphMap.insert(std::pair<std::vector<SDL_Keycode>, char*>(key1, u8"お"));
	key1.clear();

	////か
	//*key2 = { SDLK_k, SDLK_a };
	//glyphMap.insert(std::pair<SDL_Keycode*, Uint16*>(key2, Convert(L"か")));

	////き
	//*key2 = { SDLK_k, SDLK_i };
	//glyphMap.insert(std::pair<SDL_Keycode*, Uint16*>(key2, Convert(L"き")));

	////りゅ
	//*key3 = { SDLK_r, SDLK_y, SDLK_u };
	//glyphMap.insert(std::pair<SDL_Keycode*, Uint16*>(key3, Convert(L"りゅ")));
}

Input::Input(Game* game) {
	//Initializes the token reader.
	this->tokens.reserve(Input::MaxTokenSize);

	//Initializes the glyph map.
	InitializeGlyphMap(this->glyphMap);

	//Set a reference to Game object.
	this->game = game;
}

Input::~Input() {
	while (!this->tokens.empty()) {
		this->tokens.pop_back();
	}
}

void Input::HandleValidInputs(SDL_Keycode inputCode) {
	assert(inputCode >= SDLK_a);
	assert(inputCode <= SDLK_z);
	if (this->tokens.size() < Input::MaxTokenSize){
		this->tokens.push_back(inputCode);
		if (this->tokens.size() >= Input::MaxTokenSize) {
			std::cout << "Too many tokens, auto-confirming!" << std::endl;
			this->ConfirmToken();
		}
	}
}

void Input::ConfirmToken() {
	//This is fired when the user presses the Enter key to confirm the entered inputs.
	std::map<std::vector<SDL_Keycode>, char*>::iterator it;
	if ((it = this->glyphMap.find(this->tokens)) != this->glyphMap.end()) {
		//Found
		this->game->GetBlock()->ReplaceGlyph(u8"い");
	}
	else {
		std::cout << "Not found! " << std::endl;
	}
	this->tokens.clear();
}