#pragma once

#include <memory>
#include <string>

#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Logger.h"
class RotateScript : public Component {
public:
	void onAwake() {
		transform = gameObject.lock()->getComponent<Transform>();
	}

	void onUpdate(float DeltaTime) {
		transform.lock()->rotate(glm::vec3((1.0f * DeltaTime),0.0f,0.0f));
	}
private:
	std::weak_ptr<Transform> transform;
};