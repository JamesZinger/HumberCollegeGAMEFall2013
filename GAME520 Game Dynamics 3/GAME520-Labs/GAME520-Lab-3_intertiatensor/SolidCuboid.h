#pragma once
#include "btBulletDynamicsCommon.h"

class SolidCuboid
{
public:
	float mWidth;
	float mHeight;
	float mDepth;
	float mMass;
	btVector3* mCenterOfMassOffest;
	btMatrix3x3* mInertiaTensor;

	SolidCuboid(float Width, float Height, float Depth, float Mass, btVector3* CoMOffset);
	~SolidCuboid(void);
};

