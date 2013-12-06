#include "CameraApp.h"
#include "BaseFrameListener.h"
#include <OGRE\OgreMath.h>

/**
 * Creates the scene.
 */
void CameraApp::createScene()
{
	sceneMgr->setAmbientLight( Ogre::ColourValue( 1, 1, 1 ) );
	Light *l = sceneMgr->createLight( "MainLight" );


	{
		Camera *camera = sceneMgr->createCamera( "MainCam" );
		
		camNode = sceneMgr->getRootSceneNode()->createChildSceneNode( "CameraNode" );
		camNode->attachObject( camera );
		camNode->translate( Ogre::Vector3( 0, 100, 100 ) );
		camera->setNearClipDistance( 0.1f );
		camera->setFarClipDistance( 20000 );
		setActiveCamera( camera );

		Viewport *vp = window->addViewport( camera );
		vp->setDimensions( 0, 0, 1, 1 );
		camera->setAspectRatio(
			(float)vp->getActualWidth() / (float)vp->getActualHeight()
			);

		camera->setPosition( camNode->getPosition() );
		camera->lookAt( 0, 0, 0 );
	}





	{
		// Bullet initialisation
		btAxisSweep3 *mBroadphase = new btAxisSweep3( btVector3( -10000, -10000, -10000 ), btVector3( 10000, 10000, 10000 ), 1024 );
		btDefaultCollisionConfiguration* mCollisionConfig = new btDefaultCollisionConfiguration();
		btCollisionDispatcher *mDispatcher = new btCollisionDispatcher( mCollisionConfig );
		btSequentialImpulseConstraintSolver* mSolver = new btSequentialImpulseConstraintSolver();

		m_phyWorld = new btDiscreteDynamicsWorld( mDispatcher, mBroadphase, mSolver, mCollisionConfig );
		m_phyWorld->setGravity( btVector3( 0, -9.8, 0 ) );
	}


	Character = new Sinbad( sceneMgr->getRootSceneNode(), "MainCharacter", "SinbadMesh", "SwordMesh", sceneMgr, m_phyWorld );


	{
		Ogre::Vector3 position( 0, 0, 0 );

		// Create a ground plane entity
		Ogre::Plane plane( Ogre::Vector3::UNIT_Y, -10 );
		Ogre::MeshManager::getSingleton().createPlane( "plane", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z );
		Ogre::Entity *planeEntity = sceneMgr->createEntity( "PlaneEntity", "plane" );
		Ogre::SceneNode* planeNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
		planeNode->attachObject( planeEntity );
		planeEntity->setMaterialName( "Examples/BeachStones" );
		planeNode->setPosition( 0, 0, 0 );
		position = planeNode->getPosition();

		btVector3 bulletPos = Convert::toBullet( position );

		btDefaultMotionState* groundState = new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), bulletPos ) );

		StaticMeshToShapeConverter converter2( planeEntity );

		m_phyWorld->addRigidBody( new btRigidBody( 0, groundState, converter2.createTrimesh(), btVector3( 0, 0, 0 ) ) );

	}

	{
		Ogre::Vector3 position( 50, 20, 50 );

		Ogre::Plane plane( Ogre::Vector3::UNIT_Y, -10 );
		Ogre::MeshManager::getSingleton().createPlane( "platform1", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 20, 20, 10, 10, true, 1, 5, 5, Ogre::Vector3::UNIT_Z );
		Ogre::Entity* planeEntity = sceneMgr->createEntity( "Platform", "platform1" );
		Ogre::SceneNode* planeNode = sceneMgr->getRootSceneNode()->createChildSceneNode();

		planeNode->translate( position );

		planeNode->attachObject( planeEntity );
		planeEntity->setMaterialName( "Examples/BeachStones" );
		position = planeNode->getPosition( );

		btVector3 bulletPos = Convert::toBullet( position );

		btDefaultMotionState* groundState = new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), bulletPos ) );

		StaticMeshToShapeConverter converter2( planeEntity );

		m_phyWorld->addRigidBody( new btRigidBody( 0, groundState, converter2.createTrimesh( ), btVector3( 0, 0, 0 ) ) );

	}

	{

		SceneNode* houseNode = sceneMgr->getRootSceneNode()->createChildSceneNode( "HouseNode" );
		Entity* houseEnt = sceneMgr->createEntity( "HosueENT", "tudorhouse.mesh" );
		houseNode->attachObject( houseEnt );

		houseNode->setPosition( 0, 0, 100 );
		houseNode->setScale( 0.2f, 0.2f, 0.2f );

		StaticMeshToShapeConverter converter( houseEnt );

		btRigidBody* body = SetUpBtObject( converter.createBox(), *houseNode, 10000 );

		m_phyWorld->addRigidBody( body );
	}

	{
		SceneNode* ninjaNode = sceneMgr->getRootSceneNode()->createChildSceneNode( "NinjaNode" );
		Entity* ninjaEnt = sceneMgr->createEntity( "NinjaENT", "ninja.mesh" );

		ninjaNode->attachObject( ninjaEnt );
		ninjaNode->rotate( Ogre::Vector3( 0, 1, 0 ), Ogre::Radian( Math::PI ), Ogre::Node::TransformSpace::TS_LOCAL );
		ninjaNode->setPosition( Ogre::Vector3( 100, 0, 0 ) );
		ninjaNode->setScale( Ogre::Vector3( 0.4f, 0.4f, 0.4f ) );

		StaticMeshToShapeConverter converter( ninjaEnt );
		btRigidBody* body = SetUpBtObject( converter.createConvex(), *ninjaNode, 200 );

		m_phyWorld->addRigidBody( body );
	}

	{
		SceneNode* robotNode = sceneMgr->getRootSceneNode()->createChildSceneNode( "RobotNode" );
		Entity* robotEnt = sceneMgr->createEntity( "RobotENT", "robot.mesh" );

		robotNode->attachObject( robotEnt );
		robotNode->rotate( Ogre::Vector3( 0, 1, 0 ), Ogre::Radian( Math::PI ), Ogre::Node::TransformSpace::TS_LOCAL );
		robotNode->setPosition( Ogre::Vector3( -100, 0, 0 ) );
		robotNode->setScale( Ogre::Vector3( 0.7f, 0.7f, 0.7f ) );

		StaticMeshToShapeConverter converter( robotEnt );
		btRigidBody* body = SetUpBtObject( converter.createConvex(), *robotNode, 100 );

		m_phyWorld->addRigidBody( body );
	}

	{
		SceneNode* geoSphereNode = sceneMgr->getRootSceneNode( )->createChildSceneNode( "GeosphereNode" );
		Entity* geoSphereEnt = sceneMgr->createEntity( "GeosphereENT", "geosphere8000.mesh" );

		geoSphereNode->attachObject( geoSphereEnt );
		geoSphereNode->rotate( Ogre::Vector3( 0, 1, 0 ), Ogre::Radian( Math::PI ), Ogre::Node::TransformSpace::TS_LOCAL );
		geoSphereNode->setPosition( Ogre::Vector3( 0, 0, -100 ) );
		geoSphereNode->setScale( Ogre::Vector3( 0.2f, 0.2f, 0.2f ) );

		StaticMeshToShapeConverter converter( geoSphereEnt );
		btRigidBody* body = SetUpBtObject( converter.createSphere(), *geoSphereNode, 100 );

		m_phyWorld->addRigidBody( body );
	}



	m_dbgDraw = new DebugDrawer( sceneMgr->getRootSceneNode(), m_phyWorld );
	m_phyWorld->setDebugDrawer( m_dbgDraw );



}

btRigidBody* CameraApp::SetUpBtObject( btCollisionShape* shape, SceneNode& scnNode, float mass )
{

	btVector3 inertia = btVector3( 0, 0, 0 );

	if ( !shape->isConcave() )
	{
		shape->calculateLocalInertia( mass, inertia );
	}
	RigidBodyState* characterState = new RigidBodyState( &scnNode );

	characterState->setWorldTransform( btTransform( Convert::toBullet( scnNode.getOrientation() ), Convert::toBullet( scnNode.getPosition() ) ) );

	btRigidBody* body = new btRigidBody( mass, characterState, shape, inertia );

	return body;

}


void CameraApp::createFrameListener()
{
	frameListener = new BaseFrameListener( this );
}

void CameraApp::createSceneManager()
{
	// get a pointer to the default base scene manager -- sufficient for our purposes
	sceneMgr = root->createSceneManager( Ogre::ST_EXTERIOR_CLOSE );
}

void CameraApp::shutdownApp()
{

}

