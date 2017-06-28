#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <opencv.hpp>
using namespace std;
using namespace cv;
void myFolding(Mat& dst, Mat src, Mat kernel);
void mySoble(Mat& dst, Mat src);
void myHistogram(Mat& dst, Mat src, int degree = 256);

void myRoberts(Mat& dst, Mat src){
	if (src.channels()>1) cvtColor(src, src, CV_RGB2GRAY);
	Mat vkernel = (Mat_<float>(2, 2) << -1, 0, 0, 1);
	Mat hkernel = (Mat_<float>(2, 2) << 0,-1, 1, 0 );
	Mat Vdst, Hdst;
	filter2D(src, Vdst, src.depth(), vkernel);
	filter2D(src, Hdst, src.depth(), hkernel);
	Vdst.convertTo(Vdst, CV_32F);
	Hdst.convertTo(Hdst, CV_32F);
	int row = src.rows;
	int col = src.cols;
	dst = Mat(row, col, CV_32F, Scalar::all(0));
	float *p;
	int max = 0;
	for (int i = 0; i < row; i++){
		p = dst.ptr<float>(i);
		for (int j = 0; j<col; j++){
			int strenth = sqrt(pow(Vdst.at<float>(i, j), 2) + pow(Hdst.at<float>(i, j), 2));
			p[j] = strenth;// >255 ? 255 : strenth;
			if (strenth>max) max = strenth;
		}
	}
	for (int i = 0; i < row; i++){
		p = dst.ptr<float>(i);
		for (int j = 0; j < col; j++){
			p[j] = p[j] / max * 255;
		}
	}
	dst.convertTo(dst, CV_8U);
}

void myPrewitt(Mat& dst, Mat src){
	if (src.channels()>1) cvtColor(src, src, CV_RGB2GRAY);
	Mat vkernel = (Mat_<float>(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);
	Mat hkernel = (Mat_<float>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
	Mat Vdst, Hdst;
	myFolding(Vdst, src, vkernel);
	myFolding(Hdst, src, hkernel);
	Vdst.convertTo(Vdst, CV_32F);
	Hdst.convertTo(Hdst, CV_32F);
	int row = src.rows;
	int col = src.cols;
	dst = Mat(row, col, CV_32F, Scalar::all(0));
	float *p;
	int max = 0;
	for (int i = 0; i < row; i++){
		p = dst.ptr<float>(i);
		for (int j = 0; j<col; j++){
			int strenth = sqrt(pow(Vdst.at<float>(i, j), 2) + pow(Hdst.at<float>(i, j), 2));
			p[j] = strenth;// >255 ? 255 : strenth;
			if (strenth>max) max = strenth;
		}
	}
	for (int i = 0; i < row; i++){
		p = dst.ptr<float>(i);
		for (int j = 0; j < col; j++){
			p[j] = p[j] / max * 255;
		}
	}
	dst.convertTo(dst, CV_8U);
}

void myLaplaceE(Mat& dst, Mat src){
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	myFolding(dst, src, kernel);
}

//Roberts（1）、Sobel（2）、Prewitt（3）、Laplace（4） hist表示是否均衡化
void myEdgeDetection(Mat& dst,Mat src,int option,int hist=1){
	if (option == 1 || option == 5){
		myRoberts(dst, src);
		if (hist) myHistogram(dst, dst);
		//imshow("robert", dst);
	}
	if (option == 2 || option == 5){
		mySoble(dst, src);
		if (hist) myHistogram(dst, dst);
		//imshow("Sobel", dst);
	}
	if (option == 3 || option == 5){
		myPrewitt(dst, src);
		if (hist) myHistogram(dst, dst);
		//imshow("Prewitt", dst);
	}
	if (option == 4 || option == 5){
		myLaplaceE(dst, src);
		if (hist) myHistogram(dst, dst);
		//imshow("Laplace", dst);
	}
}
