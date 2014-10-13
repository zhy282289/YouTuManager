#include "stdafx.h"
#include "baidujsmanager.h"

BaiduJsManager::BaiduJsManager(QObject *parent)
	: QObject(parent)
{
	m_marketPixmap = new QPixmap(":/YouDuManager/Resources/market.png");
}



Q_INVOKABLE void BaiduJsManager::JsEvent( double lng, double lat, int type )
{
	MarkAblum(lng, lat);
}

QPixmap BaiduJsManager::getPixmap() const
{
	return *m_marketPixmap;
}


BaiduJsManager *g_baiduJsManager = NULL;
BaiduJsManager* BaiduJsManager::GetInstance()
{
	if (g_baiduJsManager == NULL)
	{
		g_baiduJsManager = new BaiduJsManager;
	}
	return g_baiduJsManager;
}

void BaiduJsManager::ReleaseInstance()
{
	if (g_baiduJsManager)
	{
		delete g_baiduJsManager;
		g_baiduJsManager = NULL;
	}
}

