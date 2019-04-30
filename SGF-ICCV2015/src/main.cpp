#include"Image.h"
int main( int argc, char *argv[])
{
	char guidfile[200];
	char dstfile[200];
	char outfile[200];
	int radius;
	float thresh=1;
	float eps;
	int Iter=1;
	Mat guid;
	Mat target;
	Mat out;
#if 1
	if(argc<6||argc>8)
	{
		cout<<"SGF command format:"<<endl;
		cout<<"./SGF [guid] [target] [output] [radius] [eps (0~1)] [thresh (0~1)] [iterations]"<<endl;
		cout<<"The last two parameters can be neglected. Default: 1"<<endl;
		exit(0);
	}
	if(argc>=6)
	{
		sprintf(guidfile,"%s",argv[1]);
		sprintf(dstfile,"%s",argv[2]);
		sprintf(outfile,"%s",argv[3]);
		radius=atoi(argv[4]);
		eps=atof(argv[5]);
	}
	if(argc>=7)
	{
		thresh=atof(argv[6]);
	}
	if(argc==8)
	{
		Iter=atoi(argv[7]);
	}
#else
	sprintf(guidfile,"1.png");
	sprintf(dstfile,"1.png");
	sprintf(outfile,"out.png");
	radius=25;
	eps=0.06;
	Iter=10;
#endif
	Image img;
	guid=imread(guidfile,1);
	//imwrite("guid.png",guid);
	
	target=imread(dstfile,-1);
	//cout<<target.channels();
	if(target.channels()>=3)
		target=imread(dstfile,1);
	if(Iter==1)
	{
		if(target.channels()>=3)
			out=img.FilteringColor(guid,target,radius,eps,thresh);
		else
			out=img.FilteringGray(guid,target,radius,eps,thresh);
	}
	else
	{
		if(strcmp(guidfile,dstfile)!=0)
		{
			cout<<"Warning: the guidance and the target should be the same image for iterative filtering."; 
			cout<<" Therefore, guidance image is neglected ..."<<endl;
		}
		out=img.IterFiltering(target,target,radius, eps,thresh,Iter);	
	}
	imwrite(outfile,out);
	return 0;
}
