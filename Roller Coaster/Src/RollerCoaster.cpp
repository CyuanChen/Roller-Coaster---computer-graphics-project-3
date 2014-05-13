#include "RollerCoaster.h"
#include "AppMain.h"
#include "OgreMovableObject.h"
#include "Matrix.h"
#include <stdio.h>

//-------------------------------------------------------------------------------------
RollerCoaster::RollerCoaster(void):
bLMouseDown(false),
bRMouseDown(false),
mCurrentObjName(""),
mRayScnQuery(0),
yKeyPressed(false),
xKeyPressed(false),
uKey(false),
zKey(false),
rKey(false),
bRedraw(false),
bReplan(false)
{
	MOVE_SCALE			= 250;
	ROT_SCALE			= Ogre::Degree(30.0f);
	mDirection			= Ogre::Vector3::ZERO;
	trainSpeed			= 10;
	MAX_TRAIN_SPEED		= 20;
	setFocusPolicy( Qt::ClickFocus );
}

//-------------------------------------------------------------------------------------
RollerCoaster::~RollerCoaster( void )
{

}

//-------------------------------------------------------------------------------------
void RollerCoaster::initSceneManager()
{
	mSceneMgr = mRoot->createSceneManager( Ogre::ST_GENERIC );
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::MovableObject::setDefaultQueryFlags(ObjectControl::OTHERS);
}

//-------------------------------------------------------------------------------------
void RollerCoaster::initTrack()
{
	bReplan = true;
	mTrack = new CTrack( mSceneMgr );
	trackNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "trackNode" );
	trackObj = mSceneMgr->createManualObject( "trackObj" );
	trackNode->attachObject( trackObj );

	currTrackType = eSimpleTrack;
	currItrplType = eLinear;
}

//-------------------------------------------------------------------------------------
void RollerCoaster::initTrain()
{
	bRun = false;
	trainU = 0.0;
	trainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* ent = mSceneMgr->createEntity( "ogrehead.mesh" );
	trainNode->attachObject( ent );
	trainNode->setScale( 0.1, 0.1, 0.1 );
}
//-------------------------------------------------------------------------------------
bool RollerCoaster::Querytest()
{
	Ogre::RaySceneQuery *mQuery = mSceneMgr->createRayQuery(Ogre::Ray());
	Ogre::Vector3 direction =trainNode->getPosition()+
		trainNode->_getDerivedOrientation()*Ogre::Vector3::UNIT_Z;
	
	Ogre::Ray objRay( trainNode->getPosition(),direction);
 
	mQuery->setRay(objRay);
 
	Ogre::RaySceneQueryResult &result = mQuery->execute();
	Ogre::RaySceneQueryResult::iterator iter = result.begin();
 
	for (iter; iter!=result.end(); iter++)
	{
		if((*iter).movable->getName()== "mTarget")
		{
			return true;
		}
	}
 
	mQuery->clearResults();
	return false;
}
//-------------------------------------------------------------------------------------
void RollerCoaster::initCamera()
{
	//==== 使用 SceneManager 創建相機物件 ====//
	mCamera = mSceneMgr->createCamera( "PlayerCam" );

	//==== 設定相機的 Near plane 及 Far plane ====//
	mCamera->setNearClipDistance( 5 );
	mCamera->setFarClipDistance( 5000 );

	mViewport = mWindow->addViewport( mCamera );
	mViewport->setBackgroundColour( Ogre::ColourValue(0.5,0.5,0.5) );

	//==== 創建三種形式的相機 SceneNode ====//

	//** 第一種:世界座標下的相機 **//
	currCamType = eWorld;
	mCamWorldNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "CamWorldNode", Ogre::Vector3(0, 100, 100) );
	mCamWorldNode->pitch( Ogre::Degree(-30) );
	mCamWorldNode->attachObject( mCamera );

	//** 第二種:由上往下俯瞰的相機 **//
	mCamTopNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "CamTopNode", Ogre::Vector3(0,600,0) );
	mCamTopNode->pitch( Ogre::Degree(-90) );

	//** 第三種:以火車為視角的相機 **//
	mCamTrainNode = trainNode->createChildSceneNode( "CamTrainNode", Ogre::Vector3(0, 25, 46) );
	mCamTrainNode->lookAt( Ogre::Vector3(0, 0, 300), Ogre::Node::TS_LOCAL );
}

