#include "MeshRenderer.h"

#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

#include <memory>

#include "Transform.h"
#include "GameObject.h"
#include "gameEngine.h"
#include "Camera.h"
#include "Shader.h"
#include "DefaultShaders.h"
#include "Logger.h"
#include "Light.h"


void MeshRenderer::attachMesh(std::shared_ptr<Mesh> _mesh) {
	mesh = _mesh;// set the mesh

	if (mesh.lock()->texture == 0) {//if the mesh isn't textured
		shader = DefaultShaders::getVertFragInstance();//create an instance of the un-textured shader
	} else {
		if (gameEngine::context->mainLight.get()) {
			Logger::Debug("Lit shader");
			shader = DefaultShaders::getLitTexturedVertFragInstance();//create an instance of the textured lit shader
		} else {
			shader = DefaultShaders::getTexturedVertFragInstance();//create an instance of the textured shader
		}
	}
}

void MeshRenderer::attachMesh(std::shared_ptr<Mesh> _mesh, std::shared_ptr<Shader> _shader) {
	mesh = _mesh;
	shader = _shader;
}

void MeshRenderer::onAwake() {
	transform = gameObject.lock()->getComponent<Transform>();
}

void MeshRenderer::onUpdate(float deltaTime){
	if(shader->liveReload){
		shader->checkForReload();
	}
}

void MeshRenderer::onRender() {
	if (mesh.lock()) {
		std::shared_ptr<GameObject> currentCam = gameEngine::context->mainCamera;
		if (currentCam.get()) {
			glUseProgram(shader->program);

			glUniformMatrix4fv(shader->getUniformID("Model"), 1, GL_FALSE, &transform.lock()->getModelMatrix()[0][0]);
			glUniformMatrix4fv(shader->getUniformID("View"), 1, GL_FALSE, &Camera::getMainCamera().lock()->getViewMatrix()[0][0]);
			glUniformMatrix4fv(shader->getUniformID("Projection"), 1, GL_FALSE, &Camera::getMainCamera().lock()->getProjectionMatrix()[0][0]);

			//Check this mesh has a texture
			if (mesh.lock()->texture != 0) {
				glActiveTexture(GL_TEXTURE0);
				glUniform1i(shader->getUniformID("texture"), 0);
				glBindTexture(GL_TEXTURE_2D, mesh.lock()->texture);
			}
			//if we have a main light
			if (gameEngine::context->mainLight) {
				glUniform4fv( shader->getUniformID("LightPosition"), 1, glm::value_ptr(gameEngine::context->mainLight->getComponent<Transform>()->getWorldPosition()));
				glUniform1f( shader->getUniformID("LightPower"), gameEngine::context->mainLight->getComponent<Light>()->getLightPower());
			}
			// Activate the VAO
			glBindVertexArray( mesh.lock()->VAO );

			// Tell OpenGL to draw it
			// Must specify the type of geometry to draw and the number of vertices
			glDrawArrays(GL_TRIANGLES, 0, mesh.lock()->numVertices);

			//glDisableVertexAttribArray(0); //Q : Why does this stop renders after the first
			// Unbind VAO
			glBindVertexArray( 0 );
		}
	}
}