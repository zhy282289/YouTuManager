#ifndef TYPE_H
#define TYPE_H

#include <QObject>

// ◊¯±Íµ„
class BPoint
{
public:
	double lng;
	double lat;

	BPoint(){lng=0.0;lat=0.0;}
	BPoint(double lng, double lat){this->lng=lng;this->lat=lat;}
};

// Õº∆¨¿‡
class BPixmap
{
public:
	QString path;
	QPixmap	img;
	QString title;
	QString desc;

	bool isValid() const
	{
		return !img.isNull();
	}
};
typedef QList<BPixmap>	BPixmaps;





//const int PixViewType_Large = 150;
//const int PixViewType_Small = 150;





#endif // TYPE_H
