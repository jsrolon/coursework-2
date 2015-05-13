#include "OpenGLFramework/OculusDistortion.h"

ScaleAndOffset2D ScaleAndOffset2D::leftScaleAndOffset(glm::vec2(0.64770395f,0.46766952f),glm::vec2(0.37124819f, 0.0f));
ScaleAndOffset2D ScaleAndOffset2D::rightScaleAndOffset(glm::vec2(0.64770395f,0.46766952f),glm::vec2(0.37124819f, 0.0f));//Replace right eye!
float Lens::K[]={1, 1.048902f, 1.1092687f, 1.1904076f, 1.3065739f, 1.4823717f, 1.7718103f, 2.2752879f, 2.9330413f, 3.7320242f, 4.6696792f};
float Lens::InvK[]={1,0.53460693f,0.40869138f, 0.34790039f, 0.31007391f, 0.28346252f, 0.26379392f, 0.24805069f, 0.23471072f, 0.22354127f, 0.21411137f};
float Lens::MaxR=1.1886176f;
float Lens::MaxInvR=5.5504627f;
float Lens::MetersPerTanAngleAtCenter=0.042500000f;
float Lens::DistortionFnInverseApprox(float r){
		float rsq = r * r;
		float scale = 1.0f;
		// A Catmull-Rom spline through the values 1.0, K[1], K[2] ... K[9]
		// evenly spaced in R^2 from 0.0 to MaxR^2
		// K[0] controls the slope at radius=0.0, rather than the actual value.
		const int NumSegments = NumCoefficients;
		//OVR_ASSERT ( NumSegments <= NumCoefficients );
		float scaledRsq = (float)(NumSegments-1) * rsq / ( MaxInvR * MaxInvR );
		scale = EvalCatmullRom10Spline ( InvK, scaledRsq );
		//Intercept, and overrule if needed
		/*if (CustomDistortionInv) //CHECK WHETHER THIS IS USED
		{
			scale = CustomDistortionInv(rsq);
		}*/
		return r * scale;
	};

	float Lens::EvalCatmullRom10Spline ( float const *K, float scaledVal ) 
	{
		int const NumSegments = Lens::NumCoefficients;
		float scaledValFloor = floorf ( scaledVal );
		scaledValFloor = glm::max ( 0.0f, glm::min( (float)(NumSegments-1), scaledValFloor ) );
		float t = scaledVal - scaledValFloor;
		int k = (int)scaledValFloor;

		float p0, p1;
		float m0, m1;
		switch ( k )
		{
		case 0:
			// Curve starts at 1.0 with gradient K[1]-K[0]
			p0 = 1.0f;
			m0 =        ( K[1] - K[0] );    // general case would have been (K[1]-K[-1])/2
			p1 = K[1];
			m1 = 0.5f * ( K[2] - K[0] );
			break;
		default:
			// General case
			p0 = K[k  ];
			m0 = 0.5f * ( K[k+1] - K[k-1] );
			p1 = K[k+1];
			m1 = 0.5f * ( K[k+2] - K[k  ] );
			break;
		case NumSegments-2:
			// Last tangent is just the slope of the last two points.
			p0 = K[NumSegments-2];
			m0 = 0.5f * ( K[NumSegments-1] - K[NumSegments-2] );
			p1 = K[NumSegments-1];
			m1 = K[NumSegments-1] - K[NumSegments-2];
			break;
		case NumSegments-1:
			// Beyond the last segment it's just a straight line
			p0 = K[NumSegments-1];
			m0 = K[NumSegments-1] - K[NumSegments-2];
			p1 = p0 + m0;
			m1 = m0;
			break;
		}

		float omt = 1.0f - t;
		float res  = ( p0 * ( 1.0f + 2.0f *   t ) + m0 *   t ) * omt * omt
				   + ( p1 * ( 1.0f + 2.0f * omt ) - m1 * omt ) *   t *   t;

		return res;
	}

DistortionRenderDesc DistortionRenderDesc::rightEyeDistortion(glm::vec2(-0.15197642f,0), glm::vec2(0.88094115f,1.1011764f));
DistortionRenderDesc DistortionRenderDesc::leftEyeDistortion(glm::vec2(0.15197642f,0), glm::vec2(0.88094115f,1.1011764f));

//IMPLEMENTATIONS:
glm::vec2 TransformRendertargetNDCToTanFovSpace( ScaleAndOffset2D &eyeToSourceNDC,
                                                const glm::vec2 &textureNDC )
{
    glm::vec2 tanEyeAngle = (textureNDC - eyeToSourceNDC.Offset) / eyeToSourceNDC.Scale;
    return tanEyeAngle;
}



glm::vec2 TransformTanFovSpaceToScreenNDC( DistortionRenderDesc &distortion,
                                          glm::vec2 &tanEyeAngle )
{
	float tanEyeAngleRadius = glm::length(tanEyeAngle);
    float tanEyeAngleDistortedRadius = distortion.lens.DistortionFnInverseApprox ( tanEyeAngleRadius );
    glm::vec2 tanEyeAngleDistorted = tanEyeAngle;
    if ( tanEyeAngleRadius > 0.0f )
    {   
        tanEyeAngleDistorted = tanEyeAngle * ( tanEyeAngleDistortedRadius / tanEyeAngleRadius );
    }

    glm::vec2 framebufferNDC;
    framebufferNDC.x = ( tanEyeAngleDistorted.x / distortion.TanEyeAngleScale.x ) + distortion.LensCenter.x;
    framebufferNDC.y = ( tanEyeAngleDistorted.y / distortion.TanEyeAngleScale.y ) + distortion.LensCenter.y;

    return framebufferNDC;
}


ScaleAndOffset2D CreateNDCScaleAndOffsetLeft ( )
{
    ScaleAndOffset2D result;
	result.Scale    = glm::vec2(0.64770395f,0.46766952f);
    result.Offset   = glm::vec2(0.37124819f,0.0f);
    // Hey - why is that Y.Offset negated?
    // It's because a projection matrix transforms from world coords with Y=up,
    // whereas this is from NDC which is Y=down.

    return result;
}

ScaleAndOffset2D CreateNDCScaleAndOffsetRight ( )
{
    ScaleAndOffset2D result;
	result.Scale    = glm::vec2(0.64770395f,0.46766952f);
    result.Offset   = glm::vec2(-0.37124819f,0.0f);
    // Hey - why is that Y.Offset negated?
    // It's because a projection matrix transforms from world coords with Y=up,
    // whereas this is from NDC which is Y=down.

    return result;
}

