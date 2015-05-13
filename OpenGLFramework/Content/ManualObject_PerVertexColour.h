
/**********************************************************************
NAME: ManualObject_PerVertexColour
DESCRIPTION: Creates an object rendered using a single colour. The coordinates are described as
a list of triangles in the constructor and are expresed in clip space coordinates. 
Thus, the rendering ignores the MVP matrix and renders in clipspace coordinates. 
SHADERS: 
	- ClipSpacePerVertexColour.vertexshader: Simple vertex shader that assumes coordinates are, already in 
	clip space coordinates. DIFFERENCES TO PREVIOUS: a) It uses an aditional input attribute (the array of colours)
	b) It adds an output variable fragmentColor, which is transfered to the fragment shader.
	- PerVertexColourFragentShader.fragmentshader: Simple fragment shader that renders each fragment according to its
	attribute fragmentColor.
************************************************************************/


#ifndef _OPENGL_MANUAL_PERVERTEXCOLOUR
#define _OPENGL_MANUAL_PERVERTEXCOLOUR
#include "OpenGLFramework/Content/OpenGLContent.h"
#include <string>




class ManualObject_PerVertexColour: public OpenGLContent{
	//Manual data (raw data provided by the user)
	int numVertex;
	 GLfloat* g_vertex_buffer_data;
	 GLfloat* g_colour_buffer_data;

	//OpenGL specific attributes.
	GLuint programID;
	GLuint MatrixID;
	//Attribute handlers
	GLuint vertexPosition_clipspaceID;
	GLuint vertexColourID;
	//Data handlers
	GLuint vertexbuffer;
	GLuint colourbuffer;
	
public:
	ManualObject_PerVertexColour(const int numVertex, const GLfloat vertex_buffer_data[],const GLfloat colour_buffer_data[]);
	virtual bool loadResourcesToMainMemory();
	virtual bool allocateOpenGLResources();
	virtual bool render(glm::mat4 P, glm::mat4 V);
	virtual bool unallocateAllResources();
};

#endif
