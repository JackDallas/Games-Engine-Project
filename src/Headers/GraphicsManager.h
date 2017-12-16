#pragma once

class GraphicsManager {
public:
	/**
	initialises the Graphics Manager
	this is handled by gameEngine()
	*/
	static void init();
	/**
	Called when the display is re-rendered.
	Calls all components onRender() functions 
	this is called by gameEngine()
	*/
	static void display();
	/**
	Called when the window is modified.
	Calls all components onDisplayChange() functions 
	this is called by gameEngine()
	*/
	static void displayChange(int width, int height);
private:
	//prevent creation 
	GraphicsManager();
	GraphicsManager(const GraphicsManager& that) = delete;
};