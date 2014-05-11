/************************************************************************/
/*																		*/
/*			Autor: Dobromir Todorov										*/
/*			Email: dobromir.todorov.todorov@gmail.com                   */
/*																		*/
/************************************************************************/
#include "OgreWidget.h"

class ObjectControl
{

public:
	enum Type
	{
		Move_Mode,
		Scale_Mode,
		Rotate_Mode,
		MoveX,
		MoveY,
		MoveZ,
		RotateX,
		RotateY,
		RotateZ,
		ScaleX,
		ScaleY,
		ScaleZ,
		ScaleXYZ,
	};
	enum QueryFlags
	{
		CONTROL_POINT  = 1<<0,
		CONTROL_WIDGET = 1<<1,
		DUMMY_PLANE	   = 1<<2,
		OTHERS		   = 1<<3
	};
	ObjectControl(Ogre::SceneManager* _mSceneMgr,Ogre::Camera* _mCamera):
	  mRaySceneQuery(0),widget(0),node(0),currentMode(Move_Mode),currntOperation(0)
	{
		mSceneMgr=_mSceneMgr;
		mCamera= _mCamera;
	}
	~ObjectControl(void);
	void init();
	void reset();
	void selectObjectForEdit(const char* idObject, char* type);
	void update();
	void switchMode(int);
	void mouseReleased();
	Ogre::String mousePressed(QPoint lastPos,float w,float h);
	Ogre::String mouseDragged(QPoint lastPos,QPoint currPos,float w,float h);
	Ogre::MovableObject* getNode(float mouseScreenX, float mouseScreenY);

protected:

	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::RaySceneQuery* mRaySceneQuery;	//pointer to our ray scene query
	Ogre::SceneNode* widget;
	Ogre::SceneNode* node;
	float MouseX,MouseY;
	int currntOperation;
	Ogre::SceneNode* planeXNode;
	Ogre::SceneNode* planeYNode;
	Ogre::SceneNode* planeZNode;
	int currentMode;
	

};