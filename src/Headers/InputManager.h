#pragma once

class InputManager {
public:
	static void init();
	/**
	Called when the mouse is moved 
	Calls all components onMouseEvent() functions
	this is called by gameEngine()
	*/
	static void motionEvent(int x, int y);
	/**
	Called when the mouse is clicked
	Calls all components onMouseEvent() functions
	this is called by gameEngine()
	*/
	static void mouseEvent(int button, int state, int x, int y);	
	/**
	Called when a Key is pressed
	Calls all components onKeyEvent() functions
	this is called by gameEngine()
	*/
	static void KeyboardEvent(unsigned char key, int x, int y);
	/**
	Called when a Key is pressed
	Calls all components onKeyEvent() functions
	this is called by gameEngine()
	*/
	static void SpecialKeyboardEvent(int key, int x, int y);
private:
	InputManager();
	InputManager(const InputManager& that) = delete;
};