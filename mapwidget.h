#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>

class BaiduWebView;
class MapWidget : public QWebView
{
	Q_OBJECT

public:
	MapWidget(QWidget *parent = 0);
	~MapWidget();


private slots:
	void	LoadFinish();
	void	MarkAblum(double lng, double lat);
private:
	bool	InitMap();

protected:
	void	showEvent(QShowEvent *event);
	void	mousePressEvent(QMouseEvent *event);

private:
	QWebFrame	*m_webFrame;
};







#endif // MAPWIDGET_H
