#include "stdafx.h"
#include "youtumanager.h"
#include <QtGui/QApplication>

#include "ablumviewer.h"

Q_IMPORT_PLUGIN(qcncodecs)

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb10830"));
	
	YouDuManager w;
	w.showMaximized();
	
	return a.exec();
}
