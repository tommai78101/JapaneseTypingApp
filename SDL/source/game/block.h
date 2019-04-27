#pragma once

#ifndef __BLOCK_H__
#	define __BLOCK_H__

#include "common.h"

class Object {
private:
	bool isActive = false;

protected:
	Vector2D oldVelocity = { 0.0f };
	Vector2D currentVelocity = { 0.0f };
	Vector2D oldPosition = { 0.0f };
	Vector2D currentPosition = { 0.0f };

public:
	//Public functions
	void Calculate(Vector2D desiredVelocity);
	void ApplyGravity();

	//Getters
	Vector2D GetVelocity() const;
	Vector2D GetPosition() const;
	bool IsActive() const;

	//Setters
	void SetVelocity(Vector2D velocity);
	void SetPosition(Vector2D position);
	void SetActive(bool value);
};

class Block : public Object {
protected:
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
	bool affectedByGravity = true;
	SDL_Color color = {};
	SDL_Surface* blockSurface = nullptr;
	SDL_Surface* glyph = nullptr;
	SDL_Texture* blockTexture = nullptr;
	SDL_Texture* glyphTexture = nullptr;
	TTF_Font* font = nullptr;

	void SetPixel(int x, int y, uint32_t color);
	uint32_t GetPixel(int x, int y);
	void Update();
	void FixedUpdate();
	void Render();
	void ReplaceGlyph(char* str);
};






#endif