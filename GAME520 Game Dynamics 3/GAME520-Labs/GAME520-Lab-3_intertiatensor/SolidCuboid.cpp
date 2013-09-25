#include "SolidCuboid.h"


SolidCuboid::SolidCuboid(float Width, float Height, float Depth, float Mass, btVector3* CoMOffset)
{
	mWidth = Width;
	mHeight = Height;
	mDepth  = Depth;
	mMass = Mass;
	float xx = (1/12) * mMass * ((mHeight * mHeight) + (mDepth * mDepth));
	float yy = (1/12) * mMass * ((mWidth * mWidth) + (mDepth * mDepth));
	float zz = (1/12) * mMass * ((mWidth * mWidth) + (mHeight * mHeight));
	
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


SolidCuboid::~SolidCuboid(void)
{
	delete mInertiaTensor;
}
