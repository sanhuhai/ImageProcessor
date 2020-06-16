#pragma once
#include <QLabel>
#include <QTextEdit>
#include <QWidget>
#include <QImage>
#include <QHBoxLayout>
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif // WIN32

class ShowWidget:public QWidget
{
	Q_OBJECT
public:
	ShowWidget(QWidget* parent = 0);
	void display();
	QLabel* getImageLabel();
	QTextEdit* getText();
protected:
	
private:
	QImage img;
	QLabel* imageLabel;
	QTextEdit* text;
	QHBoxLayout* mainLayout;
};