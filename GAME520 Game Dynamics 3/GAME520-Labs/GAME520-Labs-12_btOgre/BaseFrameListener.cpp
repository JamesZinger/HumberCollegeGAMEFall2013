#include "BaseFrameListener.h"

bool BaseFrameListener::frameStarted(const FrameEvent &evt) {
	tm += evt.timeSinceLastFrame;
	SceneManager* scnmgr = app->getSceneManager();
	stringstream sstream;
	for (int i = 0; i < 11; i++)
	{
		sstream.clear();
		sstream.str(std::string());
		sstream << "Sinbad" << i;

		if (i != 0)
		{
			scnmgr->getEntity(sstream.str())->getAnimationState("RunTop")->addTime(evt.timeSinceLastFrame);
			scnmgr->getEntity(sstream.str())->getAnimationState("RunBase")->addTime(evt.timeSinceLastFrame);
		}
	}

	scnmgr->getSceneNode("ArmyNode")->rotate(Ogre::Vector3(0,1,0),Ogre::Degree(-0.2f),Ogre::Node::TS_LOCAL);
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
	Ogre::Vector3 sinbadTranslate = Ogre::Vector3::ZERO;

	float dist = 1.0;
	float fWalkingSpeed = 4.0f;
	bool moving = false;
	bool sinbadMoving = false;
		
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
	
	if (app->getKeyboard()->isKeyDown(OIS::KC_DOWN))
	{
		sinbadTranslate.z = fWalkingSpeed;
		sinbadMoving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_UP))
	{
		sinbadTranslate.z = -fWalkingSpeed;
		sinbadMoving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_RIGHT))
	{
		sinbadTranslate.x = fWalkingSpeed;
		sinbadMoving = true;
	}
	else if (app->getKeyboard()->isKeyDown(OIS::KC_LEFT))
	{
		sinbadTranslate.x = -fWalkingSpeed;
		sinbadMoving = true;
	}

	if(moving)
	{
		moveVect = ((CameraApp*)app)->getActiveCamera()->getOrientation() * moveVect;
		((CameraApp*)app)->getCamNode()->translate(moveVect);
	}

	if (sinbadMoving)
	{
		app->getSceneManager()->getSceneNode("Node0")->translate(sinbadTranslate * evt.timeSinceLastFrame);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("RunTop")->setEnabled(true);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("RunBase")->setEnabled(true);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("Dance")->setEnabled(false);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("Dance")->setTimePosition(0);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("RunTop")->addTime(evt.timeSinceLastFrame);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("RunBase")->addTime(evt.timeSinceLastFrame);
		
		Ogre::Quaternion qOrientation(1, 0, 0, 0);
		Ogre::Vector3 src = Ogre::Vector3::UNIT_Z;
		qOrientation = src.getRotationTo(sinbadTranslate);
		app->getSceneManager()->getSceneNode("Node0")->setOrientation(qOrientation);
		
	}
	else
	{
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("RunTop")->setEnabled(false);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("RunBase")->setEnabled(false);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("Dance")->setEnabled(true);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("Dance")->addTime(evt.timeSinceLastFrame);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("RunTop")->setTimePosition(0);
		app->getSceneManager()->getEntity("Sinbad0")->getAnimationState("RunBase")->setTimePosition(0);
	}
}

void BaseFrameListener::processMouseInput(const FrameEvent &evt)
{
	float yawAngle = app->getMouse()->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
	float pitchAngle = app->getMouse()->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
	
	Ogre::Vector3 localXAxis = ((CameraApp*)app)->getActiveCamera()->getRight();
	
	yawAngle /= 10.0f;
	pitchAngle /= 10.0f;

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