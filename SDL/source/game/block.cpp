﻿#include "block.h"

//---------  Object class definitions and functions.  --------------

void Object::Calculate(Vector2D desiredVelocity) {
	//Semi-implicit Euler function for velocity and position.
	this->currentVelocity = this->oldVelocity * (1 - Game::deltaTime) + desiredVelocity * Game::deltaTime;
	this->oldVelocity = this->currentVelocity;
	this->currentPosition = this->oldPosition + (this->currentVelocity * Game::deltaTime);
	this->oldPosition = this->currentPosition;
}

Vector2D Object::GetVelocity() const {
	return this->currentVelocity;
}

Vector2D Object::GetPosition() const {
	return this->currentPosition;
}

bool Object::IsActive() const {
	return this->isActive;
}

void Object::SetVelocity(Vector2D velocity) {
	this->oldVelocity = velocity;
	this->currentVelocity = velocity;
}

void Object::SetPosition(Vector2D position) {
	this->oldPosition = position;
	this->currentPosition = position;
}

void Object::SetPosition(float x, float y) {
	Vector2D pos{ x, y };
	this->oldPosition = pos;
	this->currentPosition = pos;
}

void Object::SetActive(bool value) {
	this->isActive = value;
}

void Object::ApplyGravity() {
	Vector2D gravity{ 0.0f, 1.0f };
	this->Calculate(gravity * Game::gravity);
}

//---------  Block class definitions and functions.  --------------

//Block::Block(SDL_Renderer* gameRenderer, TTF_Font* font, Uint16* str) {
//	this->blockSurface = SDLHelper_CreateSurface(this->BlockSize, this->BlockSize, 32);
//
//	//Block class properties
//	this->pixels = this->blockSurface->pixels;
//	this->gameRenderer = gameRenderer;
//	this->blockTexture = SDL_CreateTextureFromSurface(this->gameRenderer, this->blockSurface);
//	this->positionX = 0;
//	this->positionY = 0;
//	this->color = {};
//	TTF_SizeUNICODE(font, str, &this->characterWidth, &this->characterHeight);
//	this->glyph = TTF_RenderUNICODE_Solid(font, str, this->color);
//	//TTF_RenderUTF8_Solid(font, L"い", this->color);
//	this->glyphTexture = SDL_CreateTextureFromSurface(gameRenderer, this->glyph);
//}

Block::Block(SDL_Renderer* gameRenderer, TTF_Font* font, char* str) {
	//Initialized by parameter arguments.
	this->gameRenderer = gameRenderer;
	this->font = font;
	this->ReplaceGlyph(str);

	//Block class properties initialized using other methods.
	this->blockSurface = SDLHelper_CreateSurface(this->BlockSize, this->BlockSize, 32);
	this->pixels = this->blockSurface->pixels;
	this->blockTexture = SDL_CreateTextureFromSurface(this->gameRenderer, this->blockSurface);

	//By default, this block should be affected by gravity.
	this->affectedByGravity = true;
}

Block::~Block() {
	if (this->glyph) {
		SDL_FreeSurface(this->glyph);
		this->glyph = nullptr;
	}
	if (this->blockSurface) {
		SDL_FreeSurface(this->blockSurface);
		this->blockSurface = nullptr;
	}
	if (this->blockTexture) {
		SDL_DestroyTexture(this->blockTexture);
		this->blockTexture = nullptr;
	}
}

void Block::SetPixel(int x, int y, uint32_t color) {
	if (this->blockSurface) {
		uint32_t* temp = static_cast<uint32_t*>(this->pixels);
		temp[(y * this->blockSurface->w) + x] = color;
	}
}

uint32_t Block::GetPixel(int x, int y) {
	if (this->blockSurface) {
		uint32_t* temp = static_cast<uint32_t*>(this->pixels);
		return temp[(y * this->blockSurface->w) + x];
	}
	return -1;
}

void Block::Update() {
	//If it's inactive, don't update.
	if (!this->IsActive())
		return;
}

void Block::FixedUpdate() {
	//If it's inactive, don't update.
	if (!this->IsActive())
		return;

	if (this->affectedByGravity) {
		Object::ApplyGravity();
	}
	else {
		//We don't do anything about the block for now.
	}
}

void Block::Render() {
	//If it's inactive, don't render anything.
	if (!this->IsActive())
		return;

	//Get paddings in order to center align the text in the rectangle.
	int paddingWidth = std::abs(this->BlockSize - this->characterWidth) / 2;
	int paddingHeight = std::abs(this->BlockSize - this->characterHeight) / 2;

	//First, we draw the font glyphs.
	SDL_Rect fontDestination = { ((int) this->currentPosition.x) + paddingWidth, ((int) this->currentPosition.y) + paddingHeight, this->characterWidth, this->characterHeight };
	SDL_RenderCopy(this->gameRenderer, this->glyphTexture, nullptr, &fontDestination);

	//Second, we draw a rectangle (square), depending on the width of the character glyph.
	SDL_SetRenderDrawColor(this->gameRenderer, 0, 0, 255, 255);

	//Struct object initialization
	SDL_Rect r = {
		(int) this->currentPosition.x,			//absolute left
		(int) this->currentPosition.y,			//absolute top
		Block::BlockSize,								//width
		Block::BlockSize								//height
	};
	SDL_RenderDrawRect(this->gameRenderer, &r);

	//Always reset the color after use.
	SDL_SetRenderDrawColor(this->gameRenderer, 255, 255, 255, 255);

	SDL_Rect destination = {(int) this->currentPosition.x, (int) this->currentPosition.y, this->BlockSize, this->BlockSize};
	SDL_RenderCopy(this->gameRenderer, this->blockTexture, nullptr, &destination);
}

void Block::ReplaceGlyph(char* str) {
	if (this->glyph) {
		SDL_FreeSurface(this->glyph);
	}
	if (this->glyphTexture) {
		SDL_DestroyTexture(this->glyphTexture);
	}
	TTF_SizeUTF8(this->font, str, &this->characterWidth, &this->characterHeight);
	this->glyph = TTF_RenderUTF8_Solid(this->font, str, this->color);
	this->glyphTexture = SDL_CreateTextureFromSurface(this->gameRenderer, this->glyph);
}

void Block::ReplaceGlyph(const char* str) {
	this->ReplaceGlyph(const_cast<char*>(str));
}

