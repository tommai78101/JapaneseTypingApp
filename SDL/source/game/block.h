#pragma once

#ifndef __BLOCK_H__
#	define __BLOCK_H__

#include "common.h"

class Block {
protected:
	int positionX = 0;
	int positionY = 0;
	int characterWidth = 0;
	int characterHeight = 0;
	SDL_Renderer* gameRenderer;
public:
	static const int BlockSize = 50;	//Width and height. It's a square.

	//Block(SDL_Renderer* gameRenderer, TTF_Font* font, wchar_t* character);
	//Block(SDL_Renderer* gameRenderer, TTF_Font* font, Uint16* str);
	Block(SDL_Renderer* gameRenderer, TTF_Font* font, char* str);
	~Block();
	void* pixels = nullptr;
	SDL_Color color = {};
	SDL_Surface* blockSurface = nullptr;
	SDL_Surface* glyph = nullptr;
	SDL_Texture* blockTexture = nullptr;
	SDL_Texture* glyphTexture = nullptr;
	TTF_Font* font = nullptr;

	void SetPixel(int x, int y, uint32_t color);
	uint32_t GetPixel(int x, int y);
	void Update(int newX, int newY);
	void Render();
	void ReplaceGlyph(char* str);
};






#endif