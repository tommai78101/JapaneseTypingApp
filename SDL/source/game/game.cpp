#include "game.h"

Game::Game(int newWidth = 400, int newHeight = 400, std::string title = "Hello world") : width(newWidth), height(newHeight) {
	//Setting up random numbers.
	srand(static_cast<unsigned int>(time(nullptr)));

	// Closing with exit
	std::atexit(SDL_Quit);

	//Initializing game-specific variables.
	this->position = {};
	this->velocity = {};
	this->currentUpOrientation = static_cast<UpOrientation>(UpOrientation::NORTH);
	this->clearColor = 0x0;
	this->currentTime = 0ULL;
	this->lastTime = 0ULL;
	this->hiraganaInputTokens = std::string();
	//this->glyphStorageMutex = std::mutex();
	//this->tokenStorageMutex = std::mutex();

	//SDL objects initialization.
	//SDL_Init returns a negative size_teger (error) or 0 (success). 
	//https://wiki.libsdl.org/SDL_Init (SDL docs)
#ifdef __SWITCH__
	// redirect stdout to emulators
	consoleDebugInit(debugDevice_SVC);
	stdout = stderr;

	//Preparing ROMFS. (Untested)
	Result result = romfsInit();
	if (result != 0) {
		//Emulated romfs directory
		std::cerr << DEBUG << "This may be an emulated romfs directory, continuing..." << std::endl;
		this->dictionaryFile = fopen("romfs:/edict2u", "r");
		if (!this->dictionaryFile) {
			std::cerr << DEBUG << "FATAL! Unable to open the file stored on romfs." << std::endl;
			std::cerr << DEBUG << "Unable to open the file." << std::endl;
			SDL_Delay(3000);
			this->QuitGame();
			return;
		}
	}
	else {
		this->dictionaryFile = fopen("romfs:/edict2u", "r");
		if (!this->dictionaryFile) {
			std::cerr << DEBUG << "FATAL! Unable to open the file stored on romfs." << std::endl;
			std::cerr << DEBUG << "Unable to open the file." << std::endl;
			SDL_Delay(3000);
			this->QuitGame();
			return;
		}
	}

	// mandatory at least on switch, else gfx is not properly closed
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
		printf("SDL_Init: %s\n", SDL_GetError());
		return;
	}
#else
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
#endif

	//SDL_ttf initialization.
	if (TTF_WasInit() <= 0 && TTF_Init() < 0) {
		std::cout << "SDL_ttf Error: " << TTF_GetError() << std::endl;
		return;
	}

	//Obtain the display mode, so we can get the properties of our game screen boundaries. 
	//(Finding the max limitations)
	SDL_DisplayMode currentDisplayMode = {};
	int shouldBeZero = 0;
	for (int i = 0; i < SDL_GetNumVideoDisplays(); i++) {
		shouldBeZero = SDL_GetCurrentDisplayMode(i, &currentDisplayMode);
		if (shouldBeZero == 0) {
			break;
		}
		std::cout << "Could not get display mode for video display " << i << ": " << SDL_GetError() << std::endl;
	}
	if (shouldBeZero != 0) {
		this->QuitGame();
		return;
	}

	//We then use the known display properties to determine the absolute screen position on the display, 
	//then take our application title and the size_tended game screen size Then, we and show it to the user.
	this->gameWindow = SDL_CreateWindow(title.c_str(), (currentDisplayMode.w - static_cast<int>(this->width)) / 2, (currentDisplayMode.h - static_cast<int>(this->height)) / 2, static_cast<int>(this->width), static_cast<int>(this->height), SDL_WINDOW_SHOWN);
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

	//SDL_ttf objects
	TTF_CloseFont(this->defaultFont);

	//Non-SDL objects
	if (this->block) {
		delete this->block;
		this->block = nullptr;
	}
	if (this->inputSystem) {
		delete this->inputSystem;
		this->inputSystem = nullptr;
	}
	//if (this->drawSystem) {
	//	delete this->drawSystem;
	//	this->drawSystem = nullptr;
	//}

	this->QuitGame();

