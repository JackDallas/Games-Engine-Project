#pragma once
//std
#include <string>
#include <memory>
#include <vector>
#include <map>
//ext
#include <GL/glew.h>

struct shaderFile {
	std::string location;
	uint64_t lastTimestamp;
};

class Shader {
public:
	//docs absl path
	/**
	constructor for a new shader, all file paths must be absolute, use getProgramPath() from FileUtils to get the path of the running exe
	@param vertexShaderFile absolute path to the vert shader
	@param fragShaderFile absolute path to the frag shader
	@param uniforms std::vector of std::string's each representing a uniform delared in one of the shader files, the ID's of these are then found and can be accessed using getUniformID()
	@see getUniformID()
	@see getProgramPath()
	*/
	Shader(std::string vertexShaderFile, std::string fragShaderFile, std::vector<std::string> uniforms, bool _liveReload = false);
	~Shader();

	void checkForReload();

	/**
	Buffer of the shader vert frag program
	*/
	GLuint program;
	/**
	*/
	GLuint getUniformID(std::string id);
	bool liveReload;
private:
	/**
	Shader has no Default Constructor, see DefaultShaders for shaders to use
	*/
	Shader();
	void loadVertFrag(std::string vertexShaderFile, std::string fragShaderFile, std::vector<std::string> uniforms = {});
	bool checkShaderCompileStatus(GLuint &shader, std::string shaderName);

	std::map<std::string, GLuint> uniformIDs;

	/*GLuint vertShader;
	GLuint fragShader;
*/
	shaderFile vertFile;
	shaderFile fragFile;
};