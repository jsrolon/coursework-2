// Include GLEW
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
//Base class for OpenGL objects
#include "OpenGLFramework/Content/OpenGLContent.h"
//Derived classes: Each of them render different types of objects with different shading tecniques
#include "OpenGLFramework/Content/UnitPolygonTextured.h"
#include "OpenGLFramework/Content/OpenGLManualObject.h"
#include "OpenGLFramework/Content/ManualObject_SingleColour.h"
#include "OpenGLFramework/Content/ManualObject_PerVertexColour.h"
#include "OpenGLFramework/Content/OpenGLOBJObject.h"
#include "OpenGLFramework/Content/ShadedOBJObjectPointLight.h"
#include "OpenGLFramework/Content/ShadedOBJObjectDirectionalLight.h"
//#include "OpenGLFramework/Content/SceneNode.h"

//Base class for Frama Buffer Objects
#include <OpenGLFramework/FBO/RenderBuffer.h>
#include "OpenGLFramework/FBO/DefaultRenderBufferObject.h"  //"Conventional" Monitor output
#include "OpenGLFramework/FBO/RTTRenderBufferObject.h"		//Render to texture	


namespace OpenGLFramework{
	void createWindow(int width, int height);
	void setupOpenGL();
	void postRender();
	bool programEnded();
	void destroyWindow();
	void getViewProjectionMatricesFromMouseKeyboard(glm::mat4& P, glm::mat4& V);
	//void APIENTRY DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam);
};
