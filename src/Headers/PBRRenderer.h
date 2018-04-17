#pragma once

#include <memory>
#include <map>

#include <GL/glew.h>

#include "Component.h"

class Shader;
class Transform;
class Mesh;


class PBRRenderer : public Component {
public:

	void onRender();
	void onUpdate(float deltaTime);
	void onAwake();

	void init(std::string vertShaderLoc,std::string fragShaderLoc, std::map<std::string, std::string> texMap);
	void attachMesh(std::shared_ptr<Mesh> _mesh);

	/**
	Reference to the shader we render the mesh with
	*/
	std::shared_ptr<Shader> shader;
	/**
	Reference to the transform of the GameObject
	*/
	std::weak_ptr<Transform> transform;

private:
	std::weak_ptr<Mesh> mesh;

	std::map<std::string, GLuint> textures;
};