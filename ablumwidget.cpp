#include "stdafx.h"
#include "ablumwidget.h"
#include "ablummanagerwidget.h"

AblumWidget::AblumWidget(QWidget *parent)
	: QWidget(parent)
{
	m_hspace = 10;
	m_vspace = 10;

	m_ablumController = BAblumController::GetInstance();
	connect(m_ablumController, SIGNAL(NewAblum(BAblum*)), this, SLOT(AddAblumItem(BAblum*)));


}

AblumWidget::~AblumWidget()
{

}


void AblumWidget::AddAblumItem( BAblum *ablum )
{
	AblumWidgetItem *item = new AblumWidgetItem(ablum, this);
	m_items.push_back(item);

	Update();
}

void AblumWidget::resizeEvent( QResizeEvent *event )
{
	Update();
}


void AblumWidget::Update()
{
	int w = rect().width();

	int left = m_hspace;
	int top = m_vspace;
	for (int i = 0; i < m_items.size(); ++i)
	{
		AblumWidgetItem *item = m_items.at(i);
		int itemw = item->Size().width();
		int itemh = item->Size().height();
		item->setGeometry(left, top, itemw, itemh);
		left += itemw + m_hspace;
		if (left + itemw >= w)
		{
			left = m_hspace;
			top += itemh + m_vspace;
		}
	}
}



//////////////////////////////////////////////////////////////////////////
AblumWidgetItem::AblumWidgetItem( BAblum *ablum, QWidget *parent /*= 0*/ )
	:QWidget(parent)
	,m_ablum(ablum)
{
	m_lbPixmap = new QLabel;

	m_lbDesc = new QLabel;
	m_lbDesc->setMaximumHeight(30);

	m_lbPixmap->setStyleSheet("background-color:red;");
	m_lbDesc->setStyleSheet("background-color:red;");

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(m_lbPixmap);
	layout->addWidget(m_lbDesc);
	layout->setStretch(0, 100);

	setLayout(layout);

	Update();
}

void AblumWidgetItem::Update()
{
	m_lbDesc->setText(QString("%1").arg(m_ablum->GetTitle()));
	m_lbPixmap->setPixmap(GetFirstPixmap());
}

QPixmap AblumWidgetItem::GetFirstPixmap()
{
	QPixmap pixmap;
	//if (!m_ablum->GetImages().isEmpty())
	//{
	//	pixmap = QPixmap::fromImage(m_ablum->GetImages().at(0).img);
	//}
	return pixmap;
}

QSize AblumWidgetItem::Size()
{
	return QSize(300, 300);
}

void AblumWidgetItem::mousePressEvent( QMouseEvent *event )
{
	AblumManagerWidget ablumManagerWidget(m_ablum, this);
	ablumManagerWidget.exec();

	//AblumManagerWidget *ablumManagerWidget = new AblumManagerWidget(m_ablum, this);
	//ablumManagerWidget->showMaximized();

}
