#pragma once
#include "SimpleShape.h"

class SolidCuboid : public SimpleShape
{
public:
	float mWidth;
	float mHeight;
	float mLength;

	SolidCuboid(float Width, float Height, float Depth, float Mass, btVector3* CoMOffset);
	~SolidCuboid(void);

	virtual btMatrix3x3* CalculateLocalInertia();
};

