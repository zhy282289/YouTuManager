#ifndef ABLUMVIEWER_H
#define ABLUMVIEWER_H

#include <QWidget>

class AblumViewer : public QWidget
{
	Q_OBJECT

public:
	AblumViewer(BAblums *ablums, QWidget *parent);
	~AblumViewer();


protected:
	void	resizeEvent(QResizeEvent *event);

private slots:
	void	BtnClicked();

private:
	BAblums	*m_ablums;

	QLabel	*m_lbPixmap;


	QPushButton	*m_btnClose;
	QPushButton	*m_btnPre;
	QPushButton	*m_btnNext;
	QPushButton	*m_btnAblum;
};

#endif // ABLUMVIEWER_H
