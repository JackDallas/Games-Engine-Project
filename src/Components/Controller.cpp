#include "Controller.h"

#include "Input.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "gameEngine.h"
#include "EngineConfig.h"
#include "Light.h"

#include <glm/mat4x4.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>



void Controller::onAwake() {
	transform = gameObject.lock()->getComponent<Transform>();
	gameObject.lock()->getComponent<Camera>()->setCameraMode(CameraMode::FREECAM);
}


void Controller::onKeyEvent(Key_Input i) {
	if (i.type == Key_InputType::KEY_DOWN) {
		switch (i.key) {
		case Key_InputKey::W :
			WChange = true;
			break;
		case Key_InputKey::S :
			SChange = true;
			break;
		case Key_InputKey::A :
			AChange = true;
			break;
		case Key_InputKey::D :
			DChange = true;
			break;
		case Key_InputKey::Q :
			gameEngine::context->mainLight->getComponent<Light>()->incLightPower(0.1);
			break;
		case Key_InputKey::E :
			gameEngine::context->mainLight->getComponent<Light>()->incLightPower(-0.1);
			break;
		}
	}
}

void Controller::onMouseEvent(Mouse_Input i) {
	if (i.type == Mouse_InputType::MOUSE_MOVEMENT && gameEngine::context->captureInput) {
		xMChange = i.mousePosition.xRel;
		yMChange = i.mousePosition.yRel;
	}
}

void Controller::onUpdate(float deltaT) {
	transform.lock()->rotate(glm::vec3(xMChange * deltaT, yMChange * deltaT, 0));

	if (WChange) transform.lock()->movePosition(glm::vec3(0.0f, 0.0f, 0.5f));
	if (SChange) transform.lock()->movePosition(glm::vec3(0.0f, 0.0f, -0.5f));
	if (AChange) transform.lock()->movePosition(glm::vec3(0.5f, 0.0f, 0.0f));
	if (DChange) transform.lock()->movePosition(glm::vec3(-0.5f, 0.0f, 0.0f));

	WChange = false;
	SChange = false;
	AChange = false;
	DChange = false;

	xMChange = 0;
	yMChange = 0;

}