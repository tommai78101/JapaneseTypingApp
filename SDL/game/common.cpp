#include "common.h"

Vector2D CreateIsometricPosition(Vector2D velocity, UpOrientation orientation) {
	Vector2D result = {};
	switch (orientation) {
		case NORTHEAST: {
			result.x = (velocity.x - velocity.y);
			result.y = (velocity.x + velocity.y) / 2.0f;
			break;
		}
		default:
		case NORTH: {
			result = velocity;
			break;
		}
		case NORTHWEST: {
			result.x = (velocity.x + velocity.y);
			result.y = (-velocity.x + velocity.y) / 2.0f;
			break;
		}
	}
	return result;
}

//Vector List functions

void* VectorList::Get(size_t index) const {
	assert(this->count);
	assert(index < this->count);
	return static_cast<char*>(this->items) + index * this->itemSize;
}

void* VectorList::GetFront() const {
	assert(this->count);
	return this->Get(0);
}

void* VectorList::GetBack() const {
	assert(this->count);
	return this->Get(this->itemSize - 1);
}

void VectorList::Set(size_t index, void* item) {
	assert(this->count);
	assert(index < this->count);
	std::memcpy(static_cast<char*>(this->items) + index * this->itemSize, item, this->itemSize);
}

void VectorList::Reserve(size_t size) {
	if (this->capacity < size) {
		this->items = std::realloc(this->items, size * this->count);
		this->capacity = size;
	}
}

void VectorList::Insert(size_t index, void* item) {
	assert(index <= this->count);
	if (this->capacity <= this->count) {
		this->Reserve(2 * this->capacity);
	}
	if (index < this->count) {
		std::memmove(static_cast<char*>(this->items) + (index + 1) * this->itemSize, static_cast<char*>(this->items) + (index + 0) * this->itemSize, (this->count - index) * this->itemSize);
	}
	this->count++;
	this->Set(index, item);
}

void VectorList::PushBack(void* item) {
	this->Insert(this->count, item);
}

void VectorList::PopBack() {
	assert(this->count);
	this->count--;
}

void VectorList::EraseRange(size_t first, size_t last) {
	assert(first < this->count);
	assert(last < this->count+1);
	assert(first < last);

	std::memmove(static_cast<char*>(this->items) + first * this->itemSize, static_cast<char*>(this->items) + last * this->itemSize, (this->count - last) * this->itemSize);
	this->count -= (last - first);
}

void VectorList::Erase(size_t index) {
	assert(index < this->count);
	this->EraseRange(index, index + 1);
}

VectorList* CreateVectorList(size_t itemSize = 1) {
	VectorList* self = static_cast<VectorList*>(std::malloc(sizeof(VectorList)));
	assert(itemSize > 0);
	if (!self) {
		std::fprintf(stderr, "Line %d: No more memory for allocation.", __LINE__);
		std::exit(EXIT_FAILURE);
		return nullptr;
	}
	self->itemSize = itemSize;
	self->count = 0;
	self->capacity = 1;
	self->items = std::malloc(self->itemSize * self->capacity);
	return self;
}

void DeleteVectorList(VectorList* self) {
	assert(self);
	std::free(self->items);
	std::free(self);
}

//End Vector List functions