#ifndef APPMAIN_H
#define APPMAIN_H

#include <QtWidgets/QMainWindow>
#include "RollerCoaster.h"
#include "OgreRenderThread.h"
#include "ui_AppMain.h"

class AppMain : public QMainWindow
{
	Q_OBJECT

public:
	AppMain(QWidget *parent = 0);
	~AppMain();

	void ToggleMenuBar();
	void ToggleToolBar();
	void ToggleStatusBar();
	void TogglePanel();

	RollerCoaster *m_rollerCoaster;
	OgreRenderThread rt;

	static AppMain *getInstance();
	static AppMain *Instance;

private:
	void DetachCamNode();
	void UpdateCameraState( int index );
	void UpdateCurveState( int index );
	void UpdateTrackState( int index );
	Ui::AppMainClass ui;

private slots:
	void LoadTrackPath();
	void SaveTrackPath();
	void ExitApp();
	
	void ChangeCameraType( QString type );
	void ChangeCamToWorld();
	void ChangeCamToTop();
	void ChangeCamToTrain();

	void ChangeCurveType( QString type );
	void ChangeCurveToLinear();
	void ChangeCurveToCardinal();
	void ChangeCurveToCubic();

	void ChangeTrackType( QString type );
	void ChangeTrackToLine();
	void ChangeTrackToTrack();
	void ChangeTrackToRoad();

	void SwitchPlayAndPause();
	void ChangeSpeedOfTrain( int val );

	void AddControlPoint();
	void DeleteControlPoint();

	void CallNextFrame();
};

#endif // APPMAIN_H
