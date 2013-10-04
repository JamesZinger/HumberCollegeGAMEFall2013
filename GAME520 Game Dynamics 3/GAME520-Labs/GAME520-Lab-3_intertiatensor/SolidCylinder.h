#pragma once

#include "SimpleShape.h"
class SolidCylinder : public SimpleShape
{
public:
	float mRadius;
	float mHeight;


	SolidCylinder(float Radius, float Height, float Mass, btVector3* CoMOffset, std::string name);
	~SolidCylinder(void);

	virtual btMatrix3x3* CalculateLocalInertia();
};

