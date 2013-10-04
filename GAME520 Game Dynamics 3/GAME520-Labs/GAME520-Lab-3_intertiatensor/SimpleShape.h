#pragma once
#include "btBulletDynamicsCommon.h"
#include <string>
class SimpleShape
{
public:
	std::string mName;
	float mMass;
	btVector3* CoMOffset;

	virtual btMatrix3x3* CalculateLocalInertia() = 0;
};

