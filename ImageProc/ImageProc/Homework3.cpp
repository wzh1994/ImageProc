#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <opencv.hpp>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
using namespace cv;
bool myNegate(Mat& dst, Mat src);
//均衡化
void myHistogram(Mat& dst, Mat src, int degree = 256){
	if (src.channels()>1) cvtColor(src, src, CV_RGB2GRAY);
	dst = src.clone();
	int table[256];
	for (int i = 0; i < 256; i++)
		table[i] = i;
	int items = 256 / degree;
	uchar* q;
	int hist[256];
	double fre[256];
	int cast[256];
	memset(hist, 0, sizeof(hist));
	memset(fre, 0, sizeof(fre));
	memset(cast, 0, sizeof(cast));
	int rows = src.rows;
	int cols = src.cols;
	for (int i = 0; i < rows; ++i)
	{
		q = dst.ptr<uchar>(i);
		for (int j = 0; j < cols; ++j){
			hist[q[j]/items]++;
		}
	}
	for (int i = 0; i < degree; i++){
		fre[i] = (double)hist[i] / (rows*cols);
		if (i != 0) fre[i] = fre[i] + fre[i - 1];
		cast[i] = (int)(fre[i] * degree) - 1;
		cast[i] = cast[i] < 0 ? 0 : cast[i];
		int g = cast[i] * items + items / 2;
		for (int j = 0; j < items; j++){
			table[i*items + j] = g;
		}
	}
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for (int i = 0; i < 256; ++i)
		p[i] = table[i];
	LUT(src, lookUpTable, dst);
}

//中值滤波
void myMedianFiltering(Mat& dst, Mat src,int windowsize=3){
	int cols = src.cols;
	int rows = src.rows;
	int channel = src.channels();
	uchar *p;
	int lr = windowsize / 2;
	vector<int> grees;
	for (int i = lr; i < rows - lr; i++){
		p = dst.ptr<uchar>(i);
		for (int j = lr; j < cols - lr; j++){
			int r = i - lr;
			int c = j - lr;
			for (int s = 0; s < channel; s++){
				grees.clear();
				for (int k = 0; k < windowsize; k++){
					for (int l = 0; l < windowsize; l++){
						grees.push_back(src.at<uchar>(r + k, (c + l)*channel+s));
					}
				}
				sort(grees.begin(), grees.end());
				int pos = windowsize*windowsize / 2;
				p[j*channel + s] = grees[pos];
			}
		}
	}
}

//指数变换增强
void myExponentialChangeEnhancement(Mat& dst, Mat src,double gamma=1){
	int table[256];
	for (int i = 0; i < 256; i++){
		double g = i / (double)255;
		g = pow(g, gamma);
		int gi = g * 255;
		table[i] = gi;
	}
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for (int i = 0; i < 256; ++i)
		p[i] = table[i];
	LUT(src, lookUpTable, dst);
}

//卷积
void myFolding(Mat& dst,Mat src,Mat kernel){
	if (src.channels()>1) cvtColor(src, src, CV_RGB2GRAY);
	src.convertTo(src, CV_32F);
	kernel.convertTo(kernel, CV_32F);
	int srow = src.rows;
	int scol = src.cols;
	int krow = kernel.rows;
	int kcol = kernel.cols;
	int hr = krow / 2;
	int hc = kcol / 2;
	dst = Mat(srow, scol, CV_MAKETYPE(CV_32F, 1), Scalar(0, 0, 0));
	float *p;
	for (int i = hr; i<srow - hr; i++){
		p = dst.ptr<float>(i);
		for (int j = hc; j<scol - hc; j++){
			int r = i - hr;
			int c = j - hc;
			float max = 0;
			for (int k = 0; k < krow; k++){
				for (int l = 0; l < kcol; l++){
					max += kernel.at<float>(k, l)*src.at<float>(r + k, c + l);
				}
			}
			p[j] = max;
		}
	}
	dst.convertTo(dst, CV_8U);
}
//Sobel边缘检测
void mySoble(Mat& dst, Mat src){
	if (src.channels()>1) cvtColor(src, src, CV_RGB2GRAY);
	Mat vkernel = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
	Mat hkernel = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	Mat Vdst,Hdst;
	myFolding(Vdst, src, vkernel);
	myFolding(Hdst, src, hkernel);
	int row = src.rows;
	int col = src.cols;
	dst = Mat(row, col, CV_8UC1, Scalar::all(0));
	uchar *p;
	for (int i = 0; i < row; i++){
		p = dst.ptr<uchar>(i);
		for (int j = 0; j<col; j++){
			int strenth = sqrt(pow(Vdst.at<uchar>(i, j), 2) + pow(Hdst.at<uchar>(i, j), 2));
			p[j] = strenth>255 ? 255 : strenth;
		}
	}
}

