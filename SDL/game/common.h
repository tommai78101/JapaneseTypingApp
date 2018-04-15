#ifndef __COMMON_H__
#	define __COMMON_H__

#pragma once 

#ifdef _WIN32
#	include <Windows.h>
#elif defined _UNIX
#	include <unistd.h>
#elif defined __SWITCH__
#	include <switch.h>
#endif

//Standard C++ libraries
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

//SDL libraries
#include <SDL.h>
#include <SDL_ttf.h>

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

//strcpy_s
template<typename C>
inline int strcpy_s(C*d, unsigned long dmax, const C*s) { 
	if (dmax <= 1 || !d) { 
		if (!d || !dmax)
			return -1;
		*d = C(0); 
		return 0; 
	}
	for (C*de = d + dmax - 1; (d != de || (*d = C(0))) && (*d = *s); ++d, ++s); 
	return 0; 
}

//strdup wrapper
inline char* strdupWrapper(const char* str) {
#ifdef _WIN32
	return _strdup(str);
#else
	return strdup(str);
#endif
}

//Unicode Substrings
extern std::string SubstringUpToFirstUTF8(std::string& value, char* firstContainer);
extern std::string SubstringInsideUTF8(std::string& value, char* firstContainer, char* lastContainer);

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

static void ParseLine(std::u32string& formattedLine, std::vector<std::u32string>& vocabulary, std::vector<std::u32string>& pronunciation, std::u32string& definition) {
	//Custom string parser, suitable only for extracting information from the EDICT2 (UTF-8) file.
	bool vocabularyExtracted = false;
	bool pronunciationExtracted = false;
	bool definitionExtracted = false;
	bool pronunciationMarked = false;
	bool definitionMarked = false;
	std::u32string token;
	for (unsigned int i = 0; i < formattedLine.size(); i++) {
		if (!vocabularyExtracted) {
			if (formattedLine[i] != U' ' && formattedLine[i + 1] != U'[') {
				if (formattedLine[i] == U';') {
					vocabulary.push_back(token);
					token.clear();
				}
				else if (formattedLine[i] == U'(' && formattedLine[i+1] == U'i' && formattedLine[i+2] == U'K' && formattedLine[i+3] == U')') {
					i += 3;
				}
				else {
					token += formattedLine[i];
				}
			}
			else {
				vocabularyExtracted = true;
				vocabulary.push_back(token);
				token.clear();
			}
		}
		else if (!pronunciationMarked) {
			if (formattedLine[i] != U'[')
				continue;
			else
				pronunciationMarked = true;
		}
		else if (!pronunciationExtracted) {
			if (formattedLine[i] != U']') {
				if (formattedLine[i] == U';') {
					pronunciation.push_back(token);
					token.clear();
				}
				else {
					token += formattedLine[i];
				}
			}
			else {
				pronunciationExtracted = true;
				pronunciation.push_back(token);
				token.clear();
			}
		}
		else if (!definitionMarked) {
			if (formattedLine[i] != U'/')
				continue;
			else
				definitionMarked = true;
		}
		else if (!definitionExtracted) {
			if (formattedLine[i] == U'/' && formattedLine[i + 1] == U'E' && formattedLine[i + 2] == U'n' && formattedLine[i + 3] == U't' && formattedLine[i + 4] == U'L') {
				definitionExtracted = true;
				definition = token;
				return;
			}
			else
				token += formattedLine[i];
		}
	}
}

