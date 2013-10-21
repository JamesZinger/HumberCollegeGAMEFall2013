#pragma once
#include "SolidCuboid.h"
#include "SolidCylinder.h"
#include "SolidSphere.h"
class Starship
{
public:

	SolidSphere* CommandCenter;
	SolidCylinder* MainBody;
	SolidCylinder* WarpDriveL;
	SolidCylinder* WarpDriveR;

	Starship(SolidSphere* CommandCenter, SolidCylinder* MainBody, SolidCylinder* WarpDriveL, SolidCylinder* WarpDriveR);
	~Starship(void);

	btMatrix3x3* CalculateInertiaTensor();

	float CalculateMass(void);
};