//-------------------------------------------------------------------------------------
void RollerCoaster::initLight()
{
	//==== 設置環境光 ====//
	mSceneMgr->setAmbientLight( Ogre::ColourValue(0.5, 0.5, 0.5) );

	//==== 設定陰影型態 ====//
	mSceneMgr->setShadowTechnique( Ogre::SHADOWTYPE_STENCIL_ADDITIVE );

	//==== 加入第一個燈源 ====//
	Ogre::Light* light = mSceneMgr->createLight( "MainLight" );
	light->setPosition( 120, 1000, -250 );
	light->setCastShadows( true );
}

//-------------------------------------------------------------------------------------
void RollerCoaster::initTerrain()
{
	//==== 用一個平面當作地形 ====//
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane(
		"ground", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 
		500, 500, 20, 20, true, 1, 5, 5,
		Ogre::Vector3::UNIT_Z
	);

	Ogre::Entity* entGround = mSceneMgr->createEntity( "GroundEntity", "ground" );
	mSceneMgr->getRootSceneNode()->createChildSceneNode("groundNode")->attachObject( entGround );
	entGround->setMaterialName( "Grass" );
	entGround->setCastShadows( false );
}

//-------------------------------------------------------------------------------------
void RollerCoaster::createScene( void )
{
	initSceneManager();
	initTrack();
	initTrain();
	initCamera();
	initLight();
	initTerrain();

	objControl = new ObjectControl(mSceneMgr, mCamera);
	objControl->init();
	mRayScnQuery = mSceneMgr->createRayQuery(Ogre::Ray());

	//Ray Query example
	snTar = mSceneMgr->getRootSceneNode()->createChildSceneNode("child");
	Ogre::Entity* temp = mSceneMgr->createEntity("ogrehead.mesh");
	enTar = temp->clone("mTarget");
	snTar->attachObject(enTar);
	snTar->setPosition(0, 0, 50);
	snTar->setScale(0.1, 0.1, 0.1);
}

//-------------------------------------------------------------------------------------
bool RollerCoaster::frameRenderingQueued( const Ogre::FrameEvent& evt )
{
	if(Querytest())
	{
		trainNode->translate(trainNode->_getDerivedOrientation() *Ogre::Vector3::UNIT_Z *evt.timeSinceLastFrame);
	}

	//==== 更新相機位置 ====//
	if( mDirection!=Ogre::Vector3(0,0,0) && currCamType == eWorld )
	{
		mCamWorldNode->translate( mDirection * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL );
		objControl->update();
	}
	if ( bReplan )
	{
		planTrack( currItrplType );
	}
	if( bRedraw )
	{
		drawTrack( currTrackType );
	}

	updateTrain( evt.timeSinceLastFrame );

	return true;
}

//-------------------------------------------------------------------------------------
void RollerCoaster::updateTrain( float deltatime )
{
	//==== 如果現在是暫停狀態或者軌道是空的則什麼也不做 ====//
	if( !bRun || CPtrain.empty() ) return;

	float tmpU = trainU;

	trainU += 0.01f * trainSpeed * deltatime;

	if ( trainU > 1.0f ) trainU = 0.0f;

	// Train Head position
	int idx_pre = tmpU * (CPtrain.size() - 1);
	int idx_cur = trainU * (CPtrain.size() - 1);

	Ogre::Vector3 pos( CPtrain[idx_cur].pos );
	trainNode->setPosition(pos);

	if (idx_pre != idx_cur) 
	{
		// Train Head orientation 火車頭位置移動
		Ogre::Vector3 front, up, left;
		front = CPtrain[idx_cur].pos - CPtrain[idx_pre].pos;
		up = CPtrain[idx_cur].orient;
		left = up.crossProduct(front);
		up = front.crossProduct(left);

		front.normalise();
		up.normalise();
		left.normalise();

		Ogre::Quaternion qq(left, up, front);
		trainNode->setOrientation(qq);	
	}
}

