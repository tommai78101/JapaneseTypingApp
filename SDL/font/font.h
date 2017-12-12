#pragma once

#ifndef __FONT_H__
#	define __FONT_H__

#include "../game/common.h"

//Source: 
//https://github.com/rougier/freetype-gl/blob/51dbc0b144bac298de26a87acf5e3481ffa56893/texture-atlas.c#L148
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
	int Fit(size_t index, size_t width, size_t height);
	void Merge();
} FontTextureAtlas;

FontTextureAtlas* CreateFontAtlas(size_t width, size_t height, size_t depth);
void DeleteFontAtlas(FontTextureAtlas* atlas);


#endif