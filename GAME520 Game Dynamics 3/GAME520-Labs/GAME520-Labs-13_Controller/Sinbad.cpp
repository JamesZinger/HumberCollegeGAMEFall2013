#include "Sinbad.h"

String Sinbad::SINBAD_MESH_NAME = "Sinbad.mesh";
String Sinbad::SWORD_MESH_NAME = "Sword.mesh";

Sinbad::Sinbad( SceneNode* parent, String SceneNodeName, String SinbadEntName, String SwordEntName, float mass, SceneManager* SceneManager, btDynamicsWorld* PhyWorld )
{
	this->SceneNodeName = SceneNodeName;
	this->SinbadMeshName = SinbadEntName;
	this->SwordMeshName = SinbadEntName;
	this->_sceneMgr = SceneManager;
	this->_phyWorld = PhyWorld;
	this->mass = mass;

	this->node = _sceneMgr->getRootSceneNode()->createChildSceneNode( SceneNodeName );

	this->_SinbadNode = node->createChildSceneNode( SceneNodeName + "_SINBAD" );
	this->_SwordNode = node->createChildSceneNode( SceneNodeName + "_SWORD" );

	this->SinbadMeshENT = _sceneMgr->createEntity( SINBAD_MESH_NAME );
	this->SwordMeshENT = _sceneMgr->createEntity( SWORD_MESH_NAME );

	this->_SinbadNode->attachObject( SinbadMeshENT );
	this->_SwordNode->attachObject( SwordMeshENT );

	_SinbadNode->scale( Vector3( 3, 3, 3 ) );
	_SwordNode->scale( Vector3( 3, 3, 3 ) );


	btVector3 inertia( 0, 0, 0 );

	StaticMeshToShapeConverter converter( this->SinbadMeshENT );

	btCollisionShape* shape = converter.createCapsule();

	//shape->calculateLocalInertia( 10, inertia );

	RigidBodyState* state = new RigidBodyState( this->node );

	state->setWorldTransform( btTransform( Convert::toBullet( this->node->getOrientation() ), Convert::toBullet( this->node->getPosition() ) ) );

	this->body = new btRigidBody( mass, state, shape, inertia );

	this->_phyWorld->addRigidBody( this->body );

	SinbadMeshENT->getAnimationState( "IdleBase" )->setLoop( true );
	SinbadMeshENT->getAnimationState( "IdleTop" )->setLoop( true );
	SinbadMeshENT->getAnimationState( "RunBase" )->setLoop( true );
	SinbadMeshENT->getAnimationState( "RunTop" )->setLoop( true );
	SinbadMeshENT->getAnimationState( "SliceHorizontal" )->setLoop( false );

	SinbadMeshENT->getAnimationState( "IdleBase" )->setEnabled( true );
	SinbadMeshENT->getAnimationState( "IdleTop" )->setEnabled( true );

	movingForward = true;

	SwitchAnimation( Sinbad::SinbadAnimationState::Idle );
}


Sinbad::~Sinbad()
{
}

void Sinbad::SwitchAnimation( Sinbad::SinbadAnimationState Animation )
{
	if ( animationState == Animation )
	{
		return;
	}

	switch ( animationState )
	{
		case ( Sinbad::SinbadAnimationState::Idle ) :

			SinbadMeshENT->getAnimationState( "IdleBase" )->setTimePosition( 0.0f );
			SinbadMeshENT->getAnimationState( "IdleTop" )->setTimePosition( 0.0f );
			SinbadMeshENT->getAnimationState( "IdleBase" )->setEnabled( false );
			SinbadMeshENT->getAnimationState( "IdleTop" )->setEnabled( false );

			break;

		case ( Sinbad::SinbadAnimationState::Moving ) :

			SinbadMeshENT->getAnimationState( "RunBase" )->setTimePosition( 0.0f );
			SinbadMeshENT->getAnimationState( "RunTop" )->setTimePosition( 0.0f );
			SinbadMeshENT->getAnimationState( "RunBase" )->setEnabled( false );
			SinbadMeshENT->getAnimationState( "RunTop" )->setEnabled( false );

			break;

		case( Sinbad::SinbadAnimationState::Attacking ) :

			SinbadMeshENT->getAnimationState( "SliceVertical" )->setTimePosition( 0.0f );
			SinbadMeshENT->getAnimationState( "SliceVertical" )->setEnabled( false );
			break;
	}

	animationState = Animation;

	switch ( animationState )
	{
		case ( Sinbad::SinbadAnimationState::Idle ) :

			SinbadMeshENT->getAnimationState( "IdleBase" )->setEnabled( true );
			SinbadMeshENT->getAnimationState( "IdleTop" )->setEnabled( true );

			break;

		case ( Sinbad::SinbadAnimationState::Moving ) :

			SinbadMeshENT->getAnimationState( "RunBase" )->setEnabled( true );
			SinbadMeshENT->getAnimationState( "RunTop" )->setEnabled( true );

			break;

		case( Sinbad::SinbadAnimationState::Attacking ) :

			SinbadMeshENT->getAnimationState( "SliceVertical" )->setEnabled( true );
			break;
	}
}

void Sinbad::ContinueAnimation( float dt )
{
	switch ( animationState )
	{
		case ( Sinbad::SinbadAnimationState::Idle ) :

			SinbadMeshENT->getAnimationState( "IdleBase" )->addTime( dt );
			SinbadMeshENT->getAnimationState( "IdleTop" )->addTime( dt );

			break;

		case ( Sinbad::SinbadAnimationState::Moving ) :

			if ( !movingForward )
				dt *= -1;

			SinbadMeshENT->getAnimationState( "RunBase" )->addTime( dt );
			SinbadMeshENT->getAnimationState( "RunTop" )->addTime( dt );

			break;

		case( Sinbad::SinbadAnimationState::Attacking ) :

			SinbadMeshENT->getAnimationState( "SliceVertical" )->addTime( dt );

			break;
	}
}

void Sinbad::LogAnimationNames( void )
{
	Ogre::AnimationStateIterator start = SinbadMeshENT->getAllAnimationStates( )->getAnimationStateIterator( );

	Ogre::LogManager::getSingleton( ).logMessage( "Sinbad Animation Names: \n" );

	for ( Ogre::AnimationStateIterator it = start; it.hasMoreElements( ); it.moveNext( ) )
	{

		Ogre::LogManager::getSingleton( ).logMessage( it.current( )->first );
	}

	Ogre::LogManager::getSingleton( ).logMessage( "\n" );
}