#include "OpenGLFramework/Content/ManualObject_SingleColour.h"
#include <stdio.h>
#include <string.h>

ManualObject_SingleColour::ManualObject_SingleColour( const int numVertex, const GLfloat vertex_buffer_data[]):numVertex(numVertex){
	g_vertex_buffer_data=new GLfloat[3*numVertex];
	memcpy(g_vertex_buffer_data,vertex_buffer_data,3*numVertex*sizeof(GLfloat));	
	
}

bool ManualObject_SingleColour::loadResourcesToMainMemory(){
	return true;
}

bool ManualObject_SingleColour::allocateOpenGLResources(){
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "OpenGLFramework/shaders/ClipSpaceVertexShader.vertexshader", "OpenGLFramework/shaders/SingleColourFragmentShader.fragmentshader" );
	// Get a handle for our buffers
	vertexPosition_clipspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	//Load raw data in OpenGL buffers...
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, 3*numVertex*sizeof(GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);	
	return true;

}
bool ManualObject_SingleColour::render(glm::mat4 P, glm::mat4 V){
	// Use our shader
	glUseProgram(programID);
	// We do not use MVP, this object works in clipspace coords...
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(vertexPosition_clipspaceID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		vertexPosition_clipspaceID,  // The attribute we want to configure
		3,                            // size
		GL_FLOAT,                     // type
		GL_FALSE,                     // normalized?
		0,                            // stride
		(void*)0                      // array buffer offset
	);
	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, numVertex); 
	glDisableVertexAttribArray(vertexPosition_clipspaceID);
	return true;
}

bool ManualObject_SingleColour::unallocateAllResources(){
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	return true;


}
