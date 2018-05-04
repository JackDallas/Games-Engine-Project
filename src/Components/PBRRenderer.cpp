#include "PBRRenderer.h"

#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <map>

#include "Transform.h"
#include "GameObject.h"
#include "gameEngine.h"
#include "Camera.h"
#include "Shader.h"
#include "Logger.h"
#include "Light.h"
#include "Mesh.h"

void PBRRenderer::attachMesh(std::shared_ptr<Mesh> _mesh) {
	mesh = _mesh;
}

void PBRRenderer::init(std::string vertShaderLoc, std::string fragShaderLoc,
                       std::string albedoLoc,
                       std::string roughnessLoc,
                       std::string specLoc) {

	albedoTexture = SOIL_load_OGL_texture(
	    albedoLoc.c_str(),
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	roughnessTexture = SOIL_load_OGL_texture(
	    roughnessLoc.c_str(),
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	specTexture = SOIL_load_OGL_texture(
	    specLoc.c_str(),
	    SOIL_LOAD_AUTO,
	    SOIL_CREATE_NEW_ID,
	    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	std::vector<std::string> v;

	//register uniforms
	v.push_back("Tex");
	v.push_back("Roughness");
	v.push_back("Spec");

	//Default uniforms
	v.push_back("Model");
	v.push_back("View");
	v.push_back("Projection");
	v.push_back("LightPosition");
	v.push_back("LightPower");
	v.push_back("LightColour");
	v.push_back("EmissiveColour");
	v.push_back("DiffuseColour");
	v.push_back("SpecularColour");
	v.push_back("Shininess");
	v.push_back("Alpha");

	shader = std::make_shared<Shader>(
	             vertShaderLoc,
	             fragShaderLoc,
	             v, true);

			//
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, albedoTexture);
			glUniform1i(shader->getUniformID("Tex"), 0);
			//

			//
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, roughnessTexture);
			glUniform1i(shader->getUniformID("Roughness"), 1);
			//

			//
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, specTexture);
			glUniform1i(shader->getUniformID("Spec"), 2);
			//
}

void PBRRenderer::onRender() {
	if (mesh.lock()) {
		std::shared_ptr<GameObject> currentCam = gameEngine::context->mainCamera;
		if (currentCam.get()) {
			glUseProgram(shader->program);

			glUniformMatrix4fv(shader->getUniformID("Model"), 1, GL_FALSE, &transform.lock()->getModelMatrix()[0][0]);
			glUniformMatrix4fv(shader->getUniformID("View"), 1, GL_FALSE, &Camera::getMainCamera().lock()->getViewMatrix()[0][0]);
			glUniformMatrix4fv(shader->getUniformID("Projection"), 1, GL_FALSE, &Camera::getMainCamera().lock()->getProjectionMatrix()[0][0]);


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


void PBRRenderer::onAwake() {
	transform = gameObject.lock()->getComponent<Transform>();
}

void PBRRenderer::onUpdate(float deltaTime) {
	if (shader->liveReload) {
		shader->checkForReload();
	}
}