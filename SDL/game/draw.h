#ifndef DRAW_H_
#define DRAW_H_

//TODO(Thompson): Move Draw to a single class that handles all of the blitting to the surface.
//In other words, Draw class handles everything that we need to access for drawing stuffs to the surface.
//Move the SDL_Surface from game, and place it here. Move the texture to the Game.

//TODO(Thompson): In Game class, have the Game class masize_tain a list of objects to pass to the Draw class, and update the objects individually as needed.
//Draw class should then iterate through the list of updated objects, and render them individually.

#include "common.h"

class Game;

class Draw {
protected:
	Game* game;
	uint32_t* pixels;
	float drawScale;
	SDL_Surface* gameSurface;
	SDL_Texture* gameTexture;

public:
	Draw(Game* game, float scale);
	~Draw();

	void Update();
	void Render();

	float GetScale() const;
	void SetScale(float value);

	//Fetches the pixel value and stores it in the outPixel. Returns true if succeeds. False, if otherwise.
	bool Draw::GetPixel(size_t x, size_t y, uint32_t* outPixel);
	//Sets the pixel value in the size_tended position. Returns true if succeeds. False, if otherwise.
	bool SetPixel(size_t x, size_t y, uint32_t color);

	void SetSurface(SDL_Surface* surface);
	SDL_Surface* GetSurface() const;

	void SetTexture(SDL_Texture* texture);
	SDL_Texture* GetTexture() const;

	SDL_Rect* GetDestinationRect() const;
};

#endif
