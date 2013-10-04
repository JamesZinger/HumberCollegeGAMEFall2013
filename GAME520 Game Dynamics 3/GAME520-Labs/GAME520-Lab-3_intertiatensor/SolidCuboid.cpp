#include "SolidCuboid.h"
#include <iostream>
using namespace std;
SolidCuboid::SolidCuboid(float Width, float Height, float Length, float Mass, btVector3* comOffset, std::string name)
{
	mWidth = Width;
	mHeight = Height;
	mLength  = Length;
	mMass = Mass;
	CoMOffset = comOffset;
	mName = name;
}


SolidCuboid::~SolidCuboid(void)
{
}

btMatrix3x3* SolidCuboid::CalculateLocalInertia()
{
	btMatrix3x3* returnmat = new btMatrix3x3();
	returnmat->setIdentity();

	float xx = (1.0f/12.0f) * mMass * ((mHeight * mHeight) + (mLength * mLength));
	float yy = (1.0f/12.0f) * mMass * ((mWidth * mWidth) + (mLength * mLength));
	float zz = (1.0f/12.0f) * mMass * ((mWidth * mWidth) + (mHeight * mHeight));

	returnmat->setValue(xx, 00, 00, 00, yy, 00, 00, 00, zz);

	return returnmat;
}

