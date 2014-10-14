#include "stdafx.h"
#include "bablumcontroller.h"


void _LoadImage(BPixmap &pixmap)
{
	if (!pixmap.isValid())
	{
		pixmap.img = QPixmap::fromImage(QImage(pixmap.path));
	}
}



BAblum::BAblum( const BPoint &point, QString title, QObject *parent )
	:QObject(parent)
{
	m_point = point;
	m_title = title;

	m_hadLoad = false;

	m_futureWatcher = new QFutureWatcher<void>();
	connect(m_futureWatcher, SIGNAL(resultReadyAt(int)), this, SLOT(ImageResultReady(int)));
	connect(m_futureWatcher, SIGNAL(finished()), this, SLOT(Finished()));
}




BPoint BAblum::GetBPoint()
{
	return m_point;
}

void BAblum::LoadImgs()
{
	if (!m_futureWatcher->isRunning())
	{
		m_futureWatcher->setFuture(QtConcurrent::map(m_images, _LoadImage));
	}
}

void BAblum::ImageResultReady( int index )
{
	//m_imgs[index] = m_futureWatcher->resultAt(index);
	emit OneImgReady(index);
}

void BAblum::Finished()
{

}

bool BAblum::HitHint( const BPoint &point ) const
{
	return true;
}

BPixmaps& BAblum::GetImages()
{
	return m_images;
}

QString BAblum::GetTitle()
{
	return m_title;
}

//////////////////////////////////////////////////////////////////////////
BAblumController::BAblumController( QObject *parent /*= 0*/ )
	:QObject(parent)
{

}


BAblumController *g_bAblumController = NULL;
BAblumController* BAblumController::GetInstance()
{
	if (g_bAblumController == NULL)
	{
		g_bAblumController = new BAblumController;
	}
	return g_bAblumController;
}

void BAblumController::Release()
{
	if (g_bAblumController)
	{
		delete g_bAblumController;
		g_bAblumController = NULL;
	}
}

void BAblumController::CreateAblum( const BPoint &point, QString title /*= ""*/ )
{
	BAblum	*ablum = new BAblum(point, title);
	m_BAblums.push_back(ablum);
	emit NewAblum(ablum);
}

BAblum* BAblumController::GetAblum( const BPoint &point )
{
	for (int i = 0; i < m_BAblums.size(); ++i)
	{
		BAblum *ablum = m_BAblums[i];
		if (ablum->HitHint(point))
		{
			return ablum;
		}
	}

	return NULL;
}

BAblums* BAblumController::GetAllAblum()
{
	return &m_BAblums;
}
