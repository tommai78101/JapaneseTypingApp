#include "game.h"

Game::Game() : gameWindow(nullptr), gameWindowRenderer(nullptr), quitFlag(false), width(400), height(400), pixels(nullptr), scale(8) {
	//Setting up random numbers.
	srand(static_cast<unsigned int>(time(nullptr)));

	//Initializing game-specific variables.
	this->position = {};
	this->velocity = {};
	this->currentUpOrientation = UpOrientation::NORTH;
	this->clearColor = 0x0;

	//SDL objects initialization.

	//Non-SDL objects initialization.
	this->drawSystem = new Draw(this, 1.0f);
}

Game::~Game() {
	//Handles game memory de-allocation
	//SDL objects
	this->pixels = nullptr;
	if (this->gameSurface) {
		SDL_FreeSurface(this->gameSurface);
		this->gameSurface = nullptr;
	}
	if (this->mainTexture) {
		SDL_DestroyTexture(this->mainTexture);
		this->mainTexture = nullptr;
	}
	if (this->gameWindowRenderer) {
		SDL_DestroyRenderer(this->gameWindowRenderer);
		this->gameWindowRenderer = nullptr;
	}
	if (this->gameWindow) {
		SDL_DestroyWindow(this->gameWindow);
		this->gameWindow = nullptr;
	}

	//Non-SDL objects
	if (this->drawSystem) {
		delete this->drawSystem;
		this->drawSystem = nullptr;
	}
	SDL_Quit();
}

void Game::Initialize(std::string title) {
	//Obtain the display mode, so we can get the properties of our game screen boundaries. 
	//(Finding the max limitations)
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

	//We then use the known display properties to determine the absolute screen position on the display, 
	//then take our application title and the intended game screen size Then, we and show it to the user.
	this->gameWindow = SDL_CreateWindow(title.c_str(), (currentDisplayMode.w - this->width) / 2, (currentDisplayMode.h - this->height) / 2, this->width, this->height, SDL_WINDOW_SHOWN);

	//We create a SDL renderer that we can bind to the game window.
	this->gameWindowRenderer = SDL_CreateRenderer(this->gameWindow, -1, SDL_RENDERER_ACCELERATED);

	//We create a SDL surface that we can use to send over to the SDL renderer to draw in the game window.
	this->gameSurface = SDL_CreateRGBSurface(0, this->width / this->scale, this->height / this->scale, 32, RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK);
	if (this->gameSurface == nullptr) {
		//We output the errors and then force-quit the game.
		std::cout << "SDL_CreateRGBSurface: " << SDL_GetError() << std::endl;
		this->QuitGame();
	}

	//The SDL surface's "pixels" variable is a void pointer to an array of pixels. We need to first convert the type
	//of the pointer to something that we can manage easily.
	this->pixels = static_cast<uint32_t*>(this->gameSurface->pixels);

	//Using the SDL renderer, we use the SDL surface to create a SDL texture. Output error and force-quit the game,
	//if there are any errors.
	this->mainTexture = SDL_CreateTextureFromSurface(this->gameWindowRenderer, this->gameSurface);
	if (this->mainTexture == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
		this->QuitGame();
	}
}

bool Game::IsWindowInitialized() const {
	return (this->gameWindow != nullptr);
}

void Game::GameLoop() {
	//Prepare the necessary timing calculations
	uint64_t performanceCounterFrequency = SDL_GetPerformanceFrequency();
	uint64_t lastPerformanceCounter = SDL_GetPerformanceCounter();
	uint64_t currentPerformanceCounter = SDL_GetPerformanceCounter();

	//We set the default render draw color to black. Mainly used as a way to clear the screen.
	SDL_SetRenderDrawColor(this->gameWindowRenderer, 0, 0, 0, 255);

	//Main game loop. Loops while checking if the quitFlag is not set
	while (!this->quitFlag) {
		//Calculating each tick's elapsed time, and use this to update the game according to the 
		//remaining ticks available that should be used to update the game with.
		currentPerformanceCounter = SDL_GetPerformanceCounter();
		uint64_t counterElapsed = static_cast<uint64_t>((currentPerformanceCounter - lastPerformanceCounter) * 1000.0);
		//double millisecondsPerFrame = (1000.0 * (double) counterElapsed) / (double) performanceCounterFrequency;
		//double framesPerSecond = (double) performanceCounterFrequency / (double) counterElapsed;
		double counterElapsedBySecond = static_cast<double>(counterElapsed / performanceCounterFrequency);
		while (counterElapsedBySecond > 0.0) {
			this->Update();
			counterElapsedBySecond -= 1.0;
		}

		//Once the update tick is finished, we then draw 1 frame to the screen.
		this->Render();

		//After drawing 1 frame, we handle the user inputs. Theoretically, user inputs happen only
		//after the user has seen the rendered gameplay feedback, thus we put the input polling function
		//here to simulate that theory.
		this->HandleEvent();

		//We update the last known time counter derived from the above timing calculations for the update tick.
		lastPerformanceCounter = currentPerformanceCounter;

		//We give back the CPU its own time, and delay our game up to that point. This is to prevent the CPU
		//from being hogged up by our game, avoiding the main thread (kernel thread) to be overtaken for rendering our game.
		SDL_Delay(1);
	}
}

