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
#ifndef VEHICLE_DEMO_H
#define VEHICLE_DEMO_H

class btVehicleTuning;
struct btVehicleRaycaster;
class btCollisionShape;
#include <string>
#include <sstream>
#include <iostream>
#include "BulletDynamics/Vehicle/btRaycastVehicle.h"
#include "btBulletCollisionCommon.h"
#include "GlutDemoApplication.h"

struct ContactSensorCallback : public btCollisionWorld::ContactResultCallback
{

	//! Constructor, pass whatever context you want to have available when processing contacts
	/*! You may also want to set m_collisionFilterGroup and m_collisionFilterMask
	*  (supplied by the superclass) for needsCollision() */
	ContactSensorCallback( btRigidBody& tgtBody, int context /*, ... */ )
	: btCollisionWorld::ContactResultCallback( ), body( tgtBody ), ctxt( context ) {}

	btRigidBody& body; //!< The body the sensor is monitoring
	int ctxt; //!< External information for contact processing

	//! If you don't want to consider collisions where the bodies are joined by a constraint, override needsCollision:
	/*! However, if you use a btCollisionObject for #body instead of a btRigidBody,
	*  then this is unnecessary—checkCollideWithOverride isn't available */
	virtual bool needsCollision( btBroadphaseProxy* proxy ) const
	{
		// superclass will check m_collisionFilterGroup and m_collisionFilterMask
		if ( !btCollisionWorld::ContactResultCallback::needsCollision( proxy ) )
			return false;
		// if passed filters, may also want to avoid contacts between constraints
		return body.checkCollideWithOverride( static_cast<btCollisionObject*>( proxy->m_clientObject ) );
	}

	//! Called with each contact for your own processing (e.g. test if contacts fall in within sensor parameters)
	virtual btScalar addSingleResult( btManifoldPoint& cp,
									  const btCollisionObjectWrapper* colObj0, int partId0, int index0,
									  const btCollisionObjectWrapper* colObj1, int partId1, int index1 )
	{
		btVector3 pt; // will be set to point of collision relative to body
		if ( colObj0->m_collisionObject == &body )
		{
			pt = cp.m_localPointA;
		}
		else
		{
			//assert( colObj1->m_collisionObject == &body && "body does not match either collision object" );
			pt = cp.m_localPointB;
		}
		ctxt = 1;
		// do stuff with the collision point
		return 1; // not actually sure if return value is used for anything...?
	}
};

///VehicleDemo shows how to setup and use the built-in raycast vehicle
class VehicleDemo : public GlutDemoApplication
{
public:
	
	btRigidBody* m_carChassis;

	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

	class btBroadphaseInterface*	m_overlappingPairCache;

	class btCollisionDispatcher*	m_dispatcher;

	class btConstraintSolver*	m_constraintSolver;

	class btDefaultCollisionConfiguration* m_collisionConfiguration;

	class btTriangleIndexVertexArray*	m_indexVertexArrays;

	btVector3*	m_vertices;


	btRaycastVehicle::btVehicleTuning	m_tuning;
	btVehicleRaycaster*	m_vehicleRayCaster;
	btRaycastVehicle*	m_vehicle;
	btCollisionShape*	m_wheelShape;

	float		m_cameraHeight;

	float	m_minCameraDistance;
	float	m_maxCameraDistance;


	VehicleDemo();

	virtual ~VehicleDemo();

	virtual void clientMoveAndDisplay();

	virtual void	clientResetScene();

	virtual void displayCallback();

	///a very basic camera following the vehicle
	virtual void updateCamera();

	virtual void specialKeyboard( int key, int x, int y );

	virtual void specialKeyboardUp( int key, int x, int y );

	void renderme();

	void initPhysics();

	void setupPins( const btVector3* origin, const float xdiff, const float zdiff, const float mass, const unsigned int depthOfCone );

	static DemoApplication* Create()
	{
		VehicleDemo* demo = new VehicleDemo();
		demo->myinit();
		demo->initPhysics();
		return demo;
	}
};

#endif //VEHICLE_DEMO_H


