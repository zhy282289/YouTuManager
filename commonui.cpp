#include "stdafx.h"
#include "commonui.h"


BtnPrue::BtnPrue( QWidget *parent /*= 0*/ )
	:QPushButton(parent)
{
	setObjectName("BtnPrue");
	setMinimumWidth(70);
}



BaseBtn::BaseBtn( QWidget *parent /*= 0*/ )
	:QPushButton(parent)
{

}

//////////////////////////////////////////////////////////////////////////
AblumAreaWidget::AblumAreaWidget( QWidget *parent )
	:QScrollArea(parent)
{
	m_widget = NULL;
}

void AblumAreaWidget::SetWidget( QWidget *widget )
{
	if (widget)
	{
		m_widget = widget;
		m_widget->setParent(this);
	}
	
}

void AblumAreaWidget::resizeEvent( QResizeEvent *event )
{
	if (m_widget)
	{
		m_widget->setGeometry(rect());
	}
	QScrollArea::resizeEvent(event);
}
