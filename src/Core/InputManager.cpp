#include "InputManager.h"
//Components
#include "Input.h"
#include "Component.h"
#include "GameObject.h"
//Containers
#include "gameEngine.h"
#include "Context.h"
//GL
#include <GL/freeglut.h>
//std
#include <cctype> // toupper islower
//Helpers
#include "Logger.h"

void InputManager::init() {
	glutMotionFunc(motionEvent);
	glutPassiveMotionFunc(motionEvent);
	
	glutMouseFunc(mouseEvent);
	glutKeyboardFunc(KeyboardEvent);
	glutSpecialFunc(SpecialKeyboardEvent);
}

void InputManager::motionEvent(int x, int y) {
	Mouse_Input i; 

	Mouse_Position mp ;
	mp.x = x;
	mp.y = y;
	
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

void InputManager::mouseEvent(int button, int state, int x, int y) {
	Mouse_Input i; 

	Mouse_Position mp ;
	mp.x = x;
	mp.y = y;
	
	i.type = (state == 0) ? Mouse_InputType::MOUSE_DOWN : Mouse_InputType::MOUSE_UP;
	
	i.mousePosition = mp;
	
	i.key =	Mouse_InputKey(button);

	if (!gameEngine::context->gameObjects.empty()) {
		for (std::shared_ptr<GameObject> go : gameEngine::context->gameObjects) {
			for (std::shared_ptr<Component> comp : go->Components) {
				comp->onMouseEvent(i);
			}
		}
	}
}

void InputManager::KeyboardEvent(unsigned char key, int x, int y) {
	if (key == 27) {//todo debug mode
		exit (0);
	}//if esc is pressed

	char keyCode = std::toupper(key); // Force Upper case we don't care this is controller input

	Key_Input i; //Input struct
	i.type = Key_InputType::KEY_DOWN;
	i.key = Key_InputKey(int(keyCode)); // Enums and chars require explicit casting

	if (!gameEngine::context->gameObjects.empty()) {
		for (std::shared_ptr<GameObject> go : gameEngine::context->gameObjects) {
			for (std::shared_ptr<Component> comp : go->Components) {
				comp->onKeyEvent(i);
			}
		}
	}
	//INPUT SO RE-RENDER
	//glutPostRedisplay();
}

void InputManager::SpecialKeyboardEvent(int key, int x, int y) {
	Key_Input i;
	i.type = Key_InputType::KEY_DOWN;
	i.key = Key_InputKey(int(key));
	if (!gameEngine::context->gameObjects.empty()) {
		for (std::shared_ptr<GameObject> go : gameEngine::context->gameObjects) {
			for (std::shared_ptr<Component> comp : go->Components) {
				comp->onKeyEvent(i);
			}
		}
	}
	//INPUT SO RE-RENDER
	//glutPostRedisplay();
}
