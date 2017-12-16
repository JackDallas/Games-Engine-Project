#pragma once
//std
#include <memory>
//int
#include "Input.h"
class GameObject;


class Component {

public:
	virtual ~Component() {};

	std::weak_ptr<GameObject> gameObject;
	/**
	onAwake is called after the Component has been attached to a game object and the gameObject member has been set.
	*/
	virtual void onAwake() {};
	/**
	onRender is called every time a new frame is being painted, calls to opengl should be done here.
	*/
	virtual void onRender() {};
	/**
	onDisplayChange is called when the window is modified, updates to values depending on the window should be done here.
	*/
	virtual void onDisplayChange() {};
	/**
	onUpdate is called whenever GLUT isn't doing anything else
	@param deltaTime the time in milliseconds since the last update call.
	*/
	virtual void onUpdate(float deltaTime) {};
	/**
	onKeyEvent is called whenever a key on the Keyboard is pressed
	@param i the key input object 
	@see Key_Input
	*/
	virtual void onKeyEvent(Key_Input i) {};
	/**
	onMouseEvent is called whenever the mouse is moved or clicked
	@param i the Mouse input object
	@see Mouse_Input
	*/
	virtual void onMouseEvent(Mouse_Input i) {};
};