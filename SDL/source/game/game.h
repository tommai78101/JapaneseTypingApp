#ifndef GAME_H_
#	define GAME_H_

#include "common.h"

class Input;
class Block;

class Game {
private:
	//Hidden game related data
	SDL_GLContext glContext = nullptr;
	std::thread renderingThread;
	std::mutex glyphStorageMutex;
	std::mutex tokenStorageMutex;
	void ThreadTask(Game* game);

protected:
	//Game input properties
	std::map<SDL_Scancode, bool> inputs;

	//Game object properties
	Vector2D position;
	Vector2D velocity;
	UpOrientation currentUpOrientation;
	std::vector<std::shared_ptr<Block>> hiraganaBlocks;
	std::vector<std::shared_ptr<Block>> katakanaBlocks;
	std::vector<std::shared_ptr<Block>> allBlocks;

	//Game properties
	size_t width;
	size_t height;
	size_t scale = 8;
	size_t clearColor;
	bool quitFlag = false;
	std::wstring inputString;

	//Game Surface properties
	uint32_t* pixels = nullptr;
	uint32_t pitch = 0;

	//SDL stuffs
	SDL_Window* gameWindow = nullptr;
	SDL_Renderer* gameWindowRenderer = nullptr;
	SDL_Texture* mainTexture = nullptr;
	SDL_Surface* gameSurface = nullptr;
	SDL_Thread* threadId = nullptr;

	//SDL_ttf stuffs
	int fontWidth = 0;
	int fontHeight = 0;
	int lineSkip = 0;
	TTF_Font* defaultFont = nullptr;
	SDL_Texture* fontSurfaceSolid = nullptr;
	SDL_Texture* fontSurfaceShaded = nullptr;
	SDL_Texture* fontSurfaceBlended = nullptr;

	//Subcomponents
	//Draw* drawSystem;
	Input* inputSystem = nullptr;

	//Others
	Block* block = nullptr;
	VocabularyTrie kanjiTrie;
	
	//unistd.h specific variables
	FILE* dictionaryFile = nullptr;

public:
	static const int gravity = -1;

	Game(int newWidth, int newHeight, std::string title);
	~Game();

	void Initialize();
	void InitializeThread();
	bool IsWindowInitialized() const;
	void GameLoop();
	void GameEventLoop();
	void HandleInput();
	void QuitGame();
	void Clear();

	virtual void Update();
	virtual void Render();
	void DrawPixel(uint32_t x, uint32_t y, uint32_t width, uint32_t color);

	//Game related functions
	void StoreGlyphs(char* value);

	//Getter/Setters
	size_t GetWidth() const;
	size_t GetHeight() const;
	SDL_Renderer* GetGameRenderer() const;
	TTF_Font* GetFont() const;
	std::vector<std::shared_ptr<Block>> GetHiraganaBlocks() const;
	std::vector<std::shared_ptr<Block>> GetKatakanaBlocks() const;
	std::vector<std::shared_ptr<Block>> GetAllBlocks() const;

	SDL_Texture* GetTexture() const;
	void SetTexture(SDL_Texture* texture);

	SDL_Surface* GetSurface() const;
	void SetSurface(SDL_Surface* surface);

	void SetPixel(size_t x, size_t y, uint32_t color);
	uint32_t GetPixel(size_t x, size_t y);

	Input* GetInput();
	//Block* GetBlock();
};



#endif
