#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <opencv.hpp>
#include <cmath>
#include <windows.h>
#define PI 3.14159265358979323846
using namespace std;
using namespace cv;
/*
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef struct  tagBITMAPFILEHEADER{
	WORD bfType;//������0x424D�����ַ���BM��
	DWORD bfSize;//��С
	WORD bfReserved1;//����
	WORD bfReserved2;//����
	DWORD bfOffBits;//����ƫ��
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	DWORD biSize;//��Ϣͷ��С
	DWORD biWidth;//���
	DWORD biHeight;//�߶�
	WORD biPlanes;//λƽ����
	WORD biBitCount;//ÿ����λ��
	DWORD  biCompression; //ѹ������
	DWORD  biSizeImage; //ѹ��ͼ���С
	DWORD  biXPelsPerMeter; //ˮƽ�ֱ���
	DWORD  biYPelsPerMeter; //��ֱ�ֱ���
	DWORD  biClrUsed; //ɫ����
	DWORD  biClrImportant; //��Ҫ��ɫ����
}BITMAPINFOHEADER; 

typedef struct tagRGBQUAD{//��ɫ��
	BYTE rgbBlue; //��ɫ����
	BYTE rgbGreen; //��ɫ����
	BYTE rgbRed; //��ɫ����
	BYTE rgbReserved; //����ֵ
}RGBQUAD;
*/
bool myReadBMP(char* filename){
	WORD type;
	FILE *fp;
	RGBQUAD strPla[256];
	BITMAPINFOHEADER head;
	if ((fp = fopen(filename, "rb")) == NULL) return false;
	fseek(fp,    sizeof(BITMAPFILEHEADER), 0);
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	int w, h, b;
	w = head.biWidth;
	h = head.biHeight;
	b = head.biBitCount / 8;
	int lineByte = (w * b + 3) / 4 * 4; //ÿ�е��ֽ���Ϊ4�ı���  
	if (b == 1)	fseek(fp, 1024, 1); //�Ҷ�ͼ������ɫ��
	Mat img;
	if (b == 1) img = Mat(w, h, CV_8U, Scalar::all(0));
	else img = Mat(w, h, CV_8UC3, Scalar(0, 0, 0));
	uchar *p;
	for (int i = h-1; i >= 0; i--){//������Ϊʲô ���Ŷ�ͼƬ�ᵹ����
		p = img.ptr<uchar>(i);
		fread(p, w*b, 1, fp);
		fseek(fp, lineByte - w*b, 1);
	}
	imshow(filename,img);
	fclose(fp);
	return true;
}

//������ͼƬ�ĺ�
bool myAdd(Mat& dst, Mat src1, Mat src2){
	if (src1.channels() != src2.channels()) return false;
	int s1_rows = src1.rows ;
	int s1_cols = src1.cols*src1.channels();
	int s2_rows = src2.rows;
	int s2_cols = src2.cols*src2.channels();
	if (s1_rows != s2_rows || s1_cols != s2_cols) return false;
	src1.copyTo(dst);
	uchar *p,*q;
	for (int i = 0; i < s1_rows; ++i)
	{
		p = dst.ptr<uchar>(i);
		q = src2.ptr<uchar>(i);
		for (int j = 0; j < s1_cols; ++j)
		{
			p[j] += q[j];
		}
	}
	return true;
}

//��
bool myNegate(Mat& dst, Mat src){
	int rows = src.rows;
	int cols = src.cols*src.channels();
	src.copyTo(dst);
	uchar *p;
	for (int i = 0; i < rows; ++i)
	{
		p = dst.ptr<uchar>(i);
		for (int j = 0; j < cols; ++j)
		{
			p[j] =255-p[j];
		}
	}
	return true;
}

