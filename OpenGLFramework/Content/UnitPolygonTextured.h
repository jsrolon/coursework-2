/**********************************************************************
NAME: Unit Polygon Textured
DESCRIPTION: Creates a unit polygon sitting on the XY plane with the normal pointing towards the +Z axis.
The plane has a texture applied (described in the constructor) which can be either a file (.bmp or .dds) or externally generated
(other file readers, a Render to Texture, etc.). The polygon is described in local coordinates, but its model matrix can be used 
to move it within the world. Its size can be also be adjusted by modifying the scaling factor in its Model matrix. 
The object contains data structures to contain the vertices and the uv coordinates. 

SHADERS: 
	- MVPVertexShader.vertexshader: Simple vertex shader that uses world coordinates. It descibes several attributes:
		a) vertexPosition_modelspace: As usual, this corresponds to the array of vertex.
		b) vertexUV: Texture mapping coordinates for each vertex (array of uv coordinates)
		c) uniform MVP: this contains the model-view-projection matrix that transforms coordinates in the object's local space
		to clip_space (camera) coordinates. The flag "uniform" means that all the vertex use the same value. We will retrieve a 
		handle for this attribute and update it every frame (we will build the current MVP matrix according to the current 
		position of the camera (V), its frustum (P) and the object location(M)) 
		d) It adds an output variable UV, which is transfered to the fragment shader. Varying denotes that, for the fragments 
		interpolated between frames (the pixles inside of the triangle), the UV value will be interpolated from the UVs of the 
		verted, just as in barycentric interpolation.

	- TexturedFragentShader.fragmentshader: Simple fragment shader that renders each fragment from a texture and UV coordinates.
		a) UV: This is the interpolated UV coordinates of this fragment. That is, the point inside the texture we will get the fragment colour from
		b) myTextureSample: This is the texture we read colours from. It is a uniform, as all fragments get their colour from the same
		texture file. 
	
************************************************************************/

#ifndef _OPENGL_UNIT_POLYGON_TEXTURED
#define _OPENGL_UNIT_POLYGON_TEXTURED
#include "OpenGLFramework/Content/OpenGLContent.h"
#include <string>

class UnitPolygonTextured: public OpenGLContent{
	//Name of the texture to apply to the polygon
	std::string textureFileName;

	//OpenGL Stuff
	GLuint programID; //Program handler containing the vertex shader and pixel shader
	GLuint MatrixID;
	//Handlers for shader's attributes:
	GLuint vertexPosition_modelspaceID; //handler for the 3D coordinates in our vertex shader
	GLuint vertexUVID;					//handler for the UV coordinates of each vertex (for our fragment shader).
	GLuint TextureID ;					//handler for the texture to use (for the fragment shader)
	//Actual OpenGL data structures (data allocated in the graphics card memory which we can access for main memory)
	GLuint Texture;	
	GLuint vertexbuffer;
	GLuint uvbuffer;
public:
	UnitPolygonTextured(std::string textureFileName="uvtemplate.bmp"):textureFileName(textureFileName){;}
	UnitPolygonTextured(GLuint Texture):textureFileName(""), Texture(Texture){;}
	virtual bool loadResourcesToMainMemory();
	virtual bool allocateOpenGLResources();
	virtual bool render(glm::mat4 P, glm::mat4 V);
	virtual bool unallocateAllResources();
};

#endif