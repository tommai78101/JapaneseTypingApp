#include "font.h"

int FontTextureAtlas::Fit(size_t index, size_t width, size_t height) {
	Vector3Di* node = static_cast<Vector3Di*>(this->nodes->Get(index));
	int x = node->x;
	int y = node->y;
	int widthLeft = width;
	size_t i = index;
	if ((x + width) > (this->width - 1))
		return -1;
	y = node->y;
	while (widthLeft > 0) {
		node = static_cast<Vector3Di*>(this->nodes->Get(i));
		if (node->y > y) {
			y = node->y;
		}
		if ((y + height) > (this->height - 1))
			return -1;
		widthLeft -= node->z;
		i++;
	}
	return y;
}

void FontTextureAtlas::Merge() {
	Vector3Di* currentNode;
	Vector3Di* nextNode;
	for (size_t i = 0; i < this->nodes->count - 1; i++) {
		currentNode = static_cast<Vector3Di*>(this->nodes->Get(i));
		nextNode = static_cast<Vector3Di*>(this->nodes->Get(i + 1));
		if (currentNode->y == nextNode->y) {
			currentNode->z += nextNode->z;
			this->nodes->Erase(i + 1);
			--i;
		}
	}
}

Vector4Di FontTextureAtlas::GetRegion(size_t width, size_t height) {
	Vector3Di* currentNode;
	Vector3Di* previousNode;
	Vector4Di region = { {0, 0, width, height} };
	size_t i;

	int bestIndex = -1;
	size_t bestWidth = UINT_MAX;
	size_t bestHeight = UINT_MAX;
	int y;
	for (i = 0; i < this->nodes->count; i++) {
		y = this->Fit(i, width, height);
		if (y >= 0) {
			currentNode = static_cast<Vector3Di*>(this->nodes->Get(i));
			if (((y + height) < bestHeight) || (((y + height) == bestHeight) && (currentNode->z > 0 && static_cast<size_t>(currentNode->z) < bestWidth))) {
				bestHeight = y + height;
				bestIndex = i;
				bestWidth = currentNode->z;
				region.x = currentNode->x;
				region.y = y;
			}
		}
	}
	if (bestIndex == -1) {
		region.x = -1;
		region.y = -1;
		region.width = 0;
		region.height = 0;
		return region;
	}
	currentNode = static_cast<Vector3Di*>(std::malloc(sizeof(Vector3Di)));
	if (!currentNode) {
		std::fprintf(stderr, "Line %d: No more memory for allocation.", __LINE__);
		std::exit(EXIT_FAILURE);
		return { {0, 0, 0, 0} };
	}
	currentNode->x = region.x;
	currentNode->y = region.y + height;
	currentNode->z = width;
	this->nodes->Insert(bestIndex, currentNode);
	std::free(currentNode);

	for (i = bestIndex + 1; i < this->nodes->count; i++) {
		currentNode = static_cast<Vector3Di*>(this->nodes->Get(i));
		previousNode = static_cast<Vector3Di*>(this->nodes->Get(i-1));
		if (currentNode->x < (previousNode->x + previousNode->z)) {
			int shrink = previousNode->x + previousNode->z - currentNode->x;
			currentNode->x += shrink;
			currentNode->z -= shrink;
			if (currentNode->z <= 0) {
				this->nodes->Erase(i);
				--i;
			}
			else
				break;
		}
		else
			break;
	}
	this->Merge();
	this->used += width * height;
	return region;
}


FontTextureAtlas* CreateFontAtlas(size_t width, size_t height, size_t depth) {
	//Why 1, 3, or 4, we don't know.
	assert((depth == 1) || (depth == 3) || (depth) == 4);

	FontTextureAtlas* self = static_cast<FontTextureAtlas*>(std::malloc(sizeof(FontTextureAtlas)));
	if (!self) {
		std::fprintf(stderr, "Line %d: No more memory for allocation.", __LINE__);
		std::exit(EXIT_FAILURE);
		return nullptr;
	}
	self->used = 0;
	self->width = width;
	self->height = height;
	self->depth = depth;
	self->id = 0;

	//Add a 1-pixel thick border around whole atlas, to avoid unwanted sampling noises
	Vector3Di node = { 1, 1, ((int)(width & INT_MAX) - 2) };
	self->nodes = CreateVectorList(sizeof(Vector3Di));
	self->nodes->PushBack(&node);

	self->atlasData = static_cast<unsigned char*>(std::calloc(width * height * depth, sizeof(unsigned char)));
	if (!self->atlasData) {
		std::fprintf(stderr, "Line %d: No more memory for allocation.", __LINE__);
		std::exit(EXIT_FAILURE);
		return nullptr;
	}
	return self;
}

void DeleteFontAtlas(FontTextureAtlas* atlas) {
	assert(atlas);
	DeleteVectorList(atlas->nodes);
	if (atlas->atlasData) {
		std::free(atlas->atlasData);
	}
	std::free(atlas);
}