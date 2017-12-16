#pragma once

#include <glm/vec3.hpp>
#include <memory>

#include "Component.h"
#include "GraphicsUtils.h"
#include "gameEngine.h"
#include "GameObject.h"

class Light : public Component {
public:
	static std::weak_ptr<Light> getMainLight() {
		return gameEngine::context->mainLight->getComponent<Light>();
	}

	float getLightPower() ;
	void setLightPower(float _lightPower) ;
	void incLightPower(float _inc) ;

	float getShininess() ;
	void setShininess(float _shininess) ;
	void incShininess(float _inc) ;

	float getAlpha() ;
	void setAlpha(float _alpha) ;
	void incAlpha(float _inc) ;

	Colour getLightColour() ;
	void setLightColour(Colour _c) ;

	Colour getEmmissiveColour() ;
	void setEmmissiveColour(Colour _c) ;

	Colour getDiffuseColour() ;
	void setDiffuseColour(Colour _c) ;

	Colour getSpecularColour() ;
	void setSpecularColour(Colour _c) ;
private:
	float lightPower = 1.0f;
	float shininess = 50.0f;
	float alpha = 1.0f;

	glm::vec3 lightColour = glm::vec3(0.8, 0.8, 0.8);
	glm::vec3 emissiveColour = glm::vec3(0, 0, 0);
	glm::vec3 diffuseColour = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 specularColour = glm::vec3(1.0f, 1.0f, 1.0f);
};