void Game::Update() {
	//Updates the game. 

	//Using Draw class object to update
	this->drawSystem->Update();

	//(TEMP): Updates the Cartesian position using Isometric coordinates.
	this->position += CreateIsometricPosition(this->velocity, this->currentUpOrientation) * 0.1f;
	this->velocity = {};
}

void Game::Render() {
	//Renders the game.

	//Clears everything.
	SDL_SetRenderDrawColor(this->gameWindowRenderer, 255, 255, 255, 255);
	SDL_RenderClear(this->gameWindowRenderer);

	//Drawing a rectangle (square). Requires that the values are strictly in order of the struct object's members.
	//We set the draw color to blue.
	SDL_SetRenderDrawColor(this->gameWindowRenderer, 0, 0, 255, 255);
	//Struct object initialization
	SDL_Rect r = {
		(int) std::roundf(this->position.x),        //absolute left
		(int) std::roundf(this->position.y),        //absolute top
		50,                                         //width
		50,                                         //height
	};
	SDL_RenderDrawRect(this->gameWindowRenderer, &r);

	////Creates a texture to blit to the screen surface (display surface).
	//if (this->mainTexture) {
	//	SDL_DestroyTexture(this->mainTexture);
	//}
	//this->mainTexture = SDL_CreateTextureFromSurface(this->gameWindowRenderer, this->gameSurface);
	//SDL_RenderCopy(this->gameWindowRenderer, this->mainTexture, nullptr, nullptr); //nullptr: Use defaults.

	//Using Draw class object to render
	this->drawSystem->Render();

	//Update the renderer.
	SDL_RenderPresent(this->gameWindowRenderer);
}

void Game::HandleEvent() {
	SDL_Event gameWindowEvent;
	bool isKeyDown = false;
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
				if (!gameWindowEvent.key.repeat) {
					this->inputs[gameWindowEvent.key.keysym.scancode] = true;
				}
				break; 
			}
			case SDL_KEYUP: {
				if (!gameWindowEvent.key.repeat) {
					this->inputs[gameWindowEvent.key.keysym.scancode] = false;
				}
				break;
			}
		}
	}
	this->HandleInput();
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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Game::HandleInput() {
	//This is the place to put tons of if...statements here.
	if (this->inputs[SDL_SCANCODE_LSHIFT]) {
		this->inputs[SDL_SCANCODE_LSHIFT] = false;
		switch (this->currentUpOrientation) {
			case UpOrientation::NORTHEAST: {
				this->currentUpOrientation = UpOrientation::NORTH;
				break;
			}
			default:
			case UpOrientation::NORTH: {
				this->currentUpOrientation = UpOrientation::NORTHWEST;
				break;
			}
			case UpOrientation::NORTHWEST: {
				this->currentUpOrientation = UpOrientation::NORTHEAST;
				break;
			}
		}
	}
	if (this->inputs[SDL_SCANCODE_UP]) {
		--this->velocity.y;
	}
	if (this->inputs[SDL_SCANCODE_DOWN]) {
		++this->velocity.y;
	}
	if (this->inputs[SDL_SCANCODE_LEFT]) {
		--this->velocity.x;
	}
	if (this->inputs[SDL_SCANCODE_RIGHT]) {
		++this->velocity.x;
	}
}
