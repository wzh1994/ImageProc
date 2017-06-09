#include "imageproc.h"
#include <core.hpp>
#include <highgui.hpp>
#include <opencv.hpp>
#include <QtWidgets/QApplication>
using namespace cv;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageProc w;
	w.show();
	Mat M = imread("ss.jpg");
	imshow("12",M);
	waitKey(0);
	return a.exec();}