#ifdef __SWITCH__
	romfsExit();
#endif

	//SDL library
	TTF_Quit();				//SDL_ttf
	SDL_Quit();				//SDL
}

void Game::InitializeThread() {
	this->quitFlag = false;
	this->glContext = SDL_GL_GetCurrentContext();
	SDL_GL_MakeCurrent(this->gameWindow, nullptr);
}

void Game::StartThread() {
	this->renderingThread = std::thread(&Game::ThreadTask, this);
}

void Game::StopThread() {
	std::cout << "Waiting on rendering thread to end and join the main thread." << std::endl;
	this->renderingThread.join();
}

void Game::ThreadTask() {
	SDL_GL_MakeCurrent(this->gameWindow, this->glContext);

	//We create a SDL renderer that we can bind to the game window, on the rendering thread.
#ifdef __SWITCH__
	this->gameWindowRenderer = SDL_CreateRenderer(this->gameWindow, -1, SDL_RENDERER_SOFTWARE);
#else
	this->gameWindowRenderer = SDL_CreateRenderer(this->gameWindow, -1, SDL_RENDERER_ACCELERATED);
#endif

	this->Initialize();
	this->GameLoop();
}

void Game::Initialize() {
	// Initializing the fonts.
#ifdef __SWITCH__
	this->defaultFont = TTF_OpenFontRW(SDL_RWFromMem((void*) JapanSans_ttf, JapanSans_ttf_size), 1, 36);
#else
	this->defaultFont = TTF_OpenFont(FONTPATH, 36);
#endif

#ifdef _WIN32
	if (this->defaultFont == nullptr) {
		std::cerr << "Unable to find the font." << std::endl;
		TCHAR pBuffer[MAX_PATH];		//Multibyte string in Windows (internal as UTF-16 LE)
		if (GetModuleFileName(NULL, pBuffer, MAX_PATH) != 0) {
			std::wstring str(pBuffer);
			std::wcerr << "Current working directory: " << str.c_str() << std::endl;
		}
		throw std::exception("No fonts set.");
	}
#else
	if (this->defaultFont == nullptr) {
		std::cerr << "Unable to find the font." << std::endl;
		SDL_SetRenderDrawColor(this->gameWindowRenderer, 0, 0, 255, 255);
		SDL_RenderClear(this->gameWindowRenderer);
		SDL_RenderPresent(this->gameWindowRenderer);
		SDL_Delay(10000);
		this->QuitGame();
		return;
	}
#endif

	//We create a SDL surface that we can use to send over to the SDL renderer to draw in the game window.
	this->gameSurface = SDLHelper_CreateSurface(static_cast<int>(this->width / this->scale), static_cast<int>(this->height / this->scale), 32);
	if (this->gameSurface == nullptr) {
		//We output the errors and then force-quit the game.
		std::cout << "SDL_CreateRGBSurface: " << SDL_GetError() << std::endl;
		this->QuitGame();
		return;
	}
	this->pitch = this->gameSurface->pitch;

	//The SDL surface's "pixels" variable is a void pointer to an array of pixels. We need to first convert the type
	//of the pointer to something that we can manage easily.
	this->pixels = static_cast<uint32_t*>(this->gameSurface->pixels);

	//Using the SDL renderer, we use the SDL surface to create a SDL texture. Output error and force-quit the game,
	//if there are any errors.
	this->mainTexture = SDL_CreateTextureFromSurface(this->gameWindowRenderer, this->gameSurface);
	if (this->mainTexture == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
		this->QuitGame();
		return;
	}

	//Input system initialization
	this->inputSystem = new Input(this);

	//File reading/writing (We're only going to read)
	//We're only storing vocabularies that are 1 character long.
	//It takes about 56 seconds for it to finish initializing.
	std::ifstream edict2(EDICT2PATH);
	if (edict2.is_open() && edict2.good()) {
		std::cout << "Loading dictionary... It may take a while." << std::endl;

		//Loading screen initialization
		SDL_SetRenderDrawColor(this->gameWindowRenderer, 64, 192, 64, 255);
		SDL_RenderClear(this->gameWindowRenderer);
		SDL_RenderPresent(this->gameWindowRenderer);
		//uint32_t* currentTrieLine = this->pixels[60 * this->pitch + 40];
		uint32_t maxPixelRowLength = this->gameSurface->w - (10 * 2);

		std::string buffer;
		bool skipFirstLine = true;
		uint32_t currentLine = 0;
		uint32_t oldPercent = 0;
		//SDL_Event tempEvent;
		while (std::getline(edict2, buffer)) {
			currentLine++;

			//Draw a progress bar
			float percentage = ((float) currentLine / 178532.0f);
			uint32_t percent = (uint32_t) (percentage * (float) maxPixelRowLength);
			if (oldPercent != percent && percent <= maxPixelRowLength) {
				for (uint32_t height = 0; height < 10; height++) {
					this->DrawPixel(percent, height, this->gameSurface->w, (uint32_t) 0x887799FF);
				}
				oldPercent = percent;

				//Updating the loading screen.
				SDL_UpdateTexture(this->mainTexture, nullptr, this->pixels, this->pitch);
				SDL_RenderClear(this->gameWindowRenderer);
				SDL_RenderCopy(this->gameWindowRenderer, this->mainTexture, nullptr, nullptr);
				SDL_RenderPresent(this->gameWindowRenderer);
			}

			if (skipFirstLine) {
				skipFirstLine = false;
				continue;
			}
			std::u32string formattedLine, definition;
			std::vector<std::u32string> vocabulary, pronunciation;
			Convert_utf8_utf32(buffer, formattedLine);
			ParseLine(formattedLine, vocabulary, pronunciation, definition);
			size_t v = vocabulary.size() - 1;
			size_t p = pronunciation.size() - 1;
			int count = 0;
			for (; v >= 0 && p >= 0 && v < vocabulary.size() && p < pronunciation.size(); v--, p--) {
				while (!(vocabulary[v].find(pronunciation[p]))) {
					v--;
				}
				if (vocabulary[v].size() == 1) {
					this->kanjiTrie.Insert(vocabulary[v], pronunciation[p], definition);
					this->dictionary.push_back(vocabulary[v]);
					break;
				}
			}
			buffer.clear();

			if (this->inputSystem->GetMaxTokenSize() < pronunciation.size()) {
				this->inputSystem->SetMaxTokenSize(pronunciation.size());
			}
		};
	}

	////We first need to determine the size of the fonts in pixels.
	//std::wstring testText(L"おはいよ！");
	//u16string utext(testText.begin(), testText.end());
	//if (TTF_SizeUNICODE(this->defaultFont, utext.c_str(), &this->fontWidth, &this->fontHeight) < 0) {
	//	std::cerr << "Error: Unable to retrieve size of string text." << std::endl;
	//	this->QuitGame();
	//}

	////We then determine the line skip.
	//this->lineSkip = TTF_FontLineSkip(this->defaultFont);

	////We create the font surfaces based on text solid/shaded/blended attributes.
	//SDL_Surface* tempFont;
	//SDL_Color color = {};
	//SDL_Color shade = {};
	//color.r = 255;
	//tempFont = TTF_RenderUNICODE_Solid(this->defaultFont, utext.c_str(), color);
	//this->fontSurfaceSolid = SDL_CreateTextureFromSurface(this->gameWindowRenderer, tempFont);
	//color.r = 0;
	//color.g = 200;
	//shade.b = 128;
	//tempFont = TTF_RenderUNICODE_Shaded(this->defaultFont, utext.c_str(), color, shade);
	//this->fontSurfaceShaded = SDL_CreateTextureFromSurface(this->gameWindowRenderer, tempFont);
	//color.g = 0;
	//color.b = 255;
	//tempFont = TTF_RenderUNICODE_Blended(this->defaultFont, utext.c_str(), color);
	//this->fontSurfaceBlended = SDL_CreateTextureFromSurface(this->gameWindowRenderer, tempFont);


	//Non-SDL objects initialization.
	//this->drawSystem = new Draw(this, 1.0f);
	//this->block = new Block(this->gameWindowRenderer, this->defaultFont, Convert(L"あ"));
	//this->block = new Block(this->gameWindowRenderer, this->defaultFont, const_cast<char*>(Japanese::Hiragana::a));

	//Hiragana first
	std::set<std::string> characterGlyph = this->inputSystem->GetCharacterGlyphs(true);
	for (std::set<std::string>::iterator it = characterGlyph.begin(); it != characterGlyph.end(); it++) {
		std::string glyph = *it;
		std::shared_ptr<Block> ptr(new Block(this, this->GetFont(), const_cast<char*>(glyph.c_str())));
		this->hiraganaBlocks.push_back(ptr);
		this->allBlocks.push_back(ptr);
	}

	//Katakana second
	characterGlyph = this->inputSystem->GetCharacterGlyphs(false);
	for (std::set<std::string>::iterator it = characterGlyph.begin(); it != characterGlyph.end(); it++) {
		std::string glyph = *it;
		std::shared_ptr<Block> ptr(new Block(this, this->GetFont(), const_cast<char*>(glyph.c_str())));
		this->katakanaBlocks.push_back(ptr);
		this->allBlocks.push_back(ptr);
	}

	//Creating object pool of Blocks
	int commonListSize = 10;
	int dictionarySize = this->kanjiTrie.GetSize();
	int listSize = Japanese::Hiragana::GetListSize();
	int testPoolSize = 10;
	int testRowsSize = 10;
	int currentBlockWidth = 0;
	const int outsideBoundary = this->GetWidth() + 10;
	int rows = (this->GetHeight() - (Block::BlockSize / 2 + Block::BlockSize)) / Block::BlockSize;
	for (int currentBlock = 0; currentBlock < testPoolSize; currentBlock++) {
		int randomCharacterIndex = (std::rand() * std::rand()) % dictionarySize;
		//char* str = const_cast<char*>(Japanese::Hiragana::List[randomCharacterIndex]);
		std::string u8holder;
		Convert_utf32_utf8(this->dictionary[randomCharacterIndex], u8holder);
		char* str = const_cast<char*>(u8holder.c_str());
		int rowIndex = std::rand() % rows;
		std::shared_ptr<Block> blockPtr = std::make_shared<Block>(this, this->GetFont(), str);
		blockPtr->SetPosition((float) (outsideBoundary + currentBlockWidth), (float) (rowIndex * Block::BlockSize));
		blockPtr->SetActive(true);
		blockPtr->SetRowNumber(rowIndex);
		this->blocksPool.push_back(blockPtr);
		currentBlockWidth += blockPtr->GetBlockWidth() + 10;
	}
}

