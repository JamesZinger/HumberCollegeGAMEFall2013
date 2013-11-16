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


#define LENGTH_OF_CONE 10

//maximum number of objects (and allow user to shoot additional boxes)
#define MAX_PROXIES (ARRAY_SIZE_X*ARRAY_SIZE_Y*ARRAY_SIZE_Z + 1024)

///scaling of the objects (0.1 = 20 centimeter boxes )
#define SCALING 1.
#define START_POS_X -5
#define START_POS_Y -5
#define START_POS_Z -3

#include "BasicDemo.h"
#include "GlutStuff.h"
///btBulletDynamicsCommon.h is the main Bullet include file, contains most common include files.
#include "btBulletDynamicsCommon.h"

#include <stdio.h> //printf debugging
#include "GLDebugDrawer.h"

static GLDebugDrawer gDebugDraw;



void BasicDemo::clientMoveAndDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	//simple dynamics world doesn't handle fixed-time-stepping
	float ms = getDeltaTimeMicroseconds();
	
	///step the simulation
	if (m_dynamicsWorld)
	{
		
		//m_cameraTargetPosition = m_sphere->getWorldTransform().getOrigin();
		//updateCamera();
		m_dynamicsWorld->stepSimulation(ms / 1000000.f);
		//optional but useful: debug drawing
		m_dynamicsWorld->debugDrawWorld();
	}
		
	renderme(); 

	glFlush();

	swapBuffers();

}



void BasicDemo::displayCallback(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	renderme();

	//optional but useful: debug drawing to detect problems
	if (m_dynamicsWorld)
	{
		
		m_dynamicsWorld->debugDrawWorld();
		
	}

	glFlush();
	swapBuffers();
}





void	BasicDemo::initPhysics()
{

	m_cameraDistance = 60;
	

	setTexturing(true);
	setShadows(true);

	setCameraDistance(btScalar(SCALING*50.));

	///collision configuration contains default setup for memory, collision setup
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	//m_collisionConfiguration->setConvexConvexMultipointIterations();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new	btCollisionDispatcher(m_collisionConfiguration);

	m_broadphase = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	m_solver = sol;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);
	m_dynamicsWorld->setDebugDrawer(&gDebugDraw);
	
	m_dynamicsWorld->setGravity(btVector3(0,-10,0));

	///create a few basic rigid bodies
	btBoxShape* groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));
	//groundShape->initializePolyhedralFeatures();
//	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),50);
	
	m_collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-50,0));

	//We can also use DemoApplication::localCreateRigidBody, but for clarity it is provided here:
	{
		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		

		//add the body to the dynamics world
		m_dynamicsWorld->addRigidBody(body);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////// Setting the sphere //////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	{
		btCollisionShape* sphereShape = new btSphereShape(1.0f);
		m_collisionShapes.push_back(sphereShape);

		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(50.0f);

		bool isDynamic = (mass != 0.0f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			sphereShape->calculateLocalInertia(mass,localInertia);

		startTransform.setOrigin(btVector3(
			btScalar(-2),
			btScalar(0),
			btScalar(-35)
			));

		btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState,sphereShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//body->applyCentralForce(btVector3(0,0,15000));
		body->applyCentralImpulse(btVector3(0,0,1000));
		body->applyTorqueImpulse(btVector3(0,0,-150));
		m_dynamicsWorld->addRigidBody(body);
		m_sphere = body;

	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////// Setting the pins //////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	{
		//create a few dynamic rigidbodies
		// Re-using the same collision is better for memory usage and performance

		btCollisionShape* shape = new btCylinderShape(btVector3(0.5f, 1, 1));
		m_collisionShapes.push_back(shape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(1.0f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			shape->calculateLocalInertia(mass,localInertia);

		const btVector3 origin = btVector3(0,1,30);
		const float zdiff = 1.5f;
		const float xdiff = 1.5f;

		for (int rowNumber = 0; rowNumber < LENGTH_OF_CONE; rowNumber++)
		{
			for (int cylinderInRow = 0; cylinderInRow <= rowNumber; cylinderInRow++)
			{
				startTransform.setOrigin(btVector3(
					btScalar(origin.getX() + ((cylinderInRow * xdiff * 2) - (xdiff * (rowNumber)))),
					btScalar(0),
					btScalar(rowNumber*zdiff + origin.getZ())
					));

				btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
				btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState,shape,localInertia);
				btRigidBody* body = new btRigidBody(rbInfo);
				
				m_dynamicsWorld->addRigidBody(body);



			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	/////////// Setting up Constraints ////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	{
		btCollisionShape* door = new btBoxShape(btVector3(2,2,0.1));
		m_collisionShapes.push_back(door);

		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass (1.0f);

		bool isDynamic = (mass != 0.0f);
		
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			door->calculateLocalInertia(mass,localInertia);

		startTransform.setOrigin(btVector3(0,2,-10));

		btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState,door,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		m_dynamicsWorld->addRigidBody(body);

		btHingeConstraint* hinge = new btHingeConstraint(*body, btVector3(2,0,0), btVector3(0,1,0));
		hinge->setLimit(-3.14/2,3.14/2);
		m_dynamicsWorld->addConstraint(hinge);
	}
}
void	BasicDemo::clientResetScene()
{
	exitPhysics();
	initPhysics();
}

void	BasicDemo::exitPhysics()
{

	//cleanup in the reverse order of creation/initialization

	//remove the rigidbodies from the dynamics world and delete them
	int i;
	for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	//delete collision shapes
	for (int j=0;j<m_collisionShapes.size();j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		delete shape;
	}
	m_collisionShapes.clear();

	delete m_dynamicsWorld;
	
	delete m_solver;
	
	delete m_broadphase;
	
	delete m_dispatcher;

	delete m_collisionConfiguration;

	delete m_sphere;

	
}




