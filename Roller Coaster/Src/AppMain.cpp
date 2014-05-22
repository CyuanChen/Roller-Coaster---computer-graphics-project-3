#include "AppMain.h"

AppMain* AppMain::Instance = NULL;
AppMain::AppMain(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle( "Roller Coaster" );

	connect( ui.aLoadPath	,SIGNAL(triggered()),this,SLOT(LoadTrackPath())	);
	connect( ui.aSavePath	,SIGNAL(triggered()),this,SLOT(SaveTrackPath())	);
	connect( ui.aExit		,SIGNAL(triggered()),this,SLOT(ExitApp())		);

	connect( ui.comboCamera	,SIGNAL(currentIndexChanged(QString)),this,SLOT(ChangeCameraType(QString)));
	connect( ui.aWorld		,SIGNAL(triggered()),this,SLOT(ChangeCamToWorld())	);
	connect( ui.aTop		,SIGNAL(triggered()),this,SLOT(ChangeCamToTop())	);
	connect( ui.aTrain		,SIGNAL(triggered()),this,SLOT(ChangeCamToTrain())	);

	connect( ui.comboCurve	,SIGNAL(currentIndexChanged(QString)),this,SLOT(ChangeCurveType(QString)));
	connect( ui.aLinear		,SIGNAL(triggered()),this,SLOT(ChangeCurveToLinear())	);
	connect( ui.aCardinal	,SIGNAL(triggered()),this,SLOT(ChangeCurveToCardinal())	);
	connect( ui.aCubic		,SIGNAL(triggered()),this,SLOT(ChangeCurveToCubic())	);

	connect( ui.comboTrack	,SIGNAL(currentIndexChanged(QString)),this,SLOT(ChangeTrackType(QString)));
	connect( ui.aLine		,SIGNAL(triggered()),this,SLOT(ChangeTrackToLine())		);
	connect( ui.aTrack		,SIGNAL(triggered()),this,SLOT(ChangeTrackToTrack())	);
	connect( ui.aRoad		,SIGNAL(triggered()),this,SLOT(ChangeTrackToRoad())		);

	connect( ui.bPlay		,SIGNAL(clicked()),this,SLOT(SwitchPlayAndPause())				);
	connect( ui.sSpeed		,SIGNAL(valueChanged(int)),this,SLOT(ChangeSpeedOfTrain(int))	);
	connect( ui.bAdd		,SIGNAL(clicked()),this,SLOT(AddControlPoint())					);
	connect( ui.bDelete		,SIGNAL(clicked()),this,SLOT(DeleteControlPoint())				);
	
	connect( ui.sTension    ,SIGNAL(valueChanged(int)),this,SLOT(ChangeTensionOfTrack(int)) );

	connect(&rt,SIGNAL(nextFrame()),this,SLOT(CallNextFrame()),Qt::BlockingQueuedConnection);

	rt.start();

	m_rollerCoaster = new RollerCoaster;
	ui.mainLayout->layout()->addWidget( m_rollerCoaster );
	m_rollerCoaster->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	m_rollerCoaster->setMouseTracking(true);
}

AppMain::~AppMain()
{

}

void AppMain::CallNextFrame()
{
	if( m_rollerCoaster )
	{
		m_rollerCoaster->renderAFrame();
		ui.statusBar->showMessage( QString("FPS = ")+QString::number(m_rollerCoaster->getLastFPS()) );
	}
}

void AppMain::ExitApp()
{
	QApplication::quit();
}

AppMain * AppMain::getInstance()
{
	if( !Instance )
	{
		Instance = new AppMain();
		return Instance;
	}
	else 
		return Instance;
}

void AppMain::ToggleMenuBar()
{
	ui.menuBar->setHidden( !ui.menuBar->isHidden() );
}

void AppMain::ToggleToolBar()
{
	ui.mainToolBar->setHidden( !ui.mainToolBar->isHidden() );
}

void AppMain::ToggleStatusBar()
{
	ui.statusBar->setHidden( !ui.statusBar->isHidden() );
}