bool Game::IsWindowInitialized() const {
	return (this->gameWindow != nullptr);
}

void Game::GameLoop() {
	//Prepare the necessary timing calculations
	//uint64_t performanceCounterFrequency = SDL_GetPerformanceFrequency();
	uint64_t lastPerformanceCounter = SDL_GetPerformanceCounter();
	uint64_t currentPerformanceCounter = SDL_GetPerformanceCounter();
	const float minimumTargetTime = 1.5f;

	//We set the default render draw color to black. Mainly used as a way to clear the screen.
	SDL_SetRenderDrawColor(this->gameWindowRenderer, 0, 0, 0, 255);

	//Main game loop. Loops while checking if the quitFlag is not set
	while (!this->quitFlag) {
		//We update the last known time counter derived from the above timing calculations for the update tick.
		lastPerformanceCounter = currentPerformanceCounter;

		//Calculating each tick's elapsed time, and use this to update the game according to the 
		//remaining ticks available that should be used to update the game with.
		currentPerformanceCounter = SDL_GetPerformanceCounter();

		//Obtain the delta time
		Game::deltaTime = static_cast<float>((currentPerformanceCounter - lastPerformanceCounter) * 1000.0 / (double) SDL_GetPerformanceFrequency());
		if (Game::deltaTime > minimumTargetTime)
			Game::deltaTime = minimumTargetTime;

		//uint64_t counterElapsed = static_cast<uint64_t>((currentPerformanceCounter - lastPerformanceCounter) * 1000.0);
		//double millisecondsPerFrame = (1000.0 * (double) counterElapsed) / (double) performanceCounterFrequency;
		//double framesPerSecond = (double) performanceCounterFrequency / (double) counterElapsed;
		//Game::deltaTime = static_cast<float>((float) ((float) counterElapsed / (float) performanceCounterFrequency));

		//Updating game with a non-constant update tick.
		while (Game::deltaTime >= 1.0f) {
			Game::deltaTime /= 2.0f;
			this->Update();
		}

		//Updating game with fixed update ticks
		this->FixedUpdate();

		//Once the update tick is finished, we then draw 1 frame to the screen.
		this->Render();

		//We give back the CPU its own time, and delay our game up to that posize_t. This is to prevent the CPU
		//from being hogged up by our game, avoiding the main thread (kernel thread) to be overtaken for rendering our game.
		SDL_Delay(1);
	}

	//Rendering thread should join to the main thread.
}

