#include "stdafx.h"
#include "ablummanagerwidget.h"

AblumManagerWidget::AblumManagerWidget(BAblum *ablum, QWidget *parent)
	: QDialog(parent)
	, m_ablum(ablum)
{
	setWindowModality(Qt::WindowModal);
	setAttribute(Qt::WA_DeleteOnClose);


	m_viewType = Larger;

	QSettings settings(GetSettingPath(), QSettings::IniFormat);
	m_pixmapDir = settings.value("AblumManagerWidget_pixmapDir").toString();


	m_area = new QScrollArea(this);
	m_pixmapView = new AblumManagerView;
	m_area->setWidget(m_pixmapView);

	m_btnAdd = new QPushButton(this);
	m_btnRemove = new QPushButton(this);
	m_btnClear = new QPushButton(this);
	connect(m_btnAdd, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	connect(m_btnRemove, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	connect(m_btnClear, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	m_btnAdd->setStyleSheet("background-color:blue;");
	m_btnRemove->setStyleSheet("background-color:blue;");
	m_btnClear->setStyleSheet("background-color:blue;");

	
	connect(ablum, SIGNAL(OneImgReady(BPixmap*)), this, SLOT(OneImgReady(BPixmap*)), Qt::QueuedConnection);

	BPixmaps pixmaps = m_ablum->GetImages();
	for (int i = 0; i < pixmaps.size(); ++i)
	{
		if (pixmaps.at(i).isValid())
		{
			m_pixmapView->AddPixmap(pixmaps.at(i).img);
		}

	}
}

AblumManagerWidget::~AblumManagerWidget()
{
	QString path = GetSettingPath();
	QSettings settings(GetSettingPath(), QSettings::IniFormat);
	settings.setValue("AblumManagerWidget_pixmapDir", m_pixmapDir);
}

void AblumManagerWidget::showEvent( QShowEvent *event )
{
	Update(m_viewType);
}

void AblumManagerWidget::resizeEvent( QResizeEvent *event )
{
	Update(m_viewType);
	
}

void AblumManagerWidget::Update(int type)
{
	int w = rect().width();
	int h = rect().height();
	const int margins = 10;
	int left = margins;
	int top = margins;

	const int btnw = 30;
	const int btnh = 30;
	m_btnAdd->setGeometry(left, top, btnw, btnh);
	left = m_btnAdd->geometry().right() + margins;
	m_btnRemove->setGeometry(left, top, btnw, btnh);
	left = m_btnRemove->geometry().right() + margins;
	m_btnClear->setGeometry(left, top, btnw, btnh);
	left = margins;
	top = m_btnAdd->geometry().bottom() + margins;
	m_area->setGeometry(left, top, w - 2*margins, h - top - 3*margins);
	m_pixmapView->setGeometry(left, top, w - 2*margins - 20, h - top - 3*margins);
	m_pixmapView->Update(m_viewType);
}

void AblumManagerWidget::BtnClicked()
{
	QObject *obj = sender();
	if (obj == m_btnAdd)
	{
		QStringList paths = QFileDialog::getOpenFileNames(this, "Ñ¡ÔñÍ¼Æ¬", m_pixmapDir);
		if (!paths.isEmpty())
		{
			BPixmaps pixmaps;
			foreach(const QString &path, paths)
			{
				BPixmap pixmap;
				pixmap.path = path;
				pixmap.title = QFileInfo(path).completeBaseName();
				pixmaps.push_back(pixmap);
			}
			m_ablum->AddImages(pixmaps);
			m_pixmapDir = QFileInfo(paths.at(0)).absolutePath();
		}
	}
	else if (obj == m_btnRemove)
	{

	}
	else if (obj == m_btnClear)
	{

	}

	
}

void AblumManagerWidget::OneImgReady(BPixmap *pixmap)
{
	if (pixmap->isValid())
	{
		m_pixmapView->AddPixmap(pixmap->img);
		m_pixmapView->Update(m_viewType);
	}
}

void AblumManagerWidget::paintEvent( QPaintEvent *event )
{
	//QPainter painter(this);
	//painter.fillRect(rect(), QBrush(Qt::black));
}

//////////////////////////////////////////////////////////////////////////
AblumManagerView::AblumManagerView( QWidget *parent /*= 0*/ )
	:QWidget(parent)
{
	m_itemw = PixViewType_Large;
	m_viewType = Larger;
}

void AblumManagerView::AddPixmap( const QImage &pixmap )
{
	QLabel *lb = new QLabel(this);
	lb->hide();
	lb->setPixmap(QPixmap::fromImage(pixmap));
	m_items.push_back(lb);
}

void AblumManagerView::resizeEvent( QResizeEvent *event )
{
	QWidget::resizeEvent(event);
}

void AblumManagerView::Update( int type )
{
	
	if (type == Larger)
	{
		m_itemw = PixViewType_Large;
	}
	else
	{
		m_itemw = PixViewType_Small;
	}

	const int margins = 10;
	int w = rect().width();
	int h = rect().height();

	int left = margins;
	int top = margins;

	for (int i = 0; i < m_items.size(); ++i)
	{
		QWidget *item = m_items.at(i);
		item->setGeometry(left, top, m_itemw, m_itemw);
		item->show();
		left += m_itemw + 10;
		if (left + m_itemw >= w)
		{
			left = margins;
			top += m_itemw + margins;
		}
	}
	if (top > h)
	{
		resize(w, top + m_itemw + margins);
	}
}

void AblumManagerView::paintEvent( QPaintEvent *event )
{
	//QPainter painter(this);
	//painter.fillRect(rect(), QBrush(Qt::black));
}
