#pragma once
//std
#include <memory>
//ext
#include <glm/mat4x4.hpp>
//int
#include "Component.h"
class Transform;

/**
Camera Mode.
For setting the current mode of the Camera.
*/
enum CameraMode {
	LOOKAT,/**< enum value LookAt*/
	FREECAM/** enum value FreeCam*/
};

class Camera : public Component {

public:
	static std::weak_ptr<Camera> getMainCamera();

	void onAwake();
	void onDisplayChange();
	/**
	getViewMatrix, Returns the View Matrix of the camera
	@return The View Matrix	
	*/
	glm::mat4 getViewMatrix();
	/**
	getProjectionMatrix, Returns the Projection Matrix of the camera
	@return The Projection Matrix	
	*/
	glm::mat4 getProjectionMatrix();
	/**
	getViewProjectionMatrix, Returns the View Matrix multiplied by the Projection Matrix of the camera
	@return The Projection * View Matrix	
	*/
	glm::mat4 getViewProjectInv();
	/**
	lookAt, for setting the current target the camera should look at.

	This will only work if the mode is currently set to LOOKAT
	@see setCameraMode() 
	@param _at the new target for the camera to look at.
	*/
	void lookAt(glm::vec3 _at);
	/**
	setCameraMode, for setting the current Camera Mode

	@see CameraMode 
	@param _newMode the new camera mode
	*/
	void setCameraMode(CameraMode _newMode);

	/**
	transformUpdate, called when the transform on the gameobject is updated

	@see Transform
	*/
	void transformUpdate();
	/**
	updateViewMatrix, when called the view Matrix is recalculated.
	*/
	void updateViewMatrix();

	/** 
	currentMode, the current mode of the camera
	*/ 
	CameraMode currentMode; 
	/**
	target, the current target of the camera
	*/
	glm::vec3 target;
private:
	glm::mat4 projectionMatrix;

	glm::mat4 viewMatrix;

	std::weak_ptr<Transform> transform;

};