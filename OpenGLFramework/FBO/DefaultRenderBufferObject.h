#ifndef _DEFAULT_RENDER_BUFFER
#define _DEFAULT_RENDER_BUFFER
// Include GLEW

#include "OpenGLFramework/FBO/RenderBuffer.h"
class DefaultRenderBufferObject:public RenderBufferObject{
private:	
	DefaultRenderBufferObject(){fboID=0;}
public:
	static DefaultRenderBufferObject& instance();
	void preRender();
	void postRender();
};
#endif