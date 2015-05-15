/**********************************************************************
NAME: SimpleShadowMapped.h
DESCRIPTION: Loads an OBJ model from a file (vertices, UVs, normals) and renders it with a texture applied. 
Diffuse ilumination, ambient light and reflective lights are considered, using a point light as a reference. 
The texture can be either a file (.bmp or .dds) or externally generated (other file readers, a Render to Texture, etc.).
The object is described in local coordinates, but its model matrix can be used to move it within the world. 
The lighting and the shaders are well explained in: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/
Shaders can be found in: shaders/PointLightShading.vertexshader and shaders/PointLightShading.fragmentshader 
**************************************************************************************************************/

#ifndef SIMPLE_SHADOW_MAPPED
#define SIMPLE_SHADOW_MAPPED
#include "OpenGLFramework/Content/OpenGLContent.h"
// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>
#include <vector>
#include <string>

class SimpleShadowMapped: public OpenGLContent{
	//Config parameters
	std::string textureName, model;
	//std::string vertexShader, fragmentShader; //This is fixed, as the arguments (see "vertexPosition_modelspace" "myTextureSampler" init) are specific for the shaders, changing programs makes no sense...
	//Raw data (as read from a file, etc...)
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; 
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	glm::vec3 lightPos;
	//OpenGL handlers
	GLuint programID;
	GLuint MatrixID, ViewMatrixID, ModelMatrixID; //We also need the intermediate matrixes, not only the final MVP
	GLuint vertexPosition_modelspaceID;
	GLuint vertexUVID;
	GLuint vertexNormal_modelspaceID;
	GLuint vertexTangent_modelspaceID;
	GLuint vertexBitangent_modelspaceID;
	GLuint lightID;							//Position of the light.
	GLuint TextureID;
	//Actual OpenGL data structures
	GLuint Texture ;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint tangentbuffer;
	GLuint bitangentbuffer;
	
public:
	SimpleShadowMapped( std::string model,std::string texture, glm::vec3 lightPos = glm::vec3(4,4,4))
		: TextureID (-1), textureName(texture), model(model), lightPos(lightPos)
	{;}

	virtual bool loadResourcesToMainMemory();
	virtual bool allocateOpenGLResources();	
	virtual bool render(glm::mat4 P, glm::mat4 V);
	virtual bool unallocateAllResources();
};

#endif