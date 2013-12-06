#include "BaseFrameListener.h"

bool BaseFrameListener::frameStarted( const FrameEvent &evt )
{
	tm += evt.timeSinceLastFrame;
	( (CameraApp*)app )->getDynWorld()->stepSimulation( evt.timeSinceLastFrame, 10 );
	( (CameraApp*)app )->getDynWorld()->debugDrawWorld();
	//Shows debug if B key down.
	( (CameraApp*)app )->getDebugDrawer()->setDebugMode( 1 );//app->getKeyboard()->isKeyDown( OIS::KC_B ) );
	( (CameraApp*)app )->getDebugDrawer()->step();

	return true;
}

bool BaseFrameListener::frameEnded( const FrameEvent &evt )
{

	// grab the keyboard & mouse state
	app->getKeyboard()->capture();
	app->getMouse()->capture();

	processKeyboardInput( evt );
	processMouseInput( evt );

	if ( !keepRendering )
	{
		//OGRE_APP.shutdown();
	}

	return keepRendering;
}

void BaseFrameListener::processKeyboardInput( const FrameEvent &evt )
{
	{
		Ogre::Vector3 moveVect = Ogre::Vector3::ZERO;

		float dist = 3.0;
		bool moving = false;

		if ( app->getKeyboard()->isKeyDown( OIS::KC_ESCAPE ) )
		{
			keepRendering = false;
			return;
		}

		if ( app->getKeyboard()->isKeyDown( OIS::KC_PGUP ) )
		{
			moveVect.y = -dist;
			moving = true;
		}
		else if ( app->getKeyboard()->isKeyDown( OIS::KC_PGDOWN ) )
		{
			moveVect.y = dist;
			moving = true;
		}
		else if ( app->getKeyboard()->isKeyDown( OIS::KC_D ) )
		{
			moveVect.x = dist;
			moving = true;
		}
		else if ( app->getKeyboard()->isKeyDown( OIS::KC_A ) )
		{
			moveVect.x = -dist;
			moving = true;
		}
		else if ( app->getKeyboard()->isKeyDown( OIS::KC_W ) )
		{
			moveVect.z = -dist;
			moving = true;
		}
		else if ( app->getKeyboard()->isKeyDown( OIS::KC_S ) )
		{
			moveVect.z = dist;
			moving = true;
		}


		if ( moving )
		{
			moveVect = ( (CameraApp*)app )->getActiveCamera()->getOrientation() * moveVect;
			//( (CameraApp*)app )->getCamNode()->translate( moveVect );
			Ogre::Vector3 pos = ( (CameraApp*)app )->getActiveCamera()->getPosition();
			( (CameraApp*)app )->getActiveCamera()->setPosition( pos + moveVect );
		}
	}

	{
	btVector3 impulse = btVector3( 0, 0, 0 );
	bool isAddingForce = false;
	float force = 30.0;
	if ( app->getKeyboard()->isKeyDown( OIS::KC_UP ) )
	{
		isAddingForce = true;
		impulse.setZ( impulse.getZ() - force );
	}
	else if ( app->getKeyboard()->isKeyDown( OIS::KC_DOWN ) )
	{
		isAddingForce = true;
		impulse.setZ( impulse.getZ() + force );
	}

	if ( app->getKeyboard()->isKeyDown( OIS::KC_RIGHT ) )
	{
		isAddingForce = true;
		impulse.setX( impulse.getX() + force );
	}
	else if ( app->getKeyboard()->isKeyDown( OIS::KC_LEFT ) )
	{
		isAddingForce = true;
		impulse.setX( impulse.getX() - force );
	}

	if ( app->getKeyboard()->isKeyDown( OIS::KC_SPACE ) )
	{
		isAddingForce = true;
		impulse.setY( impulse.getY() + force );
	}

	if ( isAddingForce )
	{
		( (CameraApp*)app )->Character->body->applyCentralImpulse( impulse );
	}

	else
	{
		btVector3 velocity = ( (CameraApp*)app )->Character->body->getLinearVelocity();
		( (CameraApp*)app )->Character->body->setLinearVelocity( btVector3( 0, velocity.getY(), 0 ) );
	}

}

}

void BaseFrameListener::processMouseInput( const FrameEvent &evt )
{
	float yawAngle = app->getMouse()->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
	float pitchAngle = app->getMouse()->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;

	Ogre::Vector3 localXAxis = ( (CameraApp*)app )->getActiveCamera()->getRight();

	yawAngle /= 4.0f;
	pitchAngle /= 4.0f;

	Ogre::Vector3 qVY = Ogre::Vector3::UNIT_Y * sin( yawAngle / 2 );
	Ogre::Vector3 qVX = localXAxis * sin( pitchAngle / 2 );

	Quaternion q = Quaternion( cos( yawAngle / 2 ), qVY.x, qVY.y, qVY.z );
	q = q * Quaternion( cos( pitchAngle / 2 ), qVX.x, qVX.y, qVX.z );

	( (CameraApp*)app )->getActiveCamera()->rotate( q );

}

void BaseFrameListener::terminateApp()
{
	keepRendering = false;
}