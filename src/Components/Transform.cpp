#include "Transform.h"
//internal
#include "GameObject.h"
//glm
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scaler = glm::vec3(1.0f, 1.0f, 1.0f);
	updateModelMatrix();
}
Transform::Transform(glm::vec3 _pos) {
	position = _pos;
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scaler = glm::vec3(1.0f, 1.0f, 1.0f);
	updateModelMatrix();
}
Transform::Transform(glm::vec3 _pos, glm::vec3 _rot) {
	position = _pos;
	rotation = _rot;
	scaler = glm::vec3(1.0f, 1.0f, 1.0f);
	updateModelMatrix();
}
Transform::Transform(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scaler) {
	position = _pos;
	rotation = _rot;
	scaler = _scaler;
	updateModelMatrix();
}

glm::vec3 Transform::getWorldPosition() {

	glm::vec3 worldPos = position; 

	std::shared_ptr<GameObject> parent = gameObject.lock()->parent.lock(); 

	while (parent) { 
		worldPos += parent->getComponent<Transform>()->position;
		parent = parent->parent.lock(); 
	}

	return worldPos;
}

glm::mat4 Transform::getModelMatrix() {
	return modelMatrix;
}
void Transform::updateModelMatrix() {
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), rotation.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	RotationMatrix = glm::rotate(RotationMatrix, rotation.x, glm::vec3(0.0f, 1.0f, 0.0f));
	RotationMatrix = glm::rotate(RotationMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(1.0f), scaler);

	modelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;

	//Inform Components tracking the location we've changed
	for (std::function<void()> callback : positionChangedCallbacks) {
		callback();
	}
}

void Transform::onUpdate(float deltaTime){
	
}

void Transform::setPosition(glm::vec3 _pos) {
	position = _pos;
	updateModelMatrix();

}
void Transform::movePosition(glm::vec3 _movement) {
	setPosition(position + _movement);
}
void Transform::moveTowards(float _movement, glm::vec3 _target) {
	setPosition(position + (_movement * _target));
}

glm::vec3 Transform::getLocalPosition(){
	return position;
}

void Transform::setRotation(glm::vec3 _rot) {
	rotation = _rot;
	updateModelMatrix();
}
void Transform::rotate(glm::vec3 _rot) {
	setRotation(rotation += _rot);
}
glm::vec3 Transform::getRotation(){
	return rotation;
}

void Transform::setScale(glm::vec3 _scaler) {
	scaler = _scaler;
	updateModelMatrix();
}
void Transform::scale(glm::vec3 _scaler) {
	setScale(scaler += _scaler);
}
glm::vec3 Transform::getScale(){
	return scaler;
}

void Transform::positionChangedCallback(std::function<void()> callback) {
	positionChangedCallbacks.push_back(callback);
}