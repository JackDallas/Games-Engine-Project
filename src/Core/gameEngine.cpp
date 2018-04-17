#include "gameEngine.h"
//std
#include <iostream>
#include <chrono>
//GL
#include <GL/glew.h>
#include <glm/vec3.hpp>
//GUI
#include <imgui/imgui.h>
#include "imgui_impl.h"
//Managers
#include "InputManager.h"
#include "GraphicsManager.h"
#include "GUIManager.h"
//Containers
#include "Context.h"
#include "EngineConfig.h"
//Components
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include "Controller.h"
#include "Light.h"
//Helpers
#include "Logger.h"

//Makes the linker allocate the memory for the static member
std::shared_ptr<Context> gameEngine::context;

bool gameEngine::init(int argc, char* argv[]) {
#ifdef DEBUGMODE
	Logger::Info("Starting Dallas Engine");
	Logger::Info("Made Context, Initing...");
#endif
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
#ifdef DEBUGMODE
		Logger::Error("SDL Initialization failed!");
		Logger::Error(SDL_GetError());
#endif
		return false;
	}

	context = std::make_shared<Context>();

	return true;
}

void gameEngine::configure(EngineConfig _config) {
	context->config = std::make_shared<EngineConfig>(_config);
//Managers
#ifdef DEBUGMODE
	Logger::Info("Initialising Managers");
#endif
	//GRAPHICS FIRST
	GraphicsManager::init();
	//
	InputManager::init();
	//
//

//Context build
#ifdef DEBUGMODE
	Logger::Info("Initialising Context");
	Logger::Info("Creating Default Camera");
#endif
	std::shared_ptr<GameObject> cam = gameEngine::newGameObject();

	cam->addComponent<Transform>()->setPosition(glm::vec3(-16.0f, -17.0f, -20.5f));

	std::weak_ptr<Camera> camComp = cam->addComponent<Camera>();

	camComp.lock()->lookAt(glm::vec3(2.0f,0.0f,2.0f));
	
	cam->addComponent<Controller>();

	//	camComp.lock()->setCameraMode(CameraMode::LOOKAT);

	context->mainCamera = cam;

#ifdef DEBUGMODE
	Logger::Info("Creating Default Light");
#endif
	gameEngine::context->mainLight = gameEngine::newGameObject();

	gameEngine::context->mainLight->addComponent<Transform>()->setPosition(glm::vec3(5.0f, 5.0f, 5.0f));

	gameEngine::context->mainLight->addComponent<Light>();

#ifdef DEBUGMODE
	Logger::Info("Initialised Context");

	Logger::Info("Finished Engine INIT");

	Logger::Info("~~~~~~~~Versions~~~~~~~~");
	std::cout << "INFO: OpenGL Shading Language Version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
	std::cout << "INFO: OpenGL Version: " << glGetString( GL_VERSION ) << std::endl;

	std::cout << "INFO: GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "INFO: OpenGL Version: " << glGetString( GL_VERSION ) << std::endl;

	std::cout << "INFO: OpenGL Vendor: " << glGetString( GL_VENDOR ) << std::endl;
	std::cout << "INFO: OpenGL Renderer: " << glGetString( GL_RENDERER ) << std::endl;
	std::cout << "INFO: OpenGL Shading Language Version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
	Logger::Info("~~~~~~~~Versions~~~~~~~~");
#endif

	GraphicsManager::renderLoading();
}

void gameEngine::run() {
#ifdef DEBUGMODE
	Logger::Info("Starting main loop");
#endif
	context->running = true;

	context->lastTime = SDL_GetTicks();

	while (context->running) {
		float deltaTime = float((SDL_GetTicks() - context->lastTime) / 1000.0f);

		InputManager::processInput();

		ImGui_ImplSdlGL3_NewFrame(context->window);

		gameEngine::update(deltaTime);

		GUIManager::renderGUI();

		GraphicsManager::display();

		context->lastTime = SDL_GetTicks();

		if (deltaTime < (1.0f / 50.0f)) {
			SDL_Delay((unsigned int) (((1.0f / 50.0f) - deltaTime) * 1000.0f) );
		}
	}
	ImGui_ImplSdlGL3_Shutdown();
}

void gameEngine::update(float deltaTime) {
	if (!context->gameObjects.empty()) {
		for (std::shared_ptr<GameObject> go : context->gameObjects) {
			for (std::shared_ptr<Component> comp : go->Components) {
				comp->onUpdate(deltaTime);
			}
		}
	}
}

std::shared_ptr<GameObject> gameEngine::newGameObject() {
	std::shared_ptr<GameObject> g = std::make_shared<GameObject>();
	context->gameObjects.push_back(g);
	return g;
}