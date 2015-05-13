#include "OpenGLFramework/FBO/DefaultRenderBufferObject.h"


DefaultRenderBufferObject& DefaultRenderBufferObject::instance(){
	static DefaultRenderBufferObject _instance;
	return _instance;
}

void DefaultRenderBufferObject::preRender(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
}

void DefaultRenderBufferObject::postRender(){

}