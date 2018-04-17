#include "Light.h"

float Light::getLightPower() {
	return lightPower;
}
void Light::setLightPower(float _lightPower) {
	lightPower = _lightPower;
}
void Light::incLightPower(float _inc) {
	lightPower += _inc;
}

float Light::getShininess() {
	return shininess;
}
void Light::setShininess(float _shininess) {
	shininess = _shininess;
}
void Light::incShininess(float _inc) {
	shininess += _inc;
}

float Light::getAlpha() {
	return alpha;
}
void Light::setAlpha(float _alpha) {
	alpha = _alpha;
}
void Light::incAlpha(float _inc) {
	alpha += _inc;
}

Colour Light::getLightColour() {
	return Colour(lightColour);
}
void Light::setLightColour(Colour _c) {
	lightColour = _c.toVec3();
}

Colour Light::getEmmissiveColour() {
	return Colour(emissiveColour);
}
void Light::setEmmissiveColour(Colour _c) {
	emissiveColour = _c.toVec3();
}

Colour Light::getDiffuseColour() {
	return Colour(diffuseColour);
}
void Light::setDiffuseColour(Colour _c) {
	diffuseColour = _c.toVec3();
}

Colour Light::getSpecularColour() {
	return Colour(specularColour);
}
void Light::setSpecularColour(Colour _c) {
	specularColour = _c.toVec3();
}