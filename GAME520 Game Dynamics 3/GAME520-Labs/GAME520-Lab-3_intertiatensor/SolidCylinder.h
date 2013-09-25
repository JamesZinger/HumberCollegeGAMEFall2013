#pragma once

#include "btBulletDynamicsCommon.h"
class SolidCylinder
{
public:
	float mRadius;
	float mHeight;
	float mMass;
	btVector3* mCenterOfMassOffest;
	btMatrix3x3* mInertiaTensor;


	SolidCylinder(float Radius, float Height, float Mass, btVector3* CoMOffset);
	~SolidCylinder(void);
};

