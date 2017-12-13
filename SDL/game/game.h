#ifndef GAME_H_
#	define GAME_H_

#include <SDL.h>
#include <cstring>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>

#ifdef _WIN32
#	include <Windows.h>
#elif defined _UNIX
#	include <unistd.h>
#endif

#include "../game/common.h"
#include "../game/draw.h"

class Draw;

class Game {
protected:
	std::map<SDL_Scancode, bool> inputs;

	Vector2D position;
	Vector2D velocity;
	UpOrientation currentUpOrientation;

	size_t width;
	size_t height;
	size_t scale;
	size_t clearColor;
	bool quitFlag;
	uint32_t* pixels;
	SDL_Window* gameWindow;
	SDL_Renderer* gameWindowRenderer;
	SDL_Texture* masize_texture;
	SDL_Surface* gameSurface;

	Draw* drawSystem;

public:
	Game();
	~Game();

	void Initialize(std::string title);
	bool IsWindowInitialized() const;
	void GameLoop();
	void HandleEvent();
	void HandleInput();
	void QuitGame();

	virtual void Update();
	virtual void Render();

	//Getter/Setters
	size_t GetWidth() const;
	size_t GetHeight() const;
	SDL_Renderer* GetGameRenderer() const;

	SDL_Texture* GetTexture() const;
	void SetTexture(SDL_Texture* texture);

	SDL_Surface* GetSurface() const;
	void SetSurface(SDL_Surface* surface);

	void SetPixel(size_t x, size_t y, uint32_t color);
	uint32_t GetPixel(size_t x, size_t y);

	void Clear();
};



#endif
