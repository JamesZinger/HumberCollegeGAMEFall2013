#pragma once

#include "OGRE\Ogre.h"
#include "BtOgreGP.h"
#include "BtOgrePG.h"
#include "BtOgreExtras.h"

using BtOgre::StaticMeshToShapeConverter;
using BtOgre::RigidBodyState;
using BtOgre::Convert;

using Ogre::SceneNode;
using Ogre::Entity;
using Ogre::SceneManager;
using Ogre::String;
using Ogre::Vector3;



class Sinbad
{

public:

	enum SinbadAnimationState
	{
		Idle = 0,
		Moving,
		Attacking,
		Jumping
	};

private:
	static String SINBAD_MESH_NAME;
	static String SWORD_MESH_NAME;

	SceneManager* _sceneMgr;
	btDynamicsWorld* _phyWorld;

	SceneNode* _SinbadNode;
	SceneNode* _SwordNode;

	float mass;

private:

	SinbadAnimationState animationState;

public:

	bool movingForward;

	bool isJumping;

	SceneNode* node;

	btRigidBody* body;

	Entity* SinbadMeshENT;
	Entity* SwordMeshENT;
	
	String SceneNodeName;
	String SinbadMeshName;
	String SwordMeshName;

	Sinbad( SceneNode* parent, String NodeName, String SinbadMeshName, String SwordMeshName, float mass, SceneManager* SceneManager, btDynamicsWorld* PhyWorld );
	~Sinbad();

	void SwitchAnimation( SinbadAnimationState state );

	void ContinueAnimation( float dt );

	float getMass( void )
	{
		return mass;
	}

	void LogAnimationNames( void );


};

