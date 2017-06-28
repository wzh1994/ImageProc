#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <opencv.hpp>
#include <cmath>
#include <vector>
using namespace std;
using namespace cv;
#define PI 3.141592654
typedef struct cnode
{
	double real;
	double imag; //imaginary 虚数部分
	cnode() :real(0), imag(0){}
	cnode(double r, double i) :real(r), imag(i){}
}ComplexNum;
ComplexNum operator* (ComplexNum const & c1, ComplexNum const & c2)
{
	ComplexNum result;
	result.real = c1.real * c2.real - c1.imag * c2.imag;
	result.imag = c1.real * c2.imag + c1.imag * c2.real;
	return result;
}
ComplexNum operator+ (ComplexNum const & c1, ComplexNum const & c2)
{
	ComplexNum result;
	result.real = c1.real + c2.real;
	result.imag = c1.imag + c2.imag;
	return result;
}
ComplexNum operator- (ComplexNum const & c1, ComplexNum const & c2)
{
	ComplexNum result;
	result.real = c1.real - c2.real;
	result.imag = c1.imag - c2.imag;
	return result;
}
void getWNk(ComplexNum& result,double N, double k){
	double w = 2*PI*k / N;
	result.real = cos(w);
	result.imag = -sin(w);
}
void Reverse(vector<ComplexNum>& line){
	int N = line.size();
	ComplexNum temp;
	for (int i = 0; i<N; i++)
	{
		int now = i;
		int rev = 0;
		for (int t = 0; t<log2(N); t++)
		{
			rev <<= 1;
			rev |= (now & 1);
			now >>= 1;
		}
		if (rev>i)
		{
			temp = line[i];
			line[i] = line[rev];
			line[rev] = temp;
		}
	}
}
void myFFT(vector<ComplexNum>& line){
	int N = line.size();
	Reverse(line); 
	for (int i = 0; i<log2(N); i++){  //共log2(N)级
		int l = 1 << i;//l为每组中元素的个数 等于2的i次方
		for (int j = 0; j<N; j += 2 * l){  //每级有N/2L组 
			for (int k = 0; k<l; k++){   //每组有L对运算
				ComplexNum wn;
				getWNk(wn, 2*l, k);//getWNk(wn, N, N*k/(2*l));
				ComplexNum xW = line[j + k + l] * wn;
				ComplexNum addRes = line[j + k]+ xW; 
				ComplexNum misRes = line[j + k]- xW;
				line[j + k] = addRes;
				line[j + k + l] = misRes;
			}
		}
	}
}

