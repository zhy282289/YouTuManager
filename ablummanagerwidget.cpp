#include "stdafx.h"
#include "ablummanagerwidget.h"

AblumManagerWidget::AblumManagerWidget(BAblum *ablum, QWidget *parent)
	: QScrollArea(parent)
	, m_ablum(ablum)
	, m_viewType(Larger)
{
	resize(1000, 765);
	m_itemw = 300;

	BPixmaps pixmaps = m_ablum->GetImages();
	for (int i = 0; i < pixmaps.size(); ++i)
	{
		if (pixmaps.at(i).isValid())
		{
			QLabel *lb = new QLabel(this);
			lb->setPixmap(pixmaps.at(i).img);
			m_items.push_back(lb);
		}

	}

	m_btnAdd = new QPushButton(this);
	m_btnRemove = new QPushButton(this);
	m_btnClear = new QPushButton(this);
	connect(m_btnAdd, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	connect(m_btnRemove, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	connect(m_btnClear, SIGNAL(clicked()), this, SLOT(BtnClicked()));
	m_btnAdd->setStyleSheet("background-color:blue;");
	m_btnRemove->setStyleSheet("background-color:blue;");
	m_btnClear->setStyleSheet("background-color:blue;");

	connect(ablum, SIGNAL(OneImgReady(int)), this, SLOT(OneImgReady()));
	connect(ablum, SIGNAL(ImgReadyFinish()), this, SLOT(OneImgReady()));
}

AblumManagerWidget::~AblumManagerWidget()
{

}

void AblumManagerWidget::showEvent( QShowEvent *event )
{
	//QScrollArea::showEvent(event);
}

void AblumManagerWidget::resizeEvent( QResizeEvent *event )
{
	Update(m_viewType);
}

void AblumManagerWidget::Update(int type)
{
	int w = rect().width();
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

	if (type == Larger)
	{
		m_itemw = 300;
	}
	else 
	{
		m_itemw = 70;
	}

	left = margins;
	top = m_btnAdd->geometry().bottom() + margins;
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
}

void AblumManagerWidget::BtnClicked()
{
	QObject *obj = sender();
	if (obj == m_btnAdd)
	{
		QStringList paths = QFileDialog::getOpenFileNames(this, "Ñ¡ÔñÍ¼Æ¬");
		if (!paths.isEmpty())
		{
			BPixmap pixmap;
			foreach(const QString &path, paths)
			{
				pixmap.path = path;
				pixmap.title = QFileInfo(path).completeBaseName();
				m_ablum->AddImage(pixmap);
			}
			m_ablum->LoadImgs();
		}
	}
	else if (obj == m_btnRemove)
	{

	}
	else if (obj == m_btnClear)
	{

	}

	
}

void AblumManagerWidget::OneImgReady()
{

	qDeleteAll(m_items);
	m_items.clear();
	BPixmaps pixmaps = m_ablum->GetImages();
	for (int i = 0; i < pixmaps.size(); ++i)
	{
		if (pixmaps.at(i).isValid())
		{
			QLabel *lb = new QLabel(this);
			lb->setPixmap(pixmaps.at(i).img);
			m_items.push_back(lb);
		}

	}

	Update(m_viewType);
}
