#pragma once
#include "btBulletDynamicsCommon.h"

class SimpleShape
{
public:

	float mMass;
	btVector3* CoMOffset;

	virtual btMatrix3x3* CalculateLocalInertia() = 0;
};

