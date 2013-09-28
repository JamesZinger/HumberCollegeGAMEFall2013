#include "Starship.h"
#include <iostream>

Starship::Starship(SolidCylinder* bridge, SolidCuboid* engine, SolidCuboid* warpDrive1, SolidCuboid* warpDrive2)
{
	Bridge = bridge;
	EngineRoom = engine;
	WarpDrive1 = warpDrive1;
	WarpDrive2 = warpDrive2;
}

void printMatrix(btMatrix3x3* matrix)
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << '[';
		btVector3 row = matrix->getRow(i);
		std::cout << row.getX() << ", ";
		std::cout << row.getY() << ", ";
		std::cout << row.getZ();
		std::cout << "]\n";

	}
}


Starship::~Starship(void)
{
	delete Bridge;
	delete EngineRoom;
	delete WarpDrive1;
	delete WarpDrive2;
}

btMatrix3x3* Starship::CalculateInertiaTensor()
{
	btMatrix3x3* inertiaTensor = new btMatrix3x3();
	inertiaTensor->setIdentity();

	SimpleShape* Shapes [4] = {Bridge, EngineRoom, WarpDrive1, WarpDrive2};

	for (int i = 0; i < 4; i++)
	{
		float dx = Shapes[i]->CoMOffset->getX();
		float dy = Shapes[i]->CoMOffset->getY();
		float dz = Shapes[i]->CoMOffset->getZ();
		btMatrix3x3* shapeInertiaTensor = (Shapes[i]->CalculateLocalInertia());
		
		std::cout << '\n';
		printMatrix(shapeInertiaTensor);
		std::cout << '\n';

		float Ixx = shapeInertiaTensor->getRow(0).getX() + (Shapes[i]->mMass * ((dy * dy) + (dz * dz)));
		float Iyy = shapeInertiaTensor->getRow(1).getY() + (Shapes[i]->mMass * ((dx * dx) + (dz * dz)));
		float Izz = shapeInertiaTensor->getRow(2).getZ() + (Shapes[i]->mMass * ((dx * dx) + (dy * dy)));
		float Ixy = -shapeInertiaTensor->getRow(0).getY() + (Shapes[i]->mMass * dx * dy);
		float Ixz = -shapeInertiaTensor->getRow(0).getZ() + (Shapes[i]->mMass * dx * dz);
		float Iyz = -shapeInertiaTensor->getRow(1).getZ() + (Shapes[i]->mMass * dz * dy);

		
		*inertiaTensor = btMatrix3x3(
							 Ixx, 00, 0,
							 0,  Iyy, 0,
							0, 0,  Izz);


	}

	return inertiaTensor;
}
