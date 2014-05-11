#ifndef OGREWIDGET_H
#define OGREWIDGET_H

#include <QtGui>
#include <QtWidgets/QtWidgets>
#include <Ogre.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include <stdio.h>

#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

class OgreWidget : public QWidget,public Ogre::FrameListener
{
	Q_OBJECT

public:
	OgreWidget(QWidget *parent = 0);
	~OgreWidget();
	bool mShutDown;
	Ogre::Camera *mCamera;

public slots:
	// Override QWidget::paintEngine to return NULL
	QPaintEngine* paintEngine() const; // Turn off QTs paint engine for the Ogre widget.

protected:
	virtual void keyPressEvent(QKeyEvent *e);
	virtual void keyReleaseEvent(QKeyEvent *e);
	virtual void moveEvent(QMoveEvent *e);
	virtual void mouseDoubleClickEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);

	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
	virtual void paintEvent(QPaintEvent *e);
	virtual void resizeEvent(QResizeEvent *e);
	virtual void showEvent(QShowEvent *e);
	virtual void wheelEvent(QWheelEvent *e);
	virtual void createScene(void)=0;
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:
	void initOgreSystem();
	void setupNLoadResources();
	void startApp();
	static const QPoint invalidMousePoint;

private:
	static const Ogre::Real turboModifier;
	

protected:
	Ogre::Root          *mRoot;
	Ogre::SceneManager  *mSceneMgr;
	Ogre::RenderWindow  *mWindow;
	Ogre::Viewport      *mViewport;
	
	QPoint oldPos;
};

#endif OGREWIDGET_H
