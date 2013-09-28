#include "SolidCuboid.h"
#include <iostream>
using namespace std;
SolidCuboid::SolidCuboid(float Width, float Height, float Length, float Mass, btVector3* comOffset)
{
	mWidth = Width;
	mHeight = Height;
	mLength  = Length;
	mMass = Mass;
	CoMOffset = comOffset;
	
}


SolidCuboid::~SolidCuboid(void)
{
}

btMatrix3x3* SolidCuboid::CalculateLocalInertia()
{
	btMatrix3x3* returnmat = new btMatrix3x3();
	returnmat->setIdentity();

	float xx = (0.08333333333333333333333333333333) * mMass * ((mHeight * mHeight) + (mLength * mLength));
	float yy = (0.08333333333333333333333333333333) * mMass * ((mWidth * mWidth) + (mLength * mLength));
	float zz = (0.08333333333333333333333333333333) * mMass * ((mWidth * mWidth) + (mHeight * mHeight));

	cout << "Mass: " << mMass << '\n';
	cout << "Height: " << mHeight << '\n';
	cout << "Width: " << mWidth << '\n';
	cout << "Length: " << mLength << '\n';
	cout << "xx: " << xx << '\n';
	cout << "yy: " << yy << '\n';
	cout << "zz: " << zz << '\n';

	returnmat->setValue(xx, 00, 00, 00, yy, 00, 00, 00, zz);

	return returnmat;
}

