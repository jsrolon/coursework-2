// Include GLFW
#include <OpenGLFramework/OpenGLFramework.h>
#include <GLFW/glfw3.h>
#include "OpenGLFramework/OculusPrerequisites.h" 
#include <OpenGLFramework/common/controls.hpp>

GLFWwindow* window;

namespace OpenGLFramework{
void createWindow(int width, int height){
// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		exit(0);
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1); 


	// Open a window and create its OpenGL context
	window = glfwCreateWindow( width, height, "Computer Graphics - Lab Sessions Framework", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(0);
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(0);
	}
	// Add a callback function in case any OpenGL call triggers an error.
	/*if ( GLEW_ARB_debug_output ){
		printf("The OpenGL implementation provides debug output. Let's use it !\n");
		glDebugMessageCallbackARB(&DebugOutputCallback, NULL);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB); 
	}*/

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}


void setupOpenGL(){
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
}

void postRender(){
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool programEnded(){
	return (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&	glfwWindowShouldClose(window) == 0 );
}

void destroyWindow(){
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}


void getViewProjectionMatricesFromMouseKeyboard(glm::mat4& P, glm::mat4& V){
	computeMatricesFromInputs();
	P=getProjectionMatrix();
	V=getViewMatrix();
}

/*void APIENTRY DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam){

	printf("OpenGL Debug Output message : ");

	if(source == GL_DEBUG_SOURCE_API_ARB)					printf("Source : API; ");
	else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)	printf("Source : WINDOW_SYSTEM; ");
	else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)	printf("Source : SHADER_COMPILER; ");
	else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)		printf("Source : THIRD_PARTY; ");
	else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)		printf("Source : APPLICATION; ");
	else if(source == GL_DEBUG_SOURCE_OTHER_ARB)			printf("Source : OTHER; ");

	if(type == GL_DEBUG_TYPE_ERROR_ARB)						printf("Type : ERROR; ");
	else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)	printf("Type : DEPRECATED_BEHAVIOR; ");
	else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)	printf("Type : UNDEFINED_BEHAVIOR; ");
	else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)			printf("Type : PORTABILITY; ");
	else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)			printf("Type : PERFORMANCE; ");
	else if(type == GL_DEBUG_TYPE_OTHER_ARB)				printf("Type : OTHER; ");

	if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)				printf("Severity : HIGH; ");
	else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)		printf("Severity : MEDIUM; ");
	else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)			printf("Severity : LOW; ");

	// You can set a breakpoint here ! Your debugger will stop the program,
	// and the callstack will immediately show you the offending call.
	printf("Message : %s\n", message);
}
*/
};
