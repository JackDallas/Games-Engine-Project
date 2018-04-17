#include "GraphicsUtils.h"

float GraphicsUtils::RGBtoFloat(float v) {
	//rbg has to be between 0 and 255
	if (v > 255) v = 255;
	if (v < 0 ) v = 0;
	return (v / 255.0f);
}

SDL_bool GraphicsUtils::boolToSDL(bool b) {
	if (!b) return SDL_bool::SDL_FALSE;
	if (b) return SDL_bool::SDL_TRUE;
	return SDL_bool::SDL_TRUE;
}