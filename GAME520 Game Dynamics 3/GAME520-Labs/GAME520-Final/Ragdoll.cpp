#include "Ragdoll.h"



Ragdoll::Ragdoll( btDynamicsWorld* ownerWorld, const btVector3& positionOffset, const float scale )
: m_ownerWorld( ownerWorld )
{
	// Setup the geometry
	m_shapes[ BODYPART_PELVIS ] = new btCapsuleShape( btScalar( 0.15 * scale ), btScalar( 0.20 * scale ) );
	m_shapes[ BODYPART_SPINE ] = new btCapsuleShape( btScalar( 0.15 * scale ), btScalar( 0.28 * scale ) );
	m_shapes[ BODYPART_HEAD ] = new btCapsuleShape( btScalar( 0.10 * scale ), btScalar( 0.05 * scale ) );
	m_shapes[ BODYPART_LEFT_UPPER_LEG ] = new btCapsuleShape( btScalar( 0.07 * scale ), btScalar( 0.45 * scale ) );
	m_shapes[ BODYPART_LEFT_LOWER_LEG ] = new btCapsuleShape( btScalar( 0.05 * scale ), btScalar( 0.37 * scale ) );
	m_shapes[ BODYPART_RIGHT_UPPER_LEG ] = new btCapsuleShape( btScalar( 0.07 * scale ), btScalar( 0.45 * scale ) );
	m_shapes[ BODYPART_RIGHT_LOWER_LEG ] = new btCapsuleShape( btScalar( 0.05 * scale ), btScalar( 0.37 * scale ) );
	m_shapes[ BODYPART_LEFT_UPPER_ARM ] = new btCapsuleShape( btScalar( 0.05 * scale ), btScalar( 0.33 * scale ) );
	m_shapes[ BODYPART_LEFT_LOWER_ARM ] = new btCapsuleShape( btScalar( 0.04 * scale ), btScalar( 0.25 * scale ) );
	m_shapes[ BODYPART_RIGHT_UPPER_ARM ] = new btCapsuleShape( btScalar( 0.05 * scale ), btScalar( 0.33 * scale ) );
	m_shapes[ BODYPART_RIGHT_LOWER_ARM ] = new btCapsuleShape( btScalar( 0.04 * scale ), btScalar( 0.25 * scale ) );

	// Setup all the rigid bodies
	btTransform offset; offset.setIdentity();
	offset.setOrigin( positionOffset );

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( 0. ), btScalar( 1. ), btScalar( 0. ) ) );
	m_bodies[ BODYPART_PELVIS ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_PELVIS ] );

	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( 0. ), btScalar( 1.2 ), btScalar( 0. ) ) );
	m_bodies[ BODYPART_SPINE ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_SPINE ] );

	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( 0. ), btScalar( 1.6 ), btScalar( 0. ) ) );
	m_bodies[ BODYPART_HEAD ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_HEAD ] );

	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( -0.18 * scale ), btScalar( 0.65 * scale ), btScalar( 0. ) ) );
	m_bodies[ BODYPART_LEFT_UPPER_LEG ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_LEFT_UPPER_LEG ] );

	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( -0.18 * scale ), btScalar( 0.2 * scale ), btScalar( 0. ) ) );
	m_bodies[ BODYPART_LEFT_LOWER_LEG ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_LEFT_LOWER_LEG ] );

	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( 0.18 * scale ), btScalar( 0.65 * scale ), btScalar( 0. ) ) );
	m_bodies[ BODYPART_RIGHT_UPPER_LEG ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_RIGHT_UPPER_LEG ] );

	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( 0.18 * scale ), btScalar( 0.2 * scale ), btScalar( 0. ) ) );
	m_bodies[ BODYPART_RIGHT_LOWER_LEG ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_RIGHT_LOWER_LEG ] );

	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( -0.35 * scale ), btScalar( 1.45 * scale ), btScalar( 0. ) ) );
	transform.getBasis().setEulerZYX( 0, 0, M_PI_2 );
	m_bodies[ BODYPART_LEFT_UPPER_ARM ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_LEFT_UPPER_ARM ] );

	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( -0.7 * scale ), btScalar( 1.45 * scale ), btScalar( 0. ) ) );
	transform.getBasis().setEulerZYX( 0, 0, M_PI_2 );
	m_bodies[ BODYPART_LEFT_LOWER_ARM ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_LEFT_LOWER_ARM ] );

	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( 0.35 * scale ), btScalar( 1.45 * scale), btScalar( 0. ) ) );
	transform.getBasis().setEulerZYX( 0, 0, -M_PI_2 );
	m_bodies[ BODYPART_RIGHT_UPPER_ARM ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_RIGHT_UPPER_ARM ] );

	transform.setIdentity();
	transform.setOrigin( btVector3( btScalar( 0.7 * scale ), btScalar( 1.45 * scale ), btScalar( 0. ) ) );
	transform.getBasis().setEulerZYX( 0, 0, -M_PI_2 );
	m_bodies[ BODYPART_RIGHT_LOWER_ARM ] = localCreateRigidBody( btScalar( 1. ), offset*transform, m_shapes[ BODYPART_RIGHT_LOWER_ARM ] );

	// Setup some damping on the m_bodies
	for ( int i = 0; i < BODYPART_COUNT; ++i )
	{
		m_bodies[ i ]->setDamping( 0.05, 0.85 );
		m_bodies[ i ]->setDeactivationTime( 0.8 );
		m_bodies[ i ]->setSleepingThresholds( 1.6, 2.5 );
	}

	// Now setup the constraints
	btHingeConstraint* hingeC;
	btConeTwistConstraint* coneC;

	btTransform localA, localB;

	localA.setIdentity(); localB.setIdentity();
	localA.getBasis( ).setEulerZYX( 0, M_PI_2, 0 ); localA.setOrigin( btVector3( btScalar( 0. ), btScalar( 0.15 * scale ), btScalar( 0. ) ) );
	localB.getBasis( ).setEulerZYX( 0, M_PI_2, 0 ); localB.setOrigin( btVector3( btScalar( 0. ), btScalar( -0.15 * scale ), btScalar( 0. ) ) );
	hingeC = new btHingeConstraint( *m_bodies[ BODYPART_PELVIS ], *m_bodies[ BODYPART_SPINE ], localA, localB );
	hingeC->setLimit( btScalar( -M_PI_4 ), btScalar( M_PI_2 ) );
	m_joints[ JOINT_PELVIS_SPINE ] = hingeC;
	hingeC->setDbgDrawSize( CONSTRAINT_DEBUG_SIZE );

	m_ownerWorld->addConstraint( m_joints[ JOINT_PELVIS_SPINE ], true );


	localA.setIdentity(); localB.setIdentity();
	localA.getBasis( ).setEulerZYX( 0, 0, M_PI_2 ); localA.setOrigin( btVector3( btScalar( 0. ), btScalar( 0.30 * scale ), btScalar( 0. ) ) );
	localB.getBasis( ).setEulerZYX( 0, 0, M_PI_2 ); localB.setOrigin( btVector3( btScalar( 0. ), btScalar( -0.14 * scale ), btScalar( 0. ) ) );
	coneC = new btConeTwistConstraint( *m_bodies[ BODYPART_SPINE ], *m_bodies[ BODYPART_HEAD ], localA, localB );
	coneC->setLimit( M_PI_4, M_PI_4, M_PI_2 );
	m_joints[ JOINT_SPINE_HEAD ] = coneC;
	coneC->setDbgDrawSize( CONSTRAINT_DEBUG_SIZE );

	m_ownerWorld->addConstraint( m_joints[ JOINT_SPINE_HEAD ], true );


	localA.setIdentity(); localB.setIdentity();
	localA.getBasis( ).setEulerZYX( 0, 0, -M_PI_4 * 5 ); localA.setOrigin( btVector3( btScalar( -0.18 * scale ), btScalar( -0.10 * scale ), btScalar( 0. ) ) );
	localB.getBasis( ).setEulerZYX( 0, 0, -M_PI_4 * 5 ); localB.setOrigin( btVector3( btScalar( 0. ), btScalar( 0.225 * scale ), btScalar( 0. ) ) );
	coneC = new btConeTwistConstraint( *m_bodies[ BODYPART_PELVIS ], *m_bodies[ BODYPART_LEFT_UPPER_LEG ], localA, localB );
	coneC->setLimit( M_PI_4, M_PI_4, 0 );
	m_joints[ JOINT_LEFT_HIP ] = coneC;
	coneC->setDbgDrawSize( CONSTRAINT_DEBUG_SIZE );

	m_ownerWorld->addConstraint( m_joints[ JOINT_LEFT_HIP ], true );

	localA.setIdentity(); localB.setIdentity();
	localA.getBasis( ).setEulerZYX( 0, M_PI_2, 0 ); localA.setOrigin( btVector3( btScalar( 0. ), btScalar( -0.225 * scale ), btScalar( 0. ) ) );
	localB.getBasis( ).setEulerZYX( 0, M_PI_2, 0 ); localB.setOrigin( btVector3( btScalar( 0. ), btScalar( 0.185 * scale ), btScalar( 0. ) ) );
	hingeC = new btHingeConstraint( *m_bodies[ BODYPART_LEFT_UPPER_LEG ], *m_bodies[ BODYPART_LEFT_LOWER_LEG ], localA, localB );
	hingeC->setLimit( btScalar( 0 ), btScalar( M_PI_2 ) );
	m_joints[ JOINT_LEFT_KNEE ] = hingeC;
	hingeC->setDbgDrawSize( CONSTRAINT_DEBUG_SIZE );

	m_ownerWorld->addConstraint( m_joints[ JOINT_LEFT_KNEE ], true );


	localA.setIdentity(); localB.setIdentity();
	localA.getBasis( ).setEulerZYX( 0, 0, M_PI_4 ); localA.setOrigin( btVector3( btScalar( 0.18 * scale ), btScalar( -0.10 * scale ), btScalar( 0. ) ) );
	localB.getBasis( ).setEulerZYX( 0, 0, M_PI_4 ); localB.setOrigin( btVector3( btScalar( 0. ), btScalar( 0.225 * scale ), btScalar( 0. ) ) );
	coneC = new btConeTwistConstraint( *m_bodies[ BODYPART_PELVIS ], *m_bodies[ BODYPART_RIGHT_UPPER_LEG ], localA, localB );
	coneC->setLimit( M_PI_4, M_PI_4, 0 );
	m_joints[ JOINT_RIGHT_HIP ] = coneC;
	coneC->setDbgDrawSize( CONSTRAINT_DEBUG_SIZE );

	m_ownerWorld->addConstraint( m_joints[ JOINT_RIGHT_HIP ], true );

	localA.setIdentity(); localB.setIdentity();
	localA.getBasis( ).setEulerZYX( 0, M_PI_2, 0 ); localA.setOrigin( btVector3( btScalar( 0. ), btScalar( -0.225 * scale ), btScalar( 0. ) ) );
	localB.getBasis( ).setEulerZYX( 0, M_PI_2, 0 ); localB.setOrigin( btVector3( btScalar( 0. ), btScalar( 0.185 * scale ), btScalar( 0. ) ) );
	hingeC = new btHingeConstraint( *m_bodies[ BODYPART_RIGHT_UPPER_LEG ], *m_bodies[ BODYPART_RIGHT_LOWER_LEG ], localA, localB );
	hingeC->setLimit( btScalar( 0 ), btScalar( M_PI_2 ) );
	m_joints[ JOINT_RIGHT_KNEE ] = hingeC;
	hingeC->setDbgDrawSize( CONSTRAINT_DEBUG_SIZE );

	m_ownerWorld->addConstraint( m_joints[ JOINT_RIGHT_KNEE ], true );


	localA.setIdentity(); localB.setIdentity();
	localA.getBasis( ).setEulerZYX( 0, 0, M_PI ); localA.setOrigin( btVector3( btScalar( -0.2 * scale ), btScalar( 0.15 * scale ), btScalar( 0. ) ) );
	localB.getBasis( ).setEulerZYX( 0, 0, M_PI_2 ); localB.setOrigin( btVector3( btScalar( 0. ), btScalar( -0.18 * scale ), btScalar( 0. ) ) );
	coneC = new btConeTwistConstraint( *m_bodies[ BODYPART_SPINE ], *m_bodies[ BODYPART_LEFT_UPPER_ARM ], localA, localB );
	coneC->setLimit( M_PI_2, M_PI_2, 0 );
	coneC->setDbgDrawSize( CONSTRAINT_DEBUG_SIZE );

	m_joints[ JOINT_LEFT_SHOULDER ] = coneC;
	m_ownerWorld->addConstraint( m_joints[ JOINT_LEFT_SHOULDER ], true );

	localA.setIdentity(); localB.setIdentity();
	localA.getBasis( ).setEulerZYX( 0, M_PI_2, 0 ); localA.setOrigin( btVector3( btScalar( 0. ), btScalar( 0.18 * scale ), btScalar( 0. ) ) );
	localB.getBasis( ).setEulerZYX( 0, M_PI_2, 0 ); localB.setOrigin( btVector3( btScalar( 0. ), btScalar( -0.14 * scale ), btScalar( 0. ) ) );
	hingeC = new btHingeConstraint( *m_bodies[ BODYPART_LEFT_UPPER_ARM ], *m_bodies[ BODYPART_LEFT_LOWER_ARM ], localA, localB );
	//		hingeC->setLimit(btScalar(-M_PI_2), btScalar(0));
	hingeC->setLimit( btScalar( 0 ), btScalar( M_PI_2 ) );
	m_joints[ JOINT_LEFT_ELBOW ] = hingeC;
	hingeC->setDbgDrawSize( CONSTRAINT_DEBUG_SIZE );

	m_ownerWorld->addConstraint( m_joints[ JOINT_LEFT_ELBOW ], true );



	localA.setIdentity(); localB.setIdentity();
	localA.getBasis( ).setEulerZYX( 0, 0, 0 ); localA.setOrigin( btVector3( btScalar( 0.2 * scale ), btScalar( 0.15 * scale ), btScalar( 0. ) ) );
	localB.getBasis( ).setEulerZYX( 0, 0, M_PI_2 ); localB.setOrigin( btVector3( btScalar( 0. ), btScalar( -0.18 * scale ), btScalar( 0. ) ) );
	coneC = new btConeTwistConstraint( *m_bodies[ BODYPART_SPINE ], *m_bodies[ BODYPART_RIGHT_UPPER_ARM ], localA, localB );
	coneC->setLimit( M_PI_2, M_PI_2, 0 );
	m_joints[ JOINT_RIGHT_SHOULDER ] = coneC;
	coneC->setDbgDrawSize( CONSTRAINT_DEBUG_SIZE );

	m_ownerWorld->addConstraint( m_joints[ JOINT_RIGHT_SHOULDER ], true );

	localA.setIdentity(); localB.setIdentity();
	localA.getBasis( ).setEulerZYX( 0, M_PI_2, 0 ); localA.setOrigin( btVector3( btScalar( 0. ), btScalar( 0.18 * scale ), btScalar( 0. ) ) );
	localB.getBasis( ).setEulerZYX( 0, M_PI_2, 0 ); localB.setOrigin( btVector3( btScalar( 0. ), btScalar( -0.14 * scale ), btScalar( 0. ) ) );
	hingeC = new btHingeConstraint( *m_bodies[ BODYPART_RIGHT_UPPER_ARM ], *m_bodies[ BODYPART_RIGHT_LOWER_ARM ], localA, localB );
	//		hingeC->setLimit(btScalar(-M_PI_2), btScalar(0));
	hingeC->setLimit( btScalar( 0 ), btScalar( M_PI_2 ) );
	m_joints[ JOINT_RIGHT_ELBOW ] = hingeC;
	hingeC->setDbgDrawSize( CONSTRAINT_DEBUG_SIZE );

	m_ownerWorld->addConstraint( m_joints[ JOINT_RIGHT_ELBOW ], true );
}


