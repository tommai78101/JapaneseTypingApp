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
	std::wstring inputString;

	//Game Surface properties
	uint32_t* pixels;
	uint32_t pitch;

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
	VocabularyTrie kanjiTrie;
	
	//unistd.h specific variables
	FILE* dictionaryFile;
public:
	static const int gravity = -1;

	Game(int newWidth, int newHeight, std::string title);
	~Game();

	void Initialize(std::string title);
	bool IsWindowInitialized() const;
	void GameLoop();
	bool GameLoopTick();
	void HandleEvent();
	void HandleInput();
	void QuitGame();
	void Clear();

	virtual void Update();
	virtual void Render();
	void DrawPixel(uint32_t x, uint32_t y, uint32_t width, uint32_t color);

	//Getter/Setters
	size_t GetWidth() const;
	size_t GetHeight() const;
	SDL_Renderer* GetGameRenderer() const;
	TTF_Font* GetFont() const;

	SDL_Texture* GetTexture() const;
	void SetTexture(SDL_Texture* texture);

	SDL_Surface* GetSurface() const;
	void SetSurface(SDL_Surface* surface);

	void SetPixel(size_t x, size_t y, uint32_t color);
	uint32_t GetPixel(size_t x, size_t y);

	Input* GetInput();
	Block* GetBlock();
};



#endif
