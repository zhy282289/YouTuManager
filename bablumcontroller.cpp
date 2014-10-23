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
	m_ablumData.point = point;
	m_ablumData.title = title;


	m_futureWatcher = new QFutureWatcher<BPixmap>(this);
	connect(m_futureWatcher, SIGNAL(resultReadyAt(int)), this, SLOT(SlotResultReadyAt(int)));

	
}


BAblum::BAblum( QObject *parent /*= 0*/ )
	:QObject(parent)
{

}



BPoint BAblum::GetBPoint()
{
	return m_ablumData.point;
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
	return m_ablumData.images;
}

QString BAblum::GetTitle()
{
	return m_ablumData.title;
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
	m_ablumData.images.push_back(*pixmap);
	emit OneImgReady(pixmap);
}



BPixmap& BAblum::GetImage( unsigned index )
{
	Q_ASSERT(index < m_ablumData.images.size());
	return m_ablumData.images[index];
}

void BAblum::SlotResultReadyAt( int index )
{
	BPixmap temp = m_futureWatcher->resultAt(index);
	m_ablumData.images.push_back(temp);
	emit OneImgReady(&m_ablumData.images.last());
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

const BAblumData& BAblum::GetAblumData()
{
	return m_ablumData;

}

void BAblum::SetAblumData( const BAblumData &data )
{
	m_ablumData = data;
}

//////////////////////////////////////////////////////////////////////////
BAblumController::BAblumController( QObject *parent /*= 0*/ )
	:QObject(parent)
{
	Load();
}

BAblumController::~BAblumController()
{
	for (int i = 0; i < m_BAblums.size(); ++i)
	{
		m_BAblums.at(i)->StopLoadImgs();
	}

	Save();
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

bool BAblumController::Load()
{
	QString path = GetAppDir() + "youtumanager";

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly))
	{
		return false;
	}


	QDataStream stream(&file);
	stream.setVersion(QDataStream::Qt_4_8);
	QString boy;
	stream >> boy;
	if (boy != "BOY")
	{
		return false;
	}
	qint32 v;
	stream >> v;
	if (v != 1)
	{
		return false;
	}

	int size = 0;
	stream >> size;
	for (int i = 0; i < size; ++i)
	{
		BAblumData data;
		stream >>data;
		BAblum* bablum = new BAblum(data.point, data.title);
		bablum->SetAblumData(data);
		m_BAblums.push_back(bablum);
	}

	return true;
}

bool BAblumController::Save()
{
	QString path = GetAppDir() + "youtumanager";

	QFile file(path);
	if (!file.open(QIODevice::WriteOnly))
	{
		return false;
	}


	QDataStream steram(&file);
	steram.setVersion(QDataStream::Qt_4_8);
	QString boy("BOY");
	steram << boy;
	steram << (qint32(1));
	steram << m_BAblums.size();
	for (int i = 0; i < m_BAblums.size(); ++i)
	{
		steram << m_BAblums.at(i)->GetAblumData();
	}

	return true;
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