Ragdoll::~Ragdoll()
{
	int i;

	// Remove all constraints
	for ( i = 0; i < JOINT_COUNT; ++i )
	{
		m_ownerWorld->removeConstraint( m_joints[ i ] );
		delete m_joints[ i ]; m_joints[ i ] = 0;
	}

	// Remove all bodies and shapes
	for ( i = 0; i < BODYPART_COUNT; ++i )
	{
		m_ownerWorld->removeRigidBody( m_bodies[ i ] );

		delete m_bodies[ i ]->getMotionState();

		delete m_bodies[ i ]; m_bodies[ i ] = 0;
		delete m_shapes[ i ]; m_shapes[ i ] = 0;
	}
}

btRigidBody* Ragdoll::localCreateRigidBody( btScalar mass, const btTransform& startTransform, btCollisionShape* shape )
{
	bool isDynamic = ( mass != 0.f );

	btVector3 localInertia( 0, 0, 0 );
	if ( isDynamic )
		shape->calculateLocalInertia( mass, localInertia );

	btDefaultMotionState* myMotionState = new btDefaultMotionState( startTransform );

	btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, myMotionState, shape, localInertia );
	btRigidBody* body = new btRigidBody( rbInfo );

	m_ownerWorld->addRigidBody( body );

	return body;
}
