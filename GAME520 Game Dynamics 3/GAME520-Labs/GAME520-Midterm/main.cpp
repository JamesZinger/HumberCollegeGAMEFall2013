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
	//Make all the pieces to the ship
	SolidSphere *CommandCenter = new SolidSphere(200, 300000, new btVector3(0, 50, -400), "Command Center");
	SolidCylinder *MainBody = new SolidCylinder(100, 400, 103850, new btVector3(0, 0, 0), "Main Body");
	SolidCylinder *WarpDriveL = new SolidCylinder(50, 500, 10000, new btVector3(-50, 200, 200), "Warp Drive L");
	SolidCylinder *WarpDriveR = new SolidCylinder(50, 500, 10000, new btVector3(50, 200, 200), "Warp Drive R");
	
	//Make the ship
	Starship* Enterprise = new Starship(CommandCenter, MainBody, WarpDriveL, WarpDriveR); 

	//Calculate the Local Intertia Tensor
	btMatrix3x3* total = Enterprise->CalculateInertiaTensor();

	cout << "\nStar Ship local inertia matrix\n";
	MatrixPrint(total);

	//Invert the Local Intertia Tensor
	btMatrix3x3* totalinv = &(total->inverse());

	cout << '\n';

	cout << "Star Ship Inverse local inertia matrix\n";
	MatrixPrint(totalinv);


	//Calculate Rotation
	btVector3* rotation = new btVector3(30,0,0); 

	*rotation *= pi / 180;

	btQuaternion q = btQuaternion(sqrtf(2)/2,0,0,sqrtf(2)/2);
	
	float x = q.getX();
	float y = q.getY();
	float z = q.getZ();
	float w = q.getW();

	float xx = 1 - (2 * y * y) - (2 * z * z);
	float xy = (2 * x * y) - (2  * w * z);
	float xz = (2 * x * z) + (2 * w * y);

	float yx = (2 * x * y) + (2 * w * z);
	float yy = 1 - (2 * x * x) - (2 * z * z);
	float yz = (2 * y * z) - (2 * w * x);

	float zx = (2 * x * z) - (2 * w * y);
	float zy = (2 * y * z) + (2 * w * x);
	float zz = 1 - (2 * x * x) - (2 * y * y);

	btMatrix3x3 OrientationMatrix = btMatrix3x3(
			xx, xy, xz,
			yx, yy, yz,
			zx, zy, zz
		);
	
	cout << "\nOrientation Matrix\n";

	MatrixPrint(&OrientationMatrix);


	//Calculate the World Intertia Matrix
	btMatrix3x3* worldInertia = &( (OrientationMatrix * *total) * (OrientationMatrix).transpose());

	cout << "\nWorld Inertia Tensor\n";
	MatrixPrint(worldInertia);

	//Invert the World intertia tensor matrix
	btMatrix3x3* worldInertiaInverse = &(worldInertia->inverse());

	cout << "\nWorld Inertia Tensor Inverse\n";
	MatrixPrint(worldInertiaInverse);

	cout << "\n\n";

	///////////////////////////////////////////////////////////////////////////////////////////////
	///Collision Calculation 

	btVector3 vShip = btVector3(0,0,0);
	btVector3 vAsteroid = btVector3(0,0,20);

	btVector3 wShip  = btVector3(0,0,0);

	btVector3 P = btVector3(0,0,0);

	btVector3 collisionNormal = btVector3(0,0,1);

	btVector3 shipCoM = btVector3(0,-100,50);
	btVector3 asteroidCoM = btVector3(0,0,-10);
	
	SolidSphere asteroid = SolidSphere(10, 50000, new btVector3(0,0, -10), "Asteroid");

	btMatrix3x3 iAsteroid = *(asteroid.CalculateLocalInertia());

	float CoRes = 0.5f;

	//Calculate J

	btMatrix3x3 iShip = *worldInertia;

	btVector3 rShip = P - shipCoM;

	float JDenom1 = collisionNormal.dot((iShip.inverse() * (rShip.cross(collisionNormal))).cross(rShip));

	btVector3 rAsteroid = P - asteroidCoM;

	float JDenom2 = collisionNormal.dot((iAsteroid.inverse() * (rAsteroid.cross(collisionNormal))).cross(rAsteroid));

	float mShip = Enterprise->CalculateMass();

	float Vr = collisionNormal.dot(vShip - vAsteroid);

	float J = (-1 * Vr * (CoRes + 1))/((1/mShip)+(1/asteroid.mMass)+(JDenom1)+(JDenom2));

	cout << "J: " << J << "\n\n";


	//Calculate Final Velocities
	vShip = vShip + ((J*collisionNormal)/(mShip));

	cout << "Ship Final Velocity: [" << vShip.getX() << ", " << vShip.getY() << ", " << vShip.getZ() << "]\n\n"; 

	wShip = wShip + (iShip.inverse() * (rShip.cross(J*collisionNormal)));

	cout << "Ship Final Angular Velocity [" << wShip.getX() << ", " << wShip.getY() << ", " << wShip.getZ() <<"]\n\n";

	///////////////////////////////////////////////////////////////////////////////////////////////

	string s = string();
	cin >> s;


	return 0;
}