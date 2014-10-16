#ifndef ABLUMMANAGERWIDGET_H
#define ABLUMMANAGERWIDGET_H

#include <QWidget>

enum ViewType{Larger, Small};


class PixmapVeiw;
class AblumManagerWidget : public QWidget
{
	Q_OBJECT
	

public:
	AblumManagerWidget(BAblum *ablum,  QWidget *parent);
	~AblumManagerWidget();


protected:
	void showEvent(QShowEvent *event);
	void resizeEvent(QResizeEvent *event);

	void Update(int type);

private slots:
	void BtnClicked();
	void OneImgReady();

private:
	QPushButton	*m_btnAdd;
	QPushButton	*m_btnRemove;
	QPushButton	*m_btnClear;

	BAblum	*m_ablum;

	int		m_itemw;
	int		m_viewType;

	QScrollArea	*m_area;
	PixmapVeiw	*m_pixmapView;
};

class PixmapVeiw : public QWidget
{
	Q_OBJECT
public:
	PixmapVeiw(QWidget *parent = 0);

	void AddPixmap(const QPixmap &pixmap);
	void Update(int type);

protected:
	void resizeEvent(QResizeEvent *event);

private:
	QList<QLabel*>	m_items;
	int		m_itemw;

};

#endif // ABLUMMANAGERWIDGET_H