void Game::Update() {
	//Updates the game. 
	this->inputSystem->Update();

	//Using Draw class object to update
	//this->drawSystem->Update();

	//(TEMP): Updates the Cartesian position using Isometric coordinates.
	//this->position += CreateIsometricPosition(this->velocity, this->currentUpOrientation) * 0.1f;
	//this->velocity = {};

	//Reworking the new block.
	//this->block->Update(static_cast<int>(this->position.x), static_cast<int>(this->position.y));

	//Update all the blocks in the blocks pool.
	size_t size = this->blocksPool.size();
	for (size_t i = 0; i < size; i++) {
		std::shared_ptr<Block> block = this->blocksPool.at(i);
		block->Update();
	}
}

void Game::FixedUpdate() {
	//Mostly pertaining to physics.
	size_t size = this->blocksPool.size();
	for (size_t i = 0; i < size; i++) {
		std::shared_ptr<Block> block = this->blocksPool.at(i);
		block->FixedUpdate();
	}
}

void Game::Render() {
	//Renders the game.

	//Clears everything.
	SDL_SetRenderDrawColor(this->gameWindowRenderer, 255, 255, 255, 255);
	SDL_RenderClear(this->gameWindowRenderer);

	////Creates a texture to blit to the screen surface (display surface).
	//if (this->mainTexture) {
	//	SDL_DestroyTexture(this->mainTexture);
	//}
	//this->mainTexture = SDL_CreateTextureFromSurface(this->gameWindowRenderer, this->gameSurface);
	//SDL_RenderCopy(this->gameWindowRenderer, this->mainTexture, nullptr, nullptr); //nullptr: Use defaults.

	//Using Draw class object to render
	//this->drawSystem->Render();

	//Block rendering
	//this->block->Render();
	size_t size = this->blocksPool.size();
	for (size_t i = 0; i < size; i++) {
		std::shared_ptr<Block> block = this->blocksPool.at(i);
		if (!block->IsHidden()) {
			block->Render();
		}
	}

	//Input system rendering
	this->inputSystem->Render();

	////For testing, we draw the fonts
	//SDL_Rect destination;
	//destination.x = 0;
	//destination.y = 40;
	//destination.w = this->fontWidth;
	//destination.h = this->fontHeight;
	//SDL_RenderCopy(this->gameWindowRenderer, this->fontSurfaceSolid, nullptr, &destination);
	//destination.y += this->fontHeight + 10;
	//SDL_RenderCopy(this->gameWindowRenderer, this->fontSurfaceShaded, nullptr, &destination);
	//destination.y += this->fontHeight + 10;
	//SDL_RenderCopy(this->gameWindowRenderer, this->fontSurfaceBlended, nullptr, &destination);


	//Update the renderer.
	SDL_RenderPresent(this->gameWindowRenderer);
}

