#include "GraphicsManager.h"
//GL
#include <GL/glew.h>
#include <GL/freeglut.h>
//Components
#include "GameObject.h"
#include "Component.h"
//Containers
#include "Context.h"
#include "EngineConfig.h"
//
#include "gameEngine.h"

void GraphicsManager::init() {
//glut
	//If we're full screen we let glut set the screen size otherwise set it to anything it doesn't matter at this point
	gameEngine::context->config->getFullScreenMode() ?  glutInitWindowSize(200, 400) : glutInitWindowSize(gameEngine::context->config->getScreenWidth(), gameEngine::context->config->getScreenHeight());
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(gameEngine::context->config->getWindowName().c_str());
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutSetWindowTitle(gameEngine::context->config->getWindowName().c_str());
	if (gameEngine::context->config->getFullScreenMode()) glutFullScreen();
//
//glew
	Logger::Info("Initing GLEW");
	glewInit();
//
//GL
	Logger::Info("Initing GL");
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
//
	glutDisplayFunc(display);
	glutReshapeFunc(displayChange);
}

void GraphicsManager::display() {
	//Set Buffer Clear Colour
	//Dark Blue
	//TODO Config
	Colour c = gameEngine::context->config->getScreenClearColour();
	glClearColor(c.r, c.g, c.b, c.a);
	//Clear the Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Set the Viewport
	//glViewport(0, 0, 800, 600);

	//rendering loop
	if (!gameEngine::context->gameObjects.empty()) {
		for (std::shared_ptr<GameObject> go : gameEngine::context->gameObjects) {
			for (std::shared_ptr<Component> comp : go->Components) {
				comp->onRender();
			}
		}
	}
	//Disable depth test
	//GUI

	//enable depth
	//Swap out buffers
	glutSwapBuffers();
}

void GraphicsManager::displayChange(int width, int height) {
	if (!gameEngine::context->gameObjects.empty()) {
		for (std::shared_ptr<GameObject> go : gameEngine::context->gameObjects) {
			for (std::shared_ptr<Component> comp : go->Components) {
				comp->onDisplayChange();
			}
		}
	}
}