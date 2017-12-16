#include "GraphicsUtils.h"

float GraphicsUtils::RGBtoFloat(float v) {
	//rbg has to be between 0 and 255
	if (v > 255) v = 255;
	if (v < 0 ) v = 0;
	return (v / 255.0f);
}