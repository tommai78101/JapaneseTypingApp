#ifndef GAME_H_
#	define GAME_H_

#include "../game/common.h"
#include "../game/draw.h"

class Draw;

class Game {
protected:
	//Game input properties
	std::map<SDL_Scancode, bool> inputs;

	//Game object properties
	Vector2D position;
	Vector2D velocity;
	UpOrientation currentUpOrientation;

	//Game properties
	size_t width;
	size_t height;
	size_t scale;
	size_t clearColor;
	bool quitFlag;
	uint32_t* pixels;

	//SDL stuffs
	SDL_Window* gameWindow;
	SDL_Renderer* gameWindowRenderer;
	SDL_Texture* masize_texture;
	SDL_Surface* gameSurface;

	//SDL_ttf stuffs
	TTF_Font* defaultFont;

	//Subcomponents
	Draw* drawSystem;

public:
	Game();
	~Game();

	void Initialize(std::string title);
	bool IsWindowInitialized() const;
	void GameLoop();
	void HandleEvent();
	void HandleInput();
	void QuitGame();

	virtual void Update();
	virtual void Render();

	//Getter/Setters
	size_t GetWidth() const;
	size_t GetHeight() const;
	SDL_Renderer* GetGameRenderer() const;

	SDL_Texture* GetTexture() const;
	void SetTexture(SDL_Texture* texture);

	SDL_Surface* GetSurface() const;
	void SetSurface(SDL_Surface* surface);

	void SetPixel(size_t x, size_t y, uint32_t color);
	uint32_t GetPixel(size_t x, size_t y);

	void Clear();
};



#endif