//-------------------------------------------------------------------------------------
void RollerCoaster::mouseMoveEvent( QMouseEvent *event )
{
	if( bLMouseDown )
	{
		mCurrentObjName = objControl->mouseDragged(
			lastPos,
			event->pos(),
			mCamera->getViewport()->getActualWidth(), 
			mCamera->getViewport()->getActualHeight()
		);

		if( !mCurrentObjName.empty() )
		{
			Ogre::SceneNode *currObj = mSceneMgr->getSceneNode(mCurrentObjName);
			if (currObj)
			{
				bReplan = true;

				mTrack->mMove(currObj->getName(), currObj->getPosition());
				mTrack->mRotate(currObj->getName(), currObj->getOrientation().yAxis());
			}
		}
	}
	//==== 當按下滑鼠右鍵 ====//
	if( event->buttons().testFlag(Qt::RightButton) && lastPos != invalidMousePoint )
	{
		if( currCamType != eWorld ) return;

		mCamWorldNode = mCamera->getParentSceneNode();

		Ogre::Degree rotX(0);
		Ogre::Degree rotY(0);
		int dx = event->pos().x()-lastPos.x();
		int dy = event->pos().y()-lastPos.y();
		rotX += Ogre::Degree(-dx * 0.0025f * ROT_SCALE);		// Rotate camera horizontaly
		rotY += Ogre::Degree(-dy * 0.0025f * ROT_SCALE);		// Rotate camera vertical

		mCamWorldNode->yaw	( rotX, Ogre::Node::TS_WORLD );
		mCamWorldNode->pitch( rotY, Ogre::Node::TS_LOCAL );

		objControl->update();
	}

	lastPos = event->pos();
}

//-------------------------------------------------------------------------------------
void RollerCoaster::mousePressEvent( QMouseEvent *event )
{
	if( event->buttons().testFlag(Qt::LeftButton) )
	{
		lastPos = event->pos();

		bLMouseDown = true;

		mCurrentObjName = objControl->mousePressed( 
			lastPos, 
			mCamera->getViewport()->getActualWidth(), 
			mCamera->getViewport()->getActualHeight() 
		);
	}
}

//-------------------------------------------------------------------------------------
void RollerCoaster::mouseReleaseEvent( QMouseEvent *event )
{
	if( !event->buttons().testFlag(Qt::LeftButton) )
	{
		bLMouseDown = false;
		objControl->mouseReleased();
	}
}

//-------------------------------------------------------------------------------------
void RollerCoaster::wheelEvent( QWheelEvent* e )
{
	if( currCamType == eWorld )
	{
		mCamWorldNode = mCamera->getParentSceneNode();
		mCamWorldNode->translate( 0, 0, -(e->delta()/10.0f), Ogre::Node::TS_LOCAL );

		objControl->update();
	}
}

//-------------------------------------------------------------------------------------
void RollerCoaster::keyPressEvent( QKeyEvent *e )
{
	if( e->isAutoRepeat() ) return;

	switch( e->key() )
	{
		case Qt::Key_W:
		case Qt::Key_Up:
			mDirection.z = -MOVE_SCALE;
			break;

		case Qt::Key_S:
		case Qt::Key_Down:
			mDirection.z = MOVE_SCALE;
			break;

		case Qt::Key_A:
		case Qt::Key_Left:
			mDirection.x = -MOVE_SCALE;
			break;

		case Qt::Key_D:
		case Qt::Key_Right:
			mDirection.x = MOVE_SCALE;
			break;

		case Qt::Key_E:
		case Qt::Key_PageDown:
			mDirection.y = -MOVE_SCALE;
			break;

		case Qt::Key_Q:
		case Qt::Key_PageUp:
			mDirection.y = MOVE_SCALE;
			break;

		case Qt::Key_F1:
			AppMain::Instance->ToggleMenuBar();
			break;

		case Qt::Key_F2:
			AppMain::Instance->ToggleToolBar();
			break;

		case Qt::Key_F3:
			AppMain::Instance->ToggleStatusBar();
			break;

		case Qt::Key_F4:
			AppMain::Instance->TogglePanel();
			break;

		case Qt::Key_F5:
			bRun = !bRun;
			break;

		case Qt::Key_Escape:
			QApplication::quit();
			break;

		case Qt::Key_Z:
			objControl->switchMode( ObjectControl::Move_Mode );
			break;

		case Qt::Key_X:
			objControl->switchMode( ObjectControl::Rotate_Mode );
			break;

		case Qt::Key_C:
			objControl->switchMode( ObjectControl::Scale_Mode );
			break;
	}
}

