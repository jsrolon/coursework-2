#include "OpenGLFramework/Content/UnitPolygonTextured.h"

bool UnitPolygonTextured::loadResourcesToMainMemory(){return true;}

bool UnitPolygonTextured::allocateOpenGLResources(){
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "OpenGLFramework/shaders/MVPVertexShader.vertexshader", "OpenGLFramework/shaders/TextureFragmentShader.fragmentshader" );
	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	// Get a handle for our buffers
	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	vertexUVID = glGetAttribLocation(programID, "vertexUV");
	/* Load the texture. These methods actually load into main memory, but they also allocate
	   the texture in the graphics card already, returning a handler for the texture.
	   We support two formats, one for BMP and ne for DDS.	*/
	if(		textureFileName.substr(textureFileName.find_last_of(".") + 1) == "bmp" 
		  ||textureFileName.substr(textureFileName.find_last_of(".") + 1) == "BMP")
				Texture = loadBMP_custom(textureFileName.c_str());  
	else if(textureFileName.substr(textureFileName.find_last_of(".") + 1) == "dds" 
		  ||textureFileName.substr(textureFileName.find_last_of(".") + 1) == "DDS")
				Texture = loadDDS(textureFileName.c_str());
	else if(textureFileName=="")
		;//The user provided the texture himself/herself. No need to do anything more
	else //The user did give a name, but it does not have the correct extension...
		return false;
	// Get a handle for our "myTextureSampler" uniform
	TextureID  = glGetUniformLocation(programID, "myTextureSampler");
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[] = { 
		-0.50f, 0.50f, 0.0f,
		-0.50f,-0.50f, 0.0f,
		 0.50f,-0.50f, 0.0f,
		
		 0.50f, 0.50f, 0.0f,
		-0.50f, 0.50f, 0.0f,
		 0.50f,-0.50f, 0.0f
	};

	// Two UV coordinatesfor each vertex.
	static const GLfloat g_uv_buffer_data[] = { 
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		1,1
	};
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	
	return true;

}
bool UnitPolygonTextured::render(glm::mat4 P, glm::mat4 V){
	// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glm::mat4 MVP        = P * V * M; 
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0 (our shader only uses one texture...)
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0. That is, set our handler to use the texture we allocated.
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			vertexPosition_modelspaceID,  // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(vertexUVID);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			vertexUVID,                   // The attribute we want to configure
			2,                            // size : U+V => 2
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// Draw the triangles !
		glDrawArrays(GL_TRIANGLES, 0, 2*3); // 12*3 indices starting at 0 -> 12 triangles
		glDisableVertexAttribArray(vertexPosition_modelspaceID);
		glDisableVertexAttribArray(vertexUVID);		
	return true;
}

bool UnitPolygonTextured::unallocateAllResources(){
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	return true;
}
