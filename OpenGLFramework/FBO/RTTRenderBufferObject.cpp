#include "OpenGLFramework/FBO/RTTRenderBufferObject.h"

RTTRenderBufferObject::RTTRenderBufferObject(GLuint width, GLuint height){
	glGenFramebuffers(1, &fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	// The texture we're going to render to
	glGenTextures(1, &renderedTexture);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	// Give an empty image to OpenGL ( the last "0" means "empty" )
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
	// Poor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//GL_LINEAR?
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// The depth buffer
	if ( !GLEW_ARB_framebuffer_object ){ // OpenGL 2.1 doesn't require this, 3.1+ does
		//printf("Your GPU does not provide framebuffer objects. Use a texture instead.");
		return;
	}
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;

}
void RTTRenderBufferObject::preRender(){
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RTTRenderBufferObject::postRender(){

}