#ifndef ABLUMMANAGERWIDGET_H
#define ABLUMMANAGERWIDGET_H

#include <QWidget>

enum ViewType{Larger, Small};


class AblumManagerView;
class AblumManagerWidget : public QDialog
{
	Q_OBJECT
public:
	AblumManagerWidget(BAblum *ablum,  QWidget *parent);
	~AblumManagerWidget();


protected:
	void showEvent(QShowEvent *event);
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);

	void Update(int type);

private slots:
	void BtnClicked();
	void OneImgReady(BPixmap *pixmap);

private:
	QPushButton	*m_btnAdd;
	QPushButton	*m_btnRemove;
	QPushButton	*m_btnClear;

	BAblum	*m_ablum;
	int		m_viewType;

	QScrollArea	*m_area;
	AblumManagerView	*m_pixmapView;

	QString	m_pixmapDir;
};

class AblumManagerView : public QWidget
{
	Q_OBJECT
public:
	AblumManagerView(QWidget *parent = 0);

	void AddPixmap(const QImage &pixmap);
	void Update(int type);

protected:
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);

private:
	QList<QLabel*>	m_items;
	int		m_itemw;
	int		m_viewType;
};

#endif // ABLUMMANAGERWIDGET_H
