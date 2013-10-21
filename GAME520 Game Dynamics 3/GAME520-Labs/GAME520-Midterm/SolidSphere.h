#pragma once
#include "simpleshape.h"
class SolidSphere :
	public SimpleShape
{
public:
	float mRadius;
	SolidSphere(float Radius, float Mass, btVector3* CoMOffset, std::string name);
	~SolidSphere(void);

	virtual btMatrix3x3* CalculateLocalInertia();
};

