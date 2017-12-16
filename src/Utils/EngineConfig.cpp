#include "EngineConfig.h"

#include "GraphicsUtils.h"

#include <GL/freeglut.h>

#include "Logger.h"
EngineConfig::EngineConfig(int _screenWidth, int _screenHeight, Colour _screenClearColour, bool _fullscreenMode, std::string _windowName) { //All
	fullscreenMode = _fullscreenMode;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	screenClearColour = _screenClearColour;
	windowName = _windowName;
}

EngineConfig::EngineConfig(int _screenWidth, int _screenHeight, Colour _screenClearColour, bool _fullscreenMode) { //Screen
	fullscreenMode = _fullscreenMode;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	screenClearColour = _screenClearColour;
	windowName = "Dallas Engine";
}
EngineConfig::EngineConfig(Colour _screenClearColour, bool _fullscreenMode) { //Screen
	fullscreenMode = _fullscreenMode;
	screenWidth = 800;
	screenHeight = 600;
	screenClearColour = _screenClearColour;
	windowName = "Dallas Engine";
}

EngineConfig::EngineConfig() {//None
	fullscreenMode = false;
	screenWidth = 800;
	screenHeight = 600;
	screenClearColour = Colour(0.0f, 0.0f, 0.4f, 1.0f);
	windowName = "Dallas Engine";
}