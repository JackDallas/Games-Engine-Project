#include "GraphicsManager.h"
//GL
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <imgui/imgui.h>
#include "imgui_impl.h"
//Components
#include "GameObject.h"
#include "Component.h"
//Containers
#include "Context.h"
#include "EngineConfig.h"
//
#include "gameEngine.h"

void GraphicsManager::init() {
//SDL
	//If we're full screen we let glut set the screen size otherwise set it to anything it doesn't matter at this point
	//TODO Fullscreen mode
	gameEngine::context->window = SDL_CreateWindow(
	                                  gameEngine::context->config->getWindowName().c_str(),
	                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                                  gameEngine::context->config->getScreenWidth(),
	                                  gameEngine::context->config->getScreenHeight(),
	                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	gameEngine::context->renderer = SDL_CreateRenderer(gameEngine::context->window, -1, 0);
	gameEngine::context->SDLContext = SDL_GL_CreateContext(gameEngine::context->window);
	/*
	gameEngine::context->config->getFullScreenMode() ?  glutInitWindowSize(200, 400) : glutInitWindowSize(gameEngine::context->config->getScreenWidth(), gameEngine::context->config->getScreenWidth());
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(gameEngine::context->config->getWindowName().c_str());
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutSetWindowTitle(gameEngine::context->config->getWindowName().c_str());
	if (gameEngine::context->config->getFullScreenMode()) glutFullScreen();*/
//
//glew
	Logger::Info("Initing GLEW");
	glewInit();
//
//imgui
	ImGui_ImplSdlGL3_Init(gameEngine::context->window);
	ImGui::StyleColorsClassic();
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
}

void GraphicsManager::renderLoading() {
	/*
	Temp loading bar this needs updating
	*/
	float vertices[] = {
		0.0f,  0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Colour c = gameEngine::context->config->getScreenClearColour();
	glClearColor(c.r, c.g, c.b, c.a);
	//Clear the Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(gameEngine::context->window);
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
	//imgui
	ImGui::Render();
	//Swap out buffers

	SDL_GL_SwapWindow(gameEngine::context->window);
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