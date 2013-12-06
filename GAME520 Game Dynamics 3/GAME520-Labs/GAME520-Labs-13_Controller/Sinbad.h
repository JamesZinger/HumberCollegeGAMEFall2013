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
private:
	static String SINBAD_MESH_NAME;
	static String SWORD_MESH_NAME;

	SceneManager* _sceneMgr;
	btDynamicsWorld* _phyWorld;

	SceneNode* _SinbadNode;
	SceneNode* _SwordNode;

public:

	SceneNode* node;

	btRigidBody* body;

	Entity* SinbadMeshENT;
	Entity* SwordMeshENT;
	
	String SceneNodeName;
	String SinbadMeshName;
	String SwordMeshName;

	Sinbad( SceneNode* parent, String NodeName, String SinbadMeshName, String SwordMeshName, SceneManager* SceneManager, btDynamicsWorld* PhyWorld );
	~Sinbad();
};

