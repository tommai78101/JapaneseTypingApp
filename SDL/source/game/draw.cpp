#include "draw.h"

Draw::Draw(Game* game, float scale = 1.0f) {
	this->game = game;
	this->gameSurface = nullptr;
	this->gameTexture = nullptr;
	this->drawScale = scale;

	//Setting up the game surface
	SDL_Surface* surface = this->game->GetSurface();
	if (surface) {
		this->SetSurface(surface);
	}

	//Setting up the game texture
	if (this->gameSurface) {
		this->game->SetTexture(SDL_CreateTextureFromSurface(this->game->GetGameRenderer(), this->gameSurface));
	}
}

Draw::~Draw() {
	if (this->pixels) {
		this->pixels = nullptr;
	}
	if (this->gameSurface) {
		SDL_FreeSurface(this->gameSurface);
		this->gameSurface = nullptr;
	}
	if (this->gameTexture) {
		SDL_DestroyTexture(this->gameTexture);
		this->gameTexture = nullptr;
	}
}

void Draw::Update() {
}

void Draw::Render() {
	if (this->gameTexture) {
		SDL_Renderer* renderer = this->game->GetGameRenderer();
		SDL_RenderCopy(renderer, this->gameTexture, nullptr, nullptr);
		//SDL_RenderPresent(renderer);
	}
}

bool Draw::GetPixel(size_t x, size_t y, uint32_t* outPixel) {
	if (this->gameSurface) {
		this->pixels = static_cast<uint32_t*>(this->gameSurface->pixels);
		*outPixel = this->pixels[(y * this->gameSurface->w) + x];
		return true;
	}
	return false;
}

bool Draw::SetPixel(size_t x, size_t y, uint32_t color) {
	if (this->gameSurface && this->pixels) {
		this->pixels[(y * this->gameSurface->w) + x] = color;
		return true;
	}
	return false;
}

float Draw::GetScale() const {
	return this->drawScale;
}

void Draw::SetScale(float value) {
	this->drawScale = value;
}

SDL_Rect* Draw::GetDestinationRect() const {
	return nullptr;
}

SDL_Surface* Draw::GetSurface() const {
	return this->gameSurface;
}

void Draw::SetSurface(SDL_Surface* surface = nullptr) {
	this->gameSurface = surface;
}

SDL_Texture* Draw::GetTexture() const {
	return this->gameTexture;
}

void Draw::SetTexture(SDL_Texture* texture = nullptr) {
	this->gameTexture = texture;
}