//Unicode UTF-8 <-> UTF-32 support
static void Convert_utf8_utf32(std::string& input, std::u32string& output) {
	const uint32_t UTF32Mask = 0x001fffff;
	int i = 0;
	output.clear();
	while (1) {
		uint8_t iterator = (uint8_t) input[i];
		if (!iterator)
			break;
		if (iterator < 0x80) {
			//1 codepoint
			output += (char32_t) (UTF32Mask & iterator);
			i++;
		}
		else if (iterator < 0xC0) {
			//midstream identifier, invalid
			i++;
			continue;
		}
		else if (iterator < 0xE0) {
			//2 codepoint
			uint8_t firstPoint = (uint8_t) (input[i] & 0x1F);
			uint8_t secondPoint = (uint8_t) (input[i + 1] & 0x3F);
			if (!IsLittleEndian()) {
				output += (char32_t) (UTF32Mask & ((secondPoint << 6) | firstPoint));
			}
			else {
				output += (char32_t) (UTF32Mask & ((firstPoint << 6) | secondPoint));
			}
			i += 2;
		}
		else if (iterator < 0xF0) {
			//3 codepoints
			uint8_t firstPoint = (uint8_t) (input[i] & 0x0F);
			uint8_t secondPoint = (uint8_t) (input[i + 1] & 0x3F);
			uint8_t thirdPoint = (uint8_t) (input[i + 2] & 0x3F);
			if (!IsLittleEndian()) {
				output += (char32_t) (UTF32Mask & ((thirdPoint << 12) | (secondPoint << 6) | firstPoint));
			}
			else {
				output += (char32_t) (UTF32Mask & ((firstPoint << 12) | (secondPoint << 6) | thirdPoint));
			}
			i += 3;
		}
		else if (iterator < 0xF8) {
			//4 codepoints
			uint8_t firstPoint = (uint8_t) (input[i] & 0x07);
			uint8_t secondPoint = (uint8_t) (input[i + 1] & 0x3F);
			uint8_t thirdPoint = (uint8_t) (input[i + 2] & 0x3F);
			uint8_t fourthPoint = (uint8_t) (input[i + 3] & 0x3F);
			if (!IsLittleEndian()) {
				output += (char32_t) (UTF32Mask & ((fourthPoint << 18) | (thirdPoint << 12) | (secondPoint << 6) | firstPoint));
			}
			else {
				output += (char32_t) (UTF32Mask & ((firstPoint << 18) | (secondPoint << 12) | (thirdPoint << 6) | fourthPoint));
			}
			i += 4;
		}
		else {
			//Invalid everything else
			i++;
		}
	}
}

