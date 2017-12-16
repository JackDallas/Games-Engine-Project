#include "gameEngine.h"
//std
#include <iostream>
//GL
#include <GL/glew.h>
#include <GL/freeglut.h>
//Managers
#include "InputManager.h"
#include "GraphicsManager.h"
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

void gameEngine::init(int argc, char* argv[]) {
	Logger::Info("Starting Dallas Engine");
	Logger::Info("Made Context Initing GLUT");
	glutInit(&argc, argv);

	context = std::make_shared<Context>();
}

void gameEngine::configure(EngineConfig _config) {
	context->config = std::make_shared<EngineConfig>(_config);
//Managers
	Logger::Info("Initialising Managers");
	//GRAPHICS FIRST
	GraphicsManager::init();
	//
	InputManager::init();
	//
	glutIdleFunc(idle);
//

//Context build
	Logger::Info("Initialising Context");
	Logger::Info("Creating Default Camera");
	std::shared_ptr<GameObject> cam = gameEngine::newGameObject();

	cam->addComponent<Transform>()->setPosition(glm::vec3(-5.0f, -5.0f, -5.0f));

	cam->addComponent<Camera>();

	cam->addComponent<Controller>();

	context->mainCamera = cam;

	Logger::Info("Creating Default Light");
	gameEngine::context->mainLight = gameEngine::newGameObject();

	gameEngine::context->mainLight->addComponent<Transform>()->setPosition(glm::vec3(5.0f, 5.0f, 5.0f));

	gameEngine::context->mainLight->addComponent<Light>();
	Logger::Info("Initialised Context");

	Logger::Info("Finished Engine INIT");

	Logger::Info("~~~~~~~~Versions~~~~~~~~");
#ifdef DEBUGMODE
	std::cout << "INFO: OpenGL Shading Language Version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
	std::cout << "INFO: OpenGL Version: " << glGetString( GL_VERSION ) << std::endl;

	std::cout << "INFO: GLUT Version : "  << glutGet(GLUT_VERSION) << std::endl;
	std::cout << "INFO: GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "INFO: OpenGL Version: " << glGetString( GL_VERSION ) << std::endl;

	std::cout << "INFO: OpenGL Vendor: " << glGetString( GL_VENDOR ) << std::endl;
	std::cout << "INFO: OpenGL Renderer: " << glGetString( GL_RENDERER ) << std::endl;
	std::cout << "INFO: OpenGL Shading Language Version: " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
#endif

	Logger::Info("~~~~~~~~Versions~~~~~~~~");
}

void gameEngine::run() {
	Logger::Info("Starting GLUT main loop");
	context->lastTime = glutGet(GLUT_ELAPSED_TIME);
	GraphicsManager::displayChange(0, 0); //Call right before we start so everything updates
	glutMainLoop();
}

std::shared_ptr<GameObject> gameEngine::newGameObject() {
	std::shared_ptr<GameObject> g = std::make_shared<GameObject>();
	context->gameObjects.push_back(g);
	return g;
}

void gameEngine::idle() {
	//solve delta time in milliseconds
	float deltaTime = (glutGet(GLUT_ELAPSED_TIME) - context->lastTime) / 1000.0;
	if (!context->gameObjects.empty()) {
		for (std::shared_ptr<GameObject> go : context->gameObjects) {
			for (std::shared_ptr<Component> comp : go->Components) {
				comp->onUpdate(deltaTime);
			}
		}
	}
	context->lastTime = glutGet(GLUT_ELAPSED_TIME);
	//update the display after our changes
	glutPostRedisplay();
}