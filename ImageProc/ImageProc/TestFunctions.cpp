#include <iostream>
#include "funcs.hpp"
#define max(_a,_b,_c) (_a>_b?(_a>_c?_a:_c):(_b>_c?_b:_c))
using namespace std;
void readbmpTest(){
	myReadBMP("lena.bmp");
}
void addTest(){
	Mat m1 = imread("lena.jpg");
	Mat m2 = imread("background.jpg");
	int rows = m1.rows;
	int cols = m1.cols;
	resize(m2, m2, Size(rows, cols), 0, 0, CV_INTER_LINEAR);
	m1.convertTo(m1, -1, 0.5, 0);
	m2.convertTo(m2, -1, 0.5, 0);
	Mat m(rows, 3 * cols, CV_8UC3, Scalar(0, 0, 0));
	Mat imageRIO1 = m(Rect(0, 0, cols, rows));
	m1.copyTo(imageRIO1);
	Mat imageRIO2 = m(Rect(cols, 0, cols, rows));
	m2.copyTo(imageRIO2);
	Mat imageRIO3 = m(Rect(2*cols, 0, cols, rows));
	myAdd(imageRIO3, m1, m2);
	imshow("Add", m);
}
void negateAndTranslationTest(){
	Mat m1 = imread("lena.jpg");
	int rows = m1.rows;
	int cols = m1.cols;
	Mat m(2*rows+1, 3 * cols+2, CV_8UC3, Scalar(0, 0, 0));
	Mat imageRIO1 = m(Rect(0, 0, cols, rows));
	Mat imageRIO2 = m(Rect(cols+1, 0, cols, rows));
	Mat imageRIO3 = m(Rect(2 * cols+2, 0, cols, rows));
	Mat imageRIO4 = m(Rect(0, rows+1, cols, rows));
	Mat imageRIO5 = m(Rect(cols+1, rows+1, cols, rows));
	Mat imageRIO6 = m(Rect(2 * cols+2, rows+1, cols, rows));
	m1.copyTo(imageRIO1);
	myNegate(imageRIO2, m1);
	myTranslation(imageRIO3, m1, 50, 0);
	myTranslation(imageRIO4, m1, -50, 0);
	myTranslation(imageRIO5, m1, 0, 50);
	myTranslation(imageRIO6, m1, 50, 70);
	imshow("求反和平移", m);
}
void retoteTest(){
	Mat img = imread("lena.jpg");
	Mat  m2, m3, m4, m5,m6;
	int rows = img.rows;
	int cols = img.cols;
	myRetote(m2, img, -90);
	myRetote(m3, img, 180);
	int r2 = m2.rows;
	int c2 = m2.cols;
	int r3 = m3.rows;
	int c3 = m3.cols;
	int maxrow = max(rows, r2, r3);
	Mat m(maxrow, cols+c2+c3+2, CV_8UC3, Scalar(255, 255, 255));
	Mat imageRIO1 = m(Rect(0, 0, cols, rows));
	Mat imageRIO2 = m(Rect(cols + 1, 0, c2, r2));
	Mat imageRIO3 = m(Rect(cols+c2 + 2, 0, c3, r3));
	img.copyTo(imageRIO1);
	m2.copyTo(imageRIO2);
	m3.copyTo(imageRIO3);
	imshow("旋转1", m);
	myRetote(m4, img, -45);
	myRetote(m5, img, -110);
	myRetote(m6, img, 110);
	int r4 = m4.rows;
	int c4 = m4.cols;
	int r5 = m5.rows;
	int c5 = m5.cols;
	int r6 = m6.rows;
	int c6 = m6.cols;
	maxrow = max(r4, r5, r6);
	m=Mat(maxrow, c4 + c5 + c6 + 2, CV_8UC3, Scalar(255, 255, 255));
	Mat imageRIO4 = m(Rect(0, 0, c4,r4 ));
	Mat imageRIO5 = m(Rect(c4+1, 0, c5, r5));
	Mat imageRIO6 = m(Rect(c4+c5+2, 0, c6, r6));
	m4.copyTo(imageRIO4);
	m5.copyTo(imageRIO5);
	m6.copyTo(imageRIO6);
	imshow("旋转2", m);
}
void mirrorTest(){
	Mat img = imread("lena.jpg");
	int rows = img.rows;
	int cols = img.cols;
	Mat m(2*rows+1, 2 * cols + 1, CV_8UC3, Scalar(0, 0, 0));
	Mat imageRIO1 = m(Rect(0, 0, cols, rows));
	Mat imageRIO2 = m(Rect(cols + 1, 0, cols, rows));
	Mat imageRIO3 = m(Rect(0, rows+1, cols, rows));
	Mat imageRIO4 = m(Rect(cols+1 , rows + 1, cols, rows));
	img.copyTo(imageRIO1);
	myMirror(imageRIO2, img, 1);
	myMirror(imageRIO3, img, 2);
	myMirror(imageRIO4, img, 3);
	imshow("镜像", m);
}
void scaleTest(){
	Mat img = imread("lena.jpg");
	Mat  m2, m3;
	int rows = img.rows;
	int cols = img.cols;
	myScale(m2, img,0.5,0.5);
	myScale(m3, img, 2.3,1.5);
	int r2 = m2.rows;
	int c2 = m2.cols;
	int r3 = m3.rows;
	int c3 = m3.cols;
	int maxrow = max(rows, r2, r3);
	Mat m(maxrow, cols + c2 + c3 + 2, CV_8UC3, Scalar(255, 255, 255));
	Mat imageRIO1 = m(Rect(0, 0, cols, rows));
	Mat imageRIO2 = m(Rect(cols + 1, 0, c2, r2));
	Mat imageRIO3 = m(Rect(cols + c2 + 2, 0, c3, r3));
	img.copyTo(imageRIO1);
	m2.copyTo(imageRIO2);
	m3.copyTo(imageRIO3);
	imshow("缩放", m);
}
void FFTTest(){
	Mat img = imread("lena.jpg");
	int rows = img.rows;
	int cols = img.cols;
	Mat m(rows*2+1, cols * 2 + 1, CV_8U, Scalar(255, 255, 255));
	Mat imageRIO1 = m(Rect(0, 0, cols, rows));
	Mat imageRIO2 = m(Rect(cols + 1, 0, cols, rows));
	Mat imageRIO3 = m(Rect(0, rows+1, cols, rows));
	Mat imageRIO4 = m(Rect(cols + 1, rows + 1, cols, rows));
	Mat real,imag;
	myFFT2(real, imag, img);
	Mat amplitude, phase;
	getAmplitudeAndPhase(amplitude, phase, real, imag);
	Mat fftr;
	amplitude.convertTo(fftr, -1, 255, 0);
	fftr.convertTo(fftr, CV_8U);
	fftr.copyTo(imageRIO3);
	myFFTShift(amplitude);
	amplitude.convertTo(amplitude, -1, 255, 0);
	amplitude.convertTo(amplitude, CV_8U);
	amplitude.copyTo(imageRIO2);
	Mat img_ifft;
	myiFFT2(img_ifft, real, imag);
	img_ifft.convertTo(img_ifft, CV_8U);
	img_ifft.copyTo(imageRIO4);
	cvtColor(img,img, CV_RGB2GRAY);
	img.copyTo(imageRIO1);
	imshow("FFT变换及反变换", m);
	/*---------     test2    ------------*/
	int row = 128;
	int col = 128;
	m=Mat(row*2+1, col * 4 + 3, CV_8U, Scalar(255, 255, 255));
	Mat RIO1 = m(Rect(0, 0, col, row));
	Mat RIO3 = m(Rect(col + 1, 0, col, row));
	Mat RIO5 = m(Rect(2 * col + 2, 0, col, row));
	Mat RIO7 = m(Rect(3 * col + 3, 0, col, row));
	Mat RIO2 = m(Rect(0, row + 1 ,col, row));
	Mat RIO4 = m(Rect(col + 1, row+1, col, row));
	Mat RIO6 = m(Rect(2 * col + 2, row + 1, col, row));
	Mat RIO8 = m(Rect(3 * col + 3, row + 1, col, row));
	Mat block, fftresult;
	testFFT2(block, fftresult, 4, 0);
	block.copyTo(RIO1);
	fftresult.copyTo(RIO2);
	testFFT2(block, fftresult, 10, 0);
	block.copyTo(RIO3);
	fftresult.copyTo(RIO4);
	testFFT2(block, fftresult, 2, 0);
	block.copyTo(RIO5);
	fftresult.copyTo(RIO6);
	testFFT2(block, fftresult, 4, -40);
	block.copyTo(RIO7);
	fftresult.copyTo(RIO8);
	imshow("FFT测试2", m);
}
void histogramAndMedianFilteringTest(){
	Mat img = imread("lena.jpg");
	int row = img.rows;
	int col = img.cols;
	Mat m(row , col * 3 + 2, CV_8U, Scalar(255, 255, 255));
	Mat RIO1 = m(Rect(0, 0, col, row));
	Mat RIO2 = m(Rect(col + 1, 0, col, row));
	Mat RIO3 = m(Rect(2 * col + 2, 0, col, row));
	cvtColor(img, img, CV_RGB2GRAY);
	img.copyTo(RIO1);
	Mat h;
	myHistogram(h, img);
	h.copyTo(RIO2);
	myMedianFiltering(h, img);
	h.copyTo(RIO3);
	imshow("均衡化和中值滤波",m);
}
void exponentialTest(){
	Mat img = imread("lena.jpg");
	int row = img.rows;
	int col = img.cols;
	Mat m(row, col * 3 + 2, CV_8U, Scalar(255, 255, 255));
	Mat RIO1 = m(Rect(0, 0, col, row));
	Mat RIO2 = m(Rect(col + 1, 0, col, row));
	Mat RIO3 = m(Rect(2 * col + 2, 0, col, row));
	cvtColor(img, img, CV_RGB2GRAY);
	img.copyTo(RIO1);
	Mat e;
	myExponentialChangeEnhancement(e, img,0.2);
	e.copyTo(RIO2);
	myExponentialChangeEnhancement(e, img, 3);
	e.copyTo(RIO3);
	imshow("指数变换增强", m);
}
void testSobleAndLaplace(){
	Mat img = imread("lena.jpg");
	int rows = img.rows;
	int cols = img.cols;
	Mat m(rows * 2 + 1, cols * 2 + 1, CV_8UC3, Scalar(255, 255, 255));
	Mat imageRIO1 = m(Rect(0, 0, cols, rows));
	Mat imageRIO2 = m(Rect(cols + 1, 0, cols, rows));
	Mat imageRIO3 = m(Rect(0, rows + 1, cols, rows));
	Mat imageRIO4 = m(Rect(cols + 1, rows + 1, cols, rows));
	img.copyTo(imageRIO1);
	Mat sob;
	mySoble(sob, img);
	cvtColor(sob, sob, CV_GRAY2BGR);
	sob.copyTo(imageRIO2);
	Mat lap;
	myEdgeDetection(lap, img, 4, 0);
	cvtColor(lap, lap, CV_GRAY2BGR);
	lap.copyTo(imageRIO3);
	Mat lapimg;
	myLaplace(lapimg, img);
	lapimg.copyTo(imageRIO4);
	imshow("sobel算子和laplace算子检测边缘以及锐化结果", m);
}
void edgeDetectionTest(){
	Mat img = imread("lena.jpg");
	int rows = img.rows;
	int cols = img.cols;
	Mat m(rows * 3 + 2, cols * 3 + 2, CV_8U, Scalar(255, 255, 255));
	Mat imageRIO1 = m(Rect(0, 0, cols, rows));
	Mat imageRIO2 = m(Rect(cols + 1, 0, cols, rows));
	Mat imageRIO3 = m(Rect(2*cols + 2, 0, cols, rows));
	Mat imageRIO4 = m(Rect(0, rows+1, cols, rows));
	Mat imageRIO5 = m(Rect(cols + 1, rows + 1, cols, rows));
	Mat imageRIO6 = m(Rect(2 * cols + 2, rows + 1, cols, rows));
	Mat imageRIO7 = m(Rect(0, 2*rows+2, cols, rows));
	Mat imageRIO8 = m(Rect(cols + 1, 2 * rows + 2, cols, rows));
	Mat imageRIO9 = m(Rect(2 * cols + 2, 2 * rows + 2, cols, rows));
	cvtColor(img,img, CV_RGB2GRAY);
	img.copyTo(imageRIO1);
	Mat result;
	myEdgeDetection(result, img, 1, 0);
	result.copyTo(imageRIO2);
	myEdgeDetection(result, img, 1);
	result.copyTo(imageRIO3);
	myEdgeDetection(result, img, 2, 0);
	result.copyTo(imageRIO4);
	myEdgeDetection(result, img, 2);
	result.copyTo(imageRIO5);
	myEdgeDetection(result, img, 3, 0);
	result.copyTo(imageRIO6);
	myEdgeDetection(result, img, 3);
	result.copyTo(imageRIO7);
	myEdgeDetection(result, img, 4, 0);
	result.copyTo(imageRIO8);
	myEdgeDetection(result, img, 4);
	result.copyTo(imageRIO9);
	resize(m, m, Size(0, 0), 0.8, 0.8, 1);
	imshow("边缘检测",m);
}
void houghTest(){
	Mat img = imread("hough.jpg");
	int rows = img.rows;
	int cols = img.cols;
	Mat m(rows*2+1, cols , CV_8UC3, Scalar(255, 255, 255));
	Mat imageRIO1 = m(Rect(0, 0, cols, rows));
	Mat imageRIO2 = m(Rect(0, rows + 1, cols, rows));
	Mat hresult;
	myHough(hresult, img,1);
	cvtColor(hresult, hresult, CV_GRAY2BGR);
	img.copyTo(imageRIO1);
	hresult.copyTo(imageRIO2);
	imshow("霍夫变换检测三条直线", m);
}
void testFunc(int index){
	if (index==1)
		readbmpTest();
	else if (index == 2)
		addTest();
	else if (index == 3)
		negateAndTranslationTest();
	else if (index == 4)
		retoteTest();
	else if (index == 5)
		mirrorTest();
	else if (index == 6)
		scaleTest();
	else if (index == 7)
		FFTTest();
	else if (index == 8)
		histogramAndMedianFilteringTest();
	else if (index == 9)
		exponentialTest();
	else if (index == 10)
		testSobleAndLaplace();
	else if (index == 11)
		myHuffman();
	else if (index == 12)
		edgeDetectionTest();
	else if (index == 13)
		houghTest();
}