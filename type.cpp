#include "stdafx.h"
#include "type.h"



QDataStream& operator >> (QDataStream &in, BPixmap &data)
{
	return in >> data.path  >> data.title >> data.desc;
}
QDataStream& operator << (QDataStream &out, const BPixmap &data)
{
	return out << data.path  << data.title << data.desc;
}


QDataStream& operator >> (QDataStream &in, BPoint &data)
{
	return in >> data.lng >> data.lat;
}
QDataStream& operator << (QDataStream &out, const BPoint &data)
{
	return out << data.lng << data.lat;
}

QDataStream& operator >> (QDataStream &in, BAblumData &data)
{
	return in >> data.images >> data.point >> data.title;
}
QDataStream& operator << (QDataStream &out, const BAblumData &data)
{
	return out << data.images << data.point << data.title;
}