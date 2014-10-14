#ifndef BAIDUJSMANAGER_H
#define BAIDUJSMANAGER_H

#include <QObject>

enum Type_JsEvent{
	Js_Clicked = 0x1, 
	Js_MenuContext,
};

class BaiduJsManager : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QPixmap marketPixmap READ getPixmap)
	
public:	
signals:
	// js �������¼�
	void	JsEvent(double lng, double lat, int type);	

public:
	// ����js�ķ���
	QString MarkAblum(double lng, double lat);	// ����һ������ǵ�

	
public:
	static BaiduJsManager* GetInstance();
	static void ReleaseInstance();

	QPixmap getPixmap() const;
	Q_INVOKABLE	void	_JsEvent(double lng, double lat, int type);

private:
	BaiduJsManager(QObject *parent = 0);


	QPixmap		*m_marketPixmap;
	

};





#endif // BAIDUJSMANAGER_H
