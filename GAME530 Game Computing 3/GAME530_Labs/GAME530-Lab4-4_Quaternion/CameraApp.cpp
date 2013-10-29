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

		Ogre::Camera *camera = sceneMgr->createCamera("MainCam");
		camNode = sceneMgr->getRootSceneNode()->createChildSceneNode( "CameraNode" );
		camNode->attachObject(camera);
		camera->setPosition(0.0, 0.0, 0.0);

		int originX = -15;
		int distancebetween = 10;

		for (int i = 0; i < 4; i++)
		{
			Ogre::Entity *sinbadEntity = sceneMgr->createEntity("Sinbad" + i, "Sinbad.mesh");
			Ogre::SceneNode *sinbadNode = sceneMgr->getRootSceneNode()->createChildSceneNode("SinbadNode" + i);
			sinbadNode->attachObject(sinbadEntity);
			sinbadNode->setScale(1,1,1);
			sinbadNode->translate(originX + (distancebetween * i), 0, -40);
			Quaternion q = Quaternion::IDENTITY;
			Ogre::Vector3 qV = Ogre::Vector3::ZERO;
			switch (i)
			{
			case 1:
				//sinbadNode->yaw(Ogre::Degree(90.0f));
				qV = Ogre::Vector3(0,1,0) * sin(Ogre::Math::HALF_PI/2);
				q = Quaternion(cos(Ogre::Math::HALF_PI/2), qV.x, qV.y, qV.z);  

				break;
			case 2:
				//sinbadNode->pitch(Ogre::Degree(90.0f));
				qV = Ogre::Vector3(1,0,0) * sin(Ogre::Math::HALF_PI/2);
				q = Quaternion(cos(Ogre::Math::HALF_PI/2), qV.x, qV.y, qV.z);  
				break;
			case 3:
				//sinbadNode->roll(Ogre::Degree(90.0f));
				qV = Ogre::Vector3(0,0,1) * sin(Ogre::Math::HALF_PI/2);
				q = Quaternion(cos(Ogre::Math::HALF_PI/2), qV.x, qV.y, qV.z);  
				break;
			}

			sinbadNode->rotate(q);
		}



		Ogre::Viewport *vp = window->addViewport(camera);
		vp->setDimensions(0.0f, 0.0f, 1.0f, 1.0f);
		camera->setAspectRatio((float)vp->getActualWidth() / (float) vp->getActualHeight());
		camera->setFarClipDistance(1000.0f);
		camera->setNearClipDistance(5.0f);
		camera->lookAt(0,0,-10);
		setActiveCamera(camera);

		

		
	
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

