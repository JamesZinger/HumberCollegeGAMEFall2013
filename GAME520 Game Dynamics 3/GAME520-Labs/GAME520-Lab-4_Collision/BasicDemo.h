/*
29/Sep/2010 Umer Noor
Edited original BasicDemo file
Starting point for using Bullet's debugDrawer.
For now we are not using Bullet for physics.
*/

/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
#ifndef BASIC_DEMO_H
#define BASIC_DEMO_H


#include "GlutDemoApplication.h"
#include "LinearMath/btAlignedObjectArray.h"

class btBroadphaseInterface;
class btCollisionShape;
class btOverlappingPairCache;
class btCollisionDispatcher;
class btConstraintSolver;
struct btCollisionAlgorithmCreateFunc;
class btDefaultCollisionConfiguration;

///BasicDemo is good starting point for learning the code base and porting.
class BasicDemo : public GlutDemoApplication
{
	btAlignedObjectArray<btRigidBody*>	m_rigidBody;

	//keep the collision shapes, for deletion/cleanup
	btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

	btBroadphaseInterface*	m_broadphase;

	btCollisionDispatcher*	m_dispatcher;

	btConstraintSolver*	m_solver;

	btDefaultCollisionConfiguration* m_collisionConfiguration;

	btQuaternion m_qOrientation[2];

	btVector3 m_vAngularVelocity[2];

	btVector3 m_vVelocity[2];

	btVector3 m_vPosition[2];

	btVector3 m_vAcceleration[2];

	btVector3 m_vTorque[2];

	btRigidBody* m_rigidBodys[2];

	btMatrix3x3 m_sphereInetiaTensor[2];

	public:

	BasicDemo()
	{
	}
	virtual ~BasicDemo()
	{
		exitPhysics();
	}
	void	initPhysics();

	void	exitPhysics();

	virtual void clientMoveAndDisplay();

	virtual void displayCallback();
	
	static DemoApplication* Create()
	{
		BasicDemo* demo = new BasicDemo;
		demo->myinit();
		demo->initPhysics();
		return demo;
	}

	
};

#endif //BASIC_DEMO_H

