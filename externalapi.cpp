#include "stdafx.h"
#include "externalapi.h"


QSize GetScreenSize()
{
	return QSize(qApp->desktop()->availableGeometry().width(), qApp->desktop()->availableGeometry().height());
}
