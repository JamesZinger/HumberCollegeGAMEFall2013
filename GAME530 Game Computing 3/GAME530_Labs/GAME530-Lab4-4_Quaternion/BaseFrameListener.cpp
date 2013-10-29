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
	processMouseInput(evt);

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
	else if (app->getKeyboard()->isKeyDown(OIS::KC_D))
	{
		moveVect.x = dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_A))
	{
		moveVect.x = -dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_W))
	{
		moveVect.z = -dist;
		moving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_S))
	{
		moveVect.z = dist;
		moving = true;
	}

	if(moving)
	{
		moveVect = ((CameraApp*)app)->getActiveCamera()->getOrientation() * moveVect;
		((CameraApp*)app)->getCamNode()->translate(moveVect);
	}
	
}

void BaseFrameListener::processMouseInput(const FrameEvent &evt)
{
	float yawAngle = app->getMouse()->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
	float pitchAngle = app->getMouse()->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
	
	Ogre::Vector3 localXAxis = ((CameraApp*)app)->getActiveCamera()->getRight();
	
	Ogre::Vector3 qVY = Ogre::Vector3::UNIT_Y * sin(yawAngle/2);
	Ogre::Vector3 qVX = localXAxis * sin(pitchAngle/2);

	Quaternion q = Quaternion(cos(yawAngle/2), qVY.x, qVY.y, qVY.z);
	q = q * Quaternion(cos(pitchAngle/2),qVX.x, qVX.y, qVX.z);

	((CameraApp*)app)->getActiveCamera()->rotate(q);

}

void BaseFrameListener::terminateApp()
{
	keepRendering = false;
}