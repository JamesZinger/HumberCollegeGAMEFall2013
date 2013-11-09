#include "CameraApp.h"
#include "BaseFrameListener.h"
#include <iostream>
#include <string>

using namespace std;

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

	// Jeff Rose's GAME530 Lab 3 work
	std::stringstream sstream;
	int part = 4;
	switch ( part )
	{
	case 1:

		// Part 1
		camera->setPosition( 50, 20, 110 );
		camera->lookAt( 50, 0, 0 );
		for ( int i = 0; i < 11; i++ )
		{
			sstream.clear();
			sstream << "Sinbad" << i;
	
			Ogre::Entity *entity = sceneMgr->createEntity( sstream.str(), "Sinbad.mesh" );
	
			sstream.clear();
			sstream << "Node" << i;
	
			Ogre::SceneNode* node = sceneMgr->getRootSceneNode()->createChildSceneNode( sstream.str() );
			node->attachObject( entity );
	
			node->translate( i * 10, 0, 0 );
		}
		break;


	case 2:

		// Part 2
		camera->setPosition( 0, 10, 50 );
		camera->lookAt( 0, 0, 0 );
		for ( int i = 0; i < 11; i++ )
		{
			sstream.clear();
			sstream << "Sinbad" << i;
	
			Ogre::Entity *entity = sceneMgr->createEntity( sstream.str(), "Sinbad.mesh" );
	
			sstream.clear();
			sstream << "Node" << i;
	
			Ogre::SceneNode* node = sceneMgr->getRootSceneNode()->createChildSceneNode( sstream.str() );
			node->attachObject( entity );
	
			if ( i > 0 )
			{
				node->yaw( Ogre::Degree( ( i - 1 ) * 36 ) );
				node->translate( 0, 0, 20, Ogre::Node::TS_LOCAL );
			}
		}
		break;


	case 3:

		// Part 3
		camera->setPosition( 0, 10, 50 );
		camera->lookAt( 0, 0, 0 );
		for ( int i = 0; i < 11; i++ )
		{
			sstream.clear();
			sstream << "Sinbad" << i;

			Ogre::Entity *entity = sceneMgr->createEntity( sstream.str(), "Sinbad.mesh" );

			sstream.clear();
			sstream << "Node" << i;

			Ogre::SceneNode* node = sceneMgr->getRootSceneNode()->createChildSceneNode( sstream.str() );
			node->attachObject( entity );

			if ( i > 0 )
			{
				node->translate( 0, 0, 20, Ogre::Node::TS_LOCAL );
				node->yaw( Ogre::Degree( ( i - 1 ) * 36 ) );
			}
		}
		break;


	case 4:

		// Part 3
		camera->setPosition( 0, 10, 50 );
		camera->lookAt( 0, 0, 0 );
		for ( int i = 0; i < 11; i++ )
		{
			sstream.clear();
			sstream << "Sinbad" << i;

			Ogre::Entity *entity = sceneMgr->createEntity( sstream.str(), "Sinbad.mesh" );

			sstream.clear();
			sstream << "Node" << i;

			Ogre::SceneNode* node = sceneMgr->getRootSceneNode()->createChildSceneNode( sstream.str() );
			node->attachObject( entity );

			if ( i > 0 )
			{
				node->yaw( Ogre::Degree( ( i - 1 ) * 36 ) );
				node->translate( 0, 0, 20, Ogre::Node::TS_LOCAL );
				node->yaw( Ogre::Degree( -90 ) );
			}
		}
		break;


	default: cout << "NOT A VALID PART OF THE ASSIGNMENT!" << endl;
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

