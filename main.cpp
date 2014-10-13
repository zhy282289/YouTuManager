#include "stdafx.h"
#include "youtumanager.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	
	YouDuManager w;
	w.showMaximized();


	return a.exec();
}
