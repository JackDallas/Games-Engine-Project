#include "Camera.h"

#include <memory>
#include <functional>
#include <glm/gtc/matrix_transform.hpp>

#include "GameObject.h"
#include "Transform.h"
#include "gameEngine.h"
#include "EngineConfig.h"

#include <GL/freeglut.h>

//Static getter shortcut for the main camera
std::weak_ptr<Camera> Camera::getMainCamera() {
	return gameEngine::context->mainCamera->getComponent<Camera>();
}


void Camera::onAwake() {
	transform = gameObject.lock()->getComponent<Transform>();

	transform.lock()->positionChangedCallback(std::bind(&Camera::transformUpdate, this));

	target = glm::vec3(0, 0, 0); 

	onDisplayChange();
	updateViewMatrix();
}

 
glm::mat4 Camera::getViewMatrix() {
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
	return projectionMatrix;
}

glm::mat4 Camera::getViewProjectInv() {
	return glm::inverse(projectionMatrix * viewMatrix);
}


void Camera::setCameraMode(CameraMode _newMode){
	currentMode = _newMode;
	updateViewMatrix();
}

void Camera::lookAt(glm::vec3 _at) {
	target = _at;
	updateViewMatrix();
}

void Camera::updateViewMatrix() {
	switch (currentMode) {
	case CameraMode::LOOKAT :
		viewMatrix = glm::lookAt(
		                 transform.lock()->getWorldPosition(), //Cam position in world space
		                 target, //target in world space
		                 glm::vec3(0, 1, 0)
		             );
		break;
	case CameraMode::FREECAM :
		viewMatrix = transform.lock()->getModelMatrix();//Ife we're free caming we can just use the model matrix for our view
		break;
	default:
		viewMatrix = glm::translate(glm::mat4(), transform.lock()->getWorldPosition());
		break;
	}
}

void Camera::onDisplayChange() {
	projectionMatrix = glm::perspective(
	                       glm::radians(45.0f), // The Field of View
	                       float(gameEngine::context->config->getScreenWidth()) / float(gameEngine::context->config->getScreenHeight()),// Aspect Ratio
	                       0.1f, // Near clipping plane
	                       100.0f // Far clipping plane
	                   );
}

void Camera::transformUpdate() {
	updateViewMatrix();
}