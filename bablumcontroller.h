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

public:
signals:
	void	OneImgReady(int index);

	private slots:
		void	ImageResultReady(int index);
		void	Finished();

private:
	BPixmaps		m_images;		// ͼƬ
	QString			m_title;		// �������
	BPoint			m_point;		// ��ͼ�ϵ�����
	bool			m_hadLoad;		// �Ƿ������ͼƬ
private:
	QFutureWatcher<void>	*m_futureWatcher;
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



#endif // BABLUMCONTROLLER_H
