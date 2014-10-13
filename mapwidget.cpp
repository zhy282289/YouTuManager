#include "stdafx.h"
#include "mapwidget.h"

#include "baidujsmanager.h"

MapWidget::MapWidget(QWidget *parent)
	: QWebView(parent)
{
	m_webFrame = NULL;
	connect(this, SIGNAL(loadFinished(bool)), this, SLOT(LoadFinish()));

	BaiduJsManager *manager = BaiduJsManager::GetInstance();
	connect(manager, SIGNAL(MarkAblum(double,double)), this, SLOT(MarkAblum(double,double)));
}

MapWidget::~MapWidget()
{

}

bool MapWidget::InitMap()
{
	static bool hadInit = false;
	if (hadInit)
	{
		return true;
	}
	QFile file("baidu");
	if (!file.open(QIODevice::ReadOnly))
	{
		return false;
	}
	setHtml(file.readAll());

	hadInit = true;
	return true;
}

void MapWidget::LoadFinish()
{
	BaiduJsManager *manager = BaiduJsManager::GetInstance();
	m_webFrame = this->page()->mainFrame();
	m_webFrame->addToJavaScriptWindowObject("BaiduJsManager", manager);
}

void MapWidget::showEvent( QShowEvent *event )
{
	if (!InitMap())
	{
		Q_ASSERT(false);
	}
}

void MapWidget::mousePressEvent( QMouseEvent *event )
{
	//m_webFrame->evaluateJavaScript("MarkAblum('1', '2')");
	QWebView::mousePressEvent(event);
}

void MapWidget::MarkAblum( double lng, double lat )
{
	m_webFrame->evaluateJavaScript(QString("MarkAblum(%1, %2)").arg(QString::number(lng,'f', 6)).arg(QString::number(lat,'f', 6)));
}

