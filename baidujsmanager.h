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
	// js 发出的事件
	void	JsEvent(double lng, double lat, int type);	

public:
	// 调用js的方法
	QString MarkAblum(double lng, double lat);	// 创建一个相册标记点

	
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
