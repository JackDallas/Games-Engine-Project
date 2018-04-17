#pragma once

#include <memory>
#include <string>
#include <math.h>

#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Logger.h"

#define PI180 (3.14159265 / 180)

class CircleScript : public Component {
public:

	void init(std::weak_ptr<Transform> _targetTransform, float _distance) {
		targetTransform = _targetTransform;
		distance = _distance;
		hasINIT = true;
	}

	void onAwake() {
		transform = gameObject.lock()->getComponent<Transform>();
		hasINIT = false;
		currentRotation = 0;
	}

	void onUpdate(float DeltaTime) {
		if (hasINIT) {
			currentRotation += (10 * DeltaTime);

			if (currentRotation >= 360) currentRotation -= 360;
			glm::vec3 currentTargetPos = targetTransform.lock()->getLocalPosition();

			float currentRotRads = currentRotation * PI180;

			currentTargetPos.x += cos(currentRotRads) * distance;
			currentTargetPos.z += sin(currentRotRads) * distance;

			currentTargetPos.y = transform.lock()->getLocalPosition().y;

			transform.lock()->setPosition(currentTargetPos);
		}
	}

private:
	bool hasINIT;
	std::weak_ptr<Transform> transform;
	std::weak_ptr<Transform> targetTransform;

	int currentRotation;
	float distance;
};