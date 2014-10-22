#ifndef EXTERNALAPI_H
#define EXTERNALAPI_H





QSize GetScreenSize();

void SetMainWidget(QWidget *widget);
QWidget* GetMainWidget();

QString GetSettingPath();

QFutureWatcher<BPixmap>	*GetLoadImgFutuerWatcher();

#endif // EXTERNALAPI_H
