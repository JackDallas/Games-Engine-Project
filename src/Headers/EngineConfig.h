#pragma once
//std
#include <string>
//ext
#include <GL/freeglut.h>
//int
#include "GraphicsUtils.h"

class EngineConfig {
public:
	/**
	Constructor for the Engine Config.
	@param _screenWidth screen width in pixels
	@param _screenHeight screen height in pixels
	@param _screenClearColour Colour representing the default fill on the screen
	@param _fullscreenMode bool representing if you want the program in fullscreen or not
	@param _windowName window name as a string
	@see Colour()
	*/
	EngineConfig(int _screenWidth, int _screenHeight, Colour _screenClearColour, bool _fullscreenMode, std::string _windowName); //All
	/**
	Constructor for the Engine Config.
	@param _screenWidth screen width in pixels
	@param _screenHeight screen height in pixels
	@param _screenClearColour Colour representing the default fill on the screen
	@param _fullscreenMode bool representing if you want the program in fullscreen or not
	@see Colour()
	*/
	EngineConfig(int _screenWidth, int _screenHeight, Colour _screenClearColour, bool _fullscreenMode); //Screen
	/**
	Constructor for the Engine Config.
	@param _screenClearColour Colour representing the default fill on the screen
	@param _fullscreenMode bool representing if you want the program in fullscreen or not
	@see Colour()
	*/
	EngineConfig(Colour _screenClearColour, bool _fullscreenMode);//fullscreen
	/**
	Constructor for the Engine Config.
	*/
	EngineConfig();//None

	/**
	getScreenWidth
	@return width of the screen in pixels
	*/
	int getScreenWidth() { return fullscreenMode ? screenWidth :  glutGet(GLUT_WINDOW_WIDTH);};
	/**
	getScreenHeight
	@return height of the screen in pixels
	*/
	int getScreenHeight() { return fullscreenMode ?  screenHeight : glutGet(GLUT_WINDOW_HEIGHT);};

	/**
	getScreenWidth
	@return Colour of the screen clear
	@see Colour()
	*/
	Colour getScreenClearColour() { return screenClearColour;};
	/**
	getFullscreenMode
	@return bool representing if the engine is in fullscreen mode or not
	*/
	bool getFullScreenMode() { return fullscreenMode;};
	/**
	getWindowName
	@return Name of the window as a string
	*/
	std::string getWindowName() { return windowName;};
private:
	int screenWidth;
	int screenHeight;
	
	Colour screenClearColour;

	bool fullscreenMode;

	std::string windowName;
};