void Game::DrawPixel(uint32_t x, uint32_t y, uint32_t width, uint32_t color) {
	this->pixels[y * width + x] = color;
}

void Game::GameEventLoop() {
	//We handle the user inputs on the main thread. Theoretically, user inputs happen only
	//after the user has seen the rendered gameplay feedback, thus we put the input polling function
	//here to simulate that theory.

	SDL_Event gameEvent;
	bool isKeyDown = false;
	while (!this->quitFlag) {
		while (SDL_PollEvent(&gameEvent)) {
			SDL_EventType gameEventType = static_cast<SDL_EventType>(gameEvent.type);
			switch (gameEventType) {
				case SDL_WINDOWEVENT: {
					SDL_WindowEventID eventId = static_cast<SDL_WindowEventID>(gameEvent.window.event);
					switch (eventId) {
						case SDL_WINDOWEVENT_CLOSE: {
							this->QuitGame();
							break;
						}
						default: {
							// Need to write down a log message system, to indicate to the player something has happened.
							break;
						}
					}
					break;
				}
				case SDL_KEYDOWN: {
					if (!gameEvent.key.repeat) {
						if ((gameEvent.key.keysym.sym >= SDLK_a && gameEvent.key.keysym.sym <= SDLK_z) || (gameEvent.key.keysym.sym == SDLK_MINUS)) {
							std::cout << "Hit " << gameEvent.key.keysym.sym << std::endl;
							if (this->inputSystem->HandleValidInputs(gameEvent.key.keysym.sym)) {
								this->inputSystem->ConfirmToken();
							}
						}
						else {
							switch (gameEvent.key.keysym.sym) {
								case SDLK_BACKSPACE: {
									//Handle backspace
									std::vector<SDL_Keycode>* tokens = this->inputSystem->GetTokens();
									if (!tokens->empty()) {
										tokens->pop_back();
									}
									break;
								}
								case SDLK_RETURN:
									//Enter key to confirm the inputs.
									this->inputSystem->ConfirmToken();
									break;
								default:
									this->inputs[gameEvent.key.keysym.scancode] = true;
									break;
							}
						}
					}
					break;
				}
				case SDL_KEYUP: {
					bool alt = this->inputs[SDL_SCANCODE_RALT] || this->inputs[SDL_SCANCODE_LALT];
					bool ctrl = this->inputs[SDL_SCANCODE_RCTRL] || this->inputs[SDL_SCANCODE_LCTRL];
					if (alt && ctrl) {
						this->inputSystem->SwapInputType();
					}
					this->inputs[gameEvent.key.keysym.scancode] = false;
					break;
				}
#ifdef __SWITCH__
				case SDL_JOYAXISMOTION: {
					Print("%sJoystick %d axis %d value: %d\n", DEBUG, gameEvent.jaxis.which, gameEvent.jaxis.axis, gameEvent.jaxis.value);
					break;
				}
				case SDL_JOYBUTTONDOWN: {
					// https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L51
					Print("%sJoystick %d button %d down\n", DEBUG, gameEvent.jbutton.which, gameEvent.jbutton.button);
					if (gameEvent.jbutton.which == 0 && (gameEvent.jbutton.button == JoyconButtons::KEY_A || gameEvent.jbutton.button == JoyconButtons::KEY_PLUS))
						this->QuitGame();
					break;
				}
#endif
			}
		}
	}
}

