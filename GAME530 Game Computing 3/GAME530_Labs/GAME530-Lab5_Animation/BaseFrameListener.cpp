#include "BaseFrameListener.h"
#include <iostream>
#include <string>

bool BaseFrameListener::frameStarted(const FrameEvent &evt) {
	tm += evt.timeSinceLastFrame;
	SceneManager* scnmgr = app->getSceneManager();
	stringstream sstream;
	for (int i = 0; i < 11; i++)
	{
		sstream.clear();
		sstream.str(std::string());
		sstream << "Sinbad" << i;
		if( i == 0 )
		{
			scnmgr->getEntity(sstream.str())->getAnimationState("Dance")->addTime(evt.timeSinceLastFrame);
		}
		else 
		{
			scnmgr->getEntity(sstream.str())->getAnimationState("RunBase")->addTime(evt.timeSinceLastFrame);
			scnmgr->getEntity(sstream.str())->getAnimationState("RunTop")->addTime(evt.timeSinceLastFrame);
		}
	}
	return true;
}

bool BaseFrameListener::frameEnded(const FrameEvent &evt) {

	// grab the keyboard & mouse state
	app->getKeyboard()->capture();
	app->getMouse()->capture();

	processKeyboardInput(evt);
	processMouseInput();

	if(! keepRendering)
	{
		//OGRE_APP.shutdown();
	}

	return keepRendering;
}

void BaseFrameListener::processKeyboardInput(const FrameEvent &evt)
{
	Ogre::Vector3 moveVect = Ogre::Vector3::ZERO;
	float dist = 1.0;
	bool moving = false;
	bool rotating = false;
	float rotateDir = 1.0;
		
	if (app->getKeyboard()->isKeyDown(OIS::KC_ESCAPE))
	{
		keepRendering = false;
		return;
	}

	if (app->getKeyboard()->isKeyDown(OIS::KC_PGUP))
	{
		moveVect.z = -dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_PGDOWN))
	{
		moveVect.z = dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_LEFT))
	{
		moveVect.x = -dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_RIGHT))
	{
		moveVect.x = dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_DOWN))
	{
		moveVect.y = -dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_UP))
	{
		moveVect.y = dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_A))
	{
		rotateDir = 1.0;
		rotating = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_D))
	{
		rotateDir = -1.0;
		rotating = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_W))
	{
		moveVect.z = dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_S))
	{
		moveVect.z = -dist;
		moving = true;
	}

	if(moving)
	{
		((CameraApp*)app)->getCamNode()->translate(moveVect);
	}
	if(rotating)
	{
		((CameraApp*)app)->getCamNode()->yaw(Ogre::Degree(rotateDir * 0.4));
	}
}

void BaseFrameListener::processMouseInput()
{
}

void BaseFrameListener::terminateApp()
{
	keepRendering = false;
}