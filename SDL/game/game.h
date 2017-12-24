#ifndef GAME_H_
#	define GAME_H_

#include "common.h"

class Input;
class Block;

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
	std::wstring inputString;

	//SDL stuffs
	SDL_Window* gameWindow;
	SDL_Renderer* gameWindowRenderer;
	SDL_Texture* mainTexture;
	SDL_Surface* gameSurface;

	//SDL_ttf stuffs
	int fontWidth = 0;
	int fontHeight = 0;
	int lineSkip = 0;
	TTF_Font* defaultFont;
	SDL_Texture* fontSurfaceSolid;
	SDL_Texture* fontSurfaceShaded;
	SDL_Texture* fontSurfaceBlended;

	//Subcomponents
	//Draw* drawSystem;
	Input* inputSystem;

	//Others
	Block* block;
	

public:
	static const int gravity = -1;

	Game(int newWidth, int newHeight);
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

	Input* GetInput();
	Block* GetBlock();

	void Clear();
};



#endif
