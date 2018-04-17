#pragma once
//ext
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <SDL2/SDL.h>
/**
Colour, a color made of 4 parts red,green.blue,alpha
*/
struct Colour {
	float r, g, b, a;
	/**
	toVec3 
	@return returns a glm::vec3() of the colour
	*/
	glm::vec3 toVec3(){
		return glm::vec3(r,g,b); 
	}
	Colour(float _r, float _g, float _b, float _a) {
		r = _r; g = _g; b = _b; a = _a;
	}
	Colour(glm::vec3 _v) {
		r = _v.x; g = _v.y; b = _v.z;
	}
	Colour(glm::vec4 _v) {
		r = _v.x; g = _v.y; b = _v.z; a = _v.w;
	}
	Colour() {
		r = 0.0f; g = 0.0f; b = 0.0f; a = 1.0f;
	}
};

class GraphicsUtils {
public:
	/**
	RGBtoFloat, turns an rgb value 0-255 to a float 0-1
	@param v the value of the colour between 0-255
	@return returns a float between 0 and 1 representing the colour 
	*/
	static float RGBtoFloat(float v);
	static SDL_bool boolToSDL(bool b);
private:
	//stops class creation
	GraphicsUtils();
	GraphicsUtils(const GraphicsUtils& that) = delete;
};