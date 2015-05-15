#include "OpenGLFramework/FBO/ShadowMapBufferObject.h"
#include <iostream>

ShadowMapBufferObject::ShadowMapBufferObject(GLuint width, GLuint height){
	// create the framebuffer
	glGenFramebuffers(1, &fboID);
	// The texture we're going to render to
	glGenTextures(1, &renderedTexture);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	// Give an empty image to OpenGL ( the last "0" means "empty" )
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT, width, height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	// Poor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_LINEAR?
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// framebuffer binding
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	// Set "renderedTexture" as the depth attachment
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, renderedTexture, 0);
	// we will be drawing explicity to the depth buffer
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE); 
	// The depth buffer
	if ( !GLEW_ARB_framebuffer_object ){ // OpenGL 2.1 doesn't require this, 3.1+ does
		std::cout << "Your GPU does not provide framebuffer objects. Use a texture instead.\n" << std::endl;
		return;
	}
	/*** Removed because it doesn't appear in tutorial 23

	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers*/

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Buffer status not complete.\n" << std::endl;
		return;
	}

}
void ShadowMapBufferObject::preRender(){
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboID);
	// Dark blue background
	// glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ShadowMapBufferObject::postRender(){
	// sets current fb as the default one
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// This function will be used before the second render pass to bind the shadow map for reading. 
// Note that we bind specifically the texture object, rather than the FBO itself. 
// This function takes the texture unit to which the shadow map will be bound.
void ShadowMapBufferObject::preReading(GLenum TextureUnit) {
	glActiveTexture(TextureUnit);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
}