//-------------------------------------------------------------------------------------
void RollerCoaster::keyReleaseEvent( QKeyEvent *e )
{
	if( e->isAutoRepeat() ) return;
	
	switch( e->key() )
	{
		case Qt::Key_W:
		case Qt::Key_Up:
			mDirection.z = 0;
			break;

		case Qt::Key_S:
		case Qt::Key_Down:
			mDirection.z = 0;
			break;

		case Qt::Key_A:
		case Qt::Key_Left:
			mDirection.x = 0;
			break;
		
		case Qt::Key_D:
		case Qt::Key_Right:
			mDirection.x = 0;
			break;

		case Qt::Key_E:
		case Qt::Key_PageDown:
			mDirection.y = 0;
			break;

		case Qt::Key_Q:
		case Qt::Key_PageUp:
			mDirection.y = 0;
			break;
	}
}

//-------------------------------------------------------------------------------------
bool RollerCoaster::frameEnded( const Ogre::FrameEvent& evt )
{
	return true;
}

//-------------------------------------------------------------------------------------
bool RollerCoaster::frameStarted( const Ogre::FrameEvent& evt )
{
	return true;
}

//-------------------------------------------------------------------------------------
void RollerCoaster::mouseDoubleClickEvent( QMouseEvent *e )
{

}

void RollerCoaster::drawTrack( trackType type )
{
	// clear the track that have been draw before
	trackObj->clear();

	switch (type)
	{
	case eSimpleTrack:
		drawSimpleTrack();
		break;

	case eRoadRails:
		drawRoadRails();
		break;

	case eParallelRails:
		drawParallelRails();
		break;
	}

	bRedraw = false;
}

void RollerCoaster::drawSimpleTrack()
{
	trackObj->begin( "BaseWhiteNoLighting", Ogre::RenderOperation::OT_POINT_LIST );

	for ( int i=0; i<CPtrain.size(); i++ )
	{
		int j = i + 1;
		if ( j == CPtrain.size() ) j = 0;
		
		trackObj->position(CPtrain[i].pos);
	}
	
	trackObj->end();
}

void RollerCoaster::drawParallelRails()
{
	
}

void RollerCoaster::drawRoadRails()
{

}

void RollerCoaster::planTrack( interpolationType type )
{
	CPtrain.clear();

	switch (type)
	{
	case eLinear:
		planLinear();
		break;

	case eCardinal:
		planCardinal();
		break;

	case eCubic:
		planCubic();
		break;
	}

	bReplan = false;
	bRedraw = true;
}

void RollerCoaster::planLinear()
{

	for (int i=0; i<mTrack->getSize(); i++)
	{
		int idx_Start = i, idx_End = i+1;
		if (idx_End >= mTrack->getSize()) idx_End = 0;

		Ogre::Vector3 startPos( mTrack->getItem(idx_Start).pos );
		Ogre::Vector3 endPos( mTrack->getItem(idx_End).pos );

		Ogre::Vector3 startOri( mTrack->getItem(idx_Start).orient );
		Ogre::Vector3 endOri( mTrack->getItem(idx_End).orient );

		Ogre::Vector3 temp = startPos;

		
		float segment = 1000;

		for (float j=0.0f; j<segment; j++)
		{
			Ogre::Vector3 nowPos( startPos + (endPos - startPos) * j / segment );
			Ogre::Vector3 nowOri( startOri + (endOri - startOri) * j / segment );

			// no arg-length version
			CPtrain.push_back(ControlPoint(nowPos, nowOri));
			temp = nowPos;
		}
	}
}

