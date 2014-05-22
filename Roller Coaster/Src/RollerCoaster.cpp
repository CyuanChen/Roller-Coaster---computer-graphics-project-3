#include "RollerCoaster.h"
#include "AppMain.h"
#include "OgreMovableObject.h"
#include "Matrix.h"
#include <stdio.h>
#include <string>
#include <vector>

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
	trainSpeed			= 7;
	MAX_TRAIN_SPEED		= 20;
	setFocusPolicy( Qt::ClickFocus );
	tension             = 0;
	MAX_TENSION_VALUE   = 10;
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
	roomNode  = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	// Ogre::Entity* ent = mSceneMgr->createEntity( "ogheadre.mesh" );
	Ogre::Entity* ent = mSceneMgr->createEntity( "trainnode.mesh" );
	Ogre::Entity* roomEntity = mSceneMgr->createEntity("childroom.mesh");

	trainNode->attachObject( ent );
	roomNode->attachObject(roomEntity);

	// trainNode->setScale( 0.1, 0.1, 0.1 );
	trainNode->setScale(0.5, 0.5, 0.5);
	trainNode->yaw(Ogre::Degree(-90), Ogre::Node::TS_LOCAL);

	roomNode->setScale(25, 25, 25);
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
	mCamTrainNode = trainNode->createChildSceneNode( "CamTrainNode", Ogre::Vector3(0, 15, -70) );
	mCamTrainNode->lookAt( Ogre::Vector3(0, 0, 100), Ogre::Node::TS_LOCAL );
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
	light->setDiffuseColour(0.953, 0.635, 0.196);

	Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 1, 0));
 
    pointLight->setDiffuseColour(0.8, 0.8, 0.8);
    pointLight->setSpecularColour(0.6, 0.5, 0.6);

	// Let's play light magic Yeah
	Ogre::Light* spotlight = mSceneMgr->createLight("spotlight");
	spotlight->setType(Ogre::Light::LT_SPOTLIGHT);
	spotlight->setPosition(0, 10, 0);
	spotlight->setDiffuseColour(0.953, 0.635, 0.196);
    // spotlight->setSpecularColour(0.953, 0.635, 0.196);
    spotlight->setDirection(0, -1, 0);
    spotlight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
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
	// entGround->setMaterialName( "Grass" );
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
	// snTar = mSceneMgr->getRootSceneNode()->createChildSceneNode("child");
	// Ogre::Entity* temp = mSceneMgr->createEntity("ogrehead.mesh");
	// enTar = temp->clone("mTarget");
	// snTar->attachObject(enTar);
	// snTar->setPosition(0, 0, 50);
	// snTar->setScale(0.1, 0.1, 0.1);
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

	float oldspeed=15;
	float height= trainNode->getPosition().y;
	
	trainSpeed=oldspeed-sqrt(4.9*height);
	if(trainSpeed>MAX_TRAIN_SPEED)
		trainSpeed = MAX_TRAIN_SPEED;
	if(trainSpeed<5)
		trainSpeed = 5;

	trainU += 0.01f * trainSpeed * deltatime;

	if ( trainU > 1.0f ) trainU = 0.0f;

	// Train Head position
	int idx_pre = tmpU * (CPtrain.size() - 1);
	int idx_cur = trainU * (CPtrain.size() - 1);

	Ogre::Vector3 pos( CPtrain[idx_cur].pos );

	// fix trainmesh position
	Ogre::Vector3 newPos(pos.x+1, pos.y-0.5, pos.z);

	trainNode->setPosition(newPos);

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

	// use removeAndDestroyAllChildren to clear all objects under trackNode	
	trackNode->removeAndDestroyAllChildren();

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
		// useless code, uhh?
		// int j = i + 1;
		// if ( j == CPtrain.size() ) j = 0;
		
		trackObj->position(CPtrain[i].pos);
	}
	
	trackObj->end();
}

