#ifndef YOUDUMANAGER_H
#define YOUDUMANAGER_H

#include <QtGui/QWidget>


class YouDuManager : public QWidget
{
	Q_OBJECT

public:
	YouDuManager(QWidget *parent = 0, Qt::WFlags flags = 0);
	~YouDuManager();

private:
	QPushButton	*m_btnMap;
	QPushButton *m_btnAlbum;
	QPushButton *m_btnLocalAlbum;
	QPushButton *m_btnSetting;

	QStackedLayout	*m_centralLayout;
	QWidget	*m_mapWidget;
	QWidget *m_albumWidget;
	QWidget *m_localAlbumWidget;
	QWidget *m_settingWidget;

	QWidget	*m_stateBar;
	QWidget	*m_searchBar;

};
















#endif // YOUDUMANAGER_H
