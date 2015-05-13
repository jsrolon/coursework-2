#include <OpenGLFramework/FBO/RenderBuffer.h>
#include <OpenGLFramework/FBO/DefaultRenderBufferObject.h>
#include <OpenGLFramework/FBO/RTTRenderBufferObject.h>

RenderBufferObject* RenderBufferObject::createDefaultRenderBufferObject(){
	return	&DefaultRenderBufferObject::instance();
}
RenderBufferObject* RenderBufferObjectcreateRTTBufferObject(int width,int height){
	return new RTTRenderBufferObject(width, height);
}
