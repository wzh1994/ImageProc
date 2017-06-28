#ifndef IMAGEPROC_H
#define IMAGEPROC_H

#include <QtWidgets/QMainWindow>
#include "ui_imageproc.h"

class ImageProc : public QMainWindow
{
	Q_OBJECT

public:
	ImageProc(QWidget *parent = 0);
	~ImageProc();
public slots:
	void ClickButton1();
	void ClickButton2();
	void ClickButton3();
	void ClickButton4();
	void ClickButton5();
	void ClickButton6();
	void ClickButton7();
	void ClickButton8();
	void ClickButton9();
	void ClickButton10();
	void ClickButton11();
	void ClickButton12();
	void ClickButton13();

private:
	Ui::ImageProcClass ui;
	void open();
	QAction *openAction;
};

#endif // IMAGEPROC_H
