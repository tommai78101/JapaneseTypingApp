#include "draw.h"

Draw::Draw(Game* game, int scale) {
	this->game = game;
}

Draw::~Draw() {
	if (this->pixels) {
		this->pixels = NULL;
	}
	if (this->gameSurface) {
		SDL_FreeSurface(this->gameSurface);
		this->gameSurface = NULL;
	}
}

void Draw::Update() {
}

void Draw::Render() {
	this->game->SetTexture(SDL_CreateTextureFromSurface(this->game->GetGameRenderer(), this->gameSurface));
}

uint32_t Draw::GetPixel(int x, int y) {
	if (this->gameSurface) {
		return this->pixels[(y * this->gameSurface->w) + x];
	}
	return -1;
}

void Draw::SetPixel(int x, int y, uint32_t color) {
	if (this->gameSurface) {
		this->pixels[(y * this->gameSurface->w) + x] = color;
	}
}

int Draw::GetScale() const {
	return 1;
}

SDL_Rect* Draw::GetDestinationRect() const {
	return NULL;
}

SDL_Surface* Draw::GetSurface() const {
	return this->gameSurface;
}

void Draw::SetSurface(SDL_Surface* surface) {
	this->gameSurface = surface;
	this->pixels = (uint32_t*) (this->gameSurface->pixels);
}