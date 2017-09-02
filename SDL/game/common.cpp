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