#include "CameraApp.h"
#include "BaseFrameListener.h"
#include <OGRE\OgreMath.h>
void CameraApp::createScene()
{
	sceneMgr->setAmbientLight( Ogre::ColourValue( 1, 1, 1 ) );
	Ogre::Light *l = sceneMgr->createLight( "MainLight" );

	Ogre::Camera *camera = sceneMgr->createCamera( "MainCam" );
	camNode = sceneMgr->getRootSceneNode()->createChildSceneNode( "CameraNode" );
	camNode->attachObject( camera );

	camera->setPosition( 50, 20, 110 );
	camera->lookAt( 50, 0, 0 );
	camera->setNearClipDistance( 1 );
	camera->setFarClipDistance( 200 );
	setActiveCamera( camera );

	Ogre::Viewport *vp = window->addViewport( camera );
	vp->setDimensions( 0, 0, 1, 1 );
	camera->setAspectRatio(
		(float)vp->getActualWidth() / (float) vp->getActualHeight()
	);

	std::stringstream sstream;
	camera->setPosition( 0, 10, 50 );
	camera->lookAt( 0, 0, 0 );

	Ogre::SceneNode* ArmyNode = sceneMgr->getRootSceneNode()->createChildSceneNode( "ArmyNode" );

	for ( int i = 0; i < 11; i++ )
	{
		
		sstream.clear();
		sstream.str(std::string());
		sstream << "Sinbad" << i;

		Ogre::Entity *entity = sceneMgr->createEntity( sstream.str(), "Sinbad.mesh" );


		if (i != 0)
		{
			entity->getAnimationState("RunBase")->setEnabled(true);
			entity->getAnimationState("RunTop")->setEnabled(true);
		}
		else
		{
			entity->getAnimationState("Dance")->setEnabled(true);
		}

		entity->getAnimationState("RunBase")->setLoop(true);
		entity->getAnimationState("RunTop")->setLoop(true);
		entity->getAnimationState("Dance")->setLoop(true);
		

		sstream.clear();
		sstream.str(std::string());
		sstream << "Node" << i;

		Ogre::SceneNode* node = ArmyNode->createChildSceneNode(sstream.str());
		
		node->attachObject( entity );

		if ( i > 0 )
		{
			node->yaw( Ogre::Degree( ( i - 1 ) * 36 ) );
			node->translate( 0, 0, 20, Ogre::Node::TS_LOCAL );
			node->yaw( Ogre::Degree( -90 ) );
		}
	}
		
	
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

