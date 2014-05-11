/********************************************************************************
** Form generated from reading UI file 'AppMain.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPMAIN_H
#define UI_APPMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppMainClass
{
public:
    QAction *aExit;
    QAction *aLoadPath;
    QAction *aSavePath;
    QAction *aWorld;
    QAction *aTop;
    QAction *aTrain;
    QAction *aLinear;
    QAction *aCardinal;
    QAction *aCubic;
    QAction *aLine;
    QAction *aTrack;
    QAction *aRoad;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *mainLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupCamera;
    QComboBox *comboCamera;
    QGroupBox *groupCurve;
    QComboBox *comboCurve;
    QGroupBox *groupTrack;
    QComboBox *comboTrack;
    QGroupBox *groupPlay;
    QPushButton *bPlay;
    QSlider *sSpeed;
    QGroupBox *groupCP;
    QPushButton *bAdd;
    QPushButton *bDelete;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuCamera;
    QMenu *menuCurve;
    QMenu *menuTrack;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AppMainClass)
    {
        if (AppMainClass->objectName().isEmpty())
            AppMainClass->setObjectName(QStringLiteral("AppMainClass"));
        AppMainClass->resize(1024, 819);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        AppMainClass->setFont(font);
        aExit = new QAction(AppMainClass);
        aExit->setObjectName(QStringLiteral("aExit"));
        aLoadPath = new QAction(AppMainClass);
        aLoadPath->setObjectName(QStringLiteral("aLoadPath"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/AppMain/Resources/Icons/openfile.ico"), QSize(), QIcon::Normal, QIcon::Off);
        aLoadPath->setIcon(icon);
        aSavePath = new QAction(AppMainClass);
        aSavePath->setObjectName(QStringLiteral("aSavePath"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/AppMain/Resources/Icons/savefile.ico"), QSize(), QIcon::Normal, QIcon::Off);
        aSavePath->setIcon(icon1);
        aWorld = new QAction(AppMainClass);
        aWorld->setObjectName(QStringLiteral("aWorld"));
        aWorld->setCheckable(true);
        aWorld->setChecked(true);
        aTop = new QAction(AppMainClass);
        aTop->setObjectName(QStringLiteral("aTop"));
        aTop->setCheckable(true);
        aTrain = new QAction(AppMainClass);
        aTrain->setObjectName(QStringLiteral("aTrain"));
        aTrain->setCheckable(true);
        aLinear = new QAction(AppMainClass);
        aLinear->setObjectName(QStringLiteral("aLinear"));
        aLinear->setCheckable(true);
        aLinear->setChecked(true);
        aCardinal = new QAction(AppMainClass);
        aCardinal->setObjectName(QStringLiteral("aCardinal"));
        aCardinal->setCheckable(true);
        aCubic = new QAction(AppMainClass);
        aCubic->setObjectName(QStringLiteral("aCubic"));
        aCubic->setCheckable(true);
        aLine = new QAction(AppMainClass);
        aLine->setObjectName(QStringLiteral("aLine"));
        aLine->setCheckable(true);
        aLine->setChecked(true);
        aTrack = new QAction(AppMainClass);
        aTrack->setObjectName(QStringLiteral("aTrack"));
        aTrack->setCheckable(true);
        aRoad = new QAction(AppMainClass);
        aRoad->setObjectName(QStringLiteral("aRoad"));
        aRoad->setCheckable(true);
        centralWidget = new QWidget(AppMainClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(0, 0));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));

        gridLayout_2->addLayout(mainLayout, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        groupCamera = new QGroupBox(centralWidget);
        groupCamera->setObjectName(QStringLiteral("groupCamera"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupCamera->sizePolicy().hasHeightForWidth());
        groupCamera->setSizePolicy(sizePolicy1);
        groupCamera->setMinimumSize(QSize(200, 100));
        groupCamera->setMaximumSize(QSize(200, 150));
        groupCamera->setAlignment(Qt::AlignCenter);
        comboCamera = new QComboBox(groupCamera);
        comboCamera->setObjectName(QStringLiteral("comboCamera"));
        comboCamera->setGeometry(QRect(50, 40, 111, 22));

        verticalLayout->addWidget(groupCamera);

        groupCurve = new QGroupBox(centralWidget);
        groupCurve->setObjectName(QStringLiteral("groupCurve"));
        sizePolicy1.setHeightForWidth(groupCurve->sizePolicy().hasHeightForWidth());
        groupCurve->setSizePolicy(sizePolicy1);
        groupCurve->setMinimumSize(QSize(200, 100));
        groupCurve->setMaximumSize(QSize(200, 200));
        groupCurve->setAlignment(Qt::AlignCenter);
        comboCurve = new QComboBox(groupCurve);
        comboCurve->setObjectName(QStringLiteral("comboCurve"));
        comboCurve->setGeometry(QRect(50, 40, 111, 22));

        verticalLayout->addWidget(groupCurve);

        groupTrack = new QGroupBox(centralWidget);
        groupTrack->setObjectName(QStringLiteral("groupTrack"));
        sizePolicy1.setHeightForWidth(groupTrack->sizePolicy().hasHeightForWidth());
        groupTrack->setSizePolicy(sizePolicy1);
        groupTrack->setMinimumSize(QSize(200, 100));
        groupTrack->setMaximumSize(QSize(200, 200));
        groupTrack->setAlignment(Qt::AlignCenter);
        comboTrack = new QComboBox(groupTrack);
        comboTrack->setObjectName(QStringLiteral("comboTrack"));
        comboTrack->setGeometry(QRect(50, 40, 111, 22));

        verticalLayout->addWidget(groupTrack);

        groupPlay = new QGroupBox(centralWidget);
        groupPlay->setObjectName(QStringLiteral("groupPlay"));
        sizePolicy1.setHeightForWidth(groupPlay->sizePolicy().hasHeightForWidth());
        groupPlay->setSizePolicy(sizePolicy1);
        groupPlay->setMinimumSize(QSize(200, 100));
        groupPlay->setMaximumSize(QSize(200, 200));
        groupPlay->setAlignment(Qt::AlignCenter);
        bPlay = new QPushButton(groupPlay);
        bPlay->setObjectName(QStringLiteral("bPlay"));
        bPlay->setGeometry(QRect(20, 40, 31, 31));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/AppMain/Resources/Icons/play.ico"), QSize(), QIcon::Normal, QIcon::On);
        bPlay->setIcon(icon2);
        sSpeed = new QSlider(groupPlay);
        sSpeed->setObjectName(QStringLiteral("sSpeed"));
        sSpeed->setGeometry(QRect(60, 40, 121, 31));
        sSpeed->setValue(50);
        sSpeed->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(groupPlay);

        groupCP = new QGroupBox(centralWidget);
        groupCP->setObjectName(QStringLiteral("groupCP"));
        sizePolicy1.setHeightForWidth(groupCP->sizePolicy().hasHeightForWidth());
        groupCP->setSizePolicy(sizePolicy1);
        groupCP->setMinimumSize(QSize(200, 100));
        groupCP->setMaximumSize(QSize(200, 200));
        groupCP->setAlignment(Qt::AlignCenter);
        bAdd = new QPushButton(groupCP);
        bAdd->setObjectName(QStringLiteral("bAdd"));
        bAdd->setGeometry(QRect(40, 30, 131, 23));
        bDelete = new QPushButton(groupCP);
        bDelete->setObjectName(QStringLiteral("bDelete"));
        bDelete->setGeometry(QRect(40, 60, 131, 23));
        bDelete->setFocusPolicy(Qt::ClickFocus);

        verticalLayout->addWidget(groupCP);

        verticalSpacer = new QSpacerItem(0, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        AppMainClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AppMainClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuCamera = new QMenu(menuBar);
        menuCamera->setObjectName(QStringLiteral("menuCamera"));
        menuCurve = new QMenu(menuBar);
        menuCurve->setObjectName(QStringLiteral("menuCurve"));
        menuTrack = new QMenu(menuBar);
        menuTrack->setObjectName(QStringLiteral("menuTrack"));
        AppMainClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AppMainClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AppMainClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AppMainClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AppMainClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCamera->menuAction());
        menuBar->addAction(menuCurve->menuAction());
        menuBar->addAction(menuTrack->menuAction());
        menuFile->addAction(aLoadPath);
        menuFile->addAction(aSavePath);
        menuFile->addSeparator();
        menuFile->addAction(aExit);
        menuCamera->addAction(aWorld);
        menuCamera->addAction(aTop);
        menuCamera->addAction(aTrain);
        menuCurve->addAction(aLinear);
        menuCurve->addAction(aCardinal);
        menuCurve->addAction(aCubic);
        menuTrack->addAction(aLine);
        menuTrack->addAction(aTrack);
        menuTrack->addAction(aRoad);
        mainToolBar->addAction(aLoadPath);
        mainToolBar->addAction(aSavePath);

        retranslateUi(AppMainClass);

        QMetaObject::connectSlotsByName(AppMainClass);
    } // setupUi

    void retranslateUi(QMainWindow *AppMainClass)
    {
        AppMainClass->setWindowTitle(QApplication::translate("AppMainClass", "AppMain", 0));
        aExit->setText(QApplication::translate("AppMainClass", "Exit", 0));
        aLoadPath->setText(QApplication::translate("AppMainClass", "Load Path", 0));
        aSavePath->setText(QApplication::translate("AppMainClass", "Save Path", 0));
        aWorld->setText(QApplication::translate("AppMainClass", "World", 0));
        aTop->setText(QApplication::translate("AppMainClass", "Top", 0));
        aTrain->setText(QApplication::translate("AppMainClass", "Train", 0));
        aLinear->setText(QApplication::translate("AppMainClass", "Linear", 0));
        aCardinal->setText(QApplication::translate("AppMainClass", "Cardinal", 0));
        aCubic->setText(QApplication::translate("AppMainClass", "Cubic", 0));
        aLine->setText(QApplication::translate("AppMainClass", "Line", 0));
        aTrack->setText(QApplication::translate("AppMainClass", "Track", 0));
        aRoad->setText(QApplication::translate("AppMainClass", "Road", 0));
        groupCamera->setTitle(QApplication::translate("AppMainClass", "Camera", 0));
        comboCamera->clear();
        comboCamera->insertItems(0, QStringList()
         << QApplication::translate("AppMainClass", "World", 0)
         << QApplication::translate("AppMainClass", "Top", 0)
         << QApplication::translate("AppMainClass", "Train", 0)
        );
        groupCurve->setTitle(QApplication::translate("AppMainClass", "Curve", 0));
        comboCurve->clear();
        comboCurve->insertItems(0, QStringList()
         << QApplication::translate("AppMainClass", "Linear", 0)
         << QApplication::translate("AppMainClass", "Cardinal", 0)
         << QApplication::translate("AppMainClass", "Cubic", 0)
        );
        groupTrack->setTitle(QApplication::translate("AppMainClass", "Track", 0));
        comboTrack->clear();
        comboTrack->insertItems(0, QStringList()
         << QApplication::translate("AppMainClass", "Line", 0)
         << QApplication::translate("AppMainClass", "Track", 0)
         << QApplication::translate("AppMainClass", "Road", 0)
        );
        groupPlay->setTitle(QApplication::translate("AppMainClass", "Play", 0));
        bPlay->setText(QString());
        groupCP->setTitle(QApplication::translate("AppMainClass", "Control Point", 0));
        bAdd->setText(QApplication::translate("AppMainClass", "Add", 0));
        bDelete->setText(QApplication::translate("AppMainClass", "Delete", 0));
        menuFile->setTitle(QApplication::translate("AppMainClass", "File", 0));
        menuCamera->setTitle(QApplication::translate("AppMainClass", "Camera", 0));
        menuCurve->setTitle(QApplication::translate("AppMainClass", "Curve", 0));
        menuTrack->setTitle(QApplication::translate("AppMainClass", "Track", 0));
    } // retranslateUi

};

namespace Ui {
    class AppMainClass: public Ui_AppMainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPMAIN_H
