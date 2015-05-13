#include "OpenGLFramework/OculusPrerequisites.h"
#include "OpenGLFramework/OculusDistortion.h"

const float OculusPrerequisites::inwardsFOVAngleInRadians=0.771f, OculusPrerequisites::outwardsFOVAngleInRadians=1.129f, OculusPrerequisites::topFOVAngleInRadians=1.133f, OculusPrerequisites::bottomFOVAngleInRadians=1.133f;
const float OculusPrerequisites::leftEyeOffsetMilimeters []={-35,60,-40},OculusPrerequisites::rightEyeOffsetMilimeters []={-35,60,-40};

//THESE TWO FUNCTIONS WILL DO THE SIDE BY SIDE BIT( NO DISTORTION CORRECITON)
/*glm::vec3 OculusPrerequisites::leftEyeNDCPointToOculusNDC(glm::vec3 point){
	glm::vec3 result(point.x/2, point.y, -1);
	return result;
}
static glm::vec3 rightEyeNDCPointToOculusNDC(glm::vec3 point){
	glm::vec3 result(1+point.x/2, point.y, -1);
	return result;
}*/

glm::vec3 OculusPrerequisites::leftEyeNDCPointToOculusNDC(glm::vec3 point){
	ScaleAndOffset2D scaleOffset=CreateNDCScaleAndOffsetLeft();
	glm::vec2 tanFovSpace=TransformRendertargetNDCToTanFovSpace(scaleOffset,glm::vec2(point.x,point.y));
	glm::vec2 result2D=TransformTanFovSpaceToScreenNDC(DistortionRenderDesc::leftEyeDistortion,tanFovSpace);
	result2D.x = 0.5f * result2D.x - 0.5f ;
    //result.ScreenPosNDC.y = -screenNDC.y;

	return glm::vec3(result2D.x,result2D.y,1);
}
glm::vec3 OculusPrerequisites::rightEyeNDCPointToOculusNDC(glm::vec3 point){
	ScaleAndOffset2D scaleOffset=CreateNDCScaleAndOffsetRight();
	glm::vec2 tanFovSpace=TransformRendertargetNDCToTanFovSpace(scaleOffset,glm::vec2(point.x,point.y));
	glm::vec2 result2D=TransformTanFovSpaceToScreenNDC(DistortionRenderDesc::rightEyeDistortion,tanFovSpace);
	result2D.x = 0.5f * result2D.x + 0.5f ;
	return glm::vec3(result2D.x,result2D.y,1);
}