//ƽ�� ��x��ƽ��dx����y��ƽ��dy
bool myTranslation(Mat& dst, Mat src, int dx, int dy){
	int rows = src.rows;
	int channel = src.channels();
	int cols = src.cols*src.channels();
	src.copyTo(dst);
	uchar *p;
	for (int i = 0; i < rows; ++i)
	{
		p = dst.ptr<uchar>(i);
		for (int j = 0; j < cols; ++j)
		{
			int r = (i + dy + rows) % rows;
			int c = (j + dx*channel + cols) % cols;
			p[j] = src.at<uchar>(r, c);
		}
	}
	return true;
}
//��ֵ
void myLinearInsert(Mat src, double r, double c, int *result){
	int channel = src.channels();
	int srows = src.rows;
	int scols = src.cols;
	if (r<0 || r > srows - 1 || c<0 || c>scols - 1){
		for (int k = 0; k < channel; k++)
			result[k] = 0;
	}
	else if ((r == 0 || r == srows - 1) && (c == 0 || c == scols - 1)){
		for (int k = 0; k < channel; k++)
			result[k] = src.at<uchar>(r, c*channel + k);
	}
	else if (r == 0 || r == srows - 1){
		for (int k = 0; k < channel; k++){
			double weight = c - int(c);
			result[k] = src.at<uchar>(int(r), int(c)*channel + k)*(1 - weight) + src.at<uchar>(int(r), int(c)*channel + channel + k)*weight;
		}
	}
	else if (c == 0 || c == scols - 1){
		for (int k = 0; k < channel; k++){
			double weight = r - int(r);
			result[k] = src.at<uchar>(int(r), int(c)*channel + k)*(1 - weight) + src.at<uchar>(int(r) + 1, int(c)*channel + k)*weight;
		}
	}
	else{
		int tlr, tlc, trr, trc, blr, blc, brr, brc;
		for (int k = 0; k < channel; k++){
			tlr = trr = int(r);
			blr = brr = int(r) + 1;
			tlc = blc = int(c)*channel + k;
			trc = brc = int(c)*channel + channel + k;
			double rweight = r - int(r);
			double cweight = c - int(c);
			result[k] = ((src.at<uchar>(tlr, tlc)*(1 - rweight) + src.at<uchar>(trr, trc)*rweight))*(1 - cweight) +
				((src.at<uchar>(blr, blc)*(1 - rweight) + src.at<uchar>(brr, brc)*rweight))*cweight;
		}
	}
}

//��ת ��תa�ȣ��Ƕȣ�
bool myRetote(Mat& dst, Mat src, int a){
	int srows = src.rows;
	int scols = src.cols;
	int channel = src.channels();
	a = (a+360) % 360;
	double w = a * PI/180;
	int left, right, top, bottom,dx,dy;
	if (a <= 90){
		left = -sin(w)*scols;
		top = sin(w)*srows + cos(w)*scols;
		right = cos(w)*srows;
		bottom = 0;
		dx = left;
		dy = 0;
	}
	else if (a < 180){
		top = sin(w)*srows;
		left = cos(w)*srows - sin(w)*scols;
		right = 0;
		bottom = cos(w)*scols;
		dx = left;
		dy = bottom;
	}
	else if (a < 270){
		top = 0;
		left = cos(w)*srows;
		right = -sin(w)*scols;
		bottom = sin(w)*srows+cos(w)*scols;
		dx = left;
		dy = bottom;
	}
	else{
		left = 0;
		right = cos(w)*srows - sin(w)*scols;
		top = cos(w)*scols;
		bottom = sin(w)*srows;
		dx = 0;
		dy = bottom;
	}
	int drows = right - left + 1;
	int dcols = top - bottom + 1;
	dst = Mat(drows, dcols, CV_MAKETYPE(CV_8U, channel), Scalar(0, 0, 0));
	uchar *p;
	for (int i = 0; i < drows; ++i)
	{
		p = dst.ptr<uchar>(i);
		for (int j = 0; j < dcols; ++j)
		{
			double r, c;
			int ri = i + dx;
			int ci = j + dy;
			r = cos(w)*ri + sin(w)*ci;
			c = -sin(w)*ri + cos(w)*ci;
			int result[3];
			myLinearInsert(src, r, c, result);
			for (int k = 0; k < channel; k++){
				p[3 * j + k] = result[k];
			}
		}
	}
	return true;
}

//����
bool myMirror(Mat& dst, Mat src, int option){
	int rows = src.rows;
	int channel = src.channels();
	int cols = src.cols;
	src.copyTo(dst);
	uchar *p;
	for (int i = 0; i < rows; ++i)
	{
		p = dst.ptr<uchar>(i);
		for (int j = 0; j < cols; ++j)
		{
			int r, c;
			r = (option == 1 || option == 3) ?rows-i-1 : i;
			c = (option == 2 || option == 3) ? cols- j-1 : j;
			for (int k = 0; k < channel; k++){
				p[3 * j + k] = src.at<uchar>(r, 3 * c + k);
			}
		}
	}
	return true;
}

//���� 
bool myScale(Mat& dst, Mat src, double dx, double dy){
	int channel = src.channels();
	int srows = src.rows;
	int scols = src.cols;
	int drows = srows*dy;
	dy = (drows-1) / (double)(srows-1);
	int dcols = scols*dx;
	dx = (dcols-1) / (double)(scols-1);
	dst = Mat(drows, dcols, CV_MAKETYPE(CV_8U, channel), Scalar(0, 0, 0));
	uchar *p;
	for (int i = 0; i < drows; ++i)
	{
		p = dst.ptr<uchar>(i);
		for (int j = 0; j < dcols; ++j)
		{
			double r, c;
			r = i / dy;
			c = j / dx;
			int result[3];
			myLinearInsert(src,r,c,result);
			for (int k = 0; k < channel; k++){
				p[3 * j + k] = result[k];
			}
		}
	}
	return true;
}