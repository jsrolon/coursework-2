
/**********************************************************************
NAME: ManualObject_SingleColour
DESCRIPTION: Creates an object rendered using a single colour. The coordinates are described as
a list of triangles in the constructor and are expresed in clip space coordinates. 
Thus, the rendering ignores the MVP matrix and renders in clipspace coordinates. 
SHADERS: 
	- ClipSpaceVertexShader.vertexshader: Simple vertex shader that assumes coordinates are, already in 
	clip space coordinates
	- SingleColourFragentShader.fragmentshader: Simple fragment shader that renders all fragments red.
************************************************************************/


#ifndef _OPENGL_MANUAL_SINGLECOLOUR
#define _OPENGL_MANUAL_SINGLECOLOUR
#include "OpenGLFramework/Content/OpenGLContent.h"
#include <string>




class ManualObject_SingleColour: public OpenGLContent{
	//Manual data (raw data provided by the user)
	int numVertex;
	 GLfloat* g_vertex_buffer_data;
	//OpenGL specific attributes.
	GLuint programID;
	//Attribute handlers
	GLuint vertexPosition_clipspaceID;
	//Data handlers
	GLuint vertexbuffer;
	
public:
	ManualObject_SingleColour(const int numVertex, const GLfloat vertex_buffer_data[]);
	virtual bool loadResourcesToMainMemory();
	virtual bool allocateOpenGLResources();
	virtual bool render(glm::mat4 P, glm::mat4 V);
	virtual bool unallocateAllResources();
};

#endif