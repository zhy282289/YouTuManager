#ifndef COMMONUI_H
#define COMMONUI_H






class BtnPrue : public QPushButton
{
	Q_OBJECT
public:
	BtnPrue(QWidget *parent = 0);



};



class BaseBtn : public QPushButton
{
	Q_OBJECT
public:
	BaseBtn(QWidget *parent = 0);



};




class AblumAreaWidget : public QScrollArea
{
	Q_OBJECT
public:
	AblumAreaWidget(QWidget *parent = 0);

	void SetWidget(QWidget *widget);

protected:
	void resizeEvent(QResizeEvent *event);

private:

	QWidget	*m_widget;

};




#endif // COMMONUI_H
