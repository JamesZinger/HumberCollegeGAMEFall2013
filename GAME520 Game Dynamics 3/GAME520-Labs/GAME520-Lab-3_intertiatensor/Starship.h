#pragma once
#include "SolidCuboid.h"
#include "SolidCylinder.h"

class Starship
{
public:

	SolidCylinder* Bridge;
	SolidCuboid* EngineRoom;
	SolidCuboid* WarpDrive1;
	SolidCuboid* WarpDrive2;

	Starship(SolidCylinder* Bridge, SolidCuboid* EngineRoom, SolidCuboid* WarpDrive1, SolidCuboid* WarpDrive2);
	~Starship(void);

	btMatrix3x3* CalculateInertiaTensor();
};

