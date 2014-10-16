#ifndef ABLUMMANAGERWIDGET_H
#define ABLUMMANAGERWIDGET_H

#include <QWidget>



class AblumManagerWidget : public /*QWidget*/QScrollArea
{
	Q_OBJECT
	enum ViewType{Larger, Small};

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

	QList<QLabel*>	m_items;

	BAblum	*m_ablum;

	int		m_itemw;
	int		m_viewType;
};

#endif // ABLUMMANAGERWIDGET_H
