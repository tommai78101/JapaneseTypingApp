#ifndef GAME_H_
#	define GAME_H_

#include <SDL.h>
#include <cstring>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#	include <Windows.h>
#elif defined _UNIX
#	include <unistd.h>
#endif

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
const int RED_MASK = 0xff000000;
const int GREEN_MASK = 0x00ff0000;
const int BLUE_MASK = 0x0000ff00;
const int ALPHA_MASK = 0x000000ff;
#else
const int RED_MASK = 0x000000ff;
const int GREEN_MASK = 0x0000ff00;
const int BLUE_MASK = 0x00ff0000;
const int ALPHA_MASK = 0xff000000;
#endif

#include "../game/draw.h"

class Draw;

class Game {
protected:
	int velocityX;
	int velocityY;
	int clearColor;

	int width;
	int height;
	int scale;
	bool quitFlag;
	uint32_t* pixels;
	SDL_Window* gameWindow;
	SDL_Renderer* gameWindowRenderer;
	SDL_Texture* mainTexture;
	SDL_Surface* gameSurface;

	Draw* drawSystem;

public:
	Game();
	~Game();

	void Initialize(std::string title);
	bool IsWindowInitialized() const;
	void GameLoop();
	void HandleEvent();
	void HandleInput(SDL_Keycode code);
	void QuitGame();

	virtual void Update();
	virtual void Render();

	//Getter/Setters
	int GetWidth() const;
	int GetHeight() const;
	SDL_Renderer* GetGameRenderer() const;

	SDL_Texture* GetTexture() const;
	void SetTexture(SDL_Texture* texture);

	SDL_Surface* GetSurface() const;
	void SetSurface(SDL_Surface* surface);

	void SetPixel(int x, int y, uint32_t color);
	uint32_t GetPixel(int x, int y);

	void Clear();
};



#endif
