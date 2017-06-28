#include "imageproc.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <highgui.hpp>
using namespace cv;
#define DEBUG 1
void testFunc();
int main(int argc, char *argv[])
{
#if DEBUG
	freopen("debug.txt", "w", stdout);
#endif

	QApplication imageProcWzh(argc, argv);
	ImageProc window;
	window.show();
	waitKey();
	return imageProcWzh.exec();
}
