#pragma once
//ext
#include <GL/glew.h>
#include <GL/freeglut.h>
//std
#include <string>

class Mesh {
public:
	/**
	Mesh constructor of a mesh with no texture
	*/
	Mesh(std::string filename);
	/**
	Mesh constructor of a mesh with a texture
	*/
	Mesh(std::string filename, std::string textureFilename); 
	~Mesh();
	/**
	Buffer of vec3 vertex positions set to layout 0 in GL 
	*/
	GLuint VAO;
	/**
	Buffer of vec3 Normals set to layout 1 in GL 
	*/
	GLuint normBuffer;
	/**
	Buffer of vec2 UV's set to layout 2 in GL 
	*/
	GLuint texBuffer;
	/**
	Buffer containing the Mesh's texture
	*/
	GLuint texture;

	/**
	Number of vertices in the mesh
	*/
	unsigned int numVertices;
private:
	void loadMesh(std::string filename);
};