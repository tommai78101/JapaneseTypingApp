#ifndef __COMMON_H__
#	define __COMMON_H__

#pragma once

//SDL libraries
#include <SDL.h>
#include <SDL_ttf.h>

//Standard libraries
#include <cstring>						//For std::memmove, std::memcpy only
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <sstream>
#include <locale>

#ifdef _WIN32
#	include <Windows.h>
#elif defined _UNIX
#	include <unistd.h>
#endif

typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16>> u16string;

//For anything using size_t, use size_t.
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
const size_t RED_MASK = 0xff000000;
const size_t GREEN_MASK = 0x00ff0000;
const size_t BLUE_MASK = 0x0000ff00;
const size_t ALPHA_MASK = 0x000000ff;
#else
const size_t RED_MASK = 0x000000ff;
const size_t GREEN_MASK = 0x0000ff00;
const size_t BLUE_MASK = 0x00ff0000;
const size_t ALPHA_MASK = 0xff000000;
#endif

enum UpOrientation {
	NORTH,
	NORTHEAST,
	NORTHWEST
};

//Helper functions

static inline SDL_Surface* SDLHelper_CreateSurface(int width, int height, int depth) {
	return SDL_CreateRGBSurface(0, width, height, depth, RED_MASK, GREEN_MASK, BLUE_MASK, ALPHA_MASK);
}

static bool CreateUnicodeTexture(wchar_t* LString, SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Surface** outputSurface, SDL_Texture** outputTexture) {
	try {
		std::wstring temp(LString);
		u16string buffer(temp.begin(), temp.end());
		*outputSurface = TTF_RenderUNICODE_Solid(font, buffer.c_str(), color);
		*outputTexture = SDL_CreateTextureFromSurface(renderer, *outputSurface);
		return true;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
}

static bool GetCharacterSize(wchar_t* LString, TTF_Font* font, int* outWidth, int* outHeight) {
	try {
		std::wstring temp(LString);
		u16string buffer(temp.begin(), temp.end());
		if (TTF_SizeUNICODE(font, buffer.c_str(), outWidth, outHeight) == -1) {
			std::cerr << "Wrong size of unicode text." << std::endl;
			throw std::exception("Unicode text is of wrong size.");
		}
		return true;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
}

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
	size_t data[3];
	struct {
		size_t x;
		size_t y;
		size_t z;
	};
} Vector3Di;

//End Integer Vector3D stuffs

//Integer Vector4D stuffs

typedef union {
	size_t data[4];
	struct {
		size_t x;
		size_t y;
		size_t z;
		size_t w;
	};
	struct {
		size_t x;
		size_t y;
		size_t width;
		size_t height;
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

//Float Vector4D stuffs

typedef union {
	float data[4];
	struct {
		float s0;
		float t0;
		float s1;
		float t1;
	};
	struct {
		float topLeftX;
		float topLeftY;
		float bottomRightX;
		float bottomRightY;
	};
	struct {
		float x;
		float y;
		float z;
		float w;
	};
} Vector4Df;

//End Float Vector4D stuffs

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
	void Clear();
} VectorList;

//End Vector

#endif