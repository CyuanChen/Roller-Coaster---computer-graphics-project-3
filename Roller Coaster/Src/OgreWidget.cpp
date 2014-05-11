#include "OgreWidget.h"

const QPoint     OgreWidget::invalidMousePoint(-1,-1);
const Ogre::Real OgreWidget::turboModifier(10);

OgreWidget::OgreWidget(QWidget *parent):QWidget(parent),
mRoot(0), mSceneMgr(0), mWindow(0), mViewport(0),
mCamera(0), oldPos(invalidMousePoint)
{
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_PaintOnScreen);
	setMinimumSize(240,240);
	setFocusPolicy(Qt::ClickFocus);
	initOgreSystem();
}

OgreWidget::~OgreWidget()
{
	if(mWindow)
	{
		mWindow->removeAllViewports();
	}

	if(mRoot)
	{
		mRoot->detachRenderTarget(mWindow);

		if(mSceneMgr)
		{
			mRoot->destroySceneManager(mSceneMgr);
		}
	}

	delete mRoot;
}


void OgreWidget::keyPressEvent( QKeyEvent *e )
{

}

void OgreWidget::keyReleaseEvent( QKeyEvent *e )
{

}

void OgreWidget::mouseDoubleClickEvent( QMouseEvent *e )
{

}

void OgreWidget::mouseMoveEvent( QMouseEvent *e )
{

}

void OgreWidget::mousePressEvent( QMouseEvent *e )
{

}

void OgreWidget::mouseReleaseEvent( QMouseEvent *e )
{

}

void OgreWidget::moveEvent( QMoveEvent *e )
{
	QWidget::moveEvent(e);

	if(e->isAccepted() && mWindow)
	{
		mWindow->windowMovedOrResized();
		update();
	}
}

QPaintEngine* OgreWidget::paintEngine() const
{
	// We don't want another paint engine to get in the way for our Ogre based paint engine.
	// So we return nothing.
	return NULL;
}

void OgreWidget::paintEvent(QPaintEvent *e)
{

}

bool OgreWidget::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return true;
}

void OgreWidget::resizeEvent(QResizeEvent *e)
{
	QWidget::resizeEvent(e);

	if(e->isAccepted())
	{
		const QSize &newSize = e->size();
		if(mWindow)
		{
			mWindow->resize(newSize.width(), newSize.height());
			mWindow->windowMovedOrResized();
		}
		if(mCamera)
		{
			Ogre::Real aspectRatio = Ogre::Real(newSize.width()) / Ogre::Real(newSize.height());
			mCamera->setAspectRatio(aspectRatio);
		}
	}
}

void OgreWidget::showEvent(QShowEvent *e)
{
	if(mRoot&&!mWindow)
	{
		startApp();
	}

	QWidget::showEvent(e);
}

void OgreWidget::wheelEvent(QWheelEvent *e)
{

}

void OgreWidget::initOgreSystem()
{
	bool ok = false;
	Ogre::LogManager * lm = new Ogre::LogManager();
	lm->createLog( "log.txt", true, false, false );
	mRoot = new Ogre::Root( "plugins.cfg", "ogre.cfg", "ogre.log" );

	Ogre::RenderSystemList renderers = mRoot->getAvailableRenderers();

	// See if the list is empty (no renderers available)
	if(renderers.empty())
		return;

	Ogre::RenderSystem *renderSystem;
	for(Ogre::RenderSystemList::iterator it = renderers.begin();
		it != renderers.end(); it++)
	{
		renderSystem = (*it);
		std::string rname = renderSystem->getName();
		
		if( rname == "Direct3D9 Rendering Subsystem" )
		{
			ok = true;
			break;
		}
	}
	if(!ok) {
		// We still don't have a renderer; pick
		// up the first one from the list
		renderSystem = (*renderers.begin());
	}

	mRoot->setRenderSystem(renderSystem);
	mRoot->initialise(false);
	mRoot->addFrameListener(this);
	
}
void OgreWidget::startApp()
{
	Ogre::NameValuePairList viewConfig;
	Ogre::String widgetHandle;

	widgetHandle = Ogre::StringConverter::toString((size_t)((HWND)winId()));
	viewConfig["externalWindowHandle"] = widgetHandle;
	Ogre::ConfigOptionMap configOptionMap = Ogre::Root::getSingletonPtr()->getRenderSystem()->getConfigOptions();
	Ogre::ConfigOptionMap::iterator iter = configOptionMap.find("Video Mode");
	int wid, hei;
	for (unsigned int j = 0; j<iter->second.possibleValues.size();j++){
		Ogre::String videoMode = iter->second.currentValue;
		std::string tmp;
		std::istringstream str(videoMode);
		str >> wid >> tmp >> hei;
	}

	mWindow = mRoot->createRenderWindow("Ogre rendering window",
		wid, hei, false, &viewConfig);

	setupNLoadResources();
	createScene();
}

void OgreWidget::setupNLoadResources()
{
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}