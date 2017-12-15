#pragma once

#ifndef __BLOCK_H__
#	define __BLOCK_H__

#include "common.h"

class Block {
protected:
	int positionX;
	int positionY;
	int characterWidth;
	int characterHeight;
	SDL_Renderer* gameRenderer;
public:
	static const int blockSize = 50;	//Width and height. It's a square.

	Block(SDL_Renderer* gameRenderer, TTF_Font* font, wchar_t* character);
	~Block();
	void* pixels;
	wchar_t character;
	SDL_Color color;
	SDL_Surface* blockSurface;
	SDL_Surface* glyph;
	SDL_Texture* blockTexture;
	SDL_Texture* glyphTexture;

	void SetPixel(int x, int y, uint32_t color);
	uint32_t GetPixel(int x, int y);
	void Update(int newX, int newY);
	void Render();
};






#endif