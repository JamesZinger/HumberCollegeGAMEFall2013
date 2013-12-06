#include "Sinbad.h"

String Sinbad::SINBAD_MESH_NAME = "Sinbad.mesh";
String Sinbad::SWORD_MESH_NAME = "Sword.mesh";

Sinbad::Sinbad( SceneNode* parent, String SceneNodeName, String SinbadEntName, String SwordEntName, SceneManager* SceneManager, btDynamicsWorld* PhyWorld )
{
	this->SceneNodeName = SceneNodeName;
	this->SinbadMeshName = SinbadEntName;
	this->SwordMeshName = SinbadEntName;
	this->_sceneMgr = SceneManager;
	this->_phyWorld = PhyWorld;

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

	state->setWorldTransform( btTransform( Convert::toBullet( this->node->getOrientation( ) ), Convert::toBullet( this->node->getPosition( ) ) ) );

	this->body = new btRigidBody( 100, state, shape, inertia );

	this->_phyWorld->addRigidBody( this->body );
}


Sinbad::~Sinbad()
{
}
