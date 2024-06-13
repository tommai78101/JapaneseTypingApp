#ifndef __COMMON_H__
#	define __COMMON_H__

#pragma once 

#ifdef __SWITCH__
#	undef _WIN32
#endif

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
#include <thread>
#include <mutex>
#include <memory>
#include <set>
#include <unordered_map>

//SDL libraries
#pragma warning(push, 0)
#ifdef __SWITCH__
#	include <SDL2/SDL.h>
#	include <SDL2/SDL_ttf.h>
//Exclusively POSIX header file
#	include <dirent.h>
#else
#	include <SDL.h>
#	include <SDL_ttf.h>
#	include <SDL_thread.h>
#endif
#pragma warning(pop)

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

enum class UpOrientation {
	NORTH,
	NORTHEAST,
	NORTHWEST
};

//Helper functions

//strcpy_s
template<typename C>
inline int strcpy_s(C* d, unsigned long dmax, const C* s) {
	if (dmax <= 1 || !d) {
		if (!d || !dmax)
			return -1;
		*d = C(0);
		return 0;
	}
	for (C* de = d + dmax - 1; (d != de || (*d = C(0))) && (*d = *s); ++d, ++s);
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

// SDL_vsnprintf
static void Print(const char* format, ...) {
	va_list args;
	char buffer[256];
	va_start(args, format);
	SDL_vsnprintf(buffer, 255, format, args);
	va_end(args);
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
	for (size_t i = 0; i < formattedLine.size(); i++) {
		if (!vocabularyExtracted) {
			if (formattedLine[i] != U' ' && formattedLine[i + 1] != U'[') {
				if (formattedLine[i] == U';') {
					vocabulary.push_back(token);
					token.clear();
				}
				else if (formattedLine[i] == U'(' && formattedLine[i + 1] == U'i' && formattedLine[i + 2] == U'K' && formattedLine[i + 3] == U')') {
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
	size_t i = 0;
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
	SDL_Keycode value = SDL_Keycode(0);
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
	char32_t vocabulary = 0; //Single kanji, hiragana, or katakana character.
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

#ifdef __SWITCH__
static const char* EDICT2PATH = "romfs:/edict2u";
#else
static const char* EDICT2PATH = "dict/edict2u";
#endif

//static const char* FONTPATH = "font/meiryo.ttc";
//static const char* FONTPATH = "font/JapanSan.ttf";
static const char* FONTPATH = "font/PretendardJP-Regular.ttf";
static const char* DEBUG = "(debug) ";

//Switch Joycon keys
#ifdef __SWITCH__
class JoyconButtons {
public:
	static const uint8_t KEY_A = 0;
	static const uint8_t KEY_B = 1;
	static const uint8_t KEY_X = 2;
	static const uint8_t KEY_Y = 3;

	static const uint8_t KEY_LSTICK = 4;
	static const uint8_t KEY_RSTICK = 5;

	static const uint8_t KEY_L = 6;
	static const uint8_t KEY_R = 7;

	static const uint8_t KEY_ZL = 8;
	static const uint8_t KEY_ZR = 9;

	static const uint8_t KEY_PLUS = 10;
	static const uint8_t KEY_MINUS = 11;

	static const uint8_t KEY_DLEFT = 12;
	static const uint8_t KEY_DUP = 13;
	static const uint8_t KEY_DRIGHT = 14;
	static const uint8_t KEY_DDOWN = 15;

	static const uint8_t KEY_LSTICK_LEFT = 16;
	static const uint8_t KEY_LSTICK_UP = 17;
	static const uint8_t KEY_LSTICK_RIGHT = 18;
	static const uint8_t KEY_LSTICK_DOWN = 19;

	static const uint8_t KEY_RSTICK_LEFT = 20;
	static const uint8_t KEY_RSTICK_UP = 21;
	static const uint8_t KEY_RSTICK_RIGHT = 22;
	static const uint8_t KEY_RSTICK_DOWN = 23;
};
#endif

//Japanese character constants
struct Japanese {
	//Note(asperatology): There may be more than one method of typing the characters out. Therefore, there may be multiple entries for one glyph.
	//Glyphs may be 2 characters long. Big sized glyphs go on top; Small sized glyphs go on bottom.

	//Sorted by "hiragana order"
	//There are conflicts with reserved keywords, so the conflicted variable names end with an underscore (_) for differentiation.

	struct Hiragana {
		//Hiragana
		//あ
		static inline const char* a = u8"あ";
		static inline const char* la = u8"ぁ";
		static inline const char* xa = u8"ぁ";

		//い
		static inline const char* i = u8"い";
		static inline const char* yi = u8"い";
		static inline const char* li = u8"ぃ";
		static inline const char* lyi = u8"ぃ";
		static inline const char* xi = u8"ぃ";
		static inline const char* xyi = u8"ぃ";
		static inline const char* ye = u8"いぇ";

		//う
		static inline const char* u = u8"う";
		static inline const char* whu = u8"う";
		static inline const char* wu = u8"う";
		static inline const char* lu = u8"ぅ";
		static inline const char* xu = u8"ぅ";
		static inline const char* wha = u8"うぁ";
		static inline const char* whi = u8"うぃ";
		static inline const char* wi = u8"うぃ";
		static inline const char* we = u8"うぇ";
		static inline const char* whe = u8"うぇ";
		static inline const char* who = u8"うぉ";

		//え
		static inline const char* e = u8"え";
		static inline const char* le = u8"ぇ";
		static inline const char* lye = u8"ぇ";
		static inline const char* xe = u8"ぇ";
		static inline const char* xye = u8"ぇ";

		//お
		static inline const char* o = u8"お";
		static inline const char* lo = u8"ぉ";
		static inline const char* xo = u8"ぉ";

		//------

		//か
		static inline const char* ca = u8"か";
		static inline const char* ka = u8"か";
		static inline const char* lka = u8"ゕ";
		static inline const char* xka = u8"ゕ";

		//き
		static inline const char* ki = u8"き";
		static inline const char* kyi = u8"きぃ";
		static inline const char* kye = u8"きぇ";
		static inline const char* kya = u8"きゃ";
		static inline const char* kyu = u8"きゅ";
		static inline const char* kyo = u8"きょ";

		//く
		static inline const char* cu = u8"く";
		static inline const char* ku = u8"く";
		static inline const char* qu = u8"く";
		static inline const char* kwa = u8"くぁ";
		static inline const char* qa = u8"くぁ";
		static inline const char* qwa = u8"くぁ";
		static inline const char* qi = u8"くぃ";
		static inline const char* qwi = u8"くぃ";
		static inline const char* qyi = u8"くぃ";
		static inline const char* qwu = u8"くぅ";
		static inline const char* qe = u8"くぇ";
		static inline const char* qwe = u8"くぇ";
		static inline const char* qye = u8"くぇ";
		static inline const char* qo = u8"くぉ";
		static inline const char* qwo = u8"くぉ";
		static inline const char* qya = u8"くゃ";
		static inline const char* qyu = u8"くゅ";
		static inline const char* qyo = u8"くょ";

		//け
		static inline const char* ke = u8"け";
		static inline const char* lke = u8"ゖ";
		static inline const char* xke = u8"ゖ";

		//こ
		static inline const char* co = u8"こ";
		static inline const char* ko = u8"こ";

		//------

		//さ
		static inline const char* sa = u8"さ";

		//し
		static inline const char* ci = u8"し";
		static inline const char* shi = u8"し";
		static inline const char* si = u8"し";
		static inline const char* syi = u8"しぃ";
		static inline const char* she = u8"しぇ";
		static inline const char* sye = u8"しぇ";
		static inline const char* sha = u8"しゃ";
		static inline const char* sya = u8"しゃ";
		static inline const char* shu = u8"しゅ";
		static inline const char* syu = u8"しゅ";
		static inline const char* sho = u8"しょ";
		static inline const char* syo = u8"しょ";

		//す
		static inline const char* su = u8"す";
		static inline const char* swa = u8"すぁ";
		static inline const char* swi = u8"すぃ";
		static inline const char* swu = u8"すぅ";
		static inline const char* swe = u8"すぇ";
		static inline const char* swo = u8"すぉ";

		//せ
		static inline const char* ce = u8"せ";
		static inline const char* se = u8"せ";

		//そ
		static inline const char* so = u8"そ";

		//------

		//た
		static inline const char* ta = u8"た";

		//ち
		static inline const char* chi = u8"ち";
		static inline const char* ti = u8"ち";
		static inline const char* cyi = u8"ちぃ";
		static inline const char* tyi = u8"ちぃ";
		static inline const char* che = u8"ちぇ";
		static inline const char* cye = u8"ちぇ";
		static inline const char* tye = u8"ちぇ";
		static inline const char* cha = u8"ちゃ";
		static inline const char* cya = u8"ちゃ";
		static inline const char* tya = u8"ちゃ";
		static inline const char* chu = u8"ちゅ";
		static inline const char* cyu = u8"ちゅ";
		static inline const char* tyu = u8"ちゅ";
		static inline const char* cho = u8"ちょ";
		static inline const char* cyo = u8"ちょ";
		static inline const char* tyo = u8"ちょ";

		//つ
		static inline const char* tsu = u8"つ";
		static inline const char* tu = u8"つ";
		static inline const char* tsa = u8"つぁ";
		static inline const char* tsi = u8"つぃ";
		static inline const char* tse = u8"つぇ";
		static inline const char* tso = u8"つぉ";
		static inline const char* ltsu = u8"っ";
		static inline const char* ltu = u8"っ";
		static inline const char* xtsu = u8"っ";
		static inline const char* xtu = u8"っ";

		//て
		static inline const char* te = u8"て";
		static inline const char* thi = u8"てぃ";
		static inline const char* the = u8"てぇ";
		static inline const char* tha = u8"てゃ";
		static inline const char* thu = u8"てゅ";
		static inline const char* tho = u8"てょ";


		//と
		static inline const char* to = u8"と";
		static inline const char* twa = u8"とぁ";
		static inline const char* twi = u8"とぃ";
		static inline const char* twu = u8"とぅ";
		static inline const char* twe = u8"とぇ";
		static inline const char* two = u8"とぉ";

		//------

		//な
		static inline const char* na = u8"な";

		//に
		static inline const char* ni = u8"に";
		static inline const char* nyi = u8"にぃ";
		static inline const char* nye = u8"にぇ";
		static inline const char* nya = u8"にゃ";
		static inline const char* nyu = u8"にゅ";
		static inline const char* nyo = u8"にょ";

		//ぬ
		static inline const char* nu = u8"ぬ";

		//ね
		static inline const char* ne = u8"ね";

		//の
		static inline const char* no = u8"の";

		//------

		//は
		static inline const char* ha = u8"は";

		//ひ
		static inline const char* hi = u8"ひ";
		static inline const char* hyi = u8"ひぃ";
		static inline const char* hye = u8"ひぇ";
		static inline const char* hya = u8"ひゃ";
		static inline const char* hyu = u8"ひゅ";
		static inline const char* hyo = u8"ひょ";

		//ふ
		static inline const char* fu = u8"ふ";
		static inline const char* hu = u8"ふ";
		static inline const char* fa = u8"ふぁ";
		static inline const char* fwa = u8"ふぁ";
		static inline const char* fi = u8"ふぃ";
		static inline const char* fwi = u8"ふぃ";
		static inline const char* fyi = u8"ふぃ";
		static inline const char* fwu = u8"ふぅ";
		static inline const char* fe = u8"ふぇ";
		static inline const char* fwe = u8"ふぇ";
		static inline const char* fye = u8"ふぇ";
		static inline const char* fo = u8"ふぉ";
		static inline const char* fwo = u8"ふぉ";
		static inline const char* fya = u8"ふゃ";
		static inline const char* fyu = u8"ふゅ";
		static inline const char* fyo = u8"ふょ";

		//へ
		static inline const char* he = u8"へ";

		//ほ
		static inline const char* ho = u8"ほ";

		//------

		//ま
		static inline const char* ma = u8"ま";

		//み
		static inline const char* mi = u8"み";
		static inline const char* myi = u8"みぃ";
		static inline const char* mye = u8"みぇ";
		static inline const char* mya = u8"みゃ";
		static inline const char* myu = u8"みゅ";
		static inline const char* myo = u8"みょ";

		//む
		static inline const char* mu = u8"む";

		//め
		static inline const char* me = u8"め";

		//も
		static inline const char* mo = u8"も";

		//------

		//や
		static inline const char* ya = u8"や";
		static inline const char* lya = u8"ゃ";
		static inline const char* xya = u8"ゃ";

		//ゆ
		static inline const char* yu = u8"ゆ";
		static inline const char* lyu = u8"ゅ";
		static inline const char* xyu = u8"ゅ";

		//よ
		static inline const char* yo = u8"よ";
		static inline const char* lyo = u8"ょ";
		static inline const char* xyo = u8"ょ";

		//------

		//ら
		static inline const char* ra = u8"ら";

		//り
		static inline const char* ri = u8"り";
		static inline const char* ryi = u8"りぃ";
		static inline const char* rye = u8"りぇ";
		static inline const char* rya = u8"りゃ";
		static inline const char* ryu = u8"りゅ";
		static inline const char* ryo = u8"りょ";

		//る
		static inline const char* ru = u8"る";

		//れ
		static inline const char* re = u8"れ";

		//ろ
		static inline const char* ro = u8"ろ";

		//------

		//わ
		static inline const char* wa = u8"わ";
		static inline const char* lwa = u8"ゎ";
		static inline const char* xwa = u8"ゎ";

		//ゐ
		static inline const char* wyi = u8"ゐ";

		//ゑ
		static inline const char* wye = u8"ゑ";

		//を
		static inline const char* wo = u8"を";

		//------

		//ん
		static inline const char* nn = u8"ん";
		static inline const char* xn = u8"ん";

		//------
		//Modifiers - Hiragana
		//が
		static inline const char* ga = u8"が";

		//ぎ
		static inline const char* gi = u8"ぎ";
		static inline const char* gyi = u8"ぎぃ";
		static inline const char* gye = u8"ぎぇ";
		static inline const char* gya = u8"ぎゃ";
		static inline const char* gyu = u8"ぎゅ";
		static inline const char* gyo = u8"ぎょ";

		//ぐ
		static inline const char* gu = u8"ぐ";
		static inline const char* gwa = u8"ぐぁ";
		static inline const char* gwi = u8"ぐぃ";
		static inline const char* gwu = u8"ぐぅ";
		static inline const char* gwe = u8"ぐぇ";
		static inline const char* gwo = u8"ぐぉ";

		//げ
		static inline const char* ge = u8"げ";

		//ご
		static inline const char* go = u8"ご";

		//ざ
		static inline const char* za = u8"さ";

		//じ
		static inline const char* ji = u8"じ";
		static inline const char* zi = u8"じ";
		static inline const char* jyi = u8"じぃ";
		static inline const char* zyi = u8"じぃ";
		static inline const char* je = u8"じぇ";
		static inline const char* jye = u8"じぇ";
		static inline const char* zye = u8"じぇ";
		static inline const char* ja = u8"じゃ";
		static inline const char* jya = u8"じゃ";
		static inline const char* zya = u8"じゃ";
		static inline const char* ju = u8"じゅ";
		static inline const char* jyu = u8"じゅ";
		static inline const char* zyu = u8"じゅ";
		static inline const char* jo = u8"じょ";
		static inline const char* jyo = u8"じょ";
		static inline const char* zyo = u8"じょ";

		//ず
		static inline const char* zu = u8"ず";

		//ぜ
		static inline const char* ze = u8"ぜ";

		//ぞ
		static inline const char* zo = u8"ぞ";

		//だ
		static inline const char* da = u8"だ";

		//ぢ
		static inline const char* di = u8"ぢ";
		static inline const char* dyi = u8"ぢぃ";
		static inline const char* dye = u8"ぢぇ";
		static inline const char* dya = u8"ぢゃ";
		static inline const char* dyu = u8"ぢゅ";
		static inline const char* dyo = u8"ぢょ";

		//づ
		static inline const char* du = u8"づ";

		//で
		static inline const char* de = u8"で";
		static inline const char* dhi = u8"でぃ";
		static inline const char* dhe = u8"でぇ";
		static inline const char* dha = u8"でゃ";
		static inline const char* dhu = u8"でゅ";
		static inline const char* dho = u8"でょ";

		//ど
		static inline const char* do_ = u8"ど";
		static inline const char* dwa = u8"どぁ";
		static inline const char* dwi = u8"どぃ";
		static inline const char* dwu = u8"どぅ";
		static inline const char* dwe = u8"どぇ";
		static inline const char* dwo = u8"どぉ";

		//ば
		static inline const char* ba = u8"ば";

		//ぱ
		static inline const char* pa = u8"ぱ";

		//び
		static inline const char* bi = u8"び";
		static inline const char* byi = u8"びぃ";
		static inline const char* bye = u8"びぇ";
		static inline const char* bya = u8"びゃ";
		static inline const char* byu = u8"びゅ";
		static inline const char* byo = u8"びょ";

		//ぴ
		static inline const char* pi = u8"ぴ";
		static inline const char* pyi = u8"ぴぃ";
		static inline const char* pye = u8"ぴぇ";
		static inline const char* pya = u8"ぴゃ";
		static inline const char* pyu = u8"ぴゅ";
		static inline const char* pyo = u8"ぴょ";

		//ぶ
		static inline const char* bu = u8"ぶ";

		//ぷ
		static inline const char* pu = u8"ぷ";

		//べ
		static inline const char* be = u8"べ";

		//ぺ
		static inline const char* pe = u8"ぺ";

		//ぼ
		static inline const char* bo = u8"ぼ";

		//ぽ
		static inline const char* po = u8"ぽ";

		//ヴ
		static inline const char* va = u8"ヴぁ";
		static inline const char* vi = u8"ヴぃ";
		static inline const char* vyi = u8"ヴぃ";
		static inline const char* ve = u8"ヴぇ";
		static inline const char* vye = u8"ヴぇ";
		static inline const char* vo = u8"ヴぉ";
		static inline const char* vya = u8"ヴゃ";
		static inline const char* vyu = u8"ヴゅ";
		static inline const char* vyo = u8"ヴょ";

		//Hiragana class stuffs
		static inline const char* List[] = {
			u8"あ", u8"ぁ", u8"い", u8"ぃ", u8"いぇ", u8"う", u8"ぅ", u8"うぁ", u8"うぃ", u8"うぇ", u8"うぉ", u8"え", u8"ぇ", u8"お", u8"ぉ", u8"か", u8"ゕ", u8"き", u8"きぃ", u8"きぇ", u8"きゃ", u8"きゅ", u8"きょ", u8"く", u8"くぁ", u8"くぃ", u8"くぅ", u8"くぇ", u8"くぉ", u8"くゃ", u8"くゅ", u8"くょ", u8"け", u8"ゖ", u8"こ", u8"さ", u8"し", u8"しぃ", u8"しぇ", u8"しゃ", u8"しゅ", u8"しょ", u8"す", u8"すぁ", u8"すぃ", u8"すぅ", u8"すぇ", u8"すぉ", u8"せ", u8"そ", u8"た", u8"ち", u8"ちぃ", u8"ちぇ", u8"ちゃ", u8"ちゅ", u8"ちょ", u8"つ", u8"つぁ", u8"つぃ", u8"つぇ", u8"つぉ", u8"っ", u8"て", u8"てぃ", u8"てぇ", u8"てゃ", u8"てゅ", u8"てょ", u8"と", u8"とぁ", u8"とぃ", u8"とぅ", u8"とぇ", u8"とぉ", u8"な", u8"に", u8"にぃ", u8"にぇ", u8"にゃ", u8"にゅ", u8"にょ", u8"ぬ", u8"ね", u8"の", u8"は", u8"ひ", u8"ひぃ", u8"ひぇ", u8"ひゃ", u8"ひゅ", u8"ひょ", u8"ふ", u8"ふぁ", u8"ふぃ", u8"ふぅ", u8"ふぇ", u8"ふぉ", u8"ふゃ", u8"ふゅ", u8"ふょ", u8"へ", u8"ほ", u8"ま", u8"み", u8"みぃ", u8"みぇ", u8"みゃ", u8"みゅ", u8"みょ", u8"む", u8"め", u8"も", u8"や", u8"ゃ", u8"ゆ", u8"ゅ", u8"よ", u8"ょ", u8"ら", u8"り", u8"りぃ", u8"りぇ", u8"りゃ", u8"りゅ", u8"りょ", u8"る", u8"れ", u8"ろ", u8"わ", u8"ゎ", u8"ゐ", u8"ゑ", u8"を", u8"ん", u8"が", u8"ぎ", u8"ぎぃ", u8"ぎぇ", u8"ぎゃ", u8"ぎゅ", u8"ぎょ", u8"ぐ", u8"ぐぁ", u8"ぐぃ", u8"ぐぅ", u8"ぐぇ", u8"ぐぉ", u8"げ", u8"ご", u8"さ", u8"じ", u8"じぃ", u8"じぇ", u8"じゃ", u8"じゅ", u8"じょ", u8"ず", u8"ぜ", u8"ぞ", u8"だ", u8"ぢ", u8"ぢぃ", u8"ぢぇ", u8"ぢゃ", u8"ぢゅ", u8"ぢょ", u8"づ", u8"で", u8"でぃ", u8"でぇ", u8"でゃ", u8"でゅ", u8"でょ", u8"ど", u8"どぁ", u8"どぃ", u8"どぅ", u8"どぇ", u8"どぉ", u8"ば", u8"ぱ", u8"び", u8"びぃ", u8"びぇ", u8"びゃ", u8"びゅ", u8"びょ", u8"ぴ", u8"ぴぃ", u8"ぴぇ", u8"ぴゃ", u8"ぴゅ", u8"ぴょ", u8"ぶ", u8"ぷ", u8"べ", u8"ぺ", u8"ぼ", u8"ぽ", u8"ヴぁ", u8"ヴぃ", u8"ヴぇ", u8"ヴぉ", u8"ヴゃ", u8"ヴゅ", u8"ヴょ"
		};

		//English to Hiragana stuffs
		static inline const std::map<std::string, std::string> en_Hiragana{
			{ u8"あ", "a" },
			{ u8"ぁ", "la" },
			{ u8"ぁ", "xa" },
			{ u8"い", "i" },
			{ u8"い", "yi" },
			{ u8"ぃ", "li" },
			{ u8"ぃ", "lyi" },
			{ u8"ぃ", "xi" },
			{ u8"ぃ", "xyi" },
			{ u8"いぇ", "ye" },
			{ u8"う", "u" },
			{ u8"う", "whu" },
			{ u8"う", "wu" },
			{ u8"ぅ", "lu" },
			{ u8"ぅ", "xu" },
			{ u8"うぁ", "wha" },
			{ u8"うぃ", "whi" },
			{ u8"うぃ", "wi" },
			{ u8"うぇ", "we" },
			{ u8"うぇ", "whe" },
			{ u8"うぉ", "who" },
			{ u8"え", "e" },
			{ u8"ぇ", "le" },
			{ u8"ぇ", "lye" },
			{ u8"ぇ", "xe" },
			{ u8"ぇ", "xye" },
			{ u8"お", "o" },
			{ u8"ぉ", "lo" },
			{ u8"ぉ", "xo" },
			{ u8"か", "ca" },
			{ u8"か", "ka" },
			{ u8"ゕ", "lka" },
			{ u8"ゕ", "xka" },
			{ u8"き", "ki" },
			{ u8"きぃ", "kyi" },
			{ u8"きぇ", "kye" },
			{ u8"きゃ", "kya" },
			{ u8"きゅ", "kyu" },
			{ u8"きょ", "kyo" },
			{ u8"く", "cu" },
			{ u8"く", "ku" },
			{ u8"く", "qu" },
			{ u8"くぁ", "kwa" },
			{ u8"くぁ", "qa" },
			{ u8"くぁ", "qwa" },
			{ u8"くぃ", "qi" },
			{ u8"くぃ", "qwi" },
			{ u8"くぃ", "qyi" },
			{ u8"くぅ", "qwu" },
			{ u8"くぇ", "qe" },
			{ u8"くぇ", "qwe" },
			{ u8"くぇ", "qye" },
			{ u8"くぉ", "qo" },
			{ u8"くぉ", "qwo" },
			{ u8"くゃ", "qya" },
			{ u8"くゅ", "qyu" },
			{ u8"くょ", "qyo" },
			{ u8"け", "ke" },
			{ u8"ゖ", "lke" },
			{ u8"ゖ", "xke" },
			{ u8"こ", "co" },
			{ u8"こ", "ko" },
			{ u8"さ", "sa" },
			{ u8"し", "ci" },
			{ u8"し", "shi" },
			{ u8"し", "si" },
			{ u8"しぃ", "syi" },
			{ u8"しぇ", "she" },
			{ u8"しぇ", "sye" },
			{ u8"しゃ", "sha" },
			{ u8"しゃ", "sya" },
			{ u8"しゅ", "shu" },
			{ u8"しゅ", "syu" },
			{ u8"しょ", "sho" },
			{ u8"しょ", "syo" },
			{ u8"す", "su" },
			{ u8"すぁ", "swa" },
			{ u8"すぃ", "swi" },
			{ u8"すぅ", "swu" },
			{ u8"すぇ", "swe" },
			{ u8"すぉ", "swo" },
			{ u8"せ", "ce" },
			{ u8"せ", "se" },
			{ u8"そ", "so" },
			{ u8"た", "ta" },
			{ u8"ち", "chi" },
			{ u8"ち", "ti" },
			{ u8"ちぃ", "cyi" },
			{ u8"ちぃ", "tyi" },
			{ u8"ちぇ", "che" },
			{ u8"ちぇ", "cye" },
			{ u8"ちぇ", "tye" },
			{ u8"ちゃ", "cha" },
			{ u8"ちゃ", "cya" },
			{ u8"ちゃ", "tya" },
			{ u8"ちゅ", "chu" },
			{ u8"ちゅ", "cyu" },
			{ u8"ちゅ", "tyu" },
			{ u8"ちょ", "cho" },
			{ u8"ちょ", "cyo" },
			{ u8"ちょ", "tyo" },
			{ u8"つ", "tsu" },
			{ u8"つ", "tu" },
			{ u8"つぁ", "tsa" },
			{ u8"つぃ", "tsi" },
			{ u8"つぇ", "tse" },
			{ u8"つぉ", "tso" },
			{ u8"っ", "ltsu" },
			{ u8"っ", "ltu" },
			{ u8"っ", "xtsu" },
			{ u8"っ", "xtu" },
			{ u8"て", "te" },
			{ u8"てぃ", "thi" },
			{ u8"てぇ", "the" },
			{ u8"てゃ", "tha" },
			{ u8"てゅ", "thu" },
			{ u8"てょ", "tho" },
			{ u8"と", "to" },
			{ u8"とぁ", "twa" },
			{ u8"とぃ", "twi" },
			{ u8"とぅ", "twu" },
			{ u8"とぇ", "twe" },
			{ u8"とぉ", "two" },
			{ u8"な", "na" },
			{ u8"に", "ni" },
			{ u8"にぃ", "nyi" },
			{ u8"にぇ", "nye" },
			{ u8"にゃ", "nya" },
			{ u8"にゅ", "nyu" },
			{ u8"にょ", "nyo" },
			{ u8"ぬ", "nu" },
			{ u8"ね", "ne" },
			{ u8"の", "no" },
			{ u8"は", "ha" },
			{ u8"ひ", "hi" },
			{ u8"ひぃ", "hyi" },
			{ u8"ひぇ", "hye" },
			{ u8"ひゃ", "hya" },
			{ u8"ひゅ", "hyu" },
			{ u8"ひょ", "hyo" },
			{ u8"ふ", "fu" },
			{ u8"ふ", "hu" },
			{ u8"ふぁ", "fa" },
			{ u8"ふぁ", "fwa" },
			{ u8"ふぃ", "fi" },
			{ u8"ふぃ", "fwi" },
			{ u8"ふぃ", "fyi" },
			{ u8"ふぅ", "fwu" },
			{ u8"ふぇ", "fe" },
			{ u8"ふぇ", "fwe" },
			{ u8"ふぇ", "fye" },
			{ u8"ふぉ", "fo" },
			{ u8"ふぉ", "fwo" },
			{ u8"ふゃ", "fya" },
			{ u8"ふゅ", "fyu" },
			{ u8"ふょ", "fyo" },
			{ u8"へ", "he" },
			{ u8"ほ", "ho" },
			{ u8"ま", "ma" },
			{ u8"み", "mi" },
			{ u8"みぃ", "myi" },
			{ u8"みぇ", "mye" },
			{ u8"みゃ", "mya" },
			{ u8"みゅ", "myu" },
			{ u8"みょ", "myo" },
			{ u8"む", "mu" },
			{ u8"め", "me" },
			{ u8"も", "mo" },
			{ u8"や", "ya" },
			{ u8"ゃ", "lya" },
			{ u8"ゃ", "xya" },
			{ u8"ゆ", "yu" },
			{ u8"ゅ", "lyu" },
			{ u8"ゅ", "xyu" },
			{ u8"よ", "yo" },
			{ u8"ょ", "lyo" },
			{ u8"ょ", "xyo" },
			{ u8"ら", "ra" },
			{ u8"り", "ri" },
			{ u8"りぃ", "ryi" },
			{ u8"りぇ", "rye" },
			{ u8"りゃ", "rya" },
			{ u8"りゅ", "ryu" },
			{ u8"りょ", "ryo" },
			{ u8"る", "ru" },
			{ u8"れ", "re" },
			{ u8"ろ", "ro" },
			{ u8"わ", "wa" },
			{ u8"ゎ", "lwa" },
			{ u8"ゎ", "xwa" },
			{ u8"ゐ", "wyi" },
			{ u8"ゑ", "wye" },
			{ u8"を", "wo" },
			{ u8"ん", "nn" },
			{ u8"ん", "xn" },
			{ u8"が", "ga" },
			{ u8"ぎ", "gi" },
			{ u8"ぎぃ", "gyi" },
			{ u8"ぎぇ", "gye" },
			{ u8"ぎゃ", "gya" },
			{ u8"ぎゅ", "gyu" },
			{ u8"ぎょ", "gyo" },
			{ u8"ぐ", "gu" },
			{ u8"ぐぁ", "gwa" },
			{ u8"ぐぃ", "gwi" },
			{ u8"ぐぅ", "gwu" },
			{ u8"ぐぇ", "gwe" },
			{ u8"ぐぉ", "gwo" },
			{ u8"げ", "ge" },
			{ u8"ご", "go" },
			{ u8"さ", "za" },
			{ u8"じ", "ji" },
			{ u8"じ", "zi" },
			{ u8"じぃ", "jyi" },
			{ u8"じぃ", "zyi" },
			{ u8"じぇ", "je" },
			{ u8"じぇ", "jye" },
			{ u8"じぇ", "zye" },
			{ u8"じゃ", "ja" },
			{ u8"じゃ", "jya" },
			{ u8"じゃ", "zya" },
			{ u8"じゅ", "ju" },
			{ u8"じゅ", "jyu" },
			{ u8"じゅ", "zyu" },
			{ u8"じょ", "jo" },
			{ u8"じょ", "jyo" },
			{ u8"じょ", "zyo" },
			{ u8"ず", "zu" },
			{ u8"ぜ", "ze" },
			{ u8"ぞ", "zo" },
			{ u8"だ", "da" },
			{ u8"ぢ", "di" },
			{ u8"ぢぃ", "dyi" },
			{ u8"ぢぇ", "dye" },
			{ u8"ぢゃ", "dya" },
			{ u8"ぢゅ", "dyu" },
			{ u8"ぢょ", "dyo" },
			{ u8"づ", "du" },
			{ u8"で", "de" },
			{ u8"でぃ", "dhi" },
			{ u8"でぇ", "dhe" },
			{ u8"でゃ", "dha" },
			{ u8"でゅ", "dhu" },
			{ u8"でょ", "dho" },
			{ u8"ど", "do" },
			{ u8"どぁ", "dwa" },
			{ u8"どぃ", "dwi" },
			{ u8"どぅ", "dwu" },
			{ u8"どぇ", "dwe" },
			{ u8"どぉ", "dwo" },
			{ u8"ば", "ba" },
			{ u8"ぱ", "pa" },
			{ u8"び", "bi" },
			{ u8"びぃ", "byi" },
			{ u8"びぇ", "bye" },
			{ u8"びゃ", "bya" },
			{ u8"びゅ", "byu" },
			{ u8"びょ", "byo" },
			{ u8"ぴ", "pi" },
			{ u8"ぴぃ", "pyi" },
			{ u8"ぴぇ", "pye" },
			{ u8"ぴゃ", "pya" },
			{ u8"ぴゅ", "pyu" },
			{ u8"ぴょ", "pyo" },
			{ u8"ぶ", "bu" },
			{ u8"ぷ", "pu" },
			{ u8"べ", "be" },
			{ u8"ぺ", "pe" },
			{ u8"ぼ", "bo" },
			{ u8"ぽ", "po" },
			{ u8"ヴぁ", "va" },
			{ u8"ヴぃ", "vi" },
			{ u8"ヴぃ", "vyi" },
			{ u8"ヴぇ", "ve" },
			{ u8"ヴぇ", "vye" },
			{ u8"ヴぉ", "vo" },
			{ u8"ヴゃ", "vya" },
			{ u8"ヴゅ", "vyu" },
			{ u8"ヴょ", "vyo" }
		};

		static int GetIndex(const char* value) {
			int i = 0;
			while (i < Japanese::SizeUnique && strcmp(Japanese::Hiragana::List[i], value) != 0)
				i++;
			return i;
		}

		static inline const int GetListSize() {
			return sizeof(List) / sizeof(List[0]);
		}
	};

	struct Katakana {
		//Katakana
		//ア 
		static inline const char* a = u8"ア";
		static inline const char* la = u8"ァ";
		static inline const char* xa = u8"ァ";

		//イ
		static inline const char* i = u8"イ";
		static inline const char* yi = u8"イ";
		static inline const char* li = u8"ィ";
		static inline const char* lyi = u8"ィ";
		static inline const char* xi = u8"ィ";
		static inline const char* xyi = u8"ィ";
		static inline const char* ye = u8"イェ";

		//ウ
		static inline const char* u = u8"ウ";
		static inline const char* whu = u8"ウ";
		static inline const char* wu = u8"ウ";
		static inline const char* lu = u8"ゥ";
		static inline const char* xu = u8"ゥ";
		static inline const char* wha = u8"ウァ";
		static inline const char* whi = u8"ウィ";
		static inline const char* wi = u8"ウィ";
		static inline const char* we = u8"ウェ";
		static inline const char* whe = u8"ウェ";
		static inline const char* who = u8"ウォ";

		//エ
		static inline const char* e = u8"エ";
		static inline const char* le = u8"ェ";
		static inline const char* lye = u8"ェ";
		static inline const char* xe = u8"ェ";
		static inline const char* xye = u8"ェ";

		//オ
		static inline const char* o = u8"オ";
		static inline const char* lo = u8"ォ";
		static inline const char* xo = u8"ォ";

		//------

		//カ
		static inline const char* ca = u8"カ";
		static inline const char* ka = u8"カ";
		static inline const char* lka = u8"ヵ";
		static inline const char* xka = u8"ヵ";

		//キ
		static inline const char* ki = u8"キ";
		static inline const char* kyi = u8"キィ";
		static inline const char* kye = u8"キェ";
		static inline const char* kya = u8"キャ";
		static inline const char* kyu = u8"キュ";
		static inline const char* kyo = u8"キョ";

		//ク
		static inline const char* cu = u8"ク";
		static inline const char* ku = u8"ク";
		static inline const char* qu = u8"ク";
		static inline const char* kwa = u8"クァ";
		static inline const char* qa = u8"クァ";
		static inline const char* qwa = u8"クァ";
		static inline const char* qi = u8"クィ";
		static inline const char* qwi = u8"クィ";
		static inline const char* qyi = u8"クィ";
		static inline const char* qwu = u8"クゥ";
		static inline const char* qe = u8"クェ";
		static inline const char* qwe = u8"クェ";
		static inline const char* qye = u8"クェ";
		static inline const char* qo = u8"クォ";
		static inline const char* qwo = u8"クォ";
		static inline const char* qya = u8"クャ";
		static inline const char* qyu = u8"クュ";
		static inline const char* qyo = u8"クョ";

		//ケ
		static inline const char* ke = u8"ケ";
		static inline const char* lke = u8"ヶ";
		static inline const char* xke = u8"ヶ";

		//コ
		static inline const char* co = u8"コ";
		static inline const char* ko = u8"コ";

		//------

		//サ
		static inline const char* sa = u8"サ";

		//シ
		static inline const char* ci = u8"シ";
		static inline const char* shi = u8"シ";
		static inline const char* si = u8"シ";
		static inline const char* syi = u8"シィ";
		static inline const char* she = u8"シェ";
		static inline const char* sye = u8"シェ";
		static inline const char* sha = u8"シャ";
		static inline const char* sya = u8"シャ";
		static inline const char* shu = u8"シュ";
		static inline const char* syu = u8"シュ";
		static inline const char* sho = u8"ショ";
		static inline const char* syo = u8"ショ";

		//ス
		static inline const char* su = u8"ス";
		static inline const char* swa = u8"スァ";
		static inline const char* swi = u8"スィ";
		static inline const char* swu = u8"スゥ";
		static inline const char* swe = u8"スェ";
		static inline const char* swo = u8"スォ";

		//セ
		static inline const char* ce = u8"セ";
		static inline const char* se = u8"セ";

		//ソ
		static inline const char* so = u8"ソ";

		//------

		//タ
		static inline const char* ta = u8"タ";

		//チ
		static inline const char* chi = u8"チ";
		static inline const char* ti = u8"チ";
		static inline const char* cyi = u8"チィ";
		static inline const char* tyi = u8"チィ";
		static inline const char* che = u8"チェ";
		static inline const char* cye = u8"チェ";
		static inline const char* tye = u8"チェ";
		static inline const char* cha = u8"チャ";
		static inline const char* cya = u8"チャ";
		static inline const char* tya = u8"チャ";
		static inline const char* chu = u8"チュ";
		static inline const char* cyu = u8"チュ";
		static inline const char* tyu = u8"チュ";
		static inline const char* cho = u8"チョ";
		static inline const char* cyo = u8"チョ";
		static inline const char* tyo = u8"チョ";

		//ツ
		static inline const char* tsu = u8"ツ";
		static inline const char* tu = u8"ツ";
		static inline const char* tsa = u8"ツァ";
		static inline const char* tsi = u8"ツィ";
		static inline const char* tse = u8"ツェ";
		static inline const char* tso = u8"ツォ";
		static inline const char* ltsu = u8"ッ";
		static inline const char* ltu = u8"ッ";
		static inline const char* xtsu = u8"ッ";
		static inline const char* xtu = u8"ッ";

		//テ
		static inline const char* te = u8"テ";
		static inline const char* thi = u8"ティ";
		static inline const char* the = u8"テェ";
		static inline const char* tha = u8"テャ";
		static inline const char* thu = u8"テュ";
		static inline const char* tho = u8"テョ";


		//ト
		static inline const char* to = u8"ト";
		static inline const char* twa = u8"トァ";
		static inline const char* twi = u8"トィ";
		static inline const char* twu = u8"トゥ";
		static inline const char* twe = u8"トェ";
		static inline const char* two = u8"トォ";

		//------

		//ナ
		static inline const char* na = u8"ナ";

		//ニ
		static inline const char* ni = u8"ニ";
		static inline const char* nyi = u8"ニィ";
		static inline const char* nye = u8"ニェ";
		static inline const char* nya = u8"ニャ";
		static inline const char* nyu = u8"ニュ";
		static inline const char* nyo = u8"ニョ";

		//ヌ
		static inline const char* nu = u8"ヌ";

		//ネ
		static inline const char* ne = u8"ネ";

		//ノ
		static inline const char* no = u8"ノ";

		//------

		//ハ
		static inline const char* ha = u8"ハ";

		//ヒ
		static inline const char* hi = u8"ヒ";
		static inline const char* hyi = u8"ヒィ";
		static inline const char* hye = u8"ヒェ";
		static inline const char* hya = u8"ヒャ";
		static inline const char* hyu = u8"ヒュ";
		static inline const char* hyo = u8"ヒョ";

		//フ
		static inline const char* fu = u8"フ";
		static inline const char* hu = u8"フ";
		static inline const char* fa = u8"ファ";
		static inline const char* fwa = u8"ファ";
		static inline const char* fi = u8"フィ";
		static inline const char* fwi = u8"フィ";
		static inline const char* fyi = u8"フィ";
		static inline const char* fwu = u8"フゥ";
		static inline const char* fe = u8"フェ";
		static inline const char* fwe = u8"フェ";
		static inline const char* fye = u8"フェ";
		static inline const char* fo = u8"フォ";
		static inline const char* fwo = u8"フォ";
		static inline const char* fya = u8"フャ";
		static inline const char* fyu = u8"フュ";
		static inline const char* fyo = u8"フョ";

		//ヘ
		static inline const char* he = u8"ヘ";

		//ホ
		static inline const char* ho = u8"ホ";

		//------

		//マ
		static inline const char* ma = u8"マ";

		//ミ
		static inline const char* mi = u8"ミ";
		static inline const char* myi = u8"ミィ";
		static inline const char* mye = u8"ミェ";
		static inline const char* mya = u8"ミャ";
		static inline const char* myu = u8"ミュ";
		static inline const char* myo = u8"ミョ";

		//ム
		static inline const char* mu = u8"ム";

		//メ
		static inline const char* me = u8"メ";

		//モ
		static inline const char* mo = u8"モ";

		//------

		//ヤ
		static inline const char* ya = u8"ヤ";
		static inline const char* lya = u8"ャ";
		static inline const char* xya = u8"ャ";

		//ユ
		static inline const char* yu = u8"ユ";
		static inline const char* lyu = u8"ュ";
		static inline const char* xyu = u8"ュ";

		//ヨ
		static inline const char* yo = u8"ヨ";
		static inline const char* lyo = u8"ョ";
		static inline const char* xyo = u8"ョ";

		//------

		//ラ
		static inline const char* ra = u8"ラ";

		//リ
		static inline const char* ri = u8"リ";
		static inline const char* ryi = u8"リィ";
		static inline const char* rye = u8"リェ";
		static inline const char* rya = u8"リャ";
		static inline const char* ryu = u8"リュ";
		static inline const char* ryo = u8"リョ";

		//ル
		static inline const char* ru = u8"ル";

		//レ
		static inline const char* re = u8"レ";

		//ロ
		static inline const char* ro = u8"ロ";

		//------

		//ワ
		static inline const char* wa = u8"ワ";
		static inline const char* lwa = u8"ヮ";
		static inline const char* xwa = u8"ヮ";

		//ヰ
		static inline const char* wyi = u8"ヰ";

		//ヱ
		static inline const char* wye = u8"ヱ";

		//ヲ
		static inline const char* wo = u8"ヲ";

		//------

		//ン
		static inline const char* nn = u8"ン";
		static inline const char* xn = u8"ン";

		//------
		//Modifiers - Katakana
		//ガ
		static inline const char* ga = u8"ガ";

		//ギ
		static inline const char* gi = u8"ギ";
		static inline const char* gyi = u8"ギィ";
		static inline const char* gye = u8"ギェ";
		static inline const char* gya = u8"ギャ";
		static inline const char* gyu = u8"ギュ";
		static inline const char* gyo = u8"ギョ";

		//グ
		static inline const char* gu = u8"グ";
		static inline const char* gwa = u8"グァ";
		static inline const char* gwi = u8"グィ";
		static inline const char* gwu = u8"グゥ";
		static inline const char* gwe = u8"グェ";
		static inline const char* gwo = u8"グォ";

		//ゲ
		static inline const char* ge = u8"ゲ";

		//ゴ
		static inline const char* go = u8"ゴ";

		//ザ
		static inline const char* za = u8"サ";

		//ジ
		static inline const char* ji = u8"ジ";
		static inline const char* zi = u8"ジ";
		static inline const char* jyi = u8"ジィ";
		static inline const char* zyi = u8"ジィ";
		static inline const char* je = u8"ジェ";
		static inline const char* jye = u8"ジェ";
		static inline const char* zye = u8"ジェ";
		static inline const char* ja = u8"ジャ";
		static inline const char* jya = u8"ジャ";
		static inline const char* zya = u8"ジャ";
		static inline const char* ju = u8"ジュ";
		static inline const char* jyu = u8"ジュ";
		static inline const char* zyu = u8"ジュ";
		static inline const char* jo = u8"ジョ";
		static inline const char* jyo = u8"ジョ";
		static inline const char* zyo = u8"ジョ";

		//ズ
		static inline const char* zu = u8"ズ";

		//ゼ
		static inline const char* ze = u8"ゼ";

		//ゾ
		static inline const char* zo = u8"ゾ";

		//ダ
		static inline const char* da = u8"ダ";

		//ヂ
		static inline const char* di = u8"ヂ";
		static inline const char* dyi = u8"ヂィ";
		static inline const char* dye = u8"ヂェ";
		static inline const char* dya = u8"ヂャ";
		static inline const char* dyu = u8"ヂュ";
		static inline const char* dyo = u8"ヂョ";

		//ヅ
		static inline const char* du = u8"ヅ";

		//デ
		static inline const char* de = u8"デ";
		static inline const char* dhi = u8"ディ";
		static inline const char* dhe = u8"デェ";
		static inline const char* dha = u8"デャ";
		static inline const char* dhu = u8"デュ";
		static inline const char* dho = u8"デョ";

		//ド
		static inline const char* do_ = u8"ド";
		static inline const char* dwa = u8"ドァ";
		static inline const char* dwi = u8"ドィ";
		static inline const char* dwu = u8"ドゥ";
		static inline const char* dwe = u8"ドェ";
		static inline const char* dwo = u8"ドォ";

		//バ
		static inline const char* ba = u8"バ";

		//パ
		static inline const char* pa = u8"パ";

		//ビ
		static inline const char* bi = u8"ビ";
		static inline const char* byi = u8"ビィ";
		static inline const char* bye = u8"ビェ";
		static inline const char* bya = u8"ビャ";
		static inline const char* byu = u8"ビュ";
		static inline const char* byo = u8"ビョ";

		//ピ
		static inline const char* pi = u8"ピ";
		static inline const char* pyi = u8"ピィ";
		static inline const char* pye = u8"ピェ";
		static inline const char* pya = u8"ピャ";
		static inline const char* pyu = u8"ピュ";
		static inline const char* pyo = u8"ピョ";

		//ブ
		static inline const char* bu = u8"ブ";

		//プ
		static inline const char* pu = u8"プ";

		//ベ
		static inline const char* be = u8"ベ";

		//ペ
		static inline const char* pe = u8"ペ";

		//ボ
		static inline const char* bo = u8"ボ";

		//ポ
		static inline const char* po = u8"ポ";

		//ヴ
		static inline const char* va = u8"ヴァ";
		static inline const char* vi = u8"ヴィ";
		static inline const char* vyi = u8"ヴィ";
		static inline const char* ve = u8"ヴェ";
		static inline const char* vye = u8"ヴェ";
		static inline const char* vo = u8"ヴォ";
		static inline const char* vya = u8"ヴャ";
		static inline const char* vyu = u8"ヴュ";
		static inline const char* vyo = u8"ヴョ";

		//Katakana class stuffs
		static inline const char* List[] = {
			u8"ア", u8"ァ", u8"イ", u8"ィ", u8"イェ", u8"ウ", u8"ゥ", u8"ウァ", u8"ウィ", u8"ウェ", u8"ウォ", u8"エ", u8"ェ", u8"オ", u8"ォ", u8"カ", u8"ヵ", u8"キ", u8"キィ", u8"キェ", u8"キャ", u8"キュ", u8"キョ", u8"ク", u8"クァ", u8"クィ", u8"クゥ", u8"クェ", u8"クォ", u8"クャ", u8"クュ", u8"クョ", u8"ケ", u8"ヶ", u8"コ", u8"サ", u8"シ", u8"シィ", u8"シェ", u8"シャ", u8"シュ", u8"ショ", u8"ス", u8"スァ", u8"スィ", u8"スゥ", u8"スェ", u8"スォ", u8"セ", u8"ソ", u8"タ", u8"チ", u8"チィ", u8"チェ", u8"チャ", u8"チュ", u8"チョ", u8"ツ", u8"ツァ", u8"ツィ", u8"ツェ", u8"ツォ", u8"ッ", u8"テ", u8"ティ", u8"テェ", u8"テャ", u8"テュ", u8"テョ", u8"ト", u8"トァ", u8"トィ", u8"トゥ", u8"トェ", u8"トォ", u8"ナ", u8"ニ", u8"ニィ", u8"ニェ", u8"ニャ", u8"ニュ", u8"ニョ", u8"ヌ", u8"ネ", u8"ノ", u8"ハ", u8"ヒ", u8"ヒィ", u8"ヒェ", u8"ヒャ", u8"ヒュ", u8"ヒョ", u8"フ", u8"ファ", u8"フィ", u8"フゥ", u8"フェ", u8"フォ", u8"フャ", u8"フュ", u8"フョ", u8"ヘ", u8"ホ", u8"マ", u8"ミ", u8"ミィ", u8"ミェ", u8"ミャ", u8"ミュ", u8"ミョ", u8"ム", u8"メ", u8"モ", u8"ヤ", u8"ャ", u8"ユ", u8"ュ", u8"ヨ", u8"ョ", u8"ラ", u8"リ", u8"リィ", u8"リェ", u8"リャ", u8"リュ", u8"リョ", u8"ル", u8"レ", u8"ロ", u8"ワ", u8"ヮ", u8"ヰ", u8"ヱ", u8"ヲ", u8"ン", u8"ガ", u8"ギ", u8"ギィ", u8"ギェ", u8"ギャ", u8"ギュ", u8"ギョ", u8"グ", u8"グァ", u8"グィ", u8"グゥ", u8"グェ", u8"グォ", u8"ゲ", u8"ゴ", u8"ジ", u8"ジィ", u8"ジェ", u8"ジャ", u8"ジュ", u8"ジョ", u8"ズ", u8"ゼ", u8"ゾ", u8"ダ", u8"ヂ", u8"ヂィ", u8"ヂェ", u8"ヂャ", u8"ヂュ", u8"ヂョ", u8"ヅ", u8"デ", u8"ディ", u8"デェ", u8"デャ", u8"デュ", u8"デョ", u8"ド", u8"ドァ", u8"ドィ", u8"ドゥ", u8"ドェ", u8"ドォ", u8"バ", u8"パ", u8"ビ", u8"ビィ", u8"ビェ", u8"ビャ", u8"ビュ", u8"ビョ", u8"ピ", u8"ピィ", u8"ピェ", u8"ピャ", u8"ピュ", u8"ピョ", u8"ブ", u8"プ", u8"ベ", u8"ペ", u8"ボ", u8"ポ", u8"ヴァ", u8"ヴィ", u8"ヴェ", u8"ヴォ", u8"ヴャ", u8"ヴュ", u8"ヴョ"
		};

		//English to Katakana stuffs
		static inline const std::map<std::string, std::string> en_Katakana{
			{ u8"ア","a" },
			{ u8"ァ","la" },
			{ u8"ァ","xa" },
			{ u8"イ","i" },
			{ u8"イ","yi" },
			{ u8"ィ","li" },
			{ u8"ィ","lyi" },
			{ u8"ィ","xi" },
			{ u8"ィ","xyi" },
			{ u8"イェ","ye" },
			{ u8"ウ","u" },
			{ u8"ウ","whu" },
			{ u8"ウ","wu" },
			{ u8"ゥ","lu" },
			{ u8"ゥ","xu" },
			{ u8"ウァ","wha" },
			{ u8"ウィ","whi" },
			{ u8"ウィ","wi" },
			{ u8"ウェ","we" },
			{ u8"ウェ","whe" },
			{ u8"ウォ","who" },
			{ u8"エ","e" },
			{ u8"ェ","le" },
			{ u8"ェ","lye" },
			{ u8"ェ","xe" },
			{ u8"ェ","xye" },
			{ u8"オ","o" },
			{ u8"ォ","lo" },
			{ u8"ォ","xo" },
			{ u8"カ","ca" },
			{ u8"カ","ka" },
			{ u8"ヵ","lka" },
			{ u8"ヵ","xka" },
			{ u8"キ","ki" },
			{ u8"キィ","kyi" },
			{ u8"キェ","kye" },
			{ u8"キャ","kya" },
			{ u8"キュ","kyu" },
			{ u8"キョ","kyo" },
			{ u8"ク","cu" },
			{ u8"ク","ku" },
			{ u8"ク","qu" },
			{ u8"クァ","kwa" },
			{ u8"クァ","qa" },
			{ u8"クァ","qwa" },
			{ u8"クィ","qi" },
			{ u8"クィ","qwi" },
			{ u8"クィ","qyi" },
			{ u8"クゥ","qwu" },
			{ u8"クェ","qe" },
			{ u8"クェ","qwe" },
			{ u8"クェ","qye" },
			{ u8"クォ","qo" },
			{ u8"クォ","qwo" },
			{ u8"クャ","qya" },
			{ u8"クュ","qyu" },
			{ u8"クョ","qyo" },
			{ u8"ケ","ke" },
			{ u8"ヶ","lke" },
			{ u8"ヶ","xke" },
			{ u8"コ","co" },
			{ u8"コ","ko" },
			{ u8"サ","sa" },
			{ u8"シ","ci" },
			{ u8"シ","shi" },
			{ u8"シ","si" },
			{ u8"シィ","syi" },
			{ u8"シェ","she" },
			{ u8"シェ","sye" },
			{ u8"シャ","sha" },
			{ u8"シャ","sya" },
			{ u8"シュ","shu" },
			{ u8"シュ","syu" },
			{ u8"ショ","sho" },
			{ u8"ショ","syo" },
			{ u8"ス","su" },
			{ u8"スァ","swa" },
			{ u8"スィ","swi" },
			{ u8"スゥ","swu" },
			{ u8"スェ","swe" },
			{ u8"スォ","swo" },
			{ u8"セ","ce" },
			{ u8"セ","se" },
			{ u8"ソ","so" },
			{ u8"タ","ta" },
			{ u8"チ","chi" },
			{ u8"チ","ti" },
			{ u8"チィ","cyi" },
			{ u8"チィ","tyi" },
			{ u8"チェ","che" },
			{ u8"チェ","cye" },
			{ u8"チェ","tye" },
			{ u8"チャ","cha" },
			{ u8"チャ","cya" },
			{ u8"チャ","tya" },
			{ u8"チュ","chu" },
			{ u8"チュ","cyu" },
			{ u8"チュ","tyu" },
			{ u8"チョ","cho" },
			{ u8"チョ","cyo" },
			{ u8"チョ","tyo" },
			{ u8"ツ","tsu" },
			{ u8"ツ","tu" },
			{ u8"ツァ","tsa" },
			{ u8"ツィ","tsi" },
			{ u8"ツェ","tse" },
			{ u8"ツォ","tso" },
			{ u8"ッ","ltsu" },
			{ u8"ッ","ltu" },
			{ u8"ッ","xtsu" },
			{ u8"ッ","xtu" },
			{ u8"テ","te" },
			{ u8"ティ","thi" },
			{ u8"テェ","the" },
			{ u8"テャ","tha" },
			{ u8"テュ","thu" },
			{ u8"テョ","tho" },
			{ u8"ト","to" },
			{ u8"トァ","twa" },
			{ u8"トィ","twi" },
			{ u8"トゥ","twu" },
			{ u8"トェ","twe" },
			{ u8"トォ","two" },
			{ u8"ナ","na" },
			{ u8"ニ","ni" },
			{ u8"ニィ","nyi" },
			{ u8"ニェ","nye" },
			{ u8"ニャ","nya" },
			{ u8"ニュ","nyu" },
			{ u8"ニョ","nyo" },
			{ u8"ヌ","nu" },
			{ u8"ネ","ne" },
			{ u8"ノ","no" },
			{ u8"ハ","ha" },
			{ u8"ヒ","hi" },
			{ u8"ヒィ","hyi" },
			{ u8"ヒェ","hye" },
			{ u8"ヒャ","hya" },
			{ u8"ヒュ","hyu" },
			{ u8"ヒョ","hyo" },
			{ u8"フ","fu" },
			{ u8"フ","hu" },
			{ u8"ファ","fa" },
			{ u8"ファ","fwa" },
			{ u8"フィ","fi" },
			{ u8"フィ","fwi" },
			{ u8"フィ","fyi" },
			{ u8"フゥ","fwu" },
			{ u8"フェ","fe" },
			{ u8"フェ","fwe" },
			{ u8"フェ","fye" },
			{ u8"フォ","fo" },
			{ u8"フォ","fwo" },
			{ u8"フャ","fya" },
			{ u8"フュ","fyu" },
			{ u8"フョ","fyo" },
			{ u8"ヘ","he" },
			{ u8"ホ","ho" },
			{ u8"マ","ma" },
			{ u8"ミ","mi" },
			{ u8"ミィ","myi" },
			{ u8"ミェ","mye" },
			{ u8"ミャ","mya" },
			{ u8"ミュ","myu" },
			{ u8"ミョ","myo" },
			{ u8"ム","mu" },
			{ u8"メ","me" },
			{ u8"モ","mo" },
			{ u8"ヤ","ya" },
			{ u8"ャ","lya" },
			{ u8"ャ","xya" },
			{ u8"ユ","yu" },
			{ u8"ュ","lyu" },
			{ u8"ュ","xyu" },
			{ u8"ヨ","yo" },
			{ u8"ョ","lyo" },
			{ u8"ョ","xyo" },
			{ u8"ラ","ra" },
			{ u8"リ","ri" },
			{ u8"リィ","ryi" },
			{ u8"リェ","rye" },
			{ u8"リャ","rya" },
			{ u8"リュ","ryu" },
			{ u8"リョ","ryo" },
			{ u8"ル","ru" },
			{ u8"レ","re" },
			{ u8"ロ","ro" },
			{ u8"ワ","wa" },
			{ u8"ヮ","lwa" },
			{ u8"ヮ","xwa" },
			{ u8"ヰ","wyi" },
			{ u8"ヱ","wye" },
			{ u8"ヲ","wo" },
			{ u8"ン","nn" },
			{ u8"ン","xn" },
			{ u8"ガ","ga" },
			{ u8"ギ","gi" },
			{ u8"ギィ","gyi" },
			{ u8"ギェ","gye" },
			{ u8"ギャ","gya" },
			{ u8"ギュ","gyu" },
			{ u8"ギョ","gyo" },
			{ u8"グ","gu" },
			{ u8"グァ","gwa" },
			{ u8"グィ","gwi" },
			{ u8"グゥ","gwu" },
			{ u8"グェ","gwe" },
			{ u8"グォ","gwo" },
			{ u8"ゲ","ge" },
			{ u8"ゴ","go" },
			{ u8"サ","za" },
			{ u8"ジ","ji" },
			{ u8"ジ","zi" },
			{ u8"ジィ","jyi" },
			{ u8"ジィ","zyi" },
			{ u8"ジェ","je" },
			{ u8"ジェ","jye" },
			{ u8"ジェ","zye" },
			{ u8"ジャ","ja" },
			{ u8"ジャ","jya" },
			{ u8"ジャ","zya" },
			{ u8"ジュ","ju" },
			{ u8"ジュ","jyu" },
			{ u8"ジュ","zyu" },
			{ u8"ジョ","jo" },
			{ u8"ジョ","jyo" },
			{ u8"ジョ","zyo" },
			{ u8"ズ","zu" },
			{ u8"ゼ","ze" },
			{ u8"ゾ","zo" },
			{ u8"ダ","da" },
			{ u8"ヂ","di" },
			{ u8"ヂィ","dyi" },
			{ u8"ヂェ","dye" },
			{ u8"ヂャ","dya" },
			{ u8"ヂュ","dyu" },
			{ u8"ヂョ","dyo" },
			{ u8"ヅ","du" },
			{ u8"デ","de" },
			{ u8"ディ","dhi" },
			{ u8"デェ","dhe" },
			{ u8"デャ","dha" },
			{ u8"デュ","dhu" },
			{ u8"デョ","dho" },
			{ u8"ド","do" },
			{ u8"ドァ","dwa" },
			{ u8"ドィ","dwi" },
			{ u8"ドゥ","dwu" },
			{ u8"ドェ","dwe" },
			{ u8"ドォ","dwo" },
			{ u8"バ","ba" },
			{ u8"パ","pa" },
			{ u8"ビ","bi" },
			{ u8"ビィ","byi" },
			{ u8"ビェ","bye" },
			{ u8"ビャ","bya" },
			{ u8"ビュ","byu" },
			{ u8"ビョ","byo" },
			{ u8"ピ","pi" },
			{ u8"ピィ","pyi" },
			{ u8"ピェ","pye" },
			{ u8"ピャ","pya" },
			{ u8"ピュ","pyu" },
			{ u8"ピョ","pyo" },
			{ u8"ブ","bu" },
			{ u8"プ","pu" },
			{ u8"ベ","be" },
			{ u8"ペ","pe" },
			{ u8"ボ","bo" },
			{ u8"ポ","po" },
			{ u8"ヴァ","va" },
			{ u8"ヴィ","vi" },
			{ u8"ヴィ","vyi" },
			{ u8"ヴェ","ve" },
			{ u8"ヴェ","vye" },
			{ u8"ヴォ","vo" },
			{ u8"ヴャ","vya" },
			{ u8"ヴュ","vyu" },
			{ u8"ヴョ","vyo" }
		};

		static int GetIndex(const char* value) {
			int i = 0;
			while (i < Japanese::SizeUnique && strcmp(Japanese::Katakana::List[i], value) != 0)
				i++;
			return i;
		}

		static inline const int GetListSize() {
			return sizeof(List) / sizeof(List[0]);
		}
	};

	//Combinations not from the basic Hiragana Table, basic Katakana Table and the modifiers
	//ー (pause)
	static inline const char* HYPHEN = u8"ー";
	static inline const char* MINUS = u8"ー";
	static inline const char* PAUSE = u8"ー";

	//Counting all pronunciations.
	static const int SizeAll = 278;
	//Counting all unique pronunciations
	static const int SizeUnique = 206;
};

//C++ class headers.
#include "draw.h"
#include "block.h"
#include "input.h"
#include "game.h"

#ifdef __SWITCH__
//Font headers
#	include "JapanSans_ttf.h"
#endif

#endif