#pragma once

#ifndef __BLOCK_H__
#	define __BLOCK_H__

#include "common.h"
#include "game.h"

class Object {
private:
	bool isActive = false;
	bool isHidden = false;
	bool isHit = false;
	bool isMoving = false;

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
	bool IsHidden() const;
	bool IsHit() const;
	bool IsMoving() const;

	//Setters
	void SetVelocity(Vector2D velocity);
	void SetPosition(Vector2D position);
	void SetPosition(float x, float y);
	void SetActive(bool value);
	void SetHidden(bool value);
	void SetHit(bool value);
	void SetMovingFlag(bool value);
};

class Block : public Object {
protected:
	int characterWidth = 0;
	int characterHeight = 0;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> gameRenderer{nullptr, SDL_DestroyRenderer};
	char glyphsValue[8] = {};
	Game* game = nullptr;
	int blockLength = 0;
	int totalWidth = 0;
	int rowNumber = -1;
	volatile bool affectedByGravity = true;
	volatile bool isAtBoundary = false;

public:
	static const int BlockSize = 50;	//Width and height. It's a square.

	//Block(SDL_Renderer* gameRenderer, TTF_Font* font, wchar_t* character);
	//Block(SDL_Renderer* gameRenderer, TTF_Font* font, Uint16* str);
	Block(Game* game, TTF_Font* font, char* str);
	Block(Block* block);
	~Block();
	void* pixels = nullptr;
	SDL_Color color = {};
	SDL_Surface* blockSurface = nullptr;
	SDL_Surface* glyph = nullptr;
	SDL_Texture* blockTexture = nullptr;
	SDL_Texture* glyphTexture = nullptr;
	TTF_Font* font = nullptr;

	// Setters/Getters
	void SetPixel(int x, int y, uint32_t color);
	uint32_t GetPixel(int x, int y);
	char* GetGlyphValue() const;
	int GetBlockLength() const;
	int GetBlockWidth() const;
	int GetCharacterWidth() const;
	int GetBlockRenderWidth() const;
	std::shared_ptr<Block> GetLeftBlock();
	std::shared_ptr<Block> GetRightBlock();
	void SetRowNumber(int row);
	int GetRowNumber() const;
	bool IsAffectedByGravity() const;
	void SetBoundaryFlag(bool value);
	bool GetBoundaryFlag() const;

	// Methods
	void Update();
	void FixedUpdate();
	void Render();
	void ReplaceGlyph(char* str);
	void ReplaceGlyph(const char* str);
	void TypedAway();
	void TurnOnGravity();
};






#endif