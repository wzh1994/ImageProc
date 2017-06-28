#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <opencv.hpp>
#include <map>
#include <vector>
#include <algorithm>
#define PI 3.141592654
typedef struct pair{
	int rho;
	int theta;
	pair():rho(0),theta(0){}
	pair(int rho, int theta) :rho(rho), theta(theta){};
	bool operator<(const pair& p) const{
		return rho < p.rho || rho == p.rho&&theta < p.theta;
	}
}Args;
typedef struct flue{
	int rho;
	int theta;
	int flu;
	int number;
	flue():flu(0){}
	flue(int rho, int theta,int flu) :rho(rho), theta(theta),flu(flu),number(1){};
	flue(int rho, int theta, int flu, int number) :rho(rho), theta(theta), flu(flu), number(1){};
	bool operator<(const flue& p) const{
		return flu > p.flu;
	}
}Flus;
Flus operator + (const Flus& f1, const Flus& f2){
	int num = f1.number + f2.number;
	int flu = f1.flu + f2.flu;
	int r = (f1.rho*f1.number + f2.rho*f2.number) / num;
	int t = (f1.theta*f1.number + f2.theta*f2.number) / num;
	return Flus(r, t, flu, num);
	//return Flus(f1.rho, f1.theta, flu, num);
}
using namespace std;
using namespace cv;
void myEdgeDetection(Mat& dst, Mat src, int option, int hist = 1);
void thinImage(Mat &srcimage)
{
	vector<Point> deletelist1;
	int mude[9];
	int nl = srcimage.rows;
	int nc = srcimage.cols;
	while (true)
	{
		for (int j = 1; j < (nl - 1); j++)
		{
			uchar* data_last = srcimage.ptr<uchar>(j - 1);
			uchar* data = srcimage.ptr<uchar>(j);
			uchar* data_next = srcimage.ptr<uchar>(j + 1);
			for (int i = 1; i < (nc - 1); i++)
			{
				if (data[i] == 255)
				{
					mude[0] = 1;
					if (data_last[i] == 255) mude[1] = 1;
					else  mude[1] = 0;
					if (data_last[i + 1] == 255) mude[2] = 1;
					else  mude[2] = 0;
					if (data[i + 1] == 255) mude[3] = 1;
					else  mude[3] = 0;
					if (data_next[i + 1] == 255) mude[4] = 1;
					else  mude[4] = 0;
					if (data_next[i] == 255) mude[5] = 1;
					else  mude[5] = 0;
					if (data_next[i - 1] == 255) mude[6] = 1;
					else  mude[6] = 0;
					if (data[i - 1] == 255) mude[7] = 1;
					else  mude[7] = 0;
					if (data_last[i - 1] == 255) mude[8] = 1;
					else  mude[8] = 0;
					int whitepointtotal = 0;
					for (int k = 1; k < 9; k++)
					{
						whitepointtotal = whitepointtotal + mude[k];
					}
					if ((whitepointtotal >= 2) && (whitepointtotal <= 6))
					{
						int ap = 0;
						if ((mude[1] == 0) && (mude[2] == 1)) ap++;
						if ((mude[2] == 0) && (mude[3] == 1)) ap++;
						if ((mude[3] == 0) && (mude[4] == 1)) ap++;
						if ((mude[4] == 0) && (mude[5] == 1)) ap++;
						if ((mude[5] == 0) && (mude[6] == 1)) ap++;
						if ((mude[6] == 0) && (mude[7] == 1)) ap++;
						if ((mude[7] == 0) && (mude[8] == 1)) ap++;
						if ((mude[8] == 0) && (mude[1] == 1)) ap++;
						if (ap == 1)
						{
							if ((mude[1] * mude[7] * mude[5] == 0) && (mude[3] * mude[5] * mude[7] == 0))
							{
								deletelist1.push_back(Point(i, j));
							}
						}
					}
				}
			}
		}
		if (deletelist1.size() == 0) break;
		for (size_t i = 0; i < deletelist1.size(); i++)
		{
			Point tem;
			tem = deletelist1[i];
			uchar* data = srcimage.ptr<uchar>(tem.y);
			data[tem.x] = 0;
		}
		deletelist1.clear();

		for (int j = 1; j < (nl - 1); j++)
		{
			uchar* data_last = srcimage.ptr<uchar>(j - 1);
			uchar* data = srcimage.ptr<uchar>(j);
			uchar* data_next = srcimage.ptr<uchar>(j + 1);
			for (int i = 1; i < (nc - 1); i++)
			{
				if (data[i] == 255)
				{
					mude[0] = 1;
					if (data_last[i] == 255) mude[1] = 1;
					else  mude[1] = 0;
					if (data_last[i + 1] == 255) mude[2] = 1;
					else  mude[2] = 0;
					if (data[i + 1] == 255) mude[3] = 1;
					else  mude[3] = 0;
					if (data_next[i + 1] == 255) mude[4] = 1;
					else  mude[4] = 0;
					if (data_next[i] == 255) mude[5] = 1;
					else  mude[5] = 0;
					if (data_next[i - 1] == 255) mude[6] = 1;
					else  mude[6] = 0;
					if (data[i - 1] == 255) mude[7] = 1;
					else  mude[7] = 0;
					if (data_last[i - 1] == 255) mude[8] = 1;
					else  mude[8] = 0;
					int whitepointtotal = 0;
					for (int k = 1; k < 9; k++)
					{
						whitepointtotal = whitepointtotal + mude[k];
					}
					if ((whitepointtotal >= 2) && (whitepointtotal <= 6))
					{
						int ap = 0;
						if ((mude[1] == 0) && (mude[2] == 1)) ap++;
						if ((mude[2] == 0) && (mude[3] == 1)) ap++;
						if ((mude[3] == 0) && (mude[4] == 1)) ap++;
						if ((mude[4] == 0) && (mude[5] == 1)) ap++;
						if ((mude[5] == 0) && (mude[6] == 1)) ap++;
						if ((mude[6] == 0) && (mude[7] == 1)) ap++;
						if ((mude[7] == 0) && (mude[8] == 1)) ap++;
						if ((mude[8] == 0) && (mude[1] == 1)) ap++;
						if (ap == 1)
						{
							if ((mude[1] * mude[3] * mude[5] == 0) && (mude[3] * mude[1] * mude[7] == 0))
							{
								deletelist1.push_back(Point(i, j));
							}
						}
					}
				}
			}
		}
		if (deletelist1.size() == 0) break;
		for (size_t i = 0; i < deletelist1.size(); i++)
		{
			Point tem;
			tem = deletelist1[i];
			uchar* data = srcimage.ptr<uchar>(tem.y);
			data[tem.x] = 0;
		}
		deletelist1.clear();
	}
}

