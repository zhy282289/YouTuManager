#ifndef BABLUMCONTROLLER_H
#define BABLUMCONTROLLER_H

#include "type.h"



// �����
class BAblum : public QObject
{
	Q_OBJECT
public:
	BAblum(const BPoint &point, QString title, QObject *parent = 0);

	bool		HitHint(const BPoint &point) const;
	BPixmaps&	GetImages();
	BPoint		GetBPoint();
	QString		GetTitle();
	void		LoadImgs();

	//void		AddImage(const BPixmap &pixmap);
	void		AddImages(const BPixmaps &pixmap);
public:
signals:
	void	OneImgReady(BPixmap *pixmap);

private slots:
	void	SlotOneImgReady(BPixmap *pixmap);

private:
	BPixmaps		m_images;		// ͼƬ
	QString			m_title;		// �������
	BPoint			m_point;		// ��ͼ�ϵ�����
	bool			m_hadLoad;		// �Ƿ������ͼƬ

private:
	
};

typedef QList<BAblum*> BAblums;


class BAblumController : public QObject
{
	Q_OBJECT
public:
	static BAblumController*	GetInstance();
	static void Release();

public:
	void		CreateAblum(const BPoint &point, QString title = "");
	BAblum*		GetAblum(const BPoint &point);
	BAblums*	GetAllAblum();

signals:
	void NewAblum(BAblum*);

private:
	BAblumController(QObject *parent = 0);



private:
	BAblums		m_BAblums;


};


class LoadImageThread : public QThread
{
	Q_OBJECT
public:
	LoadImageThread( const BPixmaps &pixmaps);

signals:
	void OneImageReady(BPixmap*);
protected:
	void run();

private:
	BPixmaps m_pixmaps;
};

#endif // BABLUMCONTROLLER_H
