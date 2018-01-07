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
#include <fstream>
#include <locale>
#include <vector>

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

static bool IsLittleEndian() {
	uint16_t x = 0x0001;
	auto p = reinterpret_cast<uint8_t*>(&x);
	return *p != 0;
}

static SDL_Surface* SDLHelper_CreateSurface(int width, int height, int depth) {
	/* SDL_CreateRGBSurface parameters: (Left -> Right)
		flags - the flags are unused and should be set to 0
		width - the width of the surface
		height - the height of the surface
		depth - the depth of the surface in bits; see Remarks for details
		Rmask - the red mask for the pixels
		Gmask - the green mask for the pixels
		Bmask - the blue mask for the pixels
		Amask - the alpha mask for the pixels
	*/
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

//Unicode UTF-8 <-> UTF-32 support
extern void Convert_utf8_utf32(std::string& input, std::u32string& output);
extern void Convert_utf32_utf8(std::u32string& input, std::string& output);

//Unicode Substrings
extern std::string SubstringUpToFirstUTF8(std::string& value, char* firstContainer);
extern std::string SubstringInsideUTF8(std::string& value, char* firstContainer, char* lastContainer);

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

//Trie structures

//KeycodeTrieNode
//For use with KeyCodeTrie that maps SDL_Keycode to the leaf value.

struct KeyCodeTrieNode {
	std::vector<KeyCodeTrieNode*> children;
	SDL_Keycode value;
	char* leafValue = nullptr;

	void Clear();
	bool IsLeaf();
	KeyCodeTrieNode* SearchChild(SDL_Keycode& value);
};

//KeyCodeTrie data structure
//Maps SDL_Keycode inputs to a single UTF-8 hiragana / katakana for input.

struct KeyCodeTrie {
	KeyCodeTrieNode* root = new KeyCodeTrieNode();

	~KeyCodeTrie() {
		this->root->Clear();
		delete this->root;
	}

	void Insert(std::vector<SDL_Keycode>& value, char* leafValue);
	bool Contains(std::vector<SDL_Keycode>& value);
	char* Get(std::vector<SDL_Keycode>& value);
	KeyCodeTrieNode* GetNode(std::vector<SDL_Keycode>& value);
};

struct VocabularyTrieNode {
	std::vector<VocabularyTrieNode*> children;
	std::string vocabulary; //Single kanji, hiragana, or katakana character.
	std::string pronunciation; //Multiple hiragana or katakana characters.

	void Clear();
	bool IsLeaf();
	VocabularyTrieNode* SearchChild(std::string& value);
};

struct VocabularyTrie {

};

//End Trie structures

//Constants
static const SDL_Color SDL_COLOR_Black = { };
static const SDL_Color SDL_COLOR_Red = { 255, 0 };

//C++ class headers.
#include "draw.h"
#include "block.h"
#include "input.h"
#include "game.h"

#endif