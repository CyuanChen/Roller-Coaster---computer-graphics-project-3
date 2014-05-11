#pragma once

#include "OgreWidget.h"
#include "ObjectControl.h"
#include "Track.h"

class RollerCoaster : public OgreWidget
{

public:
    RollerCoaster(void);
    virtual ~RollerCoaster(void);
	void renderAFrame();
	float getLastFPS();

	Ogre::String mCurrentObjName;									// save this for delete control point

	// for object control
	ObjectControl* objControl;

	// train
	bool bRun;														// enable to run the train
	float trainU;													// where the train is in parameter space
	CPV CPtrain;
	Ogre::SceneNode *trainNode;										// node for train
	float trainSpeed;
	float MAX_TRAIN_SPEED;

	// The track of the entire scene
	bool bRedraw;													// enable this flag in order to redraw the track with new type of track
	CTrack* mTrack;													// store each position of rails on track 
	Ogre::SceneNode *trackNode;										// node for track
	Ogre::ManualObject *trackObj;									// manualObject to draw track
	enum trackType { eSimpleTrack, eRoadRails ,eParallelRails };	// type of track
	trackType currTrackType;
	void drawTrack(trackType type);	
	void drawSimpleTrack();
	void drawRoadRails();
	void drawParallelRails();

	bool bReplan;													// enable this flag in order to update the track position with new type of interpolation
	enum interpolationType { eLinear, eCardinal, eCubic };			// type of interpolation
	interpolationType currItrplType;
	void planTrack(interpolationType type);
	void planLinear();
	void planCardinal();
	void planCubic();

	// Change the view of camera
	Ogre::Viewport* mViewPort;
	enum camTpye { eWorld, eTop, eTrain };
	camTpye currCamType;
	Ogre::SceneNode *mCamWorldNode;
	Ogre::SceneNode *mCamTopNode;
	Ogre::SceneNode *mCamTrainNode;

protected:

	virtual void createScene( void );
	virtual void mouseMoveEvent( QMouseEvent *event );
	virtual void mousePressEvent( QMouseEvent *event );
	virtual void mouseReleaseEvent( QMouseEvent *event );
	virtual void wheelEvent( QWheelEvent* e );
	virtual void keyPressEvent( QKeyEvent *e );
	virtual void keyReleaseEvent( QKeyEvent *e );
	virtual bool frameRenderingQueued( const Ogre::FrameEvent& evt );
	virtual bool frameEnded( const Ogre::FrameEvent& evt );
	virtual bool frameStarted( const Ogre::FrameEvent& evt );
	virtual void mouseDoubleClickEvent( QMouseEvent *e );

	void initSceneManager();
	void initCamera();
	void initTrack();
	void initTrain();
	void initLight();
	void initTerrain();

	void updateTrain( float deltatime );

	//query
	bool Querytest();

	Ogre::Vector3 mDirection;										// Value to move in the correct direction
	Ogre::Degree ROT_SCALE;
	float MOVE_SCALE;
	bool bLMouseDown, bRMouseDown, uKey,zKey,rKey;					//true if mouse buttons are held down

	Ogre::RaySceneQuery* mRayScnQuery;								//pointer to our ray scene query
	bool yKeyPressed;												//Flag for moving objects in Y direction
	bool xKeyPressed;												//Flag for moving objects in XZ direction
	Ogre::Vector3 realPoint;
	QPoint lastPos;

	// else
	Ogre::Plane mPlane;												//Invisible plane on which we do the mouse dragging

	//Ray test
	Ogre::SceneNode* snTar;
	Ogre::Entity* enTar;
};