void Game::QuitGame() {
	this->quitFlag = true;
}

void Game::Clear() {
	SDL_Renderer* renderer = this->GetGameRenderer();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

//Setters/Getters

SDL_Renderer* Game::GetGameRenderer() const {
	return this->gameWindowRenderer;
}

TTF_Font* Game::GetFont() const {
	return this->defaultFont;
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

size_t Game::GetWidth() const {
	return this->width;
}

size_t Game::GetHeight() const {
	return this->height;
}

void Game::SetPixel(size_t x, size_t y, uint32_t color) {
	if (this->gameSurface) {
		this->pixels[(y * this->gameSurface->w) + x] = color;
	}
}

uint32_t Game::GetPixel(size_t x, size_t y) {
	if (this->gameSurface) {
		return this->pixels[(y * this->gameSurface->w) + x];
	}
	return -1;
}

void Game::HandleInput() {
	//This is the place to put tons of if...statements here.
	//if (this->inputs[SDL_SCANCODE_LSHIFT]) {
	//	this->inputs[SDL_SCANCODE_LSHIFT] = false;
	//	switch (this->currentUpOrientation) {
	//		case UpOrientation::NORTHEAST: {
	//			this->currentUpOrientation = UpOrientation::NORTH;
	//			break;
	//		}
	//		default:
	//		case UpOrientation::NORTH: {
	//			this->currentUpOrientation = UpOrientation::NORTHWEST;
	//			break;
	//		}
	//		case UpOrientation::NORTHWEST: {
	//			this->currentUpOrientation = UpOrientation::NORTHEAST;
	//			break;
	//		}
	//	}
	//}
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

Input* Game::GetInput() {
	return this->inputSystem;
}

//Block* Game::GetBlock() {
//	return this->block;
//}

std::vector<std::shared_ptr<Block>> Game::GetHiraganaBlocks() const {
	return this->hiraganaBlocks;
}

std::vector<std::shared_ptr<Block>> Game::GetKatakanaBlocks() const {
	return this->katakanaBlocks;
}

std::vector<std::shared_ptr<Block>> Game::GetAllBlocks() const {
	return this->allBlocks;
}

std::vector<std::shared_ptr<Block>> Game::GetBlocksPool() const {
	return this->blocksPool;
}

void Game::StoreGlyphs(char* hiraganaValue, char* katakanaValue) {
	try {
		std::lock_guard<std::mutex> lockGuard(this->glyphStorageMutex);
		this->GetInput()->UpdateGlyphs(hiraganaValue);
		this->ProcessGlyphs(hiraganaValue, katakanaValue);
	}
	catch (std::exception e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void Game::ProcessGlyphs(char* hiraganaValue, char* katakanaValue) {
	// Storing the input values into their corresponding input types.
	std::string hiraganaInput(hiraganaValue);
	std::string katakanaInput(katakanaValue);
	this->hiraganaInputTokens.append(hiraganaInput);
	this->katakanaInputTokens.append(katakanaInput);

	// Getting a reference to the maximum size allowed.
	int maxSize = 0;

	//Mostly pertaining to physics.
	size_t size = this->blocksPool.size();
	for (size_t i = 0; i < size; i++) {
		std::shared_ptr<Block> block = this->blocksPool.at(i);
		std::string pronunciation = this->kanjiTrie.GetPronunciation(block->GetGlyphValue());
		if (maxSize < pronunciation.size()) {
			maxSize = pronunciation.size();
		}

		if (pronunciation.find(this->hiraganaInputTokens) != std::string::npos || pronunciation.find(this->katakanaInputTokens) != std::string::npos) {
			if (pronunciation == this->hiraganaInputTokens || pronunciation == this->katakanaInputTokens) {
				block->TypedAway();
				this->hiraganaInputTokens.clear();
				this->katakanaInputTokens.clear();
				std::cout << "Block " << block->GetGlyphValue() << " is currently inactive." << std::endl;
				break;
			}
		}
		else if (this->hiraganaInputTokens.length() >= maxSize || this->katakanaInputTokens.length() >= maxSize) {
			this->hiraganaInputTokens.clear();
			this->katakanaInputTokens.clear();
		}
	}
	int debug = 0;
}