void calcArgWithPoint(map<Args, int>& args,int x,int y,double *coses,double* sins){
	int cnt = 0;
	cout << x << " " << y<<endl;
	for (int theta = -90; theta <= 90; theta++){
		double rho = x*coses[theta + 90] + y*sins[theta + 90];
		int rho_i = round(rho);
		Args arg(rho_i, theta);
		if (args.count(arg)) args[arg]++;
		else args[arg] = 1;
		cnt++;
	}
}
int checkIfExist(vector<Flus> flu, int x, int y, double *coses, double* sins, int thres){
	for (int i = 0; i<3; i++){
		int rho = flu[i].rho;
		int theta = flu[i].theta;
		int calc_rho = round(x*coses[theta + 90] + y*sins[theta + 90]);
		if (abs(rho - calc_rho) <= thres) return 1;
	}
	return 0;
}
void myHough(Mat& dst, Mat src, int thres){
	//预处理
	if (src.channels() > 1) cvtColor(src, src, CV_RGB2GRAY);
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Mat outline;
	Laplacian(src, outline, src.depth(), 3, 1, 0, BORDER_DEFAULT);
	threshold(outline, outline, 10, 255, CV_THRESH_BINARY);
	//threshold(outline, outline, 100, 255, CV_THRESH_BINARY_INV);
	//imshow("ot", outline);
	medianBlur(outline, outline, 3);
	thinImage(outline);
	
	double coses[200];
	double sins[200];
	for (int theta = -90; theta <= 90; theta++){
		double angle = PI*(double)theta / (double)180;
		coses[theta + 90] = cos(angle);
		sins[theta + 90] = sin(angle);
	}
	//遍历
	int row = outline.rows;
	int col = outline.cols;
	map<Args, int> args;
	uchar *p;
	for (int i = 0; i < row; i++){
		p = outline.ptr<uchar>(i);
		for (int j = 0; j < col; j++){
			if (p[j]>0) calcArgWithPoint(args, i, j,coses,sins);
		}
	}
	//排序
	vector<Flus> argFlus;
	for (map<Args, int>::iterator it = args.begin(); it != args.end(); it++){
		if (it->second>20){
			if (argFlus.size() == 0)
				argFlus.push_back(Flus(it->first.rho, it->first.theta, it->second));
			else{
				int same = 0;
				for (int i = 0; i < argFlus.size(); i++){
					if (abs(argFlus[i].rho - it->first.rho) < thres&&abs(argFlus[i].theta - it->first.theta)<thres){
						argFlus[i] = argFlus[i] + Flus(it->first.rho, it->first.theta, it->second);
						same = 1;
						break;
					}
				}
				if (!same) argFlus.push_back(Flus(it->first.rho, it->first.theta, it->second));
			}
		}
	}
	sort(argFlus.begin(), argFlus.end());
	for (int i = 0; i < argFlus.size(); i++){
		cout << "(" << argFlus[i].rho << "," << argFlus[i].theta << ") : " << argFlus[i].flu << endl;
	}
	//画线
	dst = Mat(row, col, CV_8U, Scalar::all(0));
	uchar *q,*r;
	for (int i = 0; i < row; i++){
		r = outline.ptr<uchar>(i);
		q = dst.ptr<uchar>(i);
		for (int j = 0; j < col; j++){
			q[j] = (r[j]>0 && checkIfExist(argFlus, i, j, coses, sins, thres)) ? 255 : 0;
		}
	}
}
