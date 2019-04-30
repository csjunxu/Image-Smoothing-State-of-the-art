#include "Image.h"
/*
guid:	can be CV_8UC3(color) or CV_8UC1(gray) image;
target:	must be CV_8UC3(color) image;
Radius:	radius of the filtering window;
Eps:	just like the bilateral filter value. range: (0,1)
Thresh:	As Described in the paper. range: (0,1)
*/
Mat Image::FilteringColor(Mat &guid, Mat &target, int Radius, float Eps, float Thresh)
{
	initial(guid,Radius, Eps,Thresh);
	float *cost=new float[width*height];
	float * out=new float[width*height];
	float * normal=new float[width*height];
	for(int i=0;i<width*height;i++)
	{
		if(target.at<Vec3b>(i/width,i%width)[0]+target.at<Vec3b>(i/width,i%width)[1]+target.at<Vec3b>(i/width,i%width)[2]>1e-6)
			cost[i]=1;
		else
			cost[i]=0;
	}
	
	LocalFilter(cost,normal);
	cv::Mat save(height, width, CV_8UC3);
	for(int k=0;k<3;k++)
	{
		for(int i=0;i<width*height;i++)
		{
			cost[i]=(float)(target.at<Vec3b>(i/width,i%width)[k]);
		}

		LocalFilter(cost,out);
		
		for(int i=0;i<width*height;i++)
		{

			save.at<Vec3b>(i/width,i%width)[k]=(int)max(0,min(255,(int)(out[i]/normal[i]+0.5)));
		}
	}
	
	delete [] cost;
	delete [] normal;
	delete [] out; 
	FreeMem();
	return save;
}
/*
target:	must be CV_32FC1, one-channel float mat;

To use this function, you must first Initialize the SGF by:
initial(guid,Radius, Eps, Thresh);
Parameters are similar to FilteringGray and FilteringColor;

*/
Mat Image::Filtering(Mat target)
{
	float *cost=new float[width*height];
	float * out=new float[width*height];
	float * normal=new float[width*height];
	for(int i=0;i<width*height;i++)
	{
		if(target.at<float>(i/width,i%width)>1e-6)
			cost[i]=1;
		else
			cost[i]=0;
	}
	LocalFilter(cost,normal);
	cv::Mat save(height, width, CV_32FC1);
	for(int i=0;i<width*height;i++)
		cost[i]=(float)(target.at<float>(i/width,i%width));

	LocalFilter(cost,out);
		
	for(int i=0;i<width*height;i++)
		save.at<uchar>(i/width,i%width)=max(0,min(255,(int)(out[i]/normal[i]+0.5)));
	delete [] cost;
	delete [] normal;
	delete [] out; 
	return save;
	
}
/*
guid:	can be CV_8UC3(color) or CV_8UC1(gray) image;
target:	must be CV_8UC1(gray) image;
Radius:	radius of the filtering window;
Eps:	just like the bilateral filter value. range: (0,1)
Thresh:	As Described in the paper. range: (0,1)
*/
Mat Image::FilteringGray(Mat guid, Mat target, int Radius,float Eps, float Thresh)
{

	initial(guid,Radius, Eps, Thresh);
	float *cost=new float[width*height];
	float * out=new float[width*height];
	float * normal=new float[width*height];
	for(int i=0;i<width*height;i++)
	{
		if (target.at<uchar>(i/width,i%width)>0)
			cost[i]=1;
		else
			cost[i]=0;
	}
	LocalFilter(cost,normal);
	cv::Mat save(height, width, CV_8UC1);
	for(int i=0;i<width*height;i++)
		cost[i]=(float)(target.at<uchar>(i/width,i%width));

	LocalFilter(cost,out);
		
	for(int i=0;i<width*height;i++)
		save.at<uchar>(i/width,i%width)=max(0,min(255,(int)(out[i]/normal[i]+0.5)));
	delete [] cost;
	delete [] normal;
	delete [] out; 
	FreeMem();
	return save;
}
/*

guid and target must be	can be the same image, CV_8UC3(color) or CV_8UC1(gray);
Radius:	radius of the filtering window;
Eps:	just like the bilateral filter value. range: (0,1);
Thresh:	As Described in the paper. range: (0,1);
Iter:	Iterative times for iterative filtering.
*/
Mat Image::IterFiltering(Mat&guid,Mat &target,int radius, float eps, float thresh,int Iter)
{
		Mat temp;
		Mat out;
		guid.copyTo(temp);
		for(int i=0;i<Iter;i++)
		{
		
			if(target.channels()>=3)
			{
		
				out=FilteringColor(guid,target,radius,eps,thresh);
			}
			else
				out=FilteringGray(guid,target,radius,eps,thresh);
			if((i+1)%3==0)
			{
				out.copyTo(target);
				if(target.channels()>=3)
					out=FilteringColor(temp,target,radius,0.025,thresh);
				else
					out=FilteringGray(temp,target,radius,0.025,thresh);
			}
			out.copyTo(guid);
			out.copyTo(target);
		
		}
		return out;
}
