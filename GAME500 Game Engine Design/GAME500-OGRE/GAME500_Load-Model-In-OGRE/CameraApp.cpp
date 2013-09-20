#include "CameraApp.h"
#include "BaseFrameListener.h"

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

		Ogre::Camera *camera = sceneMgr->createCamera("MainCam");
		camNode = sceneMgr->getRootSceneNode()->createChildSceneNode( "CameraNode" );
		camNode->attachObject(camera);

		Ogre::Entity *sinbadEntity = sceneMgr->createEntity("Sinbad", "zombie.mesh");
		camNode->attachObject(sinbadEntity);
		sinbadEntity->getParentNode()->setScale(30,30,30);
		//sinbadEntity->getParentNode()->roll(Radian(3.14/2));
		sinbadEntity->getParentSceneNode()->pitch(Radian(3.14/2));
		camera->setPosition(0.0, 40.0, -100.0);
		camNode->translate(0.0, 10.0, 0.0);
		Ogre::Viewport *vp = window->addViewport(camera);
		vp->setDimensions(0.0f, 0.0f, 1.0f, 1.0f);
		camera->setAspectRatio((float)vp->getActualWidth() / (float) vp->getActualHeight());
		camera->setFarClipDistance(1000.0f);
		camera->setNearClipDistance(5.0f);
		camera->lookAt(0, 0, 0);
		setActiveCamera(camera);

		Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -10);
		Ogre::MeshManager::getSingleton().createPlane("plane",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
		Ogre::Entity *planeEntity = sceneMgr->createEntity("PlaneEntity", "plane");
		sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(planeEntity);
		planeEntity->setMaterialName("Examples/BeachStones");

		
	
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

