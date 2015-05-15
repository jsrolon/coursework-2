#ifndef SHADOW_MAP_BUFFER
#define SHADOW_MAP_BUFFER
// Include GLEW

#include "OpenGLFramework/FBO/RenderBuffer.h"
class ShadowMapBufferObject:public RenderBufferObject{
private:
		GLuint renderedTexture;	
public:
	ShadowMapBufferObject(GLuint width, GLuint height);
	void preRender();
	void postRender();
    void preReading(GLenum TextureUnit);
	inline const GLuint& getRTT(){return renderedTexture;}
};
#endif