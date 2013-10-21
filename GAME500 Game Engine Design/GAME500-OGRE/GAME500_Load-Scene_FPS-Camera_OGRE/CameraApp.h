#ifndef GUI_APP_H
#define GUI_APP_H

#include "OgreApp.h"
#include "DotSceneLoader.h"
#include "OGRE\Terrain\OgreTerrainGroup.h"
class CameraApp: public OgreApp
{
private:
	Ogre::SceneNode *camNode;

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


};

#endif