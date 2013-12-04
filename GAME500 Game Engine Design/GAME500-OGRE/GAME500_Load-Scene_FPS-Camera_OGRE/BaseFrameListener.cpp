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
	float dist = 0.3f;
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
		moveVect.y = -dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_PGDOWN))
	{
		moveVect.y = dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_S))
	{
		moveVect.x = dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_W))
	{
		moveVect.x = -dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_D))
	{
		moveVect.z = -dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_A))
	{
		moveVect.z = dist;
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
		moveVect = ((CameraApp*)app)->getPlayerNode()->getOrientation() * moveVect;
		((CameraApp*)app)->getPlayerNode()->translate(moveVect);
	}
	if(rotating)
	{
		((CameraApp*)app)->getPlayerNode()->yaw(Ogre::Degree(rotateDir * 0.4));
	}
}

void BaseFrameListener::processMouseInput()
{
	OIS::Mouse* mouse = app->getMouse();
	
	int x = mouse->getMouseState().X.rel;
	int y = mouse->getMouseState().Y.rel;
	
	if (x != 0 || y != 0)
	{
		Ogre::Vector2 rotation = Ogre::Vector2::ZERO;

		if (x != 0)
		{
			rotation.y += x * 0.5f;
		}

		if(y != 0)
		{
			rotation.x += y * 0.2f;
		}
		((CameraApp*)app)->getPlayerNode()->roll(Ogre::Degree(rotation.x),Node::TS_LOCAL);
		((CameraApp*)app)->getPlayerNode()->yaw(Ogre::Degree(-rotation.y), Node::TS_WORLD);
		
	}
}

void BaseFrameListener::terminateApp()
{
	keepRendering = false;
}