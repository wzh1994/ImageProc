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

private:
	Ui::ImageProcClass ui;
};

#endif // IMAGEPROC_H
