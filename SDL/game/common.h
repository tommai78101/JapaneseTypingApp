#ifndef __COMMON_H__
#	define __COMMON_H__

#pragma once

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

#endif