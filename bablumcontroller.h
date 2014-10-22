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
	BPixmap&	GetImage(unsigned index);
	BPoint		GetBPoint();
	QString		GetTitle();
	void		LoadImgs(const BPixmaps &pixmaps);
	void		StopLoadImgs();
	void		PauseLoadImgs();
	void		ContinueLoadImgs();
public:
signals:
	void	OneImgReady(BPixmap *pixmap);

private slots:
	void	SlotOneImgReady(BPixmap *pixmap);
	void	SlotResultReadyAt(int index);
private:
	BPixmaps		m_images;		// ͼƬ
	QString			m_title;		// �������
	BPoint			m_point;		// ��ͼ�ϵ�����
	bool			m_hadLoad;		// �Ƿ������ͼƬ

private:
	QFutureWatcher<BPixmap>	*m_futureWatcher;
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
	~BAblumController();


private:
	BAblums		m_BAblums;


};


class LoadImageThread : public QThread
{
	Q_OBJECT
public:
	LoadImageThread(QObject *parent);

	void SetBPixmap(const QString &path);

signals:
	void OneImageReady(QImage*);
protected:
	void run();

private:
	QString m_path;
};

#endif // BABLUMCONTROLLER_H
