#include "block.h"

Block::Block(SDL_Renderer* gameRenderer, TTF_Font* font, Uint16* str) {
	this->blockSurface = SDLHelper_CreateSurface(this->blockSize, this->blockSize, 32);

	//Block class properties
	this->pixels = this->blockSurface->pixels;
	this->gameRenderer = gameRenderer;
	this->blockTexture = SDL_CreateTextureFromSurface(this->gameRenderer, this->blockSurface);
	this->positionX = 0;
	this->positionY = 0;
	this->color = {};
	TTF_SizeUNICODE(font, str, &this->characterWidth, &this->characterHeight);
	this->glyph = TTF_RenderUNICODE_Solid(font, str, this->color);
	this->glyphTexture = SDL_CreateTextureFromSurface(gameRenderer, this->glyph);
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

void Block::Update(int newX, int newY) {
	this->positionX = newX;
	this->positionY = newY;
}

void Block::Render() {
	//Drawing a rectangle (square). Requires that the values are strictly in order of the struct object's members.
	//We set the draw color to blue.
	SDL_SetRenderDrawColor(this->gameRenderer, 0, 0, 255, 255);
	//Struct object initialization
	SDL_Rect r = {
		this->positionX,			//absolute left
		this->positionY,			//absolute top
		Block::blockSize,			//width
		Block::blockSize			//height
	};
	SDL_RenderDrawRect(this->gameRenderer, &r);

	//Always reset the color after use.
	SDL_SetRenderDrawColor(this->gameRenderer, 255, 255, 255, 255);

	SDL_Rect destination = {this->positionX, this->positionY, this->blockSize, this->blockSize};
	SDL_RenderCopy(this->gameRenderer, this->blockTexture, nullptr, &destination);

	//Get paddings in order to center align the text in the rectangle.
	int paddingWidth = std::abs(this->blockSize - this->characterWidth) / 2;
	int paddingHeight = std::abs(this->blockSize - this->characterHeight) / 2;

	//SDL_Rect fontDestination = { topLeftX + paddingWidth, topLeftY + paddingHeight, bottomRightX - paddingWidth, bottomRightY - paddingHeight };
	SDL_Rect fontDestination = { this->positionX + paddingWidth, this->positionY + paddingHeight, this->characterWidth, this->characterHeight };
	SDL_RenderCopy(this->gameRenderer, this->glyphTexture, nullptr, &fontDestination);
}