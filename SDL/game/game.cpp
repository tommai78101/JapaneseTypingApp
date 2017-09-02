#include "game.h"

Game::Game() : gameWindow(NULL), gameWindowRenderer(NULL), quitFlag(false), width(400), height(400), pixels(NULL), scale(8) {
	this->velocityX = 0;
	this->velocityY = 0;
	this->clearColor = 0x0;
	srand(static_cast<unsigned int>(time(NULL)));
}

Game::~Game() {
	this->pixels = NULL;
	if (this->gameSurface) {
		SDL_FreeSurface(this->gameSurface);
		this->gameSurface = NULL;
	}
	if (this->mainTexture) {
		SDL_DestroyTexture(this->mainTexture);
		this->mainTexture = NULL;
	}
	if (this->gameWindowRenderer) {
		SDL_DestroyRenderer(this->gameWindowRenderer);
		this->gameWindowRenderer = NULL;
	}
	if (this->gameWindow) {
		SDL_DestroyWindow(this->gameWindow);
		this->gameWindow = NULL;
	}
	SDL_Quit();
}

void Game::Initialize(std::string title) {
	SDL_DisplayMode currentDisplayMode;
	for (int i = 0; i < SDL_GetNumVideoDisplays(); i++) {
		int shouldBeZero = SDL_GetCurrentDisplayMode(i, &currentDisplayMode);
		if (shouldBeZero != 0) {
			std::cout << "Could not get display mode for video display " << i << ": " << SDL_GetError() << std::endl;
		}
		else {
			break;
		}
	}
	this->gameWindow = SDL_CreateWindow(title.c_str(), (currentDisplayMode.w - this->width) / 2, (currentDisplayMode.h - this->height) / 2, this->width, this->height, SDL_WINDOW_SHOWN);
	this->gameWindowRenderer = SDL_CreateRenderer(this->gameWindow, -1, SDL_RENDERER_ACCELERATED);
	this->gameSurface = SDL_CreateRGBSurface(0, this->width / this->scale, this->height / this->scale, 32, RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK);
	if (this->gameSurface == NULL) {
		std::cout << "SDL_CreateRGBSurface: " << SDL_GetError() << std::endl;
		this->QuitGame();
	}
	this->pixels = static_cast<uint32_t*>(this->gameSurface->pixels);
	this->mainTexture = SDL_CreateTextureFromSurface(this->gameWindowRenderer, this->gameSurface);
	if (this->mainTexture == NULL) {
		std::cout << "SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
		this->QuitGame();
	}
}

bool Game::IsWindowInitialized() const {
	return (this->gameWindow != NULL);
}

void Game::GameLoop() {
	uint64_t performanceCounterFrequency = SDL_GetPerformanceFrequency();
	uint64_t lastPerformanceCounter = SDL_GetPerformanceCounter();
	uint64_t currentPerformanceCounter = SDL_GetPerformanceCounter();
	SDL_SetRenderDrawColor(this->gameWindowRenderer, 0, 0, 0, 255);
	while (!this->quitFlag) {
		currentPerformanceCounter = SDL_GetPerformanceCounter();
		uint64_t counterElapsed = static_cast<uint64_t>((currentPerformanceCounter - lastPerformanceCounter) * 1000.0);
		//double millisecondsPerFrame = (1000.0 * (double) counterElapsed) / (double) performanceCounterFrequency;
		//double framesPerSecond = (double) performanceCounterFrequency / (double) counterElapsed;
		double counterElapsedBySecond = static_cast<double>(counterElapsed / performanceCounterFrequency);
		while (counterElapsedBySecond > 0.0) {
			this->Update();
			counterElapsedBySecond -= 1.0;
		}
		this->Render();
		this->HandleEvent();
		lastPerformanceCounter = currentPerformanceCounter;
		SDL_Delay(1);
	}
}

void Game::Update() {
	Clear();

	//Aggregate initialization. Requires the values is strictly in order of the struct's members.
	SDL_Rect r = {
		50, 50, 50, 50
	};

	SDL_SetRenderDrawColor(this->gameWindowRenderer, 0, 0, 255, 255);
	SDL_RenderDrawRect(this->gameWindowRenderer, &r);
	SDL_RenderPresent(this->gameWindowRenderer);
}

void Game::Render() {
	SDL_RenderClear(this->gameWindowRenderer);
	if (this->mainTexture) {
		SDL_DestroyTexture(this->mainTexture);
	}
	this->mainTexture = SDL_CreateTextureFromSurface(this->gameWindowRenderer, this->gameSurface);
	SDL_RenderCopy(this->gameWindowRenderer, this->mainTexture, NULL, NULL); //NULL: Use defaults.
	SDL_RenderPresent(this->gameWindowRenderer);
}

void Game::HandleEvent() {
	SDL_Event gameWindowEvent;
	while (SDL_PollEvent(&gameWindowEvent)) {
		switch (gameWindowEvent.type) {
			case SDL_WINDOWEVENT: {
				switch (gameWindowEvent.window.event) {
					case SDL_WINDOWEVENT_CLOSE: {
						this->QuitGame();
						break;
					}
				}
				break;
			}
			case SDL_KEYDOWN: {
				this->HandleInput(gameWindowEvent.key.keysym.sym);
			}
		}
	}
}

void Game::QuitGame() {
	this->quitFlag = true;
}

SDL_Renderer* Game::GetGameRenderer() const {
	return this->gameWindowRenderer;
}

SDL_Texture* Game::GetTexture() const {
	return this->mainTexture;
}

void Game::SetTexture(SDL_Texture* texture) {
	this->mainTexture = texture;
}

SDL_Surface* Game::GetSurface() const {
	return this->gameSurface;
}

void Game::SetSurface(SDL_Surface* surface) {
	this->gameSurface = surface;
}

int Game::GetWidth() const {
	return this->width;
}

int Game::GetHeight() const {
	return this->height;
}


void Game::SetPixel(int x, int y, uint32_t color) {
	if (this->gameSurface) {
		this->pixels[(y * this->gameSurface->w) + x] = color;
	}
}

uint32_t Game::GetPixel(int x, int y) {
	if (this->gameSurface) {
		return this->pixels[(y * this->gameSurface->w) + x];
	}
	return -1;
}

void Game::Clear() {
	SDL_Renderer* renderer = this->GetGameRenderer();
	int r = 
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Game::HandleInput(const SDL_Keycode code) {
	switch (code) {
		case SDLK_UP: {
			--this->velocityY;
			break;
		}
		case SDLK_DOWN: {
			++this->velocityY;
			break;
		}
		case SDLK_LEFT: {
			--this->velocityX;
			break;
		}
		case SDLK_RIGHT: {
			++this->velocityX;
			break;
		}
	}
}