void AppMain::LoadTrackPath()
{
	QString fileName = QFileDialog::getOpenFileName( 
		this,
		"OpenImage",
		"./",
		tr("Txt (*.txt)" )
	);
	
	if ( !fileName.isEmpty() )
	{
		m_rollerCoaster->mTrack->readPoints( fileName.toStdString().c_str() );
		m_rollerCoaster->bReplan = true;
		m_rollerCoaster->objControl->reset();
	}
}

void AppMain::SaveTrackPath()
{
	QString fileName = QFileDialog::getSaveFileName( 
		this,
		"OpenImage",
		"./",
		tr("Txt (*.txt)" )
	);

	m_rollerCoaster->mTrack->writePoints( fileName.toStdString().c_str() );
}

void AppMain::TogglePanel()
{
	if( !ui.groupCamera->isHidden() )
	{
		ui.verticalLayout->setContentsMargins(0,0,0,0);
		ui.groupCamera->hide();
		ui.groupCurve->hide();
		ui.groupTrack->hide();
		ui.groupPlay->hide();
		ui.groupCP->hide();
	}
	else
	{
		ui.verticalLayout->setContentsMargins(6,6,6,6);
		ui.groupCamera->show();
		ui.groupCurve->show();
		ui.groupTrack->show();
		ui.groupPlay->show();
		ui.groupCP->show();
	}
}

void AppMain::ChangeCameraType( QString type )
{
	DetachCamNode();
	
	if( type == "World" )
	{
		m_rollerCoaster->currCamType = RollerCoaster::eWorld;
		m_rollerCoaster->mCamWorldNode->attachObject( m_rollerCoaster->mCamera );
		UpdateCameraState(0);
	}
	else if( type == "Top" )
	{
		m_rollerCoaster->currCamType = RollerCoaster::eTop;
		m_rollerCoaster->mCamTopNode->attachObject( m_rollerCoaster->mCamera );
		UpdateCameraState(1);
	}
	else if( type == "Train" )
	{
		m_rollerCoaster->currCamType = RollerCoaster::eTrain;
		m_rollerCoaster->mCamTrainNode->attachObject( m_rollerCoaster->mCamera );
		UpdateCameraState(2);
	}
}

void AppMain::ChangeCurveType( QString type )
{
	if( type == "Linear" )
	{
		m_rollerCoaster->currItrplType = RollerCoaster::eLinear;
		UpdateCurveState(0);
	}
	else if( type == "Cardinal" )
	{
		m_rollerCoaster->currItrplType = RollerCoaster::eCardinal;
		UpdateCurveState(1);
	}
	else if( type == "Cubic" )
	{
		m_rollerCoaster->currItrplType = RollerCoaster::eCubic;
		UpdateCurveState(2);
	}

	m_rollerCoaster->bReplan = true;
}

void AppMain::ChangeTrackType( QString type )
{
	if( type == "Line" )
	{
		m_rollerCoaster->currTrackType = RollerCoaster::eSimpleTrack;
		UpdateTrackState(0);
	}
	else if( type == "Track" )
	{
		m_rollerCoaster->currTrackType = RollerCoaster::eParallelRails;
		UpdateTrackState(1);
	}
	else if( type == "Road" )
	{
		m_rollerCoaster->currTrackType = RollerCoaster::eRoadRails;
		UpdateTrackState(2);
	}

	m_rollerCoaster->bRedraw = true;
}

void AppMain::DetachCamNode()
{
	switch( m_rollerCoaster->currCamType )
	{
	case RollerCoaster::eWorld:
		m_rollerCoaster->mCamWorldNode->detachAllObjects();
		break;
	case RollerCoaster::eTop:
		m_rollerCoaster->mCamTopNode->detachAllObjects();
		break;
	case RollerCoaster::eTrain:
		m_rollerCoaster->mCamTrainNode->detachAllObjects();
		break;
	}
}

void AppMain::SwitchPlayAndPause()
{
	if( m_rollerCoaster->bRun )
	{
		ui.bPlay->setIcon(QIcon(":/AppMain/Resources/Icons/play.ico"));
		m_rollerCoaster->bRun = false;
	}
	else
	{
		ui.bPlay->setIcon(QIcon(":/AppMain/Resources/Icons/pause.ico"));
		m_rollerCoaster->bRun = true;
	}
}

