#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>



class BaiduWebView;
class BaiduJsManager;
class MapWidget : public QWebView
{
	Q_OBJECT

public:
	MapWidget( QWidget *parent = 0);
	~MapWidget();


private slots:
	void	LoadFinish();
	void	JsEvent(double lng, double lat, int type);

private:
	bool	InitMap();


protected:
	void	showEvent(QShowEvent *event);
	void	mousePressEvent(QMouseEvent *event);

private:
	QWebFrame	*m_webFrame;
	BaiduJsManager *m_manager;
};







#endif // MAPWIDGET_H