//Laplace锐化处理
void myLaplace(Mat& dst, Mat src){
	int rows = src.rows;
	int cols = src.cols;
	int channel = src.channels();
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	/* 对hsv做
	Mat hsvsrc;
	Mat lsrc;
	vector<Mat> hsv;
	if (src.channels() > 1) {
		cvtColor(src, hsvsrc, CV_RGB2HSV);
		split(src, hsv);
		lsrc = hsv[2];
	}
	else{
		lsrc = src;
	}
	Mat Ldst;
	//filter2D(lsrc, Ldst, lsrc.depth(), kernel);
	myFolding(Ldst, lsrc, kernel);
	imshow("l", Ldst);
	uchar *p;
	char *q;
	for (int i = 0; i < rows; ++i)
	{
		p = lsrc.ptr<uchar>(i);
		q = Ldst.ptr<char>(i);
		for (int j = 0; j < cols; ++j)
		{
			int sum = p[j] + q[j];
			p[j] = sum>255 ? 255 : sum;
		}
	}
	if (src.channels() > 1) {
		merge(hsv, dst);
		cvtColor(dst, dst, CV_HSV2RGB);
	}
	else{
		dst = lsrc;
	}
	*/
	//  三个通道分别做
	vector<Mat> bgr;
	split(src, bgr);
	for (int k = 0; k < channel; k++){
		Mat Ldst;
		myFolding(Ldst, bgr[k], kernel);
		uchar *p;
		char *q;
		for (int i = 0; i < rows; ++i)
		{
			p = bgr[k].ptr<uchar>(i);
			q = Ldst.ptr<char>(i);
			for (int j = 0; j < cols; ++j)
			{
				int sum = p[j] + q[j];
				p[j] = sum>255 ? 255 : sum;
			}
		}
	}
	merge(bgr, dst);
	/*int channel = src.channels();
	dst = Mat(rows, cols, CV_MAKETYPE(CV_8U, 3), Scalar(0, 0, 0));
	Mat gsrc;
	if (src.channels()>1) cvtColor(src, gsrc, CV_RGB2GRAY);
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	Mat Ldst;
	myFolding(Ldst, gsrc, kernel);
	imshow("ldst", Ldst);
	myNegate(Ldst, Ldst);
	uchar *p;
	char *q;
	uchar *r;
	for (int i = 0; i < rows; ++i)
	{
		p = src.ptr<uchar>(i);
		q = Ldst.ptr<char>(i);
		r = dst.ptr<uchar>(i);
		for (int j = 0; j < cols; ++j)
		{
			for (int k = 0; k < channel; k++){
				int sum = p[j*channel + k] + q[j];
				r[j*channel + k] = sum>255 ? 255 : sum;
			}	
		}
	}*/
	/*int table[256];
	memset(table, 0, sizeof(table));
	for (int i = 0; i < 15; i++){
		table[i] = 255;
	}
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for (int i = 0; i < 256; ++i)
		p[i] = table[i];
	LUT(src, lookUpTable, dst);
	*/
}