void RollerCoaster::planCardinal()
{	
	using namespace Ogre;
	for (int i=0; i<mTrack->getSize(); i++)
	{
		int idx[4];
		for (int k = 0; k < 4; k++) idx[k] = i+k;

		//making loop
		for (int k = 0; k < 4; k++)
		{
			if (idx[k] >= mTrack->getSize()) idx[k] -= mTrack->getSize();
		}

		Vector3 Pos[4],Ori[4]; 

		for (int k = 0; k < 4; k++)
		{
			Pos[k] = Vector3( mTrack->getItem(idx[k]).pos );
			Ori[k] = Vector3( mTrack->getItem(idx[k]).orient );
		}


		float M[4][4] = 
		{
			{-1.0/2.0,  1.0, -1.0/2.0, 0},
			{ 3.0/2.0, -5.0/2.0, 0, 1.0},
			{-3.0/2.0, 2.0 , 1.0/2.0, 0},
			{1.0/2.0, -1.0/2.0, 0, 0, }
		};

		// Vector3 temp = startPos;		
				
		float segment = 1000;

		// the parameter "t" is j/segment
		for (float j=0.0f; j<segment; j++)
		{
			float T[4][1] = 
			{
				(j/segment) * (j/segment) * (j/segment),
				(j/segment) * (j/segment),
				(j/segment),
				1
			};

			float MT[4][1] = {0};

			mulMatrix441(M, T, MT);

			Vector3 nowPos(Vector3::ZERO);
			Vector3 nowOri(Vector3::ZERO);

			for (int l = 0; l < 4; l++)
			{
				nowPos += Pos[l] * MT[l][0];
				nowOri += Ori[l] * MT[l][0];
			}

			CPtrain.push_back(ControlPoint(nowPos, nowOri));

		}
	}
}

void RollerCoaster::planCubic()
{
	using namespace Ogre;
	for (int i=0; i<mTrack->getSize(); i++)
	{
		int idx[4];
		for (int k = 0; k < 4; k++) idx[k] = i+k;

		//making loop
		for (int k = 0; k < 4; k++)
		{
			if (idx[k] >= mTrack->getSize()) idx[k] -= mTrack->getSize();
		}

		Vector3 Pos[4],Ori[4]; 

		for (int k = 0; k < 4; k++)
		{
			Pos[k] = Vector3( mTrack->getItem(idx[k]).pos );
			Ori[k] = Vector3( mTrack->getItem(idx[k]).orient );
		}


		float M[4][4] = 
		{
			{-1, 3, -3, 1},
			{3, -6, 0, 4},
			{-3, 3, 3, 1},
			{1, 0, 0, 0}
		};

		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				M[j][k] /= 6.0;

		// Vector3 temp = startPos;		
				
		float segment = 1000;

		// the parameter "t" is j/segment
		for (float j=0.0f; j<segment; j++)
		{
			float T[4][1] = 
			{
				(j/segment) * (j/segment) * (j/segment),
				(j/segment) * (j/segment),
				(j/segment),
				1
			};

			float MT[4][1] = {0};

			mulMatrix441(M, T, MT);

			Vector3 nowPos(Vector3::ZERO);
			Vector3 nowOri(Vector3::ZERO);

			for (int l = 0; l < 4; l++)
			{
				nowPos += Pos[l] * MT[l][0];
				nowOri += Ori[l] * MT[l][0];
			}

			CPtrain.push_back(ControlPoint(nowPos, nowOri));

		}
	}
}

void RollerCoaster::renderAFrame()
{
	if( mWindow )
	{
		mRoot->_fireFrameStarted();
		mRoot->_updateAllRenderTargets();
		mRoot->_fireFrameEnded();
	}
}

float RollerCoaster::getLastFPS()
{
	return mWindow->getLastFPS();
}

