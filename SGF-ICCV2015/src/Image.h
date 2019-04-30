#ifndef _IMAGE_H
#define _IMAGE_H
/*
This is the implementation of 'Segment Graph Based Image Filtering: Fast Structure-Preserving Smoothing' as 
described in 

@inproceedings{zhang2015segment,
  title={Segment Graph Based Image Filtering: Fast Structure-Preserving Smoothing},
  author={Zhang, Feihu and Dai, Longquan and Xiang, Shiming and Zhang, Xiaopeng},
  booktitle={Proceedings of the IEEE International Conference on Computer Vision},
  pages={361--369},
  year={2015}
}
*/

#include<iostream>
#include<time.h>
#include<cstring>
#include<string>
#include<cstdio>
#include<math.h>
#include<algorithm>

#include<fstream>
#include<queue>
#include<vector>
#include "SLIC.h"
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
using namespace cv;
using namespace std;
#define CONNECT 8

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) <= (b) ? (a) : (b))
#define PI 3.141592653
struct  EDGE//´æ´¢±ßµÄÐÅÏ¢
{
//	int index;
	int a;
	int b;
	float value;
	float dst;
	bool flag;
	/*friend bool operator<(EDGE e1,EDGE e2)
	{
		return e1.value<e2.value;
	}*/
};


class Image
{
public:
	int K;
	float m;//Compactness factor. use a value ranging from 10 to 40 depending on your needs. Default is 10
	int* klabels;
	int numlabels;
	float eps;
	int *index;
	vector<vector<int>>Spixel;
	vector<vector<int>>Neibor;
	vector<int> Center;
	float thresh;
	int **RGB;
	int height,width;
	int **num;
	int window;
	//int *tag;
	unsigned int *pbuff;
	int*father;
	int*son;
	EDGE*** structure;
public:
	void initial_structure();
	int unionsearch(int *father, int *son,int x);
	bool join(int *father, int *son,int x, int y);
	void MstTree(int i);
	void NeiborAggregate(float **cost,float **dst,int i);
	//void LocalFilter(float**result,int **RGB);
	void LocalAggregate(float *cost,float *dst,int i);
	void NeiborConnect(EDGE *Nei,int i);
	void PixelNum(int r);
	void PixelNum();
	void PixelNum(int **CumSum,int **Vertices,int i);
	void PixelNum(int*&Rec, int*&Vertices, int *&CumSum, int i);
	void LocalFilter(float*Cost,float *result);
	void LocalDist(float *&dst, int start,int i);
	void LocalDist(float*&result,float* temp,EDGE *Nei,int i);
	void SetParameters(float Eps,float Thresh=1);

public:
	

	void SuperPixel();
	void Locate();
	void FreeMem();
	void save(char*filename);
	void load(Mat img);
	void NeiborAggregate_(float **cost,float **dst,int i);
	void initial(Mat img, int Radius,float Eps,float Thresh=1);
public:
	Mat FilteringColor(Mat &guid, Mat &target, int Radius, float Eps, float Thresh=1);
	Mat Filtering(Mat target);
	Mat FilteringGray(Mat guid, Mat target, int Radius,float Eps, float Thresh=1);
	Mat IterFiltering(Mat&guid,Mat &target,int radius, float eps, float thresh,int Iter);
/*
public:
	void LocalAggregate_(float *cost,float *dst,int i);
	void NeiborAggregate_(float **cost,float **dst,int i);
	void NeiborDist(float**&temp, float *&result, EDGE *Nei,int i);
*/
public:
	Image()
	{
		
		pbuff=NULL;
		RGB=NULL;
		num=NULL;
		father=NULL;
		son=NULL;
		klabels=NULL;
		//tag=NULL;
		index=NULL;
	}
	~Image()
	{
		FreeMem();
	}
	
};


#endif