static void Convert_utf32_utf8(std::u32string& input, std::string& output) {
	const uint8_t UTF8Midstream = 0x80;
	const uint8_t UTF8MidstreamMask = 0x3f;
	int i = 0;
	output.clear();
	while (1) {
		uint32_t iterator = (uint32_t) input[i];
		if (!iterator)
			break;
		if (iterator < 0x80) {
			//U+0000..U+007F
			output += (uint8_t) (0x7f & iterator);
		}
		else if (iterator < 0x800) {
			//U+0080..U+07FF
			uint8_t firstPoint = (uint8_t) (((0xDF << 6) & iterator) >> 6);
			uint8_t secondPoint = (uint8_t) (0x3F & iterator);
			if (!IsLittleEndian()) {
				output += (uint8_t) (0xC0 | (0xDF & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & firstPoint));
			}
			else {
				output += (uint8_t) (0xC0 | (0xDF & firstPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
			}
		}
		else if (iterator < 0xE000) {
			//U+8000..U+D7FF (TUS 2.0)
			uint8_t firstPoint = (uint8_t) (((0xF << 12) & iterator) >> 12);
			uint8_t secondPoint = (uint8_t) (((0x3F << 6) & iterator) >> 6);
			uint8_t thirdPoint = (uint8_t) (0x3F & iterator);
			if (!IsLittleEndian()) {
				output += (uint8_t) (0xE0 | (0x0F & thirdPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & firstPoint));
			}
			else {
				output += (uint8_t) (0xE0 | (0x0F & firstPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & thirdPoint));
			}
		}
		else if (iterator < 0x10000) {
			//U+E000..U+FFFF (TUS 3.1)
			uint8_t firstPoint = (uint8_t) (((0xF << 12) & iterator) >> 12);
			uint8_t secondPoint = (uint8_t) (((0x3F << 6) & iterator) >> 6);
			uint8_t thirdPoint = (uint8_t) (0x3F & iterator);
			if (!IsLittleEndian()) {
				output += (uint8_t) (0xE0 | (0x0F & thirdPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & firstPoint));
			}
			else {
				output += (uint8_t) (0xE0 | (0x0F & firstPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & thirdPoint));
			}
		}
		else if (iterator < 0x1FFFF) {
			uint8_t firstPoint = (uint8_t) (((0x7 << 18) & iterator) >> 18);
			uint8_t secondPoint = (uint8_t) (((0x3F << 12) & iterator) >> 12);
			uint8_t thirdPoint = (uint8_t) (((0x3F << 6) & iterator) >> 6);
			uint8_t fourthPoint = (uint8_t) (0x3F & iterator);
			if (!IsLittleEndian()) {
				output += (uint8_t) (0xE0 | (0x07 & fourthPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & thirdPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & firstPoint));
			}
			else {
				output += (uint8_t) (0xE0 | (0x07 & firstPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & thirdPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & fourthPoint));
			}
		}
		i++;
	}
}

//End Helper functions

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
	struct vector {
		size_t x;
		size_t y;
		size_t z;
	} vector;
} Vector3Di;

//End Integer Vector3D stuffs

//Integer Vector4D stuffs

typedef union {
	size_t data[4];
	struct quaternion {
		size_t x;
		size_t y;
		size_t z;
		size_t w;
	} quaternion;
	struct rect {
		size_t x;
		size_t y;
		size_t width;
		size_t height;
	} rect;
} Vector4Di;

//End Integer Vector4D stuffs

//Float32 Vector3D stuffs

typedef union {
	float data[3];
	struct vector {
		float x;
		float y;
		float z;
	} vector;
} Vector3Df;

//End Float32 Vector3D stuffs

//Float Vector4D stuffs

typedef union {
	float data[4];
	struct coordinates {
		float s0;
		float t0;
		float s1;
		float t1;
	} coordinates;
	struct rect {
		float topLeftX;
		float topLeftY;
		float bottomRightX;
		float bottomRightY;
	} rect;
	struct quaternion {
		float x;
		float y;
		float z;
		float w;
	} quaternion;
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

//VocabularyTrieNode

struct VocabularyTrieNode {
	std::vector<VocabularyTrieNode*> children;
	char32_t vocabulary; //Single kanji, hiragana, or katakana character.
	std::u32string pronunciation; //Multiple hiragana or katakana characters.
	std::u32string englishDefinition; //Contains English definition.

	void Clear();
	bool IsLeaf();
	VocabularyTrieNode* SearchChild(char32_t& value);
};

//End of VocabularyTrieNode

//VocabularyTrie

struct VocabularyTrie {
	VocabularyTrieNode* root = new VocabularyTrieNode();
	unsigned int size = 0;

	~VocabularyTrie() {
		this->root->Clear();
		delete this->root;
	}

	void Insert(std::u32string& value, std::u32string& leafValue, std::u32string& definition);
	void Insert(std::string& value, std::string& leafValue, std::string& definition);
	void Insert(char* value, char* leafValue, char* definition);
	bool Contains(std::u32string& value);
	bool Contains(std::string& value);
	bool Contains(char* value);
	std::string GetPronunciation(std::u32string& value);
	std::string GetPronunciation(std::string& value);
	std::string GetPronunciation(char* value);
	std::string GetDefinition(std::u32string& value);
	std::string GetDefinition(std::string& value);
	std::string GetDefinition(char* value);
	VocabularyTrieNode* GetNode(std::u32string& value);
	VocabularyTrieNode* GetNode(std::string& value);
	VocabularyTrieNode* GetNode(char* value);
	unsigned int GetSize();
};

//End VocabularyTrie

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