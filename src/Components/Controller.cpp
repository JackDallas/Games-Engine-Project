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
	glutSetCursor( GLUT_CURSOR_CROSSHAIR);
}


void Controller::onKeyEvent(Key_Input i) {
	if (i.type == Key_InputType::KEY_DOWN) {
		switch (i.key) {
		case Key_InputKey::W :
			transform.lock()->movePosition(glm::vec3(0.0f, 0.0f, 0.5f));
			break;
		case Key_InputKey::S :
			transform.lock()->movePosition(glm::vec3(0.0f, 0.0f, -0.5f));
			break;
		case Key_InputKey::A :
			transform.lock()->movePosition(glm::vec3(0.5f, 0.0f, 0.0f));
			break;
		case Key_InputKey::D :
			transform.lock()->movePosition(glm::vec3(-0.5f, 0.0f, 0.0f));
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
	if (i.type == Mouse_InputType::MOUSE_MOVEMENT) {
		glm::vec4 mousePos =  glm::vec4(
		                          //Get the position in screen space between -1 and 1
		                          (2.0f * (float(i.mousePosition.x - 0) / (gameEngine::context->config->getScreenWidth() - 0))) - 1.0f,
		                          1.0f - (2.0f * (float(i.mousePosition.y - 0) / (gameEngine::context->config->getScreenHeight() - 0))),
		                          0.0f,
		                          1.0f);

		transform.lock()->rotate(glm::vec3(mousePos.x,mousePos.y,0));

		glutWarpPointer( gameEngine::context->config->getScreenWidth() / 2 , gameEngine::context->config->getScreenHeight() / 2);
	}
}