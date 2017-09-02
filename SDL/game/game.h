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

	int width;
	int height;
	int scale;
	int clearColor;
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
	void HandleInput();
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
