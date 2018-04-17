#pragma once

#include <GL/glew.h>

#include <memory>
#include <vector>
#include <string>

#include "Logger.h"
#include "FileUtils.h"
#include "Shader.h"

class Shader;

class DefaultShaders {
public:
	/**
	getVertFrag, gets a reference to the shared default vert frag shader.
	
	Note: using this shader on a mesh means when it's edited all meshes using it are effected, if you want an instance of this shader see getVertFragInstance()
	@see getVertFragInstance()
	@return a reference to the default vert frag shader
	*/
	static std::shared_ptr<Shader> getVertFrag() {
		//needs absolute path @DOCS
		static std::shared_ptr<Shader> defaultVertFrag = initVF();
		return defaultVertFrag;
	}
	/**
	getVertFragInstance, gets a reference to a new instance of the default vert frag shader.
	
	@return a reference to a new instance of the default vert frag shader
	*/
	static std::shared_ptr<Shader> getVertFragInstance() {
		return initVF();
	}
	/**
	getTexturedVertFrag, gets a reference to the shared default vert frag textured shader.
	
	Note: using this shader on a mesh means when it's edited all meshes using it are effected, if you want an instance of this shader see getVertFragTexturedInstance()
	@see getVertFragTexturedInstance()
	@return a reference to the default vert frag textured shader
	*/
	static std::shared_ptr<Shader> getTexturedVertFrag() {
		static std::shared_ptr<Shader> texturedVertFrag = initTVF();
		return texturedVertFrag;
	}
	/**
	getTexturedVertFragInstance, gets a reference to a new instance of the default vert frag textured shader.
	
	@return a reference to a new instance of the default vert frag textured shader
	*/
	static std::shared_ptr<Shader> getTexturedVertFragInstance() {
		return initTVF();
	}
	/**
	getLitTexturedVertFrag, gets a reference to the shared default vert frag textured lit shader.
	
	Note: using this shader on a mesh means when it's edited all meshes using it are effected, if you want an instance of this shader see getLitTexturedVertFragInstance()
	@see getLitTexturedVertFragInstance()
	@return a reference to the default vert frag shader
	*/
	static std::shared_ptr<Shader> getLitTexturedVertFrag() {
		//needs absolute path @DOCS
		static std::shared_ptr<Shader> litTexturedVertFrag = initLTVF();
		return litTexturedVertFrag;
	}
	/**
	getLitTexturedVertFragInstance, gets a reference to a new instance of the default vert frag textured lit shader.
	
	@return a reference to a new instance of the default vert frag textured lit shader
	*/
	static std::shared_ptr<Shader> getLitTexturedVertFragInstance() {
		return initLTVF();
	}
private:
	//Private constructor to stop instances of this class being created 
	DefaultShaders();
	//Override copy to prevent new instance of this class being made 
	DefaultShaders(const DefaultShaders& that) = delete;
	static std::shared_ptr<Shader> initVF() {
		std::vector<std::string> v;
		v.push_back("Model");
		v.push_back("View");
		v.push_back("Projection");
		return std::make_shared<Shader>(
		           FileUtils::getProgramPath() + "..\\src\\Shaders\\defaultVertShader.vert", 
		           FileUtils::getProgramPath() + "..\\src\\Shaders\\defaultFragShader.frag", 
		           v,true);
	}
	static std::shared_ptr<Shader> initTVF() {
		std::vector<std::string> v;
		v.push_back("Model");
		v.push_back("View");
		v.push_back("Projection");
		v.push_back("Tex");
		return std::make_shared<Shader>(
		           FileUtils::getProgramPath() + "..\\src\\Shaders\\texturedVertShader.vert", 
		           FileUtils::getProgramPath() + "..\\src\\Shaders\\texturedFragShader.frag",
		           v,true);
	}
	static std::shared_ptr<Shader> initLTVF() {
		std::vector<std::string> v;
		v.push_back("Model");
		v.push_back("View");
		v.push_back("Projection");
		v.push_back("LightPosition");
		v.push_back("LightPower");
		v.push_back("Tex");
		v.push_back("LightColour");
		v.push_back("EmissiveColour");
		v.push_back("DiffuseColour");
		v.push_back("SpecularColour");
		v.push_back("Shininess");
		v.push_back("Alpha");
		return std::make_shared<Shader>(
		           FileUtils::getProgramPath() + "..\\src\\Shaders\\litTexturedVertShader.vert", 
		           FileUtils::getProgramPath() + "..\\src\\Shaders\\litTexturedFragShader.frag", 
		           v,true);
	}
};