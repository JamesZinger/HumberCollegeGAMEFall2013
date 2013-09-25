#include "SolidCylinder.h"
#include <string>
#include <iostream>
using namespace std;

SolidCylinder::SolidCylinder(float Radius, float Height, float Mass, btVector3* CoMOffset)
{
	mRadius = Radius;
	mHeight = Height;
	mMass = Mass;
	mCenterOfMassOffest = CoMOffset;
	
	float xx = (mMass * ((3 * mRadius * mRadius) + (mHeight * mHeight))/12);
	float yy = xx;
	float zz = 0.5f * mMass * mRadius * mRadius;
	float xy = 0;
	float xz = 0;
	float yz = 0;

	float dx = CoMOffset->getX();
	float dy = CoMOffset->getY();
	float dz = CoMOffset->getZ();

	float Ixx = xx + (mMass * ((dy * dy) + (dz * dz)));
	float Iyy = yy + (mMass * ((dx * dx) + (dz * dz)));
	float Izz = zz + (mMass * ((dx * dx) + (dy * dy)));
	float Ixy = 0;
	float Ixz = 0;
	float Iyz = 0;

	mInertiaTensor = new btMatrix3x3(Ixx, -Ixy, -Ixz, -Ixy, Iyy, -Iyz, -Ixz, -Iyz, Izz);
}


SolidCylinder::~SolidCylinder(void)
{
	delete mInertiaTensor;
}
