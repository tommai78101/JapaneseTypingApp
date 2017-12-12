#ifndef __COMMON_H__
#	define __COMMON_H__

#pragma once

//Standard libraries
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cstring>  //For std::memmove only


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
const int RED_MASK = 0xff000000;
const int GREEN_MASK = 0x00ff0000;
const int BLUE_MASK = 0x0000ff00;
const int ALPHA_MASK = 0x000000ff;
#else
const int RED_MASK = 0x000000ff;
const int GREEN_MASK = 0x0000ff00;
const int BLUE_MASK = 0x00ff0000;
const int ALPHA_MASK = 0xff000000;
#endif

enum UpOrientation {
	NORTH,
	NORTHEAST,
	NORTHWEST
};

//Vector2D stuffs

struct Vector2D {
	float x;
	float y;

	Vector2D& operator+(const Vector2D& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2D& operator+=(const Vector2D& other) {
		return (*this + other);
	}

	Vector2D& operator-(const Vector2D& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2D& operator-=(const Vector2D& other) {
		return (*this - other);
	}

	Vector2D& operator*(const float& factor) {
		x *= factor;
		y *= factor;
		return *this;
	}

	Vector2D& operator*=(const float& other) {
		return (*this) * other;
	}
};

Vector2D CreateIsometricPosition(Vector2D velocity, UpOrientation orientation);

//End Vector2D stuffs

//Integer Vector3D stuffs

typedef union {
	int data[3];
	struct {
		int x;
		int y;
		int z;
	};
} Vector3Di;

//End Integer Vector3D stuffs

//Integer Vector4D stuffs

typedef union {
	int data[4];
	struct {
		int x;
		int y;
		int z;
		int w;
	};
	struct {
		int x;
		int y;
		int width;
		int height;
	};
} Vector4Di;

//End Integer Vector4D stuffs

//Float32 Vector3D stuffs

typedef union {
	float data[3];
	struct {
		float x;
		float y;
		float z;
	};
} Vector3Df;

//End Float32 Vector3D stuffs

//Vector (dynamically allocated list)

struct VectorList;

VectorList* CreateVectorList(size_t itemSize);
void DeleteVectorList(VectorList* self);

typedef struct VectorList {
	void* items;
	size_t capacity;
	size_t count;
	size_t itemSize;

	VectorList::~VectorList() {
		DeleteVectorList(this);
	}

	void* Get(size_t index) const;
	void* GetFront() const;
	void* GetBack() const;
	void Set(size_t index, void* item);
	void Reserve(size_t size);
	void Insert(size_t index, void* item);
	void PushBack(void* item);
	void PopBack();
	void Erase(size_t index);
	void EraseRange(size_t first, size_t last);
} VectorList;

//End Vector

#endif