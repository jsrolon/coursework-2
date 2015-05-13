#ifndef _RENDER_BUFFER
#define _RENDER_BUFFER
// Include GLEW
#include <GL/glew.h>

class RenderBufferObject{
protected:
	GLuint fboID;
public:
	virtual void preRender()=0;
	virtual void postRender()=0;
	static RenderBufferObject* createDefaultRenderBufferObject();
	static RenderBufferObject* createRTTBufferObject(int width,int height);

};
#endif