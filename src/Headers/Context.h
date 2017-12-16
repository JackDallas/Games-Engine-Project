#pragma once
//std
#include <memory>
#include <vector>
//int
class GameObject;
class EngineConfig;

struct Context {
	/**
	gameObjects, list of all the game objects currently in the scene
	*/
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	/**
	mainCamera, the current Main Camera
	*/
	std::shared_ptr<GameObject> mainCamera;
	/**
	config, the config for the engine
	*/
	std::shared_ptr<EngineConfig> config;
	/**
	mainLight, the current main light in the scene
	*/
	std::shared_ptr<GameObject> mainLight;
	/**
	lastTime, the last time for calculation the delta time
	*/
	float lastTime;
};