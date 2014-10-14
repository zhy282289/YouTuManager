#include "stdafx.h"
#include "ablumwidget.h"

AblumWidget::AblumWidget(QWidget *parent)
	: QWidget(parent)
{
	m_ablumController = BAblumController::GetInstance();
	connect(m_ablumController, SIGNAL(NewAblum(BAblum*)), this, SLOT(AddAblumItem(BAblum*)));


}

AblumWidget::~AblumWidget()
{

}


void AblumWidget::AddAblumItem( BAblum *ablum )
{
	AblumWidgetItem *item = new AblumWidgetItem(ablum);
	m_items.push_back(item);

	Update();
}

void AblumWidget::Update()
{

}


//////////////////////////////////////////////////////////////////////////
AblumWidgetItem::AblumWidgetItem( BAblum *ablum, QWidget *parent /*= 0*/ )
	:QWidget(parent)
	,m_ablum(ablum)
{
	m_lbPixmap = new QLabel;

	m_lbDesc = new QLabel;
	m_lbDesc->setMaximumHeight(22);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(m_lbPixmap);
	layout->addWidget(m_lbDesc);
	layout->setStretch(0, 100);


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
	if (!m_ablum->GetImages().isEmpty())
	{
		pixmap = m_ablum->GetImages().at(0).img;
	}
	return pixmap;
}
