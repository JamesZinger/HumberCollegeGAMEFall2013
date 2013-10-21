#include "CameraApp.h"
#include "BaseFrameListener.h"
#include <OGRE\OgreMath.h>
void CameraApp::createScene()
{
	/***************************************************************************/
	/* This create a scene with a textured plane and a penguin.  The camera    */
	/* is placed directly behind the penguin.  Both the camera and the penguin */
	/* are attached to the same scene node.  As a result, when the node is     */
	/* moved or rotated, the camera and the penguin move or rotate exactly the */
	/* same.  This gives you a first person camera that is always looking over */
	/* the shoulder of your character.                                         */
	/***************************************************************************/
		sceneMgr->setAmbientLight( Ogre::ColourValue( 1, 1, 1 ) );
		Ogre::Light *l = sceneMgr->createLight("MainLight");

		Ogre::Camera *camera = sceneMgr->createCamera("MainCam2");
		camNode = sceneMgr->getRootSceneNode()->createChildSceneNode( "CameraNode" );
		camNode->attachObject(camera);
		camera->setPosition(10.0, 60.0, 10.0);

		Ogre::Viewport *vp = window->addViewport(camera);
		vp->setDimensions(0.0f, 0.0f, 1.0f, 1.0f);
		camera->setAspectRatio((float)vp->getActualWidth() / (float) vp->getActualHeight());
		camera->setFarClipDistance(1000.0f);
		camera->setNearClipDistance(5.0f);
		camera->lookAt(0,0,-10);
		setActiveCamera(camera);
		loader = new DotSceneLoader();
		loader->parseDotScene(Ogre::String("zombiescene.scene"), 
		Ogre::String("General"), 
		sceneMgr);

		// THis call is necessary to ensure the destructor for the DotSceneLoader
		// does not delete the terrain group it created.  THis is a HACK!!
		terrainGroup = loader->takeTerrainGroup();
		Ogre::Vector3 *temp = new Ogre::Vector3(0,0,0);

		camera->lookAt(*temp);

		/*Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
		Ogre::MeshManager::getSingleton().createPlane("plane",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
		Ogre::Entity *planeEntity = sceneMgr->createEntity("PlaneEntity", "plane");
		sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(planeEntity);
		planeEntity->setMaterialName("Examples/BeachStones");*/

		
	
}

void CameraApp::createFrameListener()
{
	frameListener = new BaseFrameListener(this);
}

void CameraApp::createSceneManager()
{
	// get a pointer to the default base scene manager -- sufficient for our purposes
	sceneMgr = root->createSceneManager(Ogre::ST_EXTERIOR_CLOSE );
}

void CameraApp::shutdownApp()
{
	
}

