#ifndef EXTERNALAPI_H
#define EXTERNALAPI_H

#include <QObject>

class externalapi : public QObject
{
	Q_OBJECT

public:
	externalapi(QObject *parent);
	~externalapi();

private:
	
};

#endif // EXTERNALAPI_H
