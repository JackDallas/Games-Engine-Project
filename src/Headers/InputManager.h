#pragma once
#include <SDL2/SDL.h>

class InputManager {
public:
	static void init();

	static void processInput();
	/**
	Called when the mouse is moved
	Calls all components onMouseEvent() functions
	this is called by gameEngine()
	*/
	static void motionEvent(SDL_Event *event);
	/**
	Called when the mouse is clicked
	Calls all components onMouseEvent() functions
	this is called by gameEngine()
	*/
	static void mouseEvent(SDL_Event *event);
	/**
	Called when a Key is pressed
	Calls all components onKeyEvent() functions
	this is called by gameEngine()
	*/
	static void KeyboardEvent(SDL_Event *event);
private:
	InputManager();
	InputManager(const InputManager& that) = delete;
};