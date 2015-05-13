#ifndef _RTT_RENDER_BUFFER
#define _RTT_RENDER_BUFFER
// Include GLEW

#include "OpenGLFramework/FBO/RenderBuffer.h"
class RTTRenderBufferObject:public RenderBufferObject{
private:
		GLuint renderedTexture;	
public:
	RTTRenderBufferObject(GLuint width, GLuint height);
	void preRender();
	void postRender();
	inline const GLuint& getRTT(){return renderedTexture;}
};
#endif