void AppMain::ChangeSpeedOfTrain( int val )
{
	m_rollerCoaster->trainSpeed = m_rollerCoaster->MAX_TRAIN_SPEED * float(val) / 100.0f;
}

void AppMain::AddControlPoint()
{
	int last = m_rollerCoaster->mTrack->getSize() - 1;
	Ogre::Vector3 pos((m_rollerCoaster->mTrack->getItem(last).pos+m_rollerCoaster->mTrack->getItem(0).pos)/2);
	m_rollerCoaster->mTrack->mAdd(ControlPoint(pos));
	m_rollerCoaster->bReplan = true;
}

void AppMain::DeleteControlPoint()
{
	std::cout << m_rollerCoaster->mCurrentObjName << std::endl;
	if (m_rollerCoaster->mTrack->getSize() > 4)
	{
		m_rollerCoaster->mTrack->mDelete(m_rollerCoaster->mCurrentObjName);
		m_rollerCoaster->bReplan = true;
		m_rollerCoaster->objControl->reset();
	}
}

void AppMain::ChangeCamToWorld()
{
	if( ui.aWorld->isChecked() )
		ui.comboCamera->setCurrentIndex(0);
	else
		ui.aWorld->setChecked(true);
}

void AppMain::ChangeCamToTop()
{
	if( ui.aTop->isChecked() )
		ui.comboCamera->setCurrentIndex(1);
	else
		ui.aTop->setChecked(true);
}

void AppMain::ChangeCamToTrain()
{
	if( ui.aTrain->isChecked() )
		ui.comboCamera->setCurrentIndex(2);
	else
		ui.aTrain->setChecked(true);
}

void AppMain::ChangeCurveToLinear()
{
	if( ui.aLinear->isChecked() )
		ui.comboCurve->setCurrentIndex(0);
	else
		ui.aLinear->setChecked(true);
}

void AppMain::ChangeCurveToCardinal()
{
	if( ui.aCardinal->isChecked() )
		ui.comboCurve->setCurrentIndex(1);
	else
		ui.aCardinal->setChecked(true);
}

void AppMain::ChangeCurveToCubic()
{
	if( ui.aCubic->isChecked() )
		ui.comboCurve->setCurrentIndex(2);
	else
		ui.aCubic->setChecked(true);
}

void AppMain::ChangeTrackToLine()
{
	if( ui.aLine->isChecked() )
		ui.comboTrack->setCurrentIndex(0);
	else
		ui.aLine->setChecked(true);
}

void AppMain::ChangeTrackToTrack()
{
	if( ui.aTrack->isChecked() )
		ui.comboTrack->setCurrentIndex(1);
	else
		ui.aTrack->setChecked(true);
}

void AppMain::ChangeTrackToRoad()
{
	if( ui.aRoad->isChecked() )
		ui.comboTrack->setCurrentIndex(2);
	else
		ui.aRoad->setChecked(true);
}

void AppMain::UpdateCameraState( int index )
{
	ui.aWorld->setChecked( (index==0)?true:false );
	ui.aTop	 ->setChecked( (index==1)?true:false );
	ui.aTrain->setChecked( (index==2)?true:false );
}

void AppMain::UpdateCurveState( int index )
{
	ui.aLinear	->setChecked( (index==0)?true:false );
	ui.aCardinal->setChecked( (index==1)?true:false );
	ui.aCubic	->setChecked( (index==2)?true:false );
}

void AppMain::UpdateTrackState( int index )
{
	ui.aLine ->setChecked( (index==0)?true:false );
	ui.aTrack->setChecked( (index==1)?true:false );
	ui.aRoad ->setChecked( (index==2)?true:false );
}

void AppMain::ChangeTensionOfTrack( int val )
{
	m_rollerCoaster->tension = m_rollerCoaster->MAX_TENSION_VALUE * float(val) / 100.0f;
	
	m_rollerCoaster->bReplan = true;
}
