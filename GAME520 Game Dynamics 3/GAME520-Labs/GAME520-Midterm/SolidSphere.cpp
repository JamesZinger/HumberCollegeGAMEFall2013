#include "SolidSphere.h"


SolidSphere::SolidSphere(float Radius, float Mass, btVector3* CoMOffset, std::string name)
{
	mRadius = Radius;
	mMass = Mass;
	this->CoMOffset = CoMOffset;
	mName = name;
}


SolidSphere::~SolidSphere(void)
{
}

btMatrix3x3* SolidSphere::CalculateLocalInertia()
{
	btMatrix3x3* returnmat = new btMatrix3x3();
	returnmat->setIdentity();

	float xx = (2.0f/5.0f) * mMass * mRadius * mRadius;
	float yy = xx;
	float zz = yy;

	returnmat->setValue(xx,00,00,00,yy,00,00,00,zz);

	return returnmat;
}
