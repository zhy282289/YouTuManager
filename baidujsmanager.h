#ifndef BAIDUJSMANAGER_H
#define BAIDUJSMANAGER_H

#include <QObject>



class BaiduJsManager : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QPixmap marketPixmap READ getPixmap)

public:
	Q_INVOKABLE	void	JsEvent(double lng, double lat, int type);

signals:
	void	MarkAblum(double lng, double lat);
	void	PlanTo(const QString &city, unsigned level);
	void	PlanTo(double lng, double lat, unsigned level);
	void	ZoomTo(unsigned level);
	

public:

	static BaiduJsManager* GetInstance();
	static void ReleaseInstance();

	QPixmap getPixmap() const;


private:
	BaiduJsManager(QObject *parent = 0);


	QPixmap		*m_marketPixmap;
	

};





#endif // BAIDUJSMANAGER_H
