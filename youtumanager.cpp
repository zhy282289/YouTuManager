#include "stdafx.h"
#include "youtumanager.h"

#include "mapwidget.h"
#include "baidujsmanager.h"
#include "ablumwidget.h"

YouDuManager::YouDuManager(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	SetMainWidget(this);
	setWindowTitle("YouTuManager");

	// init global controller
	BaiduJsManager::GetInstance();
	BAblumController::GetInstance();

	// ui
	m_btnMap = new BtnPrue;
	m_btnAlbum = new BtnPrue;
	m_btnLocalAlbum = new BtnPrue;
	m_btnSetting = new BtnPrue;
	connect(m_btnMap, SIGNAL(clicked()), this,SLOT(YouTuWidgetChanged()));
	connect(m_btnAlbum, SIGNAL(clicked()), this,SLOT(YouTuWidgetChanged()));
	connect(m_btnLocalAlbum, SIGNAL(clicked()), this,SLOT(YouTuWidgetChanged()));
	connect(m_btnSetting, SIGNAL(clicked()), this,SLOT(YouTuWidgetChanged()));



	m_centralLayout = new QStackedLayout;

	m_mapWidget = new MapWidget;
	m_ablumWidget = new AblumWidget;
	m_localAblumWidget = new QWidget;
	m_settingWidget = new QWidget;
	
	m_stateBar = new QWidget;
	m_searchBar = new QWidget;

	QHBoxLayout	*btnLayout = new QHBoxLayout;
	btnLayout->addWidget(m_btnMap);
	btnLayout->addWidget(m_btnAlbum);
	btnLayout->addWidget(m_btnLocalAlbum);
	btnLayout->addWidget(m_btnSetting);
	btnLayout->addStretch();

	//m_mapWidget->setStyleSheet("background-color:rgb(0,0,250,200);min-height:30");
	m_stateBar->setStyleSheet("background-color:rgb(250,0,0,50);min-height:30");
	m_searchBar->setStyleSheet("background-color:rgb(0,250,0,50);min-height:30");


	m_centralLayout->addWidget(m_mapWidget);
	m_centralLayout->addWidget(m_ablumWidget);
	m_centralLayout->addWidget(m_localAblumWidget);
	m_centralLayout->addWidget(m_settingWidget);
	m_centralLayout->setCurrentIndex(0);

	QVBoxLayout	*mainLayout = new QVBoxLayout;
	mainLayout->addLayout(btnLayout);
	mainLayout->addLayout(m_centralLayout);
	mainLayout->addWidget(m_stateBar);
	mainLayout->addWidget(m_searchBar);
	mainLayout->setStretch(0, 1);
	mainLayout->setStretch(1, 97);
	mainLayout->setStretch(2, 1);
	mainLayout->setStretch(3, 1);
	mainLayout->setSpacing(5);

	setLayout(mainLayout);

}

YouDuManager::~YouDuManager()
{
	BaiduJsManager::Release();
	BAblumController::Release();
}

void YouDuManager::YouTuWidgetChanged()
{
	QWidget *centralWidget = NULL;
	QObject *obj = sender();
	if (obj == m_btnMap)
	{
		centralWidget = m_mapWidget;
	}
	else if (obj == m_btnAlbum)
	{
		centralWidget = m_ablumWidget;
	}
	else if (obj == m_btnLocalAlbum)
	{
		centralWidget = m_localAblumWidget;
	}
	else if (obj == m_btnSetting)
	{
		centralWidget = m_settingWidget;
	}
	m_centralLayout->setCurrentWidget(centralWidget);
}
