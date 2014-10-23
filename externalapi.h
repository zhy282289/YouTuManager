#ifndef EXTERNALAPI_H
#define EXTERNALAPI_H



void RegisterMetatype();

QSize GetScreenSize();

void SetMainWidget(QWidget *widget);
QWidget* GetMainWidget();

QString GetSettingPath();
QString GetAppDir();

QFutureWatcher<BPixmap>	*GetLoadImgFutuerWatcher();

#endif // EXTERNALAPI_H
