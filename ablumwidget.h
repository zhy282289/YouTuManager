#ifndef ABLUMWIDGET_H
#define ABLUMWIDGET_H

#include <QWidget>

class BaiduJsManager;
class BAblumController;
class AblumWidgetItem;
class AblumWidget : public QWidget
{
	Q_OBJECT

public:
	AblumWidget(QWidget *parent = 0);
	~AblumWidget();

protected:
	void	resizeEvent(QResizeEvent *event);

private slots:
	void AddAblumItem(BAblum *ablum);

	void Update();
	

private:
	QList<AblumWidgetItem*>	m_items;
	BAblumController	*m_ablumController;
	
	int	m_hspace;
	int m_vspace;
};


class BAblum;
class AblumWidgetItem : public QWidget
{
	Q_OBJECT
public:
	AblumWidgetItem(BAblum *ablum, QWidget *parent = 0);
	void Update();
	QSize Size();

protected:
	void mousePressEvent(QMouseEvent *event);

private:
	QPixmap	GetFirstPixmap();


	BAblum	*m_ablum;

	QLabel	*m_lbPixmap;
	QLabel	*m_lbDesc;
};









#endif // ABLUMWIDGET_H
