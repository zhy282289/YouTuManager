#ifndef ABLUMVIEWER_H
#define ABLUMVIEWER_H

#include <QWidget>

class AblumViewer : public QDialog
{
	Q_OBJECT
public:
	enum{Img_Pre, Img_Cur, Img_Next, };
public:
	AblumViewer(BAblum *ablums,  unsigned index, QWidget *parent);
	~AblumViewer();

	void LoadImage(int type);	

protected:
	void	resizeEvent(QResizeEvent *event);
	void	paintEvent(QPaintEvent *event);
	void	mousePressEvent(QMouseEvent *event);
	void	mouseMoveEvent(QMouseEvent *event);
	bool	eventFilter(QObject *watched, QEvent *event);

protected:
	QImage*	_LoadImage(const QString &path);

	void	SetViewerCursor(QPoint point);
	void	ChangeImageOperator(QPoint point);
private slots:
	void	BtnClicked();
	void	LoadThreadFinish(QImage*);

private:
	BAblum	*m_ablum;
	int m_index;
	QImage	*m_pixmap;
	bool m_hadLoad;
	QLabel	*m_lbPixmap;

	QPushButton	*m_btnClose;
	QPushButton	*m_btnPre;
	QPushButton	*m_btnNext;
	QPushButton	*m_btnAblum;

	//QFutureWatcher<QImage*>	*m_watcher;

	LoadImageThread		*m_LoadImageThread;
};

#endif // ABLUMVIEWER_H
