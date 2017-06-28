#include <core.hpp>
#include <highgui.hpp>
#include <opencv.hpp>
using namespace cv;
//homework1
bool myReadBMP(char* filename);
bool myAdd(Mat& dst, Mat src1, Mat src2);
bool myNegate(Mat& dst, Mat src);
bool myTranslation(Mat& dst, Mat src, int dx, int dy);
bool myRetote(Mat& dst, Mat src, int a);
bool myMirror(Mat& dst, Mat src, int option);
bool myScale(Mat& dst, Mat src, double dx, double dy);

//homework2
void testFFT2(Mat& m, Mat& amplitude, int size, int offset = 0);
void myFFT2(Mat& real, Mat& imag, Mat src);
void myiFFT2(Mat& dst, Mat real, Mat imag);
void myFFTShift(Mat& src);
void generateTestImage(Mat& img, int TSize, int WSize);
void getAmplitudeAndPhase(Mat& amp, Mat& pha, Mat real, Mat imag);

//homework3
void myHistogram(Mat& dst, Mat src, int degree = 256);
void myMedianFiltering(Mat& dst, Mat src, int windowsize = 3);
void myExponentialChangeEnhancement(Mat& dst, Mat src, double gamma);
void mySoble(Mat& dst, Mat src);
void myLaplace(Mat& dst, Mat src);

//homework4
void myHuffman();

//homework5
void myEdgeDetection(Mat& dst, Mat src, int option, int hist = 1);

//homework6
void myHough(Mat& dst, Mat src, int thres);