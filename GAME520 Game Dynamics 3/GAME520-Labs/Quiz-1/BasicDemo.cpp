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


#include "BasicDemo.h"
#include "GlutStuff.h"
///btBulletDynamicsCommon.h is the main Bullet include file, contains most common include files.
#include "btBulletDynamicsCommon.h"
#include <stdio.h> //printf debugging
#include <iostream>

float fRadius = 1.0;
const float fCoefficientOfRestitution = 1.0;
const float fDragCoefficient = 0.1f;
const float fMass = 0.5f;

void BasicDemo::clientMoveAndDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	// OpenGL calls	
	m_dynamicsWorld->debugDrawWorld();
	renderme(); 
	glFlush();
	glutSwapBuffers();
	
	float fTimeStep = 1.0/100;
	btTransform startTransform;
	startTransform.setIdentity();

	///////////////////////////////////////////////////////////////////////////
	////////////   TRANSFORMATION CALCULATIONS	///////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 2; i++)
	{
		///////////////////////////////////////////////////////////////////////
		////////////		CALCULATE FORCE			///////////////////////////
		///////////////////////////////////////////////////////////////////////
		btVector3 vDrag = btVector3();

		vDrag = -fDragCoefficient * m_vVelocity[i];

		btVector3 vTotalForce = vDrag;

		///////////////////////////////////////////////////////////////////////
		////////////	CALCULATE ACCELERATION		///////////////////////////
		///////////////////////////////////////////////////////////////////////
		m_vAcceleration[i] = vTotalForce / fMass;

		///////////////////////////////////////////////////////////////////////
		////////////		CALCULATE VELOCITY		///////////////////////////
		///////////////////////////////////////////////////////////////////////
		m_vVelocity[i] = m_vVelocity[i] + m_vAcceleration[i] * fTimeStep;

		///////////////////////////////////////////////////////////////////////
		///////////			Calculate Orientation	///////////////////////////
		///////////////////////////////////////////////////////////////////////
		//Cross Product forward vector with up vector
		m_vAngularVelocity[i] = btVector3(0,1,0).cross(m_vVelocity[i]);


		if(m_vAngularVelocity[i].length() != 0)
		{
			m_vAngularVelocity[i].normalize();
		
			
			float scale = m_vVelocity[i].length() / fRadius;
			m_vAngularVelocity[i] *= scale;

			m_qOrientation[i] = m_qOrientation[i] + ((btQuaternion(m_vAngularVelocity[i].getX(), m_vAngularVelocity[i].getY(), m_vAngularVelocity[i].getZ(), 0)* m_qOrientation[i])*(fTimeStep/2));
		}
		///////////////////////////////////////////////////////////////////////
		////////////		CALCULATE POSITION		///////////////////////////
		///////////////////////////////////////////////////////////////////////
		m_vPosition[i] += m_vVelocity[i] * fTimeStep;
		
		startTransform.setOrigin(m_vPosition[i]);
		startTransform.setRotation(m_qOrientation[i]);
		m_rigidBody[i]->getMotionState()->setWorldTransform(startTransform);
	}

	///////////////////////////////////////////////////////////////////////////
	////////////		COLLISION DETECTION		///////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	if (m_vPosition[0].distance(m_vPosition[1]) < fRadius * 2)
	{
		///////////////////////////////////////////////////////////////////////
		//////////	CALCULATE COLLISION NORMAL	///////////////////////////////
		///////////////////////////////////////////////////////////////////////
		btVector3 normal = btVector3();
		normal = m_vPosition[1] - (m_vPosition[0]);
		normal.normalize();

		m_vVelocity[0] -= 2 * (m_vVelocity[0].dot(normal) * normal);
	}

}


void BasicDemo::displayCallback(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	renderme();

	//optional but useful: debug drawing to detect problems
	if (m_dynamicsWorld)
		m_dynamicsWorld->debugDrawWorld();

	glFlush();
	glutSwapBuffers();
}


void BasicDemo::initPhysics()
{
	setTexturing(true);
	setShadows(true);

	setCameraDistance(btScalar(10.0));

	///collision configuration contains default setup for memory, collision setup
	m_collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new	btCollisionDispatcher(m_collisionConfiguration);

	m_broadphase = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
	m_solver = sol;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);

	m_dynamicsWorld->setGravity(btVector3(0,-10,0));

	///create a few basic rigid bodies
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));
	
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
		body->setRestitution(btScalar(0.8f));	

		//add the body to the dynamics world
		m_dynamicsWorld->addRigidBody(body);
	}

	// Here are the dynamic bodies
	{
		btCollisionShape* colShape = new btSphereShape(1);	

		m_collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(fMass);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
		
		float start_x[] = {0.0, 1.9}; // collision angle
		float start_y[] = {1.0, 1.0};
		float start_z[] = {-4.0, 4.0};

		// set up 2 rigid bodies and put them into the btAlignedObjectArray called m_rigidBody
		for(int ii = 0; ii < 2; ii++){
			startTransform.setOrigin(btVector3(	start_x[ii], start_y[ii], start_z[ii] ));			
			//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
			btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);	
			btRigidBody* ball = new btRigidBody(rbInfo);
			ball->setActivationState(ISLAND_SLEEPING);
			ball->setRestitution(fCoefficientOfRestitution);	
			m_dynamicsWorld->addRigidBody(ball);
			ball->setActivationState(ISLAND_SLEEPING);
			m_rigidBody.push_back(ball);
			
		}

		for(int i = 0; i < 2; i++)
		{

			float start_velx[] = {0,0};
			float start_vely[] = {0,0};
			float start_velz[] = {3,0};

			m_vAcceleration[i] = btVector3();
			m_vAngularVelocity[i] = btVector3();
			m_vPosition[i] = btVector3();
			m_vTorque[i] = btVector3();
			m_vVelocity[i] = btVector3();
			m_qOrientation[i] = btQuaternion();

			m_qOrientation[i].setValue(0.0,0.0,0.0,1.0);
			m_vAcceleration[i].setValue(0.0,0.0,0.0);
			m_vAngularVelocity[i].setValue(0.0,0.0,0.0);
			m_vVelocity[i].setValue(start_velx[i],start_vely[i], start_velz[i]);
			m_vPosition[i].setValue(start_x[i],start_y[i],start_z[i]);
			m_vTorque[i].setValue(0.0,0.0,0.0);
		}

	}

	clientResetScene();
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

	delete m_dynamicsWorld;
	
	delete m_solver;
	
	delete m_broadphase;
	
	delete m_dispatcher;

	delete m_collisionConfiguration;

	
}