void myiFFT(vector<ComplexNum>& line){
	int N = line.size();
	for (int i = 0; i < N; i++){
		line[i].imag = -line[i].imag;
	}
	myFFT(line);
	for (int i = 0; i < line.size(); i++){
		line[i].real /= N;
		line[i].imag = -line[i].imag/N;
	}
}
//dir=1:行,dir=2:列; rw=1:读到矢量,rw=2:写入图像 index:行(列)号
void calcWithVector(Mat& real,Mat& imag,vector<ComplexNum>& vec,int dir,int rw,int index){
	if (rw == 1) vec.clear();
	int col = real.cols;
	int row = real.rows;
	if (dir == 1){
		float *pr = real.ptr<float>(index);
		float *pi = imag.ptr<float>(index);
		for (int i = 0; i < col; i++){
			if (rw == 1){
				vec.push_back(ComplexNum(pr[i], pi[i]));
			}
			else{
				pr[i] = (float)vec[i].real;
				pi[i] = (float)vec[i].imag;
			}
		}
	}
	else{
		//cout << "fft:column " << index << " read";
		for (int i = 0; i < row; i++){
			//cout << " " << i;
			float *pr = real.ptr<float>(i);
			float *pi = imag.ptr<float>(i);
			if (rw == 1){
				vec.push_back(ComplexNum(pr[index], pi[index]));
			}
			else{
				pr[index] = (float)vec[i].real;
				pi[index] = (float)vec[i].imag;
			}
		}
	}
}
void myFFTShift(Mat& src){
	int cx = src.cols / 2;
	int cy = src.rows / 2;
	Mat q0(src, Rect(0, 0, cx, cy));   // Top-Left 
	Mat q1(src, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(src, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(src, Rect(cx, cy, cx, cy)); // Bottom-Right
	Mat tmp;                          
	q0.copyTo(tmp);//交换左上和右下
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);//交换右上和左下             
	q2.copyTo(q1);
	tmp.copyTo(q2);
}
void getAmplitudeAndPhase(Mat& amp,Mat& pha,Mat real,Mat imag){
	int row = real.rows;
	int col = real.cols;
	Mat m1(row, col, CV_32F, Scalar::all(0));
	Mat m2(row, col, CV_32F, Scalar::all(0));
	amp = m1;
	pha = m2;
	for (int i = 0; i < row; i++){
		float *pr = real.ptr<float>(i);
		float *pi = imag.ptr<float>(i);
		float *pa = amp.ptr<float>(i);
		float *pp = pha.ptr<float>(i);
		for (int j = 0; j < col; j++){
			float amplitude = log2(sqrt(pow(pr[j], 2) + pow(pi[j], 2)) + 1);
			float phase = atan(pi[j] / pr[j]);
			pa[j] = amplitude;
			pp[j] = phase;
		}
	}
	normalize(amp, amp, 0, 1, CV_MINMAX);
	//cout << amp;
	myFFTShift(amp);
}
//目前默认输入图像长和宽都为2的整数次幂
void myFFT2(Mat& real,Mat& imag, Mat src){
	//Mat padded;                            
	//int m = getOptimalDFTSize(src.rows);
	//int n = getOptimalDFTSize(src.cols);
	//copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));
	if (src.channels() > 1) cvtColor(src, src, CV_RGB2GRAY);
	int row = src.rows;
	int col = src.cols;
	src.convertTo(real, CV_32F);
	imag=Mat(row,col,CV_32F,Scalar::all(0));
	vector<ComplexNum> vec;
	//逐行做傅里叶变换
	for (int i = 0; i < row; i++){
		calcWithVector(real, imag, vec, 1, 1, i);
		//cout << "fft:line " << i << "read done" << endl;
		myFFT(vec);
		//cout << "fft:line " << i << "change done" << endl;
		calcWithVector(real, imag, vec, 1, 2, i);
		//cout << "fft:line " <<i <<"done"<< endl;
	}
	//逐列做傅里叶变换
	for (int i = 0; i < col; i++){
		calcWithVector(real, imag, vec, 2, 1, i);
		//cout << "fft:column " << i << "read done" << endl;
		myFFT(vec);
		//cout << "fft:column " << i << "change done" << endl;
		calcWithVector(real, imag, vec, 2, 2, i);
		//cout << "fft:column " << i << "done" << endl;
	}
}


void myiFFT2(Mat& dst, Mat real,Mat imag){
	int row = real.rows;
	int col = imag.cols;
	vector<ComplexNum> vec;
	//逐行做傅里叶变换
	for (int i = 0; i < row; i++){
		calcWithVector(real, imag, vec, 1, 1, i);
		myiFFT(vec);
		calcWithVector(real, imag, vec, 1, 2, i);
	}
	//逐列做傅里叶变换
	for (int i = 0; i < col; i++){
		calcWithVector(real, imag, vec, 2, 1, i);
		myiFFT(vec);
		calcWithVector(real, imag, vec, 2, 2, i);
	}
	dst = real.clone();
}

void generateTestImage(Mat& img,int TSize,int WSize,int offset=0){
	img = Mat(TSize, TSize, CV_8U, Scalar::all(0));
	int l = TSize / 2 - WSize / 2 + offset;
	int r = TSize / 2 + WSize / 2 + 1 + offset;
	for (int i = l; i <=r; i++){
		uchar *p = img.ptr<uchar>(i);
		for (int j = l; j <= r; j++){
			p[j] = 255;
		}
	}
}

/*void testFFT(){
	vector<ComplexNum> line;
	for (int i = 0; i < 128; i++){
		line.push_back(ComplexNum(i, 0));
	}
	myFFT(line);
	for (int i = 0; i < 128; i++)
		cout << "(" << line[i].real << "+" << line[i].imag << ") " << endl;
}*/

void testFFT2(Mat& m, Mat& amplitude,int size, int offset = 0){
	generateTestImage(m, 128, size,offset);
	//imshow("yt", m);
	Mat real,imag,phase;
	myFFT2(real,imag, m);
	getAmplitudeAndPhase(amplitude, phase, real, imag);
	//imshow("fft", amplitude);
	//myiFFT2(m, real, imag);
	//imshow("ifft", m);
	amplitude.convertTo(amplitude, -1, 255, 0);
	amplitude.convertTo(amplitude, CV_8U);
}