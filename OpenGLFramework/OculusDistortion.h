#ifndef _OCULUS_DISTORTION
#define _OCULUS_DISTORTION

#include "GL/glew.h"
// Include GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
//INTERFACE:
class ScaleAndOffset2D{
public:
	glm::vec2 Scale;
	glm::vec2 Offset;
	ScaleAndOffset2D(){;}
	ScaleAndOffset2D(glm::vec2 Scale, glm::vec2 Offset ):Scale(Scale.x,Scale.y), Offset(Offset.x,Offset.y){}
	static ScaleAndOffset2D leftScaleAndOffset, rightScaleAndOffset;
} ;

ScaleAndOffset2D CreateNDCScaleAndOffsetLeft();
ScaleAndOffset2D CreateNDCScaleAndOffsetRight();


class Lens{
private:
	float EvalCatmullRom10Spline ( float const *K, float scaledVal );


public:
	static const int NumCoefficients=11;
	static float               K[];
    static float               MaxR;       // The highest R you're going to query for - the curve is unpredictable beyond it.
	static float               MetersPerTanAngleAtCenter;
    static float               InvK[];
    static float               MaxInvR;
	float DistortionFnInverseApprox(float r);

};


class DistortionRenderDesc {
public:
	Lens lens;
	glm::vec2 TanEyeAngleScale,LensCenter;
	DistortionRenderDesc (glm::vec2 LensCenter, glm::vec2 TanEyeAngleScale):LensCenter(LensCenter),TanEyeAngleScale(TanEyeAngleScale){;}
	static DistortionRenderDesc leftEyeDistortion, rightEyeDistortion;
};



glm::vec2 TransformRendertargetNDCToTanFovSpace( ScaleAndOffset2D &eyeToSourceNDC, const glm::vec2 &textureNDC );

glm::vec2 TransformTanFovSpaceToScreenNDC( DistortionRenderDesc &distortion, glm::vec2 &tanEyeAngle);

#endif
