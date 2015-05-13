PROG=lab

EXTERNAL_DIR=./OpenGLFramework/external

GLEW_DIR=$(EXTERNAL_DIR)/glew-1.12.0
GLEW_STATIC=$(GLEW_DIR)/lib/libGLEW.a

GLFW_DIR=$(EXTERNAL_DIR)/glfw-3.1
GLFW_BUILD_DIR=$(GLFW_DIR)/build
GLFW_STATIC=$(GLFW_BUILD_DIR)/src/libglfw3.a

# This is very messy but it reflects the inconsistent treatment of header files
# in the code as provided.
INCLUDE=-I. -I$(GLEW_DIR)/include -I$(GLFW_DIR)/include -I$(GLFW_DIR)/include/GLFW -I$(EXTERNAL_DIR)/include

CXX=g++
CPPFLAGS=-Wall -Wextra $(INCLUDE)
LDLIBS=$(GLEW_STATIC) $(GLFW_STATIC) -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
# Switch the two versions of LDLIBs if you are using Linux, these *should* work
#LDLIBS=$(GLEW_STATIC) $(GLFW_STATIC) -lGL -lX11 -lXrandr -lXi -lXxf86vm -lXinerama -lXcursor

SRCS=templateFramework.cpp $(wildcard OpenGLFramework/*.cpp) $(wildcard OpenGLFramework/common/*.cpp) $(wildcard OpenGLFramework/Content/*.cpp) $(wildcard OpenGLFramework/FBO/*.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

$(PROG): $(OBJS) $(GLEW_STATIC) $(GLFW_STATIC)
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS) $(LDLIBS)

# Targets related to GLEW
.PHONY:glew
glew: $(GLEW_STATIC)

$(GLEW_STATIC):
	cd $(GLEW_DIR) && make

.PHONY: clean_glew
clean_glew:
	cd $(GLEW_DIR) && make clean

# Targets related to GLFW
.PHONY: glfw
glfw: $(GLFW_STATIC)

$(GLFW_STATIC):
	mkdir -p $(GLFW_BUILD_DIR) && cd $(GLFW_BUILD_DIR) && cmake ../ && make

# Clean-up targets
.PHONY: clean_glfw
clean_glfw:
	rm -rf $(GLFW_BUILD_DIR) && cd $(GLFW_DIR); if [ -f Makefile ] ; then make clean ; fi

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: clean_all
clean_all: clean clean_glew clean_glfw
