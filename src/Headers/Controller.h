#pragma once
//std
#include <memory>
//ext
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
//int
#include "Component.h"
class Transform;

class Controller : public Component {
public:
	void onAwake();
	void onKeyEvent(Key_Input i);
	void onMouseEvent(Mouse_Input i);
	void onUpdate(float deltaT);
private:
	/**
	lastMousePos, the last position of the mouse in screen space
	*/
	float xMChange = 0, yMChange = 0;
	bool WChange = false, SChange = false, AChange = false, DChange = false;
	/**
	transform, reference to the gameobjects transform component
	*/
	std::weak_ptr<Transform> transform;

};