#pragma once
#include <glm/vec3.hpp>


class GUIManager {
public:
	static void renderGUI();

private:
	static void preUpdateGUIComponents();

	static void renderGUIComponents();

	static void updateGUIComponents();
	//temp holding values

	static float light;
	static glm::vec3 camPos;

	//prevent creation
	GUIManager();
	GUIManager(const GUIManager& that) = delete;
};