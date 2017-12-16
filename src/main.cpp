#include "gameEngine.h"

#include <iostream>
#include <memory>
#include <vector>

#include "EngineConfig.h"
#include "GraphicsUtils.h"

#include "GameObject.h"
#include "Component.h"

#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "RotateScript.h"

#include <glm/vec3.hpp>

#include "Logger.h"

int main(int argc, char* argv[]) {
	gameEngine::init(argc, argv);

	EngineConfig config(1280, 720, Colour(0.0f, 0.0f, 0.4f, 1.0f), false, "Dallas' Game");

	gameEngine::configure(config);

	//Create a new GameObject
	std::shared_ptr<GameObject> go = gameEngine::newGameObject();
		//Attach a transform and set the position
		std::shared_ptr<Transform> goTrans = go->addComponent<Transform>();
		goTrans->setPosition(glm::vec3(0.0f, 10.0f, 0.0f));

		//create a mesh
		std::shared_ptr<Mesh> mesh_jiggy = std::make_shared<Mesh>("Models\\Jiggy\\Jiggy.obj","Models\\Jiggy\\image_0000.png");

		//Attach a mesh renderer
		std::shared_ptr<MeshRenderer> meshR = go->addComponent<MeshRenderer>();

			meshR->attachMesh(mesh_jiggy);


	std::shared_ptr<Mesh> mesh_emerald = std::make_shared<Mesh>("Models\\Emerald\\EmeraldPiece.obj","Models\\Emerald\\ref_eme.png");
	
	//Create a new GameObject
	std::shared_ptr<GameObject> Emerald1 = gameEngine::newGameObject();
		//Attach a transform and set the position
		Emerald1->addComponent<Transform>()->setPosition(glm::vec3(-5.0f, 10.0f, 0.0f));
		//Attach a mesh renderer and mesh
		Emerald1->addComponent<MeshRenderer>()->attachMesh(mesh_emerald);
		Emerald1->addComponent<RotateScript>();

	//Create a new GameObject
	std::shared_ptr<GameObject> Emerald2 = gameEngine::newGameObject();
		//Attach a transform and set the position
		Emerald2->addComponent<Transform>()->setPosition(glm::vec3(5.0f, 10.0f, 0.0f));
		//Attach a mesh renderer and mesh
		Emerald2->addComponent<MeshRenderer>()->attachMesh(mesh_emerald);
		Emerald2->addComponent<RotateScript>();


	//Create a new GameObject
	std::shared_ptr<GameObject> landscape = gameEngine::newGameObject();
		//Attach a transform and set the position
		std::shared_ptr<Transform> landscapeTrans = landscape->addComponent<Transform>();
			landscapeTrans->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
			landscapeTrans->setScale(glm::vec3(4.0f,4.0f,4.0f));
		//create a mesh
		std::shared_ptr<Mesh> mesh_landscape = std::make_shared<Mesh>("Models\\mountain\\mountT.blend1.obj","Models\\mountain\\ground_grass_3264_4062_Small.jpg");

		//Attach a mesh renderer
		landscape->addComponent<MeshRenderer>()->attachMesh(mesh_landscape);

	std::shared_ptr<GameObject> plane = gameEngine::newGameObject();
		plane->addComponent<Transform>()->setPosition(glm::vec3(0.0f,0.0f,0.0f));
		std::shared_ptr<Mesh> mesh_plane = std::make_shared<Mesh>("Models\\plane.obj");
		plane->addComponent<MeshRenderer>()->attachMesh(mesh_plane);


	gameEngine::run();

	return 0;
}