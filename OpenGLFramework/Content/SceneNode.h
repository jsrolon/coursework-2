#ifndef _SCENE_NODE
#define _SCENE_NODE
#include <OpenGLFramework\Content\OpenGLContent.h>
#include <map>

class SceneNode:public OpenGLContent{
	std::map<unsigned int, OpenGLContent*> children;
public:
	virtual bool loadResourcesToMainMemory(){
		std::map<unsigned int, OpenGLContent*>::iterator it=children.begin();
		for(;it!=children.end();it++)
			it->second->loadResourcesToMainMemory();
	}
	virtual bool allocateOpenGLResources(){
		std::map<unsigned int, OpenGLContent*>::iterator it=children.begin();
		for(;it!=children.end();it++)
			it->second->allocateOpenGLResources();
	}
	virtual bool render(glm::mat4 P, glm::mat4 V){
		std::map<unsigned int, OpenGLContent*>::iterator it=children.begin();
		//We will accumulate our model matrix in V before calling child->render. 
		//This way, children's V matrix contains the transformation matrix that goes from its local coordinates
		// to clipspace coordinates. 
		for(;it!=children.end();it++)
			it->second->render(P,V*this->M);
	}
	virtual bool unallocateAllResources(){
		std::map<unsigned int, OpenGLContent*>::iterator it=children.begin();
		for(;it!=children.end();it++)
			it->second->unallocateAllResources();
	}
	
	/**Add an object to the node.*/
	inline void addChild(OpenGLContent* child){
		children[child->getID()]=child;
	}

	/**Retrieve a child from the node. The child is still stored in the node*/
	inline OpenGLContent* getChild(unsigned int id){
		if(children.find(id)!=children.end())
			return children[id];
		return NULL;
	}

	/**Retrieve a child from the node. The child is removed from the node*/
	inline OpenGLContent* removeChild(unsigned int id){
		std::map<unsigned int, OpenGLContent*>::iterator it=children.find(id);
		if(it!=children.end()){
			OpenGLContent* result=it->second;
			children.erase(it);
			return result;
		}
		return NULL;
	}
	~SceneNode(){
		std::map<unsigned int, OpenGLContent*>::iterator it=children.begin();
		for(;it!=children.end();it++)
			delete(it->second);	
	}
};

#endif