#pragma once

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "OGRE\Ogre.h"

using Ogre::SceneNode;
using Ogre::Vector3;

class MyPhysics
{
private:
	btAlignedObjectArray<btCollisionShape*> mCollisionShapes;
	btBroadphaseInterface * mBroadphase;
	btCollisionDispatcher * mDispatcher;
	btConstraintSolver * mSolver;
	btDefaultCollisionConfiguration * mColConfig;
	btDiscreteDynamicsWorld * mWorld;
	SceneNode * mRootSceneNode;

public:
	MyPhysics();
	~MyPhysics();

	void addStaticPlane( SceneNode* node );
	void addStaticPlane2( SceneNode* node );

	btRigidBody*				addDynamicBox( SceneNode * node, float m = 1.0f );
	btRigidBody*				addRigidBody( btTransform transform, btCollisionShape * shape, btScalar mass, SceneNode * node = NULL );
	void						addCollisionShape( btCollisionShape * colShape );
	btDiscreteDynamicsWorld*	getDynamicsWorld( void );
	btCollisionWorld*			getCollisionWorld( void );
	btBroadphaseInterface*		getBroadphase( void );
	void						setRootSceneNode( SceneNode * node );
	btVector3					toBullet( const Vector3 & vec ) const;
	void						shootBox( const Vector3 & camPosition );

	static void					debugBtVector3( const btVector3 & vec, const char * str = 0 );

};
