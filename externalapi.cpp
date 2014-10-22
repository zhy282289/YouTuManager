#include "stdafx.h"
#include "externalapi.h"


QSize GetScreenSize()
{
	return QSize(qApp->desktop()->availableGeometry().width(), qApp->desktop()->availableGeometry().height());
}

QString GetSettingPath()
{
	return QApplication::applicationDirPath() + QDir::separator() + "setting.ini";
}


QFutureWatcher<BPixmap>	*g_futureWatcher = NULL;
QFutureWatcher<BPixmap>	*GetLoadImgFutuerWatcher()
{
	if (g_futureWatcher == NULL)
	{
		g_futureWatcher = new QFutureWatcher<BPixmap>;
	}
	return g_futureWatcher;
}

QWidget *g_mainWidget = NULL;
void SetMainWidget( QWidget *widget )
{
	g_mainWidget = widget;
}

QWidget* GetMainWidget()
{
	return g_mainWidget;
}
