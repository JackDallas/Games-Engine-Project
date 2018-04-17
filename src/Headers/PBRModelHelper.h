#pragma once

#include <memory>
#include <string>

#include "FileUtils.h"

#include "GameObject.h"
#include "Component.h"

#include "Transform.h"
#include "PBRRenderer.h"
#include "Mesh.h"

#include <glm/vec3.hpp>

class PBRModelHelper {
public:
	static std::shared_ptr<GameObject> newPBRObject(std::string _folderLocation, std::string assetName, glm::vec3 location) {
		std::shared_ptr<GameObject> Rock = gameEngine::newGameObject();
		Rock->addComponent<Transform>()->setPosition(location);

		std::shared_ptr<Mesh> rockMesh = std::make_shared<Mesh>(_folderLocation + "\\" + assetName + "_LOD0.obj");

		std::shared_ptr<PBRRenderer> rockRenderer = Rock->addComponent<PBRRenderer>();

		rockRenderer->attachMesh(rockMesh);
		rockRenderer->init(
		    FileUtils::getProgramPath() + "..\\src\\Shaders\\Rewrite_PBRVertShader.vert",
		    FileUtils::getProgramPath() + "..\\src\\Shaders\\Rewrite_PBRFragShader.frag",
		{
			{"Tex", _folderLocation + "\\" + assetName + "_4K_Albedo.jpg"},
			{"Roughness", _folderLocation + "\\" + assetName + "_4K_Roughness.jpg"},
			{"Spec", _folderLocation + "\\" + assetName + "_4K_Specular.jpg"}
		});


		return Rock;
	}
};