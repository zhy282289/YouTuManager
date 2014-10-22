#include "stdafx.h"
#include "bablumcontroller.h"


BPixmap _LoadImage(const BPixmap &pixmap)
{
	BPixmap temp = pixmap;
	QImage img(pixmap.path);
	temp.img = img.scaled(QSize(PixViewType_Large, PixViewType_Large), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	return temp;
}



BAblum::BAblum( const BPoint &point, QString title, QObject *parent )
	:QObject(parent)
{
	m_point = point;
	m_title = title;

	m_hadLoad = false;

	m_futureWatcher = new QFutureWatcher<BPixmap>(this);
	connect(m_futureWatcher, SIGNAL(resultReadyAt(int)), this, SLOT(SlotResultReadyAt(int)));

	
}




BPoint BAblum::GetBPoint()
{
	return m_point;
}

void BAblum::LoadImgs(const BPixmaps &pixmaps)
{
	if (!m_futureWatcher->isRunning())
	{
		m_futureWatcher->setFuture(QtConcurrent::mapped(pixmaps, _LoadImage));
	}
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


void BAblum::StopLoadImgs()
{
	if (m_futureWatcher->isRunning() || m_futureWatcher->isPaused())
	{
		m_futureWatcher->cancel();
	}
}

void BAblum::SlotOneImgReady( BPixmap *pixmap )
{
	m_images.push_back(*pixmap);
	emit OneImgReady(pixmap);
}



BPixmap& BAblum::GetImage( unsigned index )
{
	Q_ASSERT(index < m_images.size());
	return m_images[index];
}

void BAblum::SlotResultReadyAt( int index )
{
	BPixmap temp = m_futureWatcher->resultAt(index);
	m_images.push_back(temp);
	emit OneImgReady(&m_images.last());
}

void BAblum::PauseLoadImgs()
{
	if (m_futureWatcher->isRunning())
	{
		m_futureWatcher->pause();
	}
}

void BAblum::ContinueLoadImgs()
{
	if (m_futureWatcher->isPaused())
	{
		m_futureWatcher->resume();
	}
}

//////////////////////////////////////////////////////////////////////////
BAblumController::BAblumController( QObject *parent /*= 0*/ )
	:QObject(parent)
{

}

BAblumController::~BAblumController()
{
	for (int i = 0; i < m_BAblums.size(); ++i)
	{
		m_BAblums.at(i)->StopLoadImgs();
	}
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

LoadImageThread::LoadImageThread( QObject *parent)
	:QThread(parent)
{
	
}

void LoadImageThread::run()
{		
	Q_ASSERT(!m_path.isEmpty());

	QImage *img = new QImage;
	if (img->load(m_path))
	{
		//*img = img->scaled(QSize(PixViewType_Large, PixViewType_Large), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		emit OneImageReady(img);
	}
	else
	{
		delete img;
	}
	
	
}

void LoadImageThread::SetBPixmap( const QString &path )
{
	m_path = path;
}
