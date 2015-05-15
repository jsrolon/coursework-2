#ifndef _OPENGL_MESH
#define _OPENGL_MESH

// Include GLEW
#include <GL/glew.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <OpenGLFramework/common/shader.hpp>
#include <OpenGLFramework/common/texture.hpp>

class OpenGLContent{
	static unsigned int idSeed;
	unsigned int objectID;
protected:
	glm::mat4 M;
public:
	OpenGLContent();
	virtual bool loadResourcesToMainMemory()=0;
	virtual bool allocateOpenGLResources()=0;
	virtual bool render(glm::mat4 P, glm::mat4 V)=0;
	virtual bool unallocateAllResources()=0;
	// virtual void setShader(std::string name);
	inline OpenGLContent& setModelMatrix(glm::mat4 M){
		this->M=M;
		return *this;
	}
	inline glm::mat4 getModelMatrix(){
		return M;
	}
	inline unsigned int getID(){return objectID;}
};

#endif