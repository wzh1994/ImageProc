#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QSpinBox>
#include <QHBoxLayout>
#include <iostream>
using namespace std;
#include "imageproc.h"
void testFunc(int index);
ImageProc::ImageProc(QWidget *parent):
	QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.b1, SIGNAL(clicked()), this, SLOT(ClickButton1()));
	connect(ui.b2, SIGNAL(clicked()), this, SLOT(ClickButton2()));
	connect(ui.b3, SIGNAL(clicked()), this, SLOT(ClickButton3()));
	connect(ui.b4, SIGNAL(clicked()), this, SLOT(ClickButton4()));
	connect(ui.b5, SIGNAL(clicked()), this, SLOT(ClickButton5()));
	connect(ui.b6, SIGNAL(clicked()), this, SLOT(ClickButton6()));
	connect(ui.b7, SIGNAL(clicked()), this, SLOT(ClickButton7()));
	connect(ui.b8, SIGNAL(clicked()), this, SLOT(ClickButton8()));
	connect(ui.b9, SIGNAL(clicked()), this, SLOT(ClickButton9()));
	connect(ui.b10, SIGNAL(clicked()), this, SLOT(ClickButton10()));
	connect(ui.b11, SIGNAL(clicked()), this, SLOT(ClickButton11()));
	connect(ui.b12, SIGNAL(clicked()), this, SLOT(ClickButton12()));
	connect(ui.b13, SIGNAL(clicked()), this, SLOT(ClickButton13()));
	setWindowTitle(tr("Homework for image process -- SY1606220"));
}

ImageProc::~ImageProc()
{

}
void ImageProc::ClickButton1()
{
	testFunc(1);
}
void ImageProc::ClickButton2()
{
	testFunc(2);
}
void ImageProc::ClickButton3()
{
	testFunc(3);
}
void ImageProc::ClickButton4()
{
	testFunc(4);
}
void ImageProc::ClickButton5()
{
	testFunc(5);
}
void ImageProc::ClickButton6()
{
	testFunc(6);
}
void ImageProc::ClickButton7()
{
	testFunc(7);
}
void ImageProc::ClickButton8()
{
	testFunc(8);
}
void ImageProc::ClickButton9()
{
	testFunc(9);
}
void ImageProc::ClickButton10()
{
	testFunc(10);
}
void ImageProc::ClickButton11()
{
	testFunc(11);
	const char * str = "average length: 4.49915\n entropy of information: 4.47194 \nCoding efficiencyΪ: 99.3951%\ngo to \"Huffman_result.txt\" for more information";
	QMessageBox::information(this, tr("Huffman Results"), tr(str));
}
void ImageProc::ClickButton12()
{
	testFunc(12);
}
void ImageProc::ClickButton13()
{
	testFunc(13);
}
