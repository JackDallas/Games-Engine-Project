#pragma once
//ext
#include <GL/glew.h>
//std
#include <memory>
//int
#include "Mesh.h"
#include "Component.h"
class Transform;
class Shader;

class MeshRenderer : public Component {
public:
	/**
	Attaches a Mesh to this Mesh Renderer to render
	*/
	void attachMesh(std::shared_ptr<Mesh> _mesh);
	/**
	Attaches a Mesh to this Mesh Renderer to render and a shader to render it with
	*/
	void attachMesh(std::shared_ptr<Mesh> _mesh,std::shared_ptr<Shader> _shader);

	void onRender();
	void onUpdate(float deltaTime);
	void onAwake();
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
};