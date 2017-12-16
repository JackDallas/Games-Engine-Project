#pragma once
//glm
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
//std
#include <vector>
#include <functional>
//internal
#include "Component.h"

class Transform : public Component {

public :
	/**
	Default constructor for a transform everything set to
	*/
	Transform();
	/**
	Transform Constructor
	@param _pos glm::vec3 representing the position of the transform
	*/
	Transform(glm::vec3 _pos);
	/**
	Transform Constructor
	@param _pos glm::vec3 representing the position of the transform
	@param _rot glm::vec3 representing the rotation of the transform
	*/
	Transform(glm::vec3 _pos, glm::vec3 _rot);
	/**
	Transform Constructor
	@param _pos glm::vec3 representing the position of the transform
	@param _rot glm::vec3 representing the rotation of the transform
	@param _scaler glm::vec3 representing the scale of the transform
	*/
	Transform(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scaler);

	/**
	getModelMatrix
	@return returns a glm::mat4 representing the transforms Model Matrix
	*/
	glm::mat4 getModelMatrix();
	/**
	recalculated the model matrix
	*/
	void updateModelMatrix();

	void onUpdate(float deltaTime);
	/**
	sets the local position of the transform
	@param _pos the new position
	*/
	void setPosition(glm::vec3 _pos);
	/**
	moves the local position of the transform
	@param _movement the movement to be added to the position
	*/
	void movePosition(glm::vec3 _movement);
	/**
	moves the local position of the transform towards the target
	@param _movement the amount to move the transform
	@param _target the glm::vec3 to move towards
	*/
	void moveTowards(float _movement, glm::vec3 _target);
	/**
	getWorldPosition
	@return returns a glm::vec3 representing the transforms position in world space
	*/
	glm::vec3 getWorldPosition();
	/**
	getLocalPosition
	@return returns a glm::vec3 representing the transforms position locally
	*/
	glm::vec3 getLocalPosition();
	/**
	sets the local rotation of the transform
	@param _rot the new rotation
	*/
	void setRotation(glm::vec3 _rot);
	/**
	moves the local rotation of the transform
	@param _rot the movement to be added to the rotation
	*/
	void rotate(glm::vec3 _rot);
	/**
	getRotation
	@return returns a glm::mat3 representing the transforms rotation
	*/
	glm::vec3 getRotation();
	/**
	sets the local scale of the transform
	@param _scaler the new scale
	*/
	void setScale(glm::vec3 _scaler);
	/**
	scales the local position of the transform
	@param _scaler the amount to be added to the scale
	*/
	void scale(glm::vec3 _scaler);
	/**
	getScale
	@return returns a glm::vec3 representing the transforms scale
	*/
	glm::vec3 getScale();
	/**
	Pass in std::bind() functions to be called when the position of the transform is changed
	e.g. in the class Foo to have the Function Bar called pass through :
	std::bind(&Foo::Bar, this)
	where this is the reference to the instance of the class you want to be called
	@param callback the std::bind function you want called
	*/
	void positionChangedCallback(std::function<void()> callback);
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scaler;

	glm::mat4 modelMatrix;

	std::vector<std::function<void()>> positionChangedCallbacks;
};