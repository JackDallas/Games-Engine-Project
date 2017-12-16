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

private:
	/**
	lastMousePos, the last position of the mouse in screen space
	*/
	glm::vec4 lastMousePos;
	/**
	transform, reference to the gameobjects transform component
	*/
	std::weak_ptr<Transform> transform;

};