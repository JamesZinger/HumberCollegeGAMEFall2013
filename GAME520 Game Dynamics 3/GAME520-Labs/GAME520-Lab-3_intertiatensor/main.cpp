/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
#pragma once
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics\ConstraintSolver\btGeneric6DofConstraint.h"
#include "LinearMath/btHashMap.h"
#include "Starship.h"
#include <string>
#include <iostream>

#define _USE_MATH_DEFINES true

using namespace std;

void MatrixPrint(btMatrix3x3* matrix)
{
	for (int i = 0; i < 3; i++)
	{
		cout << '[';
		btVector3 row = matrix->getRow(i);
		cout << row.getX() << ", ";
		cout << row.getY() << ", ";
		cout << row.getZ();
		cout << "]\n";

	}
}

const double pi = 3.1415926535897;

int main(int argc,char** argv)
{
	SolidCylinder *Bridge = new SolidCylinder(150, 50, 300000, new btVector3(0, 50, -300), "Bridge");
	SolidCuboid *EngineRoom = new SolidCuboid(50, 100, 150, 400000, new btVector3(0, 0, 0), "Engine");
	SolidCuboid *WarpDrive1 = new SolidCuboid(50, 50, 250, 150000, new btVector3(150, 75, 100), "Warp Drive 1");
	SolidCuboid *WarpDrive2 = new SolidCuboid(50, 50, 250, 150000, new btVector3(-150, 75, 100), "Warp Drive 2");
	Starship* Enterprise = new Starship(Bridge, EngineRoom, WarpDrive1, WarpDrive2); 

	btMatrix3x3* total = Enterprise->CalculateInertiaTensor();

	cout << "\nStar Ship local inertia matrix\n";
	MatrixPrint(total);

	btMatrix3x3* totalinv = &(total->inverse());

	cout << '\n';

	cout << "Star Ship Inverse local inertia matrix\n";
	MatrixPrint(totalinv);

	btVector3* rotation = new btVector3(30,0,0); 

	*rotation *= pi / 180;

	btMatrix3x3* RotX = new btMatrix3x3(1,	0,							0,
										0,	btCos(rotation->getX()),	-btSin(rotation->getX()),
										0,	btSin(rotation->getX()),	btCos(rotation->getX()));

	btMatrix3x3* RotY = new btMatrix3x3(btCos(rotation->getY()),	0,	btSin(rotation->getY()),
												0,					1,				0,
										-btSin(rotation->getY()),	0,	btCos(rotation->getY()));

	btMatrix3x3* RotZ = new btMatrix3x3(btCos(rotation->getZ()), -btSin(rotation->getZ()), 0,
										btSin(rotation->getZ()), btCos(rotation->getZ()), 0,
										0, 0, 1);

	
	btMatrix3x3* OrientationMatrix = &(*RotX * *RotZ * *RotY);
	
	cout << "\nOrientation Matrix\n";

	MatrixPrint(OrientationMatrix);

	btMatrix3x3* worldInertia = &( (*OrientationMatrix * *total) * (OrientationMatrix)->transpose());

	cout << "\nWorld Inertia Tensor\n";
	MatrixPrint(worldInertia);

	cout << "\nWorld Inertia Tensor Inverse\n";
	MatrixPrint(&(worldInertia->inverse()));

	string s = string();
	cin >> s;


	return 0;
}