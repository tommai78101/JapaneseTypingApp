#ifndef DRAW_H_
#define DRAW_H_

//TODO(Thompson): Move Draw to a single class that handles all of the blitting to the surface.
//In other words, Draw class handles everything that we need to access for drawing stuffs to the surface.
//Move the SDL_Surface from game, and place it here. Move the texture to the Game.

#include <SDL.h>

#include "game.h"

class Game;

class Draw {
protected:
	uint32_t* pixels;
	SDL_Surface* gameSurface;

public:
	Draw(int scale);
	~Draw();

	void Update();
	void Render();

	int GetScale() const;
	uint32_t GetPixel(int x, int y);
	void SetPixel(int x, int y, uint32_t color);
	void SetSurface(SDL_Surface* surface);
	SDL_Surface* GetSurface() const;
	SDL_Rect* GetDestinationRect() const;
};

#endif
