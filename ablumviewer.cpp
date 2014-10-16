#include "stdafx.h"
#include "ablumviewer.h"

AblumViewer::AblumViewer(BAblums *ablums, QWidget *parent)
	: QWidget(parent)
	, m_ablums(ablums)
{

	m_lbPixmap = new QLabel(this);

	m_btnClose = new QPushButton(this);
	m_btnPre = new QPushButton(this);
	m_btnNext = new QPushButton(this);
	m_btnAblum = new QPushButton(this);

	m_btnClose->setStyleSheet("background-color:blue;");
	m_btnPre->setStyleSheet("background-color:blue;");
	m_btnNext->setStyleSheet("background-color:blue;");
	m_btnAblum->setStyleSheet("background-color:blue;");
	m_lbPixmap->setStyleSheet("background-color:yellow;");

	connect(m_btnClose, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	connect(m_btnPre, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	connect(m_btnNext, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	connect(m_btnAblum, SIGNAL(clicked()), this, SLOT(BtnClicked()));

	resize(600, 1000);
	setWindowFlags(Qt::FramelessWindowHint);
}

AblumViewer::~AblumViewer()
{

}

void AblumViewer::BtnClicked()
{
	QObject *obj = sender();
	if (obj == m_btnClose)
	{
		close();
	}
	else if (obj == m_btnPre)
	{
	}
	else if (obj == m_btnNext)
	{
	}
	else if (obj == m_btnAblum)
	{
	}
}

void AblumViewer::resizeEvent( QResizeEvent *event )
{
	const int margins = 10;
	const int btnw = 40;

	m_lbPixmap->setGeometry(rect());


	int left = rect().width() - btnw - margins;
	m_btnClose->setGeometry(left, margins, btnw, btnw);

	int chumk = rect().width() / 4;
	left = chumk;
	int top = rect().height() - btnw -margins;
	m_btnPre->setGeometry(left , top, btnw, btnw);
	left = 3*chumk - btnw;
	m_btnNext->setGeometry(left , top, btnw, btnw);
	left = rect().width() - btnw - margins;
	m_btnAblum->setGeometry(left , top, btnw, btnw);
}
