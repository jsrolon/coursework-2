#include "OpenGLFramework/Content/ManualObject_PerVertexColour.h"
#include <string.h>
#include <stdio.h>

ManualObject_PerVertexColour::ManualObject_PerVertexColour( const int numVertex, const GLfloat vertex_buffer_data[], const GLfloat colour_buffer_data[]):numVertex(numVertex){
	g_vertex_buffer_data=new GLfloat[3*numVertex];
	memcpy(g_vertex_buffer_data,vertex_buffer_data,3*numVertex*sizeof(GLfloat));	
	g_colour_buffer_data=new GLfloat[3*numVertex];
	memcpy(g_colour_buffer_data,colour_buffer_data,3*numVertex*sizeof(GLfloat));	
}

bool ManualObject_PerVertexColour::loadResourcesToMainMemory(){
	return true;
}

bool ManualObject_PerVertexColour::allocateOpenGLResources(){
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "OpenGLFramework/shaders/MVP_PerVertexColor.vertexshader", "OpenGLFramework/shaders/PerVertexColorFragmentShader.fragmentshader" );
	// Get a handle for our buffers
	vertexPosition_clipspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	vertexColourID = glGetAttribLocation(programID, "vertexColor");
	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	//Load raw data in OpenGL buffers...
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, 3*numVertex*sizeof(GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);	

	glGenBuffers(1, &colourbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glBufferData(GL_ARRAY_BUFFER, 3*numVertex*sizeof(GLfloat), g_colour_buffer_data, GL_STATIC_DRAW);	
	return true;

}
bool ManualObject_PerVertexColour::render(glm::mat4 P, glm::mat4 V){
	// Use our shader
	glUseProgram(programID);
	// Se the MVP matrix
	glm::mat4 MVP        = P * V * M;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
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
	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(vertexColourID);
	glBindBuffer(GL_ARRAY_BUFFER, colourbuffer);
	glVertexAttribPointer(
		vertexColourID,               // The attribute we want to configure
		3,                           // size
		GL_FLOAT,                    // type
		GL_FALSE,                    // normalized?
		0,                           // stride
		(void*)0                     // array buffer offset
	);
	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, numVertex); 
	glDisableVertexAttribArray(vertexPosition_clipspaceID);
	glDisableVertexAttribArray(vertexColourID);
	return true;
}

bool ManualObject_PerVertexColour::unallocateAllResources(){
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colourbuffer);
	glDeleteProgram(programID);
	return true;


}
