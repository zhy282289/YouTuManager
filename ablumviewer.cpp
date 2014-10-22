#include "stdafx.h"
#include "ablumviewer.h"

AblumViewer::AblumViewer(BAblum *ablum, unsigned index, QWidget *parent)
	: QDialog(parent)
	, m_ablum(ablum)
	, m_index(index)
	,m_hadLoad(false)
	,m_pixmap(0)
{
	setMouseTracking(true);
	resize(parent->rect().size());
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	//setWindowModality(Qt::ApplicationModal);

	//m_lbPixmap = new QLabel(this);
	m_lbPixmap = new QLabel(this);
	m_lbPixmap->setMouseTracking(true);
	m_lbPixmap->installEventFilter(this);
	//m_watcher = new QFutureWatcher<QImage*>();
	//connect(m_watcher, SIGNAL(finished()), this, SLOT(Finished()));

	m_btnClose = new QPushButton(this);
	//m_btnPre = new QPushButton(this);
	//m_btnNext = new QPushButton(this);
	//m_btnAblum = new QPushButton(this);

	m_btnClose->setStyleSheet("background-color:blue;");
	//m_btnPre->setStyleSheet("background-color:blue;");
	//m_btnNext->setStyleSheet("background-color:blue;");
	//m_btnAblum->setStyleSheet("background-color:blue;");
	//m_lbPixmap->setStyleSheet("background-color:yellow;");

	connect(m_btnClose, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	//connect(m_btnPre, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	//connect(m_btnNext, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	//connect(m_btnAblum, SIGNAL(clicked()), this, SLOT(BtnClicked()));

	m_LoadImageThread = new LoadImageThread(this);
	connect(m_LoadImageThread, SIGNAL(OneImageReady(QImage*)), this, SLOT(LoadThreadFinish(QImage*)));


}

AblumViewer::~AblumViewer()
{
	if (m_pixmap)
	{
		delete m_pixmap;
	}
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

	//m_lbPixmap->setGeometry(rect());


	int left = rect().width() - btnw - margins;
	m_btnClose->setGeometry(left, margins, btnw, btnw);

	int chumk = rect().width() / 4;
	left = chumk;
	int top = rect().height() - btnw -margins;
	//m_btnPre->setGeometry(left , top, btnw, btnw);
	//left = 3*chumk - btnw;
	//m_btnNext->setGeometry(left , top, btnw, btnw);
	//left = rect().width() - btnw - margins;
	//m_btnAblum->setGeometry(left , top, btnw, btnw);

	QDialog::resizeEvent(event);
}

void AblumViewer::paintEvent( QPaintEvent *event )
{
	QPainter painter(this);
	painter.fillRect(rect(), QBrush(QColor(0, 0, 0, 100)));

	QSize screen = GetScreenSize();
	if (m_pixmap && !m_pixmap->isNull())
	{	
		m_lbPixmap->resize(m_pixmap->width(), m_pixmap->height());
		m_lbPixmap->setPixmap(QPixmap::fromImage(*m_pixmap));
		QPoint imgPoint((screen.width() - m_pixmap->width())/2, (screen.height() - m_pixmap->height())/ 2);
		//painter.drawImage(imgPoint, *m_pixmap);
		m_lbPixmap->move(imgPoint);
	}

}


void AblumViewer::LoadImage(int type)
{
	if (type == Img_Pre)
	{
		--m_index;
		m_index = m_index < 0 ? m_ablum->GetImages().size()-1 : m_index;
	}
	else if (type == Img_Next)
	{
		++m_index;
		m_index = m_index > m_ablum->GetImages().size()-1 ? 0 : m_index;
	}

	m_hadLoad = false;
	if (m_LoadImageThread->isRunning())
	{
		m_LoadImageThread->wait();
		
	}
	m_LoadImageThread->SetBPixmap(m_ablum->GetImage(m_index).path);
	m_LoadImageThread->start();
	
}


void AblumViewer::LoadThreadFinish( QImage *img )
{
	if (m_pixmap)
	{
		delete m_pixmap;
		m_pixmap = NULL;
	}
	m_pixmap = img;
	QSize screen = GetScreenSize();
	int imgw = qMin(m_pixmap->width(),screen.width());
	int imgh = qMin(m_pixmap->height(), screen.height());
	*m_pixmap = m_pixmap->scaled(imgw, imgh, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	m_hadLoad = true;
	update();
}


QImage* AblumViewer::_LoadImage( const QString &path )
{
	QImage *img = new QImage(path);
	return img;
}

void AblumViewer::mousePressEvent( QMouseEvent *event )
{
	if (event->button() == Qt::LeftButton)
	{
		QPoint point = event->pos();
		ChangeImageOperator(point);
	}

}

void AblumViewer::mouseMoveEvent( QMouseEvent *event )
{
	SetViewerCursor(event->pos());
}

bool AblumViewer::eventFilter( QObject *watched, QEvent *event )
{
	if (event->type() == QEvent::MouseMove)
	{
		if (watched == m_lbPixmap)
		{
			SetViewerCursor(mapToParent(((QMouseEvent*)event)->pos()));
		}
		return true;
	}
	else if (event->type() == QEvent::MouseButtonPress)
	{
		if (watched == m_lbPixmap)
		{
			QMouseEvent* pEvent = (QMouseEvent*)event;
			if (pEvent->button() == Qt::LeftButton)
			{
				QPoint point = mapToParent(pEvent->pos());

				ChangeImageOperator(point);
			
			}

		}
		return true;
	}

	return QDialog::eventFilter(watched, event);
}

void AblumViewer::SetViewerCursor(QPoint point)
{	
	QRect leftRect =rect();
	leftRect.setRight(rect().width() / 4);
	QRect rightRect = rect();
	rightRect.setX(2* rect().width() / 4);

	if (leftRect.contains(point))
	{
		setCursor(Qt::SizeHorCursor);

	}
	else if (rightRect.contains(point))
	{
		setCursor(Qt::SizeHorCursor);
	}
	else
	{
		setCursor(Qt::ArrowCursor);
	}
}

void AblumViewer::ChangeImageOperator( QPoint point )
{
	QRect leftRect =rect();
	leftRect.setRight(rect().width() / 4);
	QRect rightRect = rect();
	rightRect.setX(2* rect().width() / 4);

	if (leftRect.contains(point))
	{
		LoadImage(Img_Pre);

	}
	else if (rightRect.contains(point))
	{
		LoadImage(Img_Next);
	}
}
