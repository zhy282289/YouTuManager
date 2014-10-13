#include "stdafx.h"
#include "youtumanager.h"

#include "mapwidget.h"

YouDuManager::YouDuManager(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	

	// ui
	m_btnMap = new BtnPrue;
	m_btnAlbum = new BtnPrue;
	m_btnLocalAlbum = new BtnPrue;
	m_btnSetting = new BtnPrue;

	m_centralLayout = new QStackedLayout;

	m_mapWidget = new MapWidget;
	m_albumWidget = new QWidget;
	m_localAlbumWidget = new QWidget;
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
	m_centralLayout->addWidget(m_albumWidget);
	m_centralLayout->addWidget(m_localAlbumWidget);
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

}
