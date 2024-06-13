#include "block.h"

//---------  Object class definitions and functions.  --------------

void Object::Calculate(Vector2D desiredVelocity) {
	//Semi-implicit Euler function for velocity and position.
	this->currentVelocity = this->oldVelocity * (1 - Game::deltaTime) + desiredVelocity * Game::deltaTime;
	this->oldVelocity = this->currentVelocity;
	this->currentPosition = this->oldPosition + (this->currentVelocity * Game::deltaTime);
	this->oldPosition = this->currentPosition;
}

Vector2D Object::GetVelocity() const {
	return this->currentVelocity;
}

Vector2D Object::GetPosition() const {
	return this->currentPosition;
}

bool Object::IsActive() const {
	return this->isActive;
}

bool Object::IsHidden() const {
	return this->isHidden;
}

bool Object::IsHit() const {
	return this->isHit;
}

bool Object::IsMoving() const {
	return this->isMoving;
}

void Object::SetVelocity(Vector2D velocity) {
	this->oldVelocity = velocity;
	this->currentVelocity = velocity;
}

void Object::SetPosition(Vector2D position) {
	this->oldPosition = position;
	this->currentPosition = position;
}

void Object::SetPosition(float x, float y) {
	Vector2D pos{ x, y };
	this->oldPosition = pos;
	this->currentPosition = pos;
}

void Object::SetActive(bool value) {
	this->isActive = value;
}

void Object::SetHidden(bool value) {
	this->isHidden = value;
}

void Object::SetHit(bool value) {
	this->isHit = value;
}

void Object::SetMovingFlag(bool value) {
	this->isMoving = value;
}

void Object::ApplyGravity() {
	Vector2D gravity{ -1.0f, 0.0f };
	this->Calculate(gravity * Game::gravity);
}

//---------  Block class definitions and functions.  --------------

//Block::Block(SDL_Renderer* gameRenderer, TTF_Font* font, Uint16* str) {
//	this->blockSurface = SDLHelper_CreateSurface(this->BlockSize, this->BlockSize, 32);
//
//	//Block class properties
//	this->pixels = this->blockSurface->pixels;
//	this->gameRenderer = gameRenderer;
//	this->blockTexture = SDL_CreateTextureFromSurface(this->gameRenderer, this->blockSurface);
//	this->positionX = 0;
//	this->positionY = 0;
//	this->color = {};
//	TTF_SizeUNICODE(font, str, &this->characterWidth, &this->characterHeight);
//	this->glyph = TTF_RenderUNICODE_Solid(font, str, this->color);
//	//TTF_RenderUTF8_Solid(font, L"い", this->color);
//	this->glyphTexture = SDL_CreateTextureFromSurface(gameRenderer, this->glyph);
//}

Block::Block(Game* game, TTF_Font* font, char* str) {
	//Initialized by parameter arguments.
	this->game = game;
	this->gameRenderer.reset(game->GetGameRenderer());
	this->font = font;
	this->ReplaceGlyph(str);
	this->blockLength = strlen(str) / 3;

	// Custom width calculations.
	int paddingWidth = std::abs(this->BlockSize - this->characterWidth) / 2;
	this->totalWidth = Block::BlockSize * this->blockLength + (this->blockLength > 1 ? -paddingWidth : 0);

	//Block class properties initialized using other methods.
	this->blockSurface = SDLHelper_CreateSurface(this->BlockSize * this->blockLength, this->BlockSize, 32);
	this->pixels = this->blockSurface->pixels;
	this->blockTexture = SDL_CreateTextureFromSurface(this->gameRenderer.get(), this->blockSurface);

	//By default, this block should be affected by gravity.
	this->affectedByGravity = true;
}

