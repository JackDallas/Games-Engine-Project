#include "InputManager.h"
//Components
#include "Input.h"
#include "Component.h"
#include "GameObject.h"
//Containers
#include "gameEngine.h"
#include "Context.h"
//GL
#include "imgui_impl.h"

//std
#include <cctype>
//Helpers
#include "Logger.h"
#include "GraphicsUtils.h"
#include <iostream>

void InputManager::init() {
	SDL_SetRelativeMouseMode(GraphicsUtils::boolToSDL(gameEngine::context->captureInput));
}

void InputManager::processInput() {
	SDL_SetRelativeMouseMode(GraphicsUtils::boolToSDL(gameEngine::context->captureInput));

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSdlGL3_ProcessEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			gameEngine::context->running = false;
			break;
		case SDL_KEYDOWN | SDL_KEYDOWN:
			KeyboardEvent(&event);
			break;
		case SDL_MOUSEMOTION:
			motionEvent(&event);
			break;
		case SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONUP :
			mouseEvent(&event);
			break;
		}

	}
}

void InputManager::motionEvent(SDL_Event *event) {
	Mouse_Input i;

	Mouse_Position mp ;
	mp.x = event->motion.x;
	mp.y = event->motion.y;
	mp.xRel = event->motion.xrel;
	mp.yRel = event->motion.yrel;

	i.type = Mouse_InputType::MOUSE_MOVEMENT;
	i.mousePosition = mp;

	if (!gameEngine::context->gameObjects.empty()) {
		for (std::shared_ptr<GameObject> go : gameEngine::context->gameObjects) {
			for (std::shared_ptr<Component> comp : go->Components) {
				comp->onMouseEvent(i);
			}
		}
	}
}

void InputManager::mouseEvent(SDL_Event *event) {
	Mouse_Input i;

	Mouse_Position mp;
	mp.x = event->button.x;
	mp.y = event->button.y;

	i.type = (event->button.type == SDL_MOUSEBUTTONDOWN) ? Mouse_InputType::MOUSE_DOWN : Mouse_InputType::MOUSE_UP;

	i.mousePosition = mp;

	i.key =	Mouse_InputKey(event->button.button);

	if (!gameEngine::context->gameObjects.empty()) {
		for (std::shared_ptr<GameObject> go : gameEngine::context->gameObjects) {
			for (std::shared_ptr<Component> comp : go->Components) {
				comp->onMouseEvent(i);
			}
		}
	}
}

void InputManager::KeyboardEvent(SDL_Event *event) {
	if (event->key.keysym.sym == SDLK_ESCAPE) { //todo debug mode
		gameEngine::context->running = false;
		exit (0);
	} else if (event->key.keysym.sym == SDLK_m) {
		gameEngine::context->captureInput = !gameEngine::context->captureInput;
	}

	Key_Input i; //Input struct

	i.type = (event->type == SDL_KEYDOWN) ? Key_InputType::KEY_DOWN : Key_InputType::KEY_UP;

	i.key = Key_InputKey(event->key.keysym.sym); // Enums and chars require explicit casting

	if (!gameEngine::context->gameObjects.empty()) {
		for (std::shared_ptr<GameObject> go : gameEngine::context->gameObjects) {
			for (std::shared_ptr<Component> comp : go->Components) {
				comp->onKeyEvent(i);
			}
		}
	}
}