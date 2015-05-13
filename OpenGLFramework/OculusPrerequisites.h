#ifndef _OCULUS_PREREQUISITES
#define _OCULUS_PREREQUISITES
#include <GL/glew.h>
#include <glm/glm.hpp>
class OculusPrerequisites{
public:
	static const int screenWidth=1280, screenHeight=800;
	static const float inwardsFOVAngleInRadians, outwardsFOVAngleInRadians, topFOVAngleInRadians, bottomFOVAngleInRadians;
	static const float leftEyeOffsetMilimeters [],rightEyeOffsetMilimeters [];
	static glm::vec3 leftEyeNDCPointToOculusNDC(glm::vec3 point);
	static glm::vec3 rightEyeNDCPointToOculusNDC(glm::vec3 point);
};

#endif
