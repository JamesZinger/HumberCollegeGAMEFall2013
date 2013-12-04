#ifndef GUI_APP_H
#define GUI_APP_H

#include "OgreApp.h"
#include "BtOgreGP.h"
#include "BtOgrePG.h"
#include "BtOgreExtras.h"

using BtOgre::DebugDrawer;
using BtOgre::StaticMeshToShapeConverter;
using BtOgre::RigidBodyState;
using BtOgre::Convert;

using Ogre::Viewport;
using Ogre::Camera;
using Ogre::Light;
using Ogre::Entity;
using Ogre::SceneNode;
using Ogre::Vector3;


class CameraApp : public OgreApp
{
private:
	Ogre::SceneNode *camNode;


	Entity* m_characterEnt;
	SceneNode* m_characterNode;
	btRigidBody* m_characterBody;
	btDynamicsWorld* m_phyWorld;
	DebugDrawer* m_dbgDraw;

	btRigidBody* SetUpBtObject( btCollisionShape* shape, SceneNode& scnNode, float mass );

public:
	CameraApp( Ogre::FrameListener *listener, bool useOIS )
		:OgreApp( listener, useOIS ), camNode( NULL )
	{

	}

	virtual void createScene();

	virtual void createFrameListener();

	virtual void createSceneManager();

	virtual void shutdownApp();

	Ogre::SceneNode* getCamNode() { return camNode; }

	btRigidBody* getCharBody( void ) { return m_characterBody; }

	btDynamicsWorld* getDynWorld( void ) { return m_phyWorld; }

	DebugDrawer* getDebugDrawer( void ) { return m_dbgDraw; }

	SceneNode* getCharacterNode( void ) { return m_characterNode; }


};

#endif