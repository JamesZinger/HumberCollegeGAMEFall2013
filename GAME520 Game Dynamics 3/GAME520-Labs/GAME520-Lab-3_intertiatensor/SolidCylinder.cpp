#include "SolidCylinder.h"
#include <string>
#include <iostream>
using namespace std;

SolidCylinder::SolidCylinder(float Radius, float Height, float Mass, btVector3* comOffset, std::string name)
{
	mRadius = Radius;
	mHeight = Height;
	mMass = Mass;
	CoMOffset = comOffset;
	mName = name;
}


SolidCylinder::~SolidCylinder(void)
{
}

btMatrix3x3* SolidCylinder::CalculateLocalInertia()
{
	btMatrix3x3* returnmat = new btMatrix3x3();
	returnmat->setIdentity();

	float xx = (mMass * ((3 * mRadius * mRadius) + (mHeight * mHeight))/12);
	float zz = xx;
	float yy = 0.5f * mMass * mRadius * mRadius;


	returnmat->setValue(xx, 00, 00, 00, yy, 00, 00, 00, zz);

	return returnmat;
}
