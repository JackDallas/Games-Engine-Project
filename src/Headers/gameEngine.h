#pragma once
//Makes sure gl is included first
#include <GL/glew.h>
//std
#include <vector>
#include <memory>
//int
#include "Context.h"
class GameObject;

class gameEngine {
public:
	/**
	init, initialises the games Engine
	THIS MUST BE CALLED FIRST IN YOUR PROGRAM
	the arguments from main need to be passed to this
	@param argc
	@param argv
	*/
	static void init(int argc, char* argv[]);
	/**
	configure the engine with an EngineConfig
	this must be called after init() but before any other gameEngine calls
	@see init()
	@param _config the EngineConfig to configure the engine with
	*/
	static void configure(EngineConfig _config);
	/**
	starts the engine running, this should be called when you've set your program up and want to start
	*/
	static void run();
	/**
	called whenever the engine isn't doing anything, calls onUpdate on all components 
	*/
	static void idle();
	/**
	creates a new game object on the engine and returns a reference to it
	@return a reference to a new gameObject
	*/
	static std::shared_ptr<GameObject> newGameObject();
	/**
	container for our non-static members
	*/
	static std::shared_ptr<Context> context;
private:
	//prevent instances
	gameEngine();
	//Override the default copy constructor
	gameEngine(const gameEngine& that) = delete;
};
