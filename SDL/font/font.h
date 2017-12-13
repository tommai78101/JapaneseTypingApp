#pragma once

#ifndef __FONT_H__
#	define __FONT_H__

#include "../game/common.h"

typedef enum OutLineType {
	NONE,
	LINE,
	INNER,
	OUTER
} OutLineType;

//Font texture glyph

typedef struct FontTextureGlyph {
	

	//Unicode codepoint represented in UTF-32 LE encoding
	unsigned int codepoint;
	size_t width;
	size_t height;
	size_t offset_x;
	size_t offset_y;
	Vector4Df textureCoord;
	float outlineThickness;
} FontTextureGlyph;

//End font texture glyph

//Font texture atlas

typedef struct FontTextureAtlas {
	VectorList* nodes;
	size_t width;
	size_t height;
	size_t depth;

	//Allocated surface size
	size_t used;

	//OpenGL texture identity
	unsigned int id;

	unsigned char* atlasData;

	Vector4Di GetRegion(size_t width, size_t height);
	void SetRegion(size_t x, size_t y, size_t width, size_t height, unsigned char* data, size_t stride);
	void ClearAtlas();
	size_t Fit(size_t index, size_t width, size_t height);
	void Merge();
} FontTextureAtlas;

FontTextureAtlas* CreateFontAtlas(size_t width, size_t height, size_t depth);
void DeleteFontAtlas(FontTextureAtlas* atlas);

//End font texture atlas

//Font

typedef struct Font {
	enum {
		TEXTURE_FONT_FILE = 0,
		TEXTURE_FONT_MEMORY
	} location;

	VectorList* glyphs;
	FontTextureAtlas* atlas;

	union {
		//When "location" is TEXTURE_FONT_FILE
		char* filename;

		//When "location" is TEXTURE_FONT_MEMORY, for font memory address
		struct {
			const void* base;
			size_t size;
		} memory;
	};

	float fontSize;

	//Vertical hinting trick
	float hiResolution;

	//Whether to use auto-hint when rendering fonts
	bool useHinting;

	OutLineType outlineType;
	float outlineThickness;

	//Whether to use custom LCD filtering.
	bool useFiltering;

	//LCD filter weights
	unsigned char lcd_weights[5];

} Font;

//End font

#endif