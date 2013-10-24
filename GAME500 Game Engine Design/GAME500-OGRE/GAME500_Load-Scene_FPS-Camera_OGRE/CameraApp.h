#ifndef GUI_APP_H
#define GUI_APP_H

#include "OgreApp.h"
#include "DotSceneLoader.h"
#include "OGRE\Terrain\OgreTerrainGroup.h"
using Ogre::SceneNode;

class CameraApp: public OgreApp
{
private:
	SceneNode *camNode;

	SceneNode* mPlayerNode;
	
	SceneNode* mGunNode;

	DotSceneLoader* loader;

	Ogre::TerrainGroup* terrainGroup;

public:
	CameraApp(Ogre::FrameListener *listener, bool useOIS)
		:OgreApp(listener, useOIS), camNode(NULL)
	{
		
	}

	virtual void createScene();

	virtual void createFrameListener();

	virtual void createSceneManager();

	virtual void shutdownApp();

	Ogre::SceneNode* getCamNode(){return camNode;}

	SceneNode* getPlayerNode() {return mPlayerNode;}


};

#endif