Block::Block(Block* block) {
	//Initialized by parameter arguments.
	this->game = block->game;
	this->gameRenderer.reset(block->game->GetGameRenderer());
	this->font = block->font;
	this->ReplaceGlyph(block->GetGlyphValue());
	this->blockLength = strlen(block->GetGlyphValue()) / 3;

	// Custom width calculations.
	int paddingWidth = std::abs(block->BlockSize - block->characterWidth) / 2;
	this->totalWidth = Block::BlockSize * block->blockLength + (block->blockLength > 1 ? -paddingWidth : 0);

	//Block class properties initialized using other methods.
	this->blockSurface = SDLHelper_CreateSurface(block->BlockSize * block->blockLength, block->BlockSize, 32);
	this->pixels = block->blockSurface->pixels;
	this->blockTexture = SDL_CreateTextureFromSurface(block->gameRenderer.get(), block->blockSurface);
	this->SetHit(block->IsHit());
	this->SetActive(block->IsActive());
	this->SetPosition(block->GetPosition());
	this->SetVelocity(block->GetVelocity());
	this->SetRowNumber(block->GetRowNumber());
	//this->SetBoundaryFlag(block->GetBoundaryFlag());

	//By default, this block should be affected by gravity.
	this->affectedByGravity = block->affectedByGravity;
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

void Block::Update() {
	//If it's inactive or if it's at the boundary, don't update.
	if (!this->IsActive() || this->IsHidden()) {
		return;
	}

	//Calculate whether the block has reached the bottom of the screen, but above the input system.
	Vector2D position = this->currentPosition;

	// This is for when blocks are coming down from the top.
	/*if (position.y >= rect.y - this->BlockSize) {
		position.y = (float) (rect.y - this->BlockSize);
		this->SetPosition(position);
		this->affectedByGravity = false;
	}*/

	// This is for when blocks are coming from the right, and has reached the left boundary.
	// Temporarily setting the left boundary to be 1 block size wide.
	int boundaryX = Block::BlockSize / 2;
	int count = 0;
	std::shared_ptr<Block> nearest = this->GetLeftBlock();
	if (nearest.get() != nullptr) {
		while (nearest.get() != nullptr) {
			if (!nearest.get()->IsHit() && !nearest.get()->IsMoving()) {
				count += nearest.get()->GetBlockWidth();
			}
			nearest = nearest.get()->GetLeftBlock();
		}
	}
	float newBoundaryX = (float) boundaryX + count;
	if (position.x < newBoundaryX) {
		position.x = newBoundaryX;
		this->SetPosition(position);
		this->SetBoundaryFlag(true);
		this->SetMovingFlag(false);
	}
}

void Block::FixedUpdate() {
	if (this->affectedByGravity && !this->GetBoundaryFlag()) {
		Object::ApplyGravity();
	}
	else {
		//We don't do anything about the block for now.
	}
}

void Block::Render() {
	//If it's inactive, don't render anything.
	if (!this->IsActive())
		return;

	//Get paddings in order to center align the text in the rectangle.
	int paddingWidth = std::abs(this->BlockSize - this->characterWidth) / 2;
	int paddingHeight = std::abs(this->BlockSize - this->characterHeight) / 2;
	int fullBlockSize = this->GetBlockWidth();

	//First, we draw the font glyphs.
	SDL_SetRenderDrawColor(this->gameRenderer.get(), 0, 0, 0, 255);
	SDL_Rect fontDestination = { ((int) this->currentPosition.x) + paddingWidth, ((int) this->currentPosition.y) + paddingHeight, fullBlockSize - paddingWidth * 2, this->characterHeight };
	SDL_RenderCopy(this->gameRenderer.get(), this->glyphTexture, nullptr, &fontDestination);

	//Second, we draw a rectangle (square), depending on the width of the character glyph.
	SDL_SetRenderDrawColor(this->gameRenderer.get(), 0, 0, 255, 255);

	//Struct object initialization
	SDL_Rect r = {
		(int) this->currentPosition.x, //absolute left
		(int) this->currentPosition.y, //absolute top
		fullBlockSize, //width
		Block::BlockSize //height
	};
	SDL_RenderDrawRect(this->gameRenderer.get(), &r);

	//Always reset the color after use.
	SDL_SetRenderDrawColor(this->gameRenderer.get(), 0, 0, 0, 255);

	SDL_Rect destination = { r };
	SDL_RenderCopy(this->gameRenderer.get(), this->blockTexture, nullptr, &destination);
}

void Block::ReplaceGlyph(char* str) {
	if (this->glyph) {
		SDL_FreeSurface(this->glyph);
	}
	if (this->glyphTexture) {
		SDL_DestroyTexture(this->glyphTexture);
	}
	TTF_SizeUTF8(this->font, str, &this->characterWidth, &this->characterHeight);
	this->glyph = TTF_RenderUTF8_Solid(this->font, str, this->color);
	this->glyphTexture = SDL_CreateTextureFromSurface(this->gameRenderer.get(), this->glyph);

	//Store the glyph value
	strcpy_s(this->glyphsValue, 8, str);
}

void Block::ReplaceGlyph(const char* str) {
	this->ReplaceGlyph(const_cast<char*>(str));
}

char* Block::GetGlyphValue() const {
	return (char*) &this->glyphsValue[0];
}

int Block::GetBlockLength() const {
	return this->blockLength;
}

int Block::GetBlockWidth() const {
	int length = strlen(this->GetGlyphValue());
	int stride = 3;
	if (length > 5) {
		stride *= 2;
	}
	return (length / stride) * Block::BlockSize;
}

int Block::GetCharacterWidth() const {
	return this->characterWidth;
}

int Block::GetBlockRenderWidth() const {
	return this->totalWidth;
}

std::shared_ptr<Block> Block::GetLeftBlock() {
	int leftBlockIndex = -1;
	int distance = this->game->GetWidth();
	std::vector<std::shared_ptr<Block>> blocksPool = this->game->GetBlocksPool();
	for (size_t i = 0; i < blocksPool.size(); i++) {
		std::shared_ptr<Block> block = blocksPool.at(i);
		if (block->GetRowNumber() == this->GetRowNumber() && this != block.get() && !block.get()->IsHit()) {
			int newDistance = (int) (this->GetPosition().x - block->GetPosition().x);
			if (newDistance > 0 && newDistance < distance) {
				distance = newDistance;
				leftBlockIndex = i;
			}
		}
	}
	if (leftBlockIndex == -1) {
		return nullptr;
	}
	return blocksPool.at(leftBlockIndex);
}

std::shared_ptr<Block> Block::GetRightBlock() {
	int rightBlockIndex = -1;
	int distance = this->game->GetWidth();
	std::vector<std::shared_ptr<Block>> blocksPool = this->game->GetBlocksPool();
	for (size_t i = 0; i < blocksPool.size(); i++) {
		std::shared_ptr<Block> block = blocksPool.at(i);
		if (block->GetRowNumber() == this->GetRowNumber() && this != block.get() && !block.get()->IsHit()) {
			int newDistance = (int) (block->GetPosition().x - this->GetPosition().x);
			if (newDistance > 0 && newDistance < distance) {
				distance = newDistance;
				rightBlockIndex = i;
			}
		}
	}
	if (rightBlockIndex != -1) {
		return blocksPool.at(rightBlockIndex);
	}
	return nullptr;
}

void Block::SetRowNumber(int row) {
	this->rowNumber = row;
}

int Block::GetRowNumber() const {
	return this->rowNumber;
}

bool Block::IsAffectedByGravity() const {
	return this->affectedByGravity;
}

void Block::SetBoundaryFlag(bool value) {
	this->isAtBoundary = value;
}

bool Block::GetBoundaryFlag() const {
	return this->isAtBoundary;
}

void Block::TypedAway() {
	std::shared_ptr<Block> rightBlock = this->GetRightBlock();
	while (rightBlock != nullptr) {
		if (!rightBlock.get()->IsHit()) {
			rightBlock.get()->TurnOnGravity();
		}
		rightBlock = rightBlock->GetRightBlock();
	}
	this->SetHidden(true);
	this->SetHit(true);
}

void Block::TurnOnGravity() {
	this->affectedByGravity = true;
	this->SetBoundaryFlag(false);
	this->SetMovingFlag(true);
}