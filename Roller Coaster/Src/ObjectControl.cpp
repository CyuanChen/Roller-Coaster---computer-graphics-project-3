/************************************************************************/
/*																		*/
/*			Autor: Dobromir Todorov										*/
/*			Email: dobromir.todorov.todorov@gmail.com                   */
/*																		*/
/************************************************************************/

#include "ObjectControl.h"

//move widgets
void ObjectControl::init()
{
	using namespace Ogre;
	try
	{
		//sceneNodes
		node = mSceneMgr->createSceneNode("move_widget");
		SceneNode* node_x = node->createChildSceneNode("move_widget_x");node_x->showBoundingBox(false);
		SceneNode* node_y = node->createChildSceneNode("move_widget_y");node_y->showBoundingBox(false);
		SceneNode* node_z = node->createChildSceneNode("move_widget_z");node_z->showBoundingBox(false);

		node_x->roll(Degree(90));
		node_z->pitch(Degree(-90));

		node = mSceneMgr->createSceneNode("rotate_widget");
		SceneNode* node_rot_x = node->createChildSceneNode("rotate_widget_x");node_rot_x->showBoundingBox(false);
		SceneNode* node_rot_y = node->createChildSceneNode("rotate_widget_y");node_rot_y->showBoundingBox(false);
		SceneNode* node_rot_z = node->createChildSceneNode("rotate_widget_z");node_rot_z->showBoundingBox(false);
		node_rot_x->roll(Degree(90));
		node_rot_z->pitch(Degree(90));

		node = mSceneMgr->createSceneNode("scale_widget");
		SceneNode* node_scale_x = node->createChildSceneNode("scale_widget_x");node_scale_x->showBoundingBox(false);
		SceneNode* node_scale_y = node->createChildSceneNode("scale_widget_y");node_scale_y->showBoundingBox(false);
		SceneNode* node_scale_z = node->createChildSceneNode("scale_widget_z");node_scale_z->showBoundingBox(false);
		SceneNode* node_scale_xyz = node->createChildSceneNode("scale_widget_xyz");node_scale_xyz->showBoundingBox(false);

		node_scale_x->roll(Degree(90));
		node_scale_z->pitch(Degree(-90));

		//Materials

		MaterialPtr blue = MaterialManager::getSingleton().create("blue_widget",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		blue->setSelfIllumination(0,0,1);
		blue->setAmbient(0,0,0);
		blue->setSpecular(0,0,0,1);
		blue->setDiffuse(0.5,0.5,0.5,1);
		MaterialPtr red = MaterialManager::getSingleton().create("red_widget",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		red->setSelfIllumination(1,0,0);
		red->setAmbient(0,0,0);
		red->setSpecular(0,0,0,1);
		red->setDiffuse(0.5,0.5,0.5,1);
		MaterialPtr green = MaterialManager::getSingleton().create("green_widget",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		green->setSelfIllumination(0,1,0);
		green->setAmbient(0,0,0);
		green->setSpecular(0,0,0,1);
		green->setDiffuse(0.5,0.5,0.5,1);

		MaterialPtr yellow = MaterialManager::getSingleton().create("yellow_widget",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		yellow->setSelfIllumination(1,1,0);
		yellow->setAmbient(0,0,0);
		yellow->setSpecular(0,0,0,1);
		yellow->setDiffuse(0.5,0.5,0.5,1);

		//Entities
		Entity* entityZ = mSceneMgr->createEntity("move_widget_z", "arrow.mesh");
		Entity* entityX = mSceneMgr->createEntity("move_widget_x", "arrow.mesh");
		Entity* entityY = mSceneMgr->createEntity("move_widget_y", "arrow.mesh");

		entityZ->setQueryFlags(CONTROL_WIDGET);
		entityX->setQueryFlags(CONTROL_WIDGET);
		entityY->setQueryFlags(CONTROL_WIDGET);

		Entity* entity_rot_Z = mSceneMgr->createEntity("rotate_widget_z", "torus.mesh");
		Entity* entity_rot_X = mSceneMgr->createEntity("rotate_widget_x", "torus.mesh");
		Entity* entity_rot_Y = mSceneMgr->createEntity("rotate_widget_y", "torus.mesh");
		
		entity_rot_Z->setQueryFlags(CONTROL_WIDGET);
		entity_rot_X->setQueryFlags(CONTROL_WIDGET);
		entity_rot_Y->setQueryFlags(CONTROL_WIDGET);

		Entity* entity_scale_Z = mSceneMgr->createEntity("scale_widget_z", "ScaleArrow.mesh");
		Entity* entity_scale_X = mSceneMgr->createEntity("scale_widget_x", "ScaleArrow.mesh");
		Entity* entity_scale_Y = mSceneMgr->createEntity("scale_widget_y", "ScaleArrow.mesh");
		Entity* entity_scale_XYZ = mSceneMgr->createEntity("scale_widget_xyz", "ScaleUniform.mesh");

		entity_scale_Z->setQueryFlags(CONTROL_WIDGET);
		entity_scale_X->setQueryFlags(CONTROL_WIDGET);
		entity_scale_Y->setQueryFlags(CONTROL_WIDGET);
		entity_scale_XYZ->setQueryFlags(CONTROL_WIDGET);

		MovablePlane *mPlane;
		mPlane = new MovablePlane("dummy_plane_x");
		mPlane->normal = Vector3::UNIT_X;
		MeshManager::getSingleton().createPlane("dummy_plane_x",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,*mPlane, 3000, 3000, 1, 1, true, 1, 1, 1, Vector3::UNIT_Y);
		Ogre::Entity *dummy_X = mSceneMgr->createEntity( "dummy_plane_x", "dummy_plane_x" );
		dummy_X->setQueryFlags(DUMMY_PLANE);
		mSceneMgr->getEntity("dummy_plane_x")->setVisible(false);

		mPlane = new MovablePlane("dummy_plane_z");
		mPlane->normal = Vector3::UNIT_Z;
		MeshManager::getSingleton().createPlane("dummy_plane_z",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,*mPlane, 3000, 3000, 1, 1, true, 1, 1, 1, Vector3::UNIT_Y);
		Ogre::Entity *dummy_Z = mSceneMgr->createEntity( "dummy_plane_z", "dummy_plane_z" );
		dummy_Z->setQueryFlags(DUMMY_PLANE);
		mSceneMgr->getEntity("dummy_plane_z")->setVisible(false);

		mPlane = new MovablePlane("dummy_plane_y");
		mPlane->normal = Vector3::UNIT_Y;
		MeshManager::getSingleton().createPlane("dummy_plane_y",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,*mPlane, 3000, 3000, 1, 1, true, 1, 1, 1, Vector3::UNIT_X);
		Ogre::Entity *dummy_Y = mSceneMgr->createEntity( "dummy_plane_y", "dummy_plane_y" );
		dummy_Y->setQueryFlags(DUMMY_PLANE);
		mSceneMgr->getEntity("dummy_plane_y")->setVisible(false);

		planeXNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		planeXNode->attachObject(mSceneMgr->getEntity("dummy_plane_x"));

		planeYNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		planeYNode->attachObject(mSceneMgr->getEntity("dummy_plane_y"));

		planeZNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		planeZNode->attachObject(mSceneMgr->getEntity("dummy_plane_z"));

		//ZZ components 
		entityZ->setCastShadows(false);
		entityZ->setMaterialName("blue_widget");
		node_z->attachObject(entityZ);

		entity_rot_Z->setCastShadows(false);
		entity_rot_Z->setMaterialName("blue_widget");
		node_rot_z->attachObject(entity_rot_Z);

		entity_scale_Z->setCastShadows(false);
		entity_scale_Z->setMaterialName("blue_widget");
		node_scale_z->attachObject(entity_scale_Z);

		//XX components
		entityX->setCastShadows(false);
		entityX->setMaterialName("red_widget");
		node_x->attachObject(entityX);

		entity_rot_X->setCastShadows(false);
		entity_rot_X->setMaterialName("red_widget");
		node_rot_x->attachObject(entity_rot_X);

		entity_scale_X->setCastShadows(false);
		entity_scale_X->setMaterialName("red_widget");
		node_scale_x->attachObject(entity_scale_X);

		//YY components
		entityY->setCastShadows(false);
		entityY->setMaterialName("green_widget");
		node_y->attachObject(entityY);

		entity_rot_Y->setCastShadows(false);
		entity_rot_Y->setMaterialName("green_widget");
		node_rot_y->attachObject(entity_rot_Y);

		entity_scale_Y->setCastShadows(false);
		entity_scale_Y->setMaterialName("green_widget");
		node_scale_y->attachObject(entity_scale_Y);

		entity_scale_XYZ->setCastShadows(false);
		entity_scale_XYZ->setMaterialName("yellow_widget");
		node_scale_xyz->attachObject(entity_scale_XYZ);

		mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
	}
	catch(Ogre::Exception e)
	{
		std::cout << "An exception has occured while creating widgets: " << e.getFullDescription().c_str() << std::endl;
	}
}

Ogre::MovableObject* ObjectControl::getNode(float mouseScreenX, float mouseScreenY)
{
	using namespace Ogre;
	Ray mouseRay = mCamera->getCameraToViewportRay(mouseScreenX,mouseScreenY);
	mRaySceneQuery->setRay(mouseRay);
	mRaySceneQuery->setSortByDistance(true);
	mRaySceneQuery->setQueryMask(CONTROL_POINT|CONTROL_WIDGET|DUMMY_PLANE);
	mRaySceneQuery->setQueryTypeMask(SceneManager::ENTITY_TYPE_MASK);
	RaySceneQueryResult &result = mRaySceneQuery->execute();

	Ogre::MovableObject *closestObject = NULL;
	Real closestDistance = 100000;

	Ogre::RaySceneQueryResult::iterator rayIterator= result.begin();

	for(rayIterator; rayIterator != result.end(); rayIterator++ ) 
	{
		if ((*rayIterator).movable !=NULL && closestDistance>(*rayIterator).distance)
		{
			if( (*rayIterator).movable->getName()!="dummy_plane_x"&&
				(*rayIterator).movable->getName()!="dummy_plane_y"&&
				(*rayIterator).movable->getName()!="dummy_plane_z" )
			{
				closestObject = ( *rayIterator ).movable;
				closestDistance = ( *rayIterator ).distance;
			}
		}
	}

	mRaySceneQuery->clearResults();
	return closestObject;
}
void ObjectControl::selectObjectForEdit(const char* idObject, char* type)
{
	using namespace Ogre;
	try
	{
		widget	= mSceneMgr->getSceneNode( type );
		node	= mSceneMgr->getSceneNode( idObject );
		widget->setScale(0.3,0.3,0.3);

		Vector3 objPos = node->_getWorldAABB().getCenter();
		mSceneMgr->getRootSceneNode()->removeChild(widget);
		mSceneMgr->getRootSceneNode()->addChild(widget);

		Vector3 raytoCam = objPos-mCamera->getRealPosition();
		raytoCam.normalise();
		raytoCam *= 20;

		widget->setPosition( mCamera->getRealPosition()+raytoCam );
		widget->setVisible( true );
	}
	catch(...)
	{
		
	}
}
void ObjectControl::update()
{
	using namespace Ogre;

	if( widget && node )
	{
		Vector3 objPos = node->_getWorldAABB().getCenter();
		mSceneMgr->getRootSceneNode()->removeChild( widget );
		mSceneMgr->getRootSceneNode()->addChild( widget );

		Vector3 raytoCam = objPos-mCamera->getRealPosition();
		raytoCam.normalise();
		raytoCam *= 20;

		widget->setPosition( mCamera->getRealPosition()+raytoCam );
		widget->setVisible( true );

		planeXNode->setPosition( objPos );
		planeYNode->setPosition( objPos );
		planeZNode->setPosition( objPos );
	}
}

Ogre::String ObjectControl::mousePressed(QPoint lastPos,float w,float h)
{
	using namespace Ogre;

	float RatioX = float(lastPos.x())/w;
	float RatioY = float(lastPos.y())/h;

	MovableObject* nodeM = getNode(RatioX,RatioY); 

	if( nodeM != NULL )
	{
		String name = nodeM->getParentSceneNode()->getName();

		if ( name == "move_widget_x" )
		{
			Vector3 objPos = Vector3(node->_getWorldAABB().getCenter());
			planeXNode->setPosition(objPos);
			planeYNode->setPosition(objPos);
			planeZNode->setPosition(objPos);
			currntOperation=MoveX;                
		}
		else if ( name == "move_widget_y" )
		{
			Vector3 objPos = Vector3(node->_getWorldAABB().getCenter());			
			planeXNode->setPosition(objPos);
			planeYNode->setPosition(objPos);
			planeZNode->setPosition(objPos);
			currntOperation=MoveY; 
		}
		else if ( name == "move_widget_z" )
		{
			Vector3 objPos = Vector3(node->_getWorldAABB().getCenter());						
			planeXNode->setPosition(objPos);
			planeYNode->setPosition(objPos);
			planeZNode->setPosition(objPos);
			currntOperation=MoveZ;                 
		}
		else if ( name == "rotate_widget_x"  ) currntOperation = RotateX;     
		else if ( name == "rotate_widget_y"  ) currntOperation = RotateY;
		else if ( name == "rotate_widget_z"  ) currntOperation = RotateZ;
		else if ( name == "scale_widget_x"   ) currntOperation = ScaleX;
		else if ( name == "scale_widget_y"   ) currntOperation = ScaleY;
		else if ( name == "scale_widget_z"   ) currntOperation = ScaleZ;
		else if ( name == "scale_widget_xyz" ) currntOperation = ScaleXYZ;
		else 
		{
			if		(currentMode==Move_Mode  ) selectObjectForEdit(name.c_str(),"move_widget"  );
			else if	(currentMode==Rotate_Mode) selectObjectForEdit(name.c_str(),"rotate_widget");
			else if	(currentMode==Scale_Mode ) selectObjectForEdit(name.c_str(),"scale_widget" );
		}

		return name;
	}
	else
	{
		reset();
		return "";
	}
}

void ObjectControl::mouseReleased()
{
	currntOperation = 0;
}

Ogre::String ObjectControl::mouseDragged (QPoint lastPos,QPoint currPos,float w,float h) 
{
	using namespace Ogre;

	float RatioX = float(lastPos.x())/w;
	float RatioY = float(lastPos.y())/h;

	Ray mouseRay = mCamera->getCameraToViewportRay(RatioX,RatioY);
	mRaySceneQuery->setRay(mouseRay);
	mRaySceneQuery->setSortByDistance(true);
	mRaySceneQuery->setQueryMask(DUMMY_PLANE);
	mRaySceneQuery->setQueryTypeMask(SceneManager::ENTITY_TYPE_MASK);
	RaySceneQueryResult &result = mRaySceneQuery->execute();

	Ogre::MovableObject *closestObject = NULL;
	Real closestDistance = 100000;

	Ogre::RaySceneQueryResult::iterator rayIterator= result.begin();

	for( rayIterator; rayIterator != result.end(); rayIterator++ ) 
	{
		if ( (*rayIterator).movable !=NULL && closestDistance>(*rayIterator).distance )
		{
			closestObject = ( *rayIterator ).movable;
			Ogre::String name = closestObject->getName();

			Ogre::Vector3 newpos	= Ogre::Vector3::ZERO;
			float rotateFactor		= 0.0f;
			float scaleFactor		= 0.0f;

			switch( currntOperation )
			{
				//==== 處理物體平移 ====//
				case MoveX:
					if ( name != "dummy_plane_y" ) continue;
					newpos = mouseRay.getPoint((*rayIterator).distance);
					node->setPosition(newpos.x,node->getPosition().y,node->getPosition().z);
					break;
				case MoveY:
					if( name == "dummy_plane_y" ) continue; 
					newpos = mouseRay.getPoint((*rayIterator).distance);
					node->setPosition(node->getPosition().x,newpos.y-node->_getWorldAABB().getHalfSize().y,node->getPosition().z);
					break;
				case MoveZ:
					if( name != "dummy_plane_y" ) continue; 
					newpos = mouseRay.getPoint((*rayIterator).distance);
					node->setPosition(node->getPosition().x,node->getPosition().y,newpos.z);				
					break;

				//==== 處理物體旋轉 ====//
				case RotateX:
					rotateFactor = 1*(currPos.y()-lastPos.y());
					node->pitch(Ogre::Degree(rotateFactor),Node::TS_WORLD);
					break;
				case RotateY:
					rotateFactor = 1*(currPos.x()-lastPos.x());
					node->yaw(Ogre::Degree(rotateFactor),Node::TS_WORLD);
					break;
				case RotateZ:
					rotateFactor = 1*(currPos.y()-lastPos.y());
					node->roll(Ogre::Degree(rotateFactor),Node::TS_WORLD);
					break;

				//==== 處理物體縮放 ====//
				case ScaleX:
					scaleFactor = 1+0.001*(currPos.x()-lastPos.x());
					node->scale(scaleFactor,1,1);
					break;
				case ScaleY:
					scaleFactor = 1-0.001*(currPos.y()-lastPos.y());
					node->scale(1,scaleFactor,1);
					break;
				case ScaleZ:
					scaleFactor = 1+0.001*(currPos.x()-lastPos.x());
					node->scale(1,1,scaleFactor);
					break;
				case ScaleXYZ:
					scaleFactor = 1+0.001*(currPos.x()-lastPos.x());
					node->scale(scaleFactor,scaleFactor,scaleFactor);
					break;
			}

			update();
		}	
	}
	mRaySceneQuery->clearResults();

	return (node==NULL)?"":node->getName();
}
void ObjectControl::switchMode(int mode)
{
	currentMode = mode;

	if(widget)
	{	
		mSceneMgr->getRootSceneNode()->removeChild(widget);
		char* type; 

		if		( mode == Move_Mode  ) type="move_widget";
		else if	( mode == Rotate_Mode) type="rotate_widget";
		else if	( mode == Scale_Mode ) type="scale_widget";

		widget = mSceneMgr->getSceneNode(type);
		widget->setScale(0.3,0.3,0.3);
		update();
	}
}

void ObjectControl::reset()
{
	if( widget ) mSceneMgr->getRootSceneNode()->removeChild(widget);
	node = NULL;
}
