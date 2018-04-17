#include "GUIManager.h"
//GUI
#include <imgui/imgui.h>
#include "imgui_impl.h"
//
#include "gameEngine.h"
#include "GameObject.h"
#include "Light.h"
#include "Transform.h"
//
#include <memory>

//static initialisation
	float GUIManager::light;
	glm::vec3 GUIManager::camPos;

//
void GUIManager::renderGUI(){
	preUpdateGUIComponents();
	renderGUIComponents();
	updateGUIComponents();
}

void GUIManager::preUpdateGUIComponents() {
	light = gameEngine::context->mainLight->getComponent<Light>()->getLightPower();
	camPos = gameEngine::context->mainCamera->getComponent<Transform>()->getLocalPosition();
}

void GUIManager::renderGUIComponents() {
	ImGui::Text("World Controller!");

	ImGui::SliderFloat("Light Level", &light, 0.0f, 5.0f);
	ImGui::InputFloat3("Look At ", (float*)&camPos, -20.0f, 20.0f);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void GUIManager::updateGUIComponents() {
	gameEngine::context->mainLight->getComponent<Light>()->setLightPower(light);
	gameEngine::context->mainCamera->getComponent<Transform>()->setPosition(camPos);
}