#ifndef TYPE_H
#define TYPE_H

#include <QObject>

// ×ø±êµã
class BPoint
{
public:
	double lng;
	double lat;

	BPoint(){lng=0.0;lat=0.0;}
	BPoint(double lng, double lat){this->lng=lng;this->lat=lat;}

	friend QDataStream& operator >> (QDataStream &in, BPoint &data);
	friend QDataStream& operator << (QDataStream &out, const BPoint &data);
};
Q_DECLARE_METATYPE(BPoint)


// Í¼Æ¬Àà
class BPixmap
{
public:
	QString path;
	QImage	img;
	QString title;
	QString desc;
	
	bool isValid() const
	{
		return !img.isNull();
	}
	friend QDataStream& operator >> (QDataStream &in, BPixmap &data);
	friend QDataStream& operator << (QDataStream &out, const BPixmap &data);
};
Q_DECLARE_METATYPE(BPixmap)

typedef QList<BPixmap>	BPixmaps;





const int PixViewType_Large = 200;
const int PixViewType_Small = 150;





#endif // TYPE_H