void RollerCoaster::drawParallelRails()
{
	// CPtrain[i].orient.y as UP normal
	// std::vector<Cuboid> CBList;
	trackObj->begin( "BaseWhiteNoLighting", Ogre::RenderOperation::OT_POINT_LIST );

	for (int i = 0; i < CPtrain.size(); i++)
	{
		trackObj->position(CPtrain[i].pos);

		if ((i % 15) != 0) continue;
		// set Strings for naming objects
		std::stringstream num;
		num << i+1;

		std::string railsName = "Rails" + num.str();

		// // New Child SceneNode under trackNode
		// Ogre::SceneNode *railsNode = 
		// 		trackNode->createChildSceneNode(railsNodeName, CPtrain[i].pos);

		Ogre::SceneNode *railsNode = 
			trackNode->createChildSceneNode(railsName, CPtrain[i].pos);
		// Ogre::SceneNode *railsNodeL = 
		// 	trackNode->createChildSceneNode(railsLName, CPtrain[i].pos);

		// Create Cuboids
		Cuboid* temp = new Cuboid(railsName);

		Ogre::Vector3 front, up, left;

		if (i < CPtrain.size()-1)
		{
			
			front = CPtrain[i+1].pos - CPtrain[i].pos;
			up = CPtrain[i].orient;
			left = up.crossProduct(front);
			up = front.crossProduct(left);
			CPtrain[i].orient = up;
		}
		else break;
		
		front.normalise();
		up.normalise();
		left.normalise();

		std::cout << "front: ";
		printVector(front);

		std::cout << "left: ";
		printVector(left);

		// Why!!???? = =, okay it's computer graphics.
		// Setup Cuboids
		temp->setCorners(front, -left, up, Ogre::Vector3(0.1, 0.8, 0.1));
		// tempL->setCorners(front, -left, up, Ogre::Vector3(10, 10, 10));
		
		// std::cout << "x = " << CPtrain[i].orient.x << "y = " << CPtrain[i].orient.y << "z = " << CPtrain[i].orient.z << std::endl;

		railsNode->attachObject(temp);
		// railsNodeL->attachObject(tempL);

		// railsNodeR->translate(-left);
		// railsNodeL->translate( left);

		// Ogre::Radian nighty = Ogre::Radian(Ogre::Math::DegreesToRadians(90));
		Ogre::Radian fortyfive = Ogre::Radian(Ogre::Math::DegreesToRadians(-45));
		railsNode->yaw(fortyfive, Ogre::Node::TS_LOCAL);


		// railsNodeR->pitch(nighty, Ogre::Node::TS_LOCAL);
		// railsNodeL->pitch(nighty, Ogre::Node::TS_LOCAL);

		// railsNodeR->roll(fortyfive, Ogre::Node::TS_LOCAL);
		// railsNodeL->roll(fortyfive, Ogre::Node::TS_LOCAL);

	}

	trackObj->end();

}

void RollerCoaster::drawRoadRails()
{
	trackObj->begin( "BaseWhiteNoLighting", Ogre::RenderOperation::OT_POINT_LIST );

	for (int i = 0; i < CPtrain.size(); i++)
	{
		trackObj->position(CPtrain[i].pos);

		if ((i % 7) != 0) continue;
		// set Strings for naming objects
		std::stringstream num;
		num << i+1;

		std::string railsName = "Rails" + num.str();
		std::string railsNamet = "tRails" + num.str();

		// // New Child SceneNode under trackNode
		Ogre::SceneNode *railsNode = 
			trackNode->createChildSceneNode(railsName, CPtrain[i].pos);
		Ogre::SceneNode *railsNodet = 
			trackNode->createChildSceneNode(railsNamet, CPtrain[i].pos);			

		// Create Cuboids
		Cuboid* temp = new Cuboid(railsName);
		Cuboid* tempt = new Cuboid(railsNamet);

		Ogre::Vector3 front, up, left;

		if (i < CPtrain.size()-1)
		{
			
			front = CPtrain[i+1].pos - CPtrain[i].pos;
			up = CPtrain[i].orient;
			left = up.crossProduct(front);
			up = front.crossProduct(left);
		}
		else break;
		
		front.normalise();
		up.normalise();
		left.normalise();

		// Setup Cuboids
		temp->setCorners(front, -left, up, Ogre::Vector3(0.8, 0.04, 0.04));
		tempt->setCorners(front, -left, up, Ogre::Vector3(0.8, 0.04, 0.04));

		railsNode->attachObject(temp);
		railsNodet->attachObject(tempt);

		railsNode->translate(left);
		railsNodet->translate(-left);		

		// railsNode->translate(-left);

		Ogre::Radian fortyfive = Ogre::Radian(Ogre::Math::DegreesToRadians(-45));
		railsNode->yaw(fortyfive, Ogre::Node::TS_LOCAL);
		railsNodet->yaw(fortyfive, Ogre::Node::TS_LOCAL);

	}

	trackObj->end();

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
		for (int k = 0; k < 4; k++) 
		{
			idx[k] = i+k;
			//make loop
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
			{-1, 2, -1, 0},
			{3, -5, 0, 2},
			{-3, 4, 1, 0},
			{1, -1, 0, 0}
		};

		// float t = tension;

		// float M[4][4] = 
		// {
		// 	{ -t,  2-t,  t-2 ,  t },
		// 	{2*t,  t-3,  3-2*t, -t },
		// 	{ -t,   0 ,   t  ,  0 },
		// 	{  0,   1 ,   0  ,  0 }
		// };

		// float sum = 0;
		// for (int j = 0; j < 4; j++)
		// {
		// 	for (int k = 0; k < 4; k++)
		// 	{
		// 		sum += M[j][k];		
		// 	}
		// }

		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				M[j][k] /= 2.0;		
			}
		}
					
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
		for (int k = 0; k < 4; k++) 
		{
			idx[k] = i+k;
			//make loop
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
		float t = tension;
		// printf("tension = %f\n", tension);

		// float M[4][4] = 
		// {
		// 	{ -t,  12-9*t,  9*t-12 ,  t },
		// 	{3*t,  12*t-18,  18-15*t, 0 },
		// 	{-3*t,   0 ,   3*t  ,  0 },
		// 	{  t,   6-2*t ,   t  ,  0 }
		// };		

		// float sum = 0;
		// for (int j = 0; j < 4; j++)
		// {
		// 	for (int k = 0; k < 4; k++)
		// 	{
		// 		sum += M[j][k];		
		// 	}
		// }

		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				M[j][k] /= 6.0;	
				printf("%.2f\t", M[j][k]);	
			}
			printf("\n");
		}
		//printf("sum = %d\n", sum);

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

