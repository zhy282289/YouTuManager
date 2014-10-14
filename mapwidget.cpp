#include "stdafx.h"
#include "mapwidget.h"

#include "baidujsmanager.h"

MapWidget::MapWidget( QWidget *parent)
	: QWebView(parent)
{
	m_webFrame = NULL;

	m_manager = BaiduJsManager::GetInstance();
	connect(m_manager, SIGNAL(JsEvent(double,double,int)), this, SLOT(JsEvent(double,double,int)));

	connect(this, SIGNAL(loadFinished(bool)), this, SLOT(LoadFinish()));

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
	m_webFrame = this->page()->mainFrame();
	m_webFrame->addToJavaScriptWindowObject("BaiduJsManager", m_manager);
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
	QWebView::mousePressEvent(event);
}



void MapWidget::JsEvent( double lng, double lat, int type )
{
	switch (type)
	{
	case Js_Clicked:
		{

		}
		break;
	case Js_MenuContext:
		{
			m_webFrame->evaluateJavaScript(m_manager->MarkAblum(lng,lat));
			BPoint point(lng, lat);
			BAblumController::GetInstance()->CreateAblum(point, "dafult");
		}
		break;
	case Js_MarkerClicked:
		{

			//QWidget *w = new QWidget(NULL);
			//w->resize(300, 500);
			//w->show();
		}
		break;
	default:
		{

		}
	}
}


