#include "BaseFrameListener.h"

bool BaseFrameListener::frameStarted(const FrameEvent &evt) {
	tm += evt.timeSinceLastFrame;
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
	else if (app->getKeyboard()->isKeyDown(OIS::KC_L))
	{
		rotateDir = 1.0;
		rotating = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_R))
	{
		rotateDir = -1.0;
		rotating = true;
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