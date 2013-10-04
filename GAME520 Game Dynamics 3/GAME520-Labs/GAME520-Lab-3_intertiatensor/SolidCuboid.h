#pragma once
#include "SimpleShape.h"

class SolidCuboid : public SimpleShape
{
public:
	float mWidth;
	float mHeight;
	float mLength;

	SolidCuboid(float Width, float Height, float Length, float Mass, btVector3* CoMOffset, std::string name);
	~SolidCuboid(void);

	virtual btMatrix3x3* CalculateLocalInertia();
};

