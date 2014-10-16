#include "stdafx.h"
#include "bablumcontroller.h"


//void _LoadImage(BPixmap &pixmap)
//{
//	if (!pixmap.isValid())
//	{
//		pixmap.img = QPixmap::fromImage(QImage(pixmap.path));
//	}
//}



BAblum::BAblum( const BPoint &point, QString title, QObject *parent )
	:QObject(parent)
{
	m_point = point;
	m_title = title;

	m_hadLoad = false;
}




BPoint BAblum::GetBPoint()
{
	return m_point;
}

void BAblum::LoadImgs()
{
	//if (!m_futureWatcher->isRunning())
	//{
	//	m_futureWatcher->setFuture(QtConcurrent::map(m_images, _LoadImage));
	//}
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

//void BAblum::AddImage( const BPixmap &pixmap )
//{
//	//BPixmap temp = pixmap;
//	//QImage img = QImage(temp.path);
//	//temp.img = QPixmap::fromImage(img).scaled(QSize(PixViewType_Large, PixViewType_Large), Qt::KeepAspectRatio);
//	//m_images.push_back(temp);
//	//emit OneImgReady(&m_images.last());
//}

void BAblum::AddImages( const BPixmaps &pixmaps )
{
	LoadImageThread *th = new LoadImageThread(pixmaps);
	connect(th, SIGNAL(OneImageReady(BPixmap*)), this, SLOT(SlotOneImgReady(BPixmap*)));
	connect(th, SIGNAL(finished()), th, SLOT(deleteLater()));
	th->start();
	//for (int i = 0; i < pixmaps.size(); ++i)
	//{
	//	AddImage(pixmaps.at(i));
	//	QApplication::processEvents();
	//	
	//}
}

void BAblum::SlotOneImgReady( BPixmap *pixmap )
{
	m_images.push_back(*pixmap);
	emit OneImgReady(pixmap);
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

LoadImageThread::LoadImageThread( const BPixmaps &pixmaps )
	:QThread(NULL)
	,m_pixmaps(pixmaps)
{
	
}

void LoadImageThread::run()
{
	for (int i = 0; i < m_pixmaps.size(); ++i)
	{
		BPixmap &pixmap = m_pixmaps[i];
		if (!pixmap.isValid())
		{
			QImage img;
			if (img.load(pixmap.path))
			{
				pixmap.img = img.scaled(QSize(PixViewType_Large, PixViewType_Large), Qt::KeepAspectRatio, Qt::SmoothTransformation);
				emit OneImageReady(&pixmap);
			}
		}
	}
}
