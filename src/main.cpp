#include "gameEngine.h"

#include <iostream>
#include <memory>
#include <vector>

#include "EngineConfig.h"
#include "GraphicsUtils.h"
#include "FileUtils.h"

#include "GameObject.h"
#include "Component.h"

#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "PBRRenderer.h"
#include "Mesh.h"
#include "CircleScript.h"
#include "PBRModelHelper.h"

#include <glm/vec3.hpp>

#include "Logger.h"

int main(int argc, char* argv[]) {
	gameEngine::init(argc, argv);
//1280, 720
	EngineConfig config(1280, 720, Colour(1.0f, 1.0f, 1.0f, 1.0f), false, "PBR Renderer - DISSO");

	gameEngine::configure(config);
////////////////////////////////////
	/*

	std::shared_ptr<GameObject> plane = gameEngine::newGameObject();
	plane->addComponent<Transform>()->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	std::shared_ptr<Mesh> mesh_plane = std::make_shared<Mesh>(FileUtils::getProgramPath() + "..\\dependencies\\Models\\plane.obj");
	plane->addComponent<MeshRenderer>()->attachMesh(mesh_plane);


	std::shared_ptr<GameObject> jiggy = gameEngine::newGameObject();
	jiggy->addComponent<Transform>()->setPosition(glm::vec3(10.0f, 0.0f, 10.0f));

	std::shared_ptr<Mesh> mesh_jiggy = std::make_shared<Mesh>(FileUtils::getProgramPath() + "..\\dependencies\\Models\\Jiggy\\Jiggy.obj",FileUtils::getProgramPath() + "..\\dependencies\\Models\\Jiggy\\image_0000.png");s

	std::shared_ptr<GameObject> Rock = gameEngine::newGameObject();
	Rock->addComponent<Transform>()->setPosition(glm::vec3(5.0f, 0.0f, 0.0f));
	std::shared_ptr<Mesh> rockMesh = std::make_shared<Mesh>(FileUtils::getProgramPath() + "..\\dependencies\\Models\\Rock\\Aset_rock_granite_M_rbjtT_LOD0.obj");

	std::shared_ptr<PBRRenderer> rockRenderer = Rock->addComponent<PBRRenderer>();

	rockRenderer->attachMesh(rockMesh);
	rockRenderer->init(
		FileUtils::getProgramPath() + "..\\src\\Shaders\\Rewrite_PBRVertShader.vert",
		FileUtils::getProgramPath() + "..\\src\\Shaders\\Rewrite_PBRFragShader.frag",
	
		FileUtils::getProgramPath() + "..\\dependencies\\Models\\Rock\\Aset_rock_granite_M_rbjtT_4K_Albedo.jpg",
		FileUtils::getProgramPath() + "..\\dependencies\\Models\\Rock\\Aset_rock_granite_M_rbjtT_4K_Roughness.jpg",
		FileUtils::getProgramPath() + "..\\dependencies\\Models\\Rock\\Aset_rock_granite_M_rbjtT_4K_Specular.jpg"
	);*/
////////////////////////////////////
	std::shared_ptr<GameObject> mug = gameEngine::newGameObject();

	std::shared_ptr<Transform> mugTrans = mug->addComponent<Transform>();
	mugTrans->setPosition(glm::vec3(5.0f, 0.0f, 0.0f));
	mugTrans->setScale(glm::vec3(0.4f,0.4f,0.4f));

	std::shared_ptr<Mesh> mugMesh = std::make_shared<Mesh>
	(FileUtils::getProgramPath() + "..\\dependencies\\Models\\Mug\\Mug.obj");

	std::shared_ptr<PBRRenderer> mugRenderer = mug->addComponent<PBRRenderer>();

	mugRenderer->attachMesh(mugMesh);
	mugRenderer->init(
		FileUtils::getProgramPath() + "..\\src\\Shaders\\Rewrite_PBRVertShader.vert",
		FileUtils::getProgramPath() + "..\\src\\Shaders\\Rewrite_PBRFragShader.frag",
	
		FileUtils::getProgramPath() + "..\\dependencies\\Models\\Mug\\Mug_Albedo.jpg",
		FileUtils::getProgramPath() + "..\\dependencies\\Models\\Mug\\Mug_Roughness.jpg",
		FileUtils::getProgramPath() + "..\\dependencies\\Models\\Mug\\Mug_Specular.jpg"
	);
//////////////////////////////////////
	gameEngine::run();

	return 0;
}