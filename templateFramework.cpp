#include <OpenGLFramework/OpenGLFramework.h>

//0. Elements that we use for our OpenGL program
//0.1. A FrameBuffer, to write our scene to (this can be the monitor or a render to texture buffer)
RenderBufferObject* def_fbo;
//0.2. The Projection and view matrices that will control the location of our camera
glm::mat4 P,V;
//0.3. The OpenGL contents that we are going to display
OpenGLContent *objectA;
OpenGLContent *objectB;
//OpenGLContent *objectC; //Object C is deactivated by default, uncomment all the lines to load and display it

//1. Methods required to build our program:
//1.1. Create the contents and place them where appropriate
void createWorldScene();
//1.2. Render our world
void renderWorldScene(RenderBufferObject* rf, glm::mat4 P,glm::mat4 V);
//1.3. Update the world according to: user events (inputs), time, etc...
void updateWorldScene();
//1.4. Deallocate the resources once our program is finihed.
void destroyWorldScene();


//2. Main program
int main( void )
{
	//2.1. Initialize our framework
	OpenGLFramework::createWindow(800,600);
	OpenGLFramework::setupOpenGL();

    // Print OpenGL Version
    printf("OpenGL version: %s\n",glGetString(GL_VERSION));

	//2.2. Create our scene
	createWorldScene();
	//2.3. Main program loop
	do{
		renderWorldScene(def_fbo,P,V); //A. Send commands to trigger rendering
		OpenGLFramework::postRender(); //B. Ask OpenGL to display the final render (as soon as it is ready). We use "Double buffer".
		updateWorldScene();			   //C. React to user's inputs, update your animations...
	} 
	while( OpenGLFramework::programEnded());// D. Check if the ESC key was pressed or the window was closed
	//2.4. Finish the program
	destroyWorldScene();
	OpenGLFramework::destroyWindow();
	return 0;
}


void updateWorldScene(){
	//The framework provides a FPS-like control for the camera (P, V), using mouse and keyboard. 
	//This method call retrieves these matrices and stores them in our global P and V matrices (we will use them to render)
	OpenGLFramework::getViewProjectionMatricesFromMouseKeyboard(P,V);

	//We can also redefine the projection matrix manually, for example:
	//P = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);

	//We can also have a little rotation animation on objectC.
	//glm::mat4 Model=glm::rotate(glm::mat4(), 60.0f, glm::vec3(0,1.0f,0));
	//objectC->setModelMatrix(glm::rotate(glm::mat4(), 0.1f, glm::vec3(0,1.0f,0))*objectC->getModelMatrix());
}

OpenGLContent* createWorldAxis();
void createWorldScene(){
	//1. Create the buffer where our stuff is going to be rendered.
	def_fbo=RenderBufferObject::createDefaultRenderBufferObject();

	//2. Create our objects:
	//2.1. Create our axis
	objectA=createWorldAxis();
	//2.2. Create a simple Triangle with an array of positions for its 3 vertices
	GLfloat aSillyTriangle[]={ -0.5,0,-1,   0.5,0,-1,  0,0.5f,-1};
	objectB=new ManualObject_SingleColour(3, aSillyTriangle);
	//2.3. We can also load an obj file
	//objectC=new ShadedOBJObjectDirectionalLight("suzanne.obj","suzanne.DDS");

	//2.2. load resources from disc into main memory
	objectA->loadResourcesToMainMemory();
	objectB->loadResourcesToMainMemory();

	//2.3. Allocate resources in the graphics card: get handles to attributes, create buffers, copy data accross
	objectA->allocateOpenGLResources();
	objectB->allocateOpenGLResources();

	//2.4. We can also adjust each object's position
	//glm::mat4 Model;
	//Model= glm::translate(Model, glm::vec3(4,0,0));
	//objectC->setModelMatrix(Model);
}

void renderWorldScene(RenderBufferObject* rtt_fbo, glm::mat4 P,glm::mat4 V){
		//1. Prepare the buffer for rendering:
		rtt_fbo->preRender();
		//2. Render all our contents
		objectA->render(P,V);
		objectB->render(P,V);
		//objectC->render(P,V);
		rtt_fbo->postRender();		
}

void destroyWorldScene(){
	objectA->unallocateAllResources();
	objectB->unallocateAllResources();
	//objectC->unallocateAllResources();
	delete objectA;
	delete objectB;
	//delete objectC;
}



///////////////////////////////////////////////////////////////////////////////////////////////
OpenGLContent* createWorldAxis(){
	//Data for our axis (one thin long triangle per axis: one red, one green and one blue)
	static const GLfloat g_vertex_buffer_data[] = { 
		//X axis
		0.0f, -0.01f, 0.0f,
		1.0f,  0.0f,  0.0f,
		0.0f, 0.01f,  0.0f,
		//Y axis
		0.01f, 0.0f, 0.0f,
		0.0f,  1.0f,  0.0f,
		-0.01f, 0.01f,  0.0f,
		//Z axis
		0.01f, 0.0f, 0.0f,
		-0.01f, 0.01f,  0.0f,
		0.0f,  0.0f,  1.0f,
		
	};
	static const GLfloat g_colour_buffer_data[] = { 
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f,0.0f, 1.0f,
		0.0f,0.0f, 1.0f,
		0.0f,0.0f, 1.0f,};

	 return new ManualObject_PerVertexColour(9, g_vertex_buffer_data,g_colour_buffer_data);
}
