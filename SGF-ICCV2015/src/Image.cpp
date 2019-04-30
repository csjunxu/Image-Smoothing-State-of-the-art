#include "Image.h"

void Image::load(Mat img )
{
	
	width=img.size().width;
	height=img.size().height;
	pbuff=new unsigned int[height*width];
	unsigned int temp=0;
	
	RGB=new int*[width*height];
	if(height*width>=600*600)
		medianBlur(img, img, 5);
	else if(height*width>1400*1200)
		medianBlur(img, img, 7);
	else
		medianBlur(img,img,3);
	for(int row=0;row<height;row++)
		for(int col=0;col<width;col++)
		{
			//RGB[row*width+col]=new int[3];
			temp=0;
			RGB[row*width+col]=new int[3];
//			img.channels;
			if(img.channels()>=3)
			{
				temp+=(unsigned int)(img.at<Vec3b>(row,col)[0]);
				temp+=(unsigned int)(img.at<Vec3b>(row,col)[1])*256;
				temp+=(unsigned int)(img.at<Vec3b>(row,col)[2])*256*256;
				RGB[row*width+col][0]=(int)img.at<Vec3b>(row,col)[0];
				RGB[row*width+col][1]=(int)img.at<Vec3b>(row,col)[1];
				RGB[row*width+col][2]=(int)img.at<Vec3b>(row,col)[2];
			}
			else
			{	
				temp+=((unsigned int)(img.at<uchar>(row,col)))*(1+256+256*256);
				RGB[row*width+col][0]=(int)img.at<uchar>(row,col);
				RGB[row*width+col][1]=(int)img.at<uchar>(row,col);
				RGB[row*width+col][2]=(int)img.at<uchar>(row,col);
			
			}
			pbuff[row*width+col]=temp;
		}
}
void Image::SetParameters(float Eps,float Thresh)
{
	eps=Eps*255*3;
	thresh=Thresh*255;
}
void Image::initial(Mat img, int radius, float EPS, float Thresh)
{
	load(img);
	srand(time(NULL)*10+radius);
	m=5+rand()%20;
	eps=EPS*255*3;
	thresh=Thresh*255;
	window=radius;
	K=(int)((2*window+1)*(2*window+1)/(2.5+0.1*(rand()%11)));
	SuperPixel();	
	initial_structure();
#pragma omp parallel for
	for(int i=0;i<Spixel.size();i++)
	{
		MstTree(i);
	}
	PixelNum();
}
void Image::save(char*filename)
{
	cv::Mat save(height, width, CV_8UC3);
	for ( int row = 0; row < height; row++ )
	{
		for ( int col = 0; col < width; col++ )
		{
				
				save.at<Vec3b>(row,col)[0]=pbuff[row*width+col]%256;
				save.at<Vec3b>(row,col)[1]=(pbuff[row*width+col]/256)%256;
				save.at<Vec3b>(row,col)[2]=pbuff[row*width+col]/(256*256);
		} 
	}
	Mat disp;
	convertScaleAbs(save, disp);
	imwrite(filename,disp);

}

void Image::Locate()
{

	int row,col;
	int ve[4][2]={{-1,0},{-1,1},{0,-1},{-1,-1}};
	vector<int> temp;
	int Num=0;
	for(int i=0;i<width*height;i++)if(Num<klabels[i])
			Num=klabels[i];
	//cout<<num+1;
	for(int i=0;i<Num+1;i++)
	{
		Spixel.push_back(temp);
		Neibor.push_back(temp);
		Neibor[i].push_back(i);
	}
	for(row=0;row<height;row++)
	{
		for(col=0;col<width;col++)
		{
		
			Spixel[klabels[row*width+col]].push_back(row*width+col);

		//	system("pause");
			for(int k=0;k<4;k++)
			{
				int r=row+ve[k][0];
				int c=col+ve[k][1];
				if(r<0||r>=height||c<0||c>=width)
					continue;
				if(klabels[row*width+col]!=klabels[r*width+c])
				{
					bool flag=false;
					for(int t=1;t<Neibor[klabels[row*width+col]].size();t++)
					{
						
						if(Neibor[klabels[row*width+col]][t]==klabels[r*width+c])
						{
							flag=true;
							break;
						}
					}
					if(!flag)
						Neibor[klabels[row*width+col]].push_back(klabels[r*width+c]);

					flag=false;
					for(int t=1;t<Neibor[klabels[r*width+c]].size();t++)
					{
						
						if(Neibor[klabels[r*width+c]][t]==klabels[row*width+col])
						{
							flag=true;
							break;
						}
					}
					if(!flag)
						Neibor[klabels[r*width+c]].push_back(klabels[row*width+col]);
				}
			}
				
		}
	}
}

void Image::SuperPixel()
{
	int start,end;
	SLIC segment;
#if 0
	segment.DoSuperpixelSegmentation_ForGivenNumberOfSuperpixels(pbuff, width, height, klabels, numlabels, K, m);
#else
	segment.DoSuperpixelSegmentation_ForGivenSuperpixelSize(pbuff, width, height, klabels, numlabels, K, m);
#endif

	Locate();
	

	if(pbuff) 
	{
		delete [] pbuff;
		pbuff=NULL;
	}
	//segment.~SLIC();
}

void Image::FreeMem()
{
	for(int i=0;i<width*height;i++)
	{
		if(RGB)
		{
		if(RGB[i]!=NULL)
		{
			delete []RGB[i];
			RGB[i]=NULL;
		}
		}
	}
	for(int i=0;i<Spixel.size();i++)
	{
		for(int j=0;j<Spixel[i].size();j++)
		{
			if(structure[i][j])
			{
				delete[]structure[i][j];
				structure[i][j]=NULL;
			}
			
			
		}
		if(num[i])
		{
			delete[]num[i];
			num[i]=NULL;
		}
		if(structure[i])
		{
			delete[] structure[i];
			structure[i]=NULL;
		}
	}
	if(RGB)
	{	
		delete[]RGB;
		RGB=NULL;
	}
	
	if(num!=NULL)
	{
		delete[] num;
		
		num=NULL;
	//	cout<<num<<endl;
	}


	if(klabels!=NULL){
	delete[]klabels;klabels=NULL;}
	if(index!=NULL)
	{
	delete [] index;index=NULL;}
	for(int i=0;i<Spixel.size();i++)
	{
		Spixel[i].clear();
		vector<int>().swap(Spixel[i]);
	}
	Spixel.clear();
	vector<vector<int>>().swap(Spixel);

	for(int i=0;i<Neibor.size();i++)
	{
		Neibor[i].clear();
		vector<int>().swap(Neibor[i]);
	}
	Neibor.clear();
	vector<vector<int>>().swap(Neibor);
	Center.clear();
	vector<int>().swap(Center);
	if(structure)
	{
		delete[]structure;structure=NULL;}

}
int cmp(const EDGE e1,const EDGE e2)
{
	return e1.value<e2.value;
}
void Image::initial_structure()
{
	int de[CONNECT][2]={{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
	structure=new EDGE**[Spixel.size()];
	index=new int[width*height];

	for(int i=0;i<Spixel.size();i++)
	{
		
		structure[i]=new EDGE*[Spixel[i].size()];
		for(int j=0;j<Spixel[i].size();j++)
			structure[i][j]=new EDGE[CONNECT];
	}
	for(int i=0;i<Spixel.size();i++)
	{
		for(int j=0;j<Spixel[i].size();j++)
		{
			index[Spixel[i][j]]=j;
			for(int k=0;k<CONNECT;k++)
			{
				int x=Spixel[i][j]%width+de[k][0];
				int y=Spixel[i][j]/width+de[k][1];
				if(x>=0&&x<width&&y>=0&&y<height)
				{
					if(klabels[y*width+x]==klabels[Spixel[i][j]])
					{ 
					//	structure[i][j][k].index=
						structure[i][j][k].a=Spixel[i][j];
						structure[i][j][k].b=y*width+x;
						structure[i][j][k].flag=false;
		//
						structure[i][j][k].value=fabs((float)RGB[y*width+x][0]-RGB[Spixel[i][j]][0])
							+fabs((float)RGB[y*width+x][1]-RGB[Spixel[i][j]][1])
							+fabs((float)RGB[y*width+x][2]-RGB[Spixel[i][j]][2]);
						structure[i][j][k].dst=sqrt((float)de[k][0]*de[k][0]+de[k][1]*de[k][1]);
						continue;
					}
				}
				structure[i][j][k].a=-1;
				structure[i][j][k].b=-1;
				structure[i][j][k].flag=false;
			}

		}
	}
}
int Image::unionsearch(int *father, int*son,int x) //look for the root and compress the route
{
	int p=x,q=x;
	while(x!=father[x])
		x=father[x];
	while(p!=father[p])
	{
		q=p;
		p=father[p];
		father[q]=x;

	}
	return x;
}

bool Image::join(int *father, int *son,int x, int y) //union
{
	int root1, root2;
	root1 = unionsearch(father, son, x);
	root2 = unionsearch(father, son,y);
	if(root1 == root2) //loop
		return false;
	else if(son[root1] >= son[root2])
		{
			father[root2] = root1;
			son[root1] += son[root2];
		}
		else
		{
			father[root1] = root2;
			son[root2] += son[root1];
		}
	return true;
}

void Image::MstTree(int i)
{
	int *father=new int[Spixel[i].size()];
	int *son=new int[Spixel[i].size()];
	for(int j=0;j<Spixel[i].size();j++)
	{
		father[j]=j;
		son[j]=1;
	}
	int de[CONNECT][2]={{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
	int start,end;
	start=clock();
	int row,col;
	vector<EDGE>temp;
	EDGE rem;
	int Enum=0;

	for(int j=0;j<Spixel[i].size();j++)
	{
		for(int k=0;k<CONNECT/2;k++)
		{
			if(structure[i][j][k].a<0)
				continue;
			rem.a=Spixel[i][j];
			rem.b=(Spixel[i][j]/width+de[k][1])*width+Spixel[i][j]%width+de[k][0];
			//structure[i][j][k].flag=true;
			
			temp.push_back(structure[i][j][k]);
					
			Enum++;
		}

	}
	std::sort(temp.begin(),temp.end(),cmp);
	int count=0;
	float sum=0;
	int ii=0;
	
	while(ii<Enum&&count<Spixel[i].size()-1)
	{
		
		if(join(father, son,index[temp[ii].a], index[temp[ii].b]))
		{
			sum+=temp[ii].value;
			count++;
			temp[ii].flag=true;
			int k=0;
			while(structure[i][index[temp[ii].a]][k].flag&&k<CONNECT)
				k++;
			memcpy(&structure[i][index[temp[ii].a]][k],&temp[ii],sizeof(EDGE));
			structure[i][index[temp[ii].a]][k]=temp[ii];
			int re=temp[ii].b;
			temp[ii].b=temp[ii].a;
			temp[ii].a=re;
			k=0;
			while(structure[i][index[temp[ii].a]][k].flag&&k<CONNECT)
				k++;
			
			memcpy(&structure[i][index[temp[ii].a]][k],&temp[ii],sizeof(EDGE));
			structure[i][index[temp[ii].a]][k]=temp[ii];
		//	cout<<temp[i].value<<endl;
		
		}
		ii++;
	}

	delete []father;
	delete []son;
	temp.clear();	
	vector<EDGE>().swap(temp);

}
////////////////////////////////
void Image::PixelNum()
{
	num=new int*[width*height];
	int **Rec=new int *[Spixel.size()];
	int **Vertices=new int *[Spixel.size()];
	int **CumSum=new int *[Spixel.size()];
#pragma omp parallel for
	for(int i=0;i<width*height;i++)
	{

		num[i]=new int [Neibor[klabels[i]].size()];
		for(int j=0;j<Neibor[klabels[i]].size();j++)
			num[i][j]=0;

	}

#pragma omp parallel for
	for(int i=0;i<Spixel.size();i++)
	{
		
		PixelNum(Rec[i],Vertices[i],CumSum[i],i);
	}
#pragma omp parallel for	
	for(int i=0;i<Spixel.size();i++)
	{
	//	cout<<i<<endl;
		PixelNum(CumSum,Vertices,i);
	}
	delete[] Rec;
#pragma omp parallel for
	for(int i=0;i<Spixel.size();i++)
	{
		delete[] Vertices[i];
		delete[] CumSum[i];
	}
	delete[] Vertices;
	delete[] CumSum;

}
void Image::PixelNum(int **CumSum,int **Vertices,int i)
{
	for(int j=0;j<Spixel[i].size();j++)
	{
		for(int k=0;k<Neibor[i].size();k++)
		{
			int A,B,C,D;
			int row=Spixel[i][j]/width-Vertices[Neibor[i][k]][1];
			
			int col=Spixel[i][j]%width-Vertices[Neibor[i][k]][2];
			int Rec_height=Vertices[Neibor[i][k]][0]-Vertices[Neibor[i][k]][1]+1;
			int Rec_width=Vertices[Neibor[i][k]][3]-Vertices[Neibor[i][k]][2]+1;
			int y0=max(0,row-window);
			int x0=max(0,col-window);
			int y1=min(Rec_height-1,row+window);
			int x1=min(Rec_width-1,col+window);
			if(x0>=Rec_width||y0>=Rec_height||x1<0||y1<0)
				num[Spixel[i][j]][k]=0;
			else
			{
				float A,B,C;
				if(y0-1>=0)
					A=CumSum[Neibor[i][k]][(y0-1)*Rec_width+x1];
				else
					A=0;
				if(x0-1>=0)
					B=CumSum[Neibor[i][k]][y1*Rec_width+(x0-1)];
				else
					B=0;
				if(y0-1>=0&&x0-1>=0)
					C=CumSum[Neibor[i][k]][(y0-1)*Rec_width+x0-1];
				else
					C=0;
				num[Spixel[i][j]][k]=CumSum[Neibor[i][k]][y1*Rec_width+x1]-A-B+C;

			
			}

		
		}
	}
}
void Image::PixelNum(int*&Rec, int*&Vertices, int *&CumSum, int i)//cumsum;
{
	Vertices=new int [4];
	Vertices[0]=0;
	Vertices[1]=height;
	Vertices[2]=width;
	Vertices[3]=0;
	for(int j=0;j<Spixel[i].size();j++)
	{
		int row=Spixel[i][j]/width;
		int col=Spixel[i][j]%width;
		if(Vertices[0]<row)
			Vertices[0]=row;
		if(Vertices[1]>row)
			Vertices[1]=row;
		if(Vertices[2]>col)
			Vertices[2]=col;
		if(Vertices[3]<col)
			Vertices[3]=col;

	}
	if(Vertices[0]<Vertices[1]||Vertices[2]>Vertices[3])
	{

		cout<<"Error!"<<endl;
		exit(0);
		//system("pause");
	}
	int Rec_height=Vertices[0]-Vertices[1]+1;
	int Rec_width=(Vertices[3]-Vertices[2]+1);
	Rec=new int [Rec_width*Rec_height];
	
	for(int j=0;j<Rec_width*Rec_height;j++)
		Rec[j]=0;

	for(int j=0;j<Spixel[i].size();j++)
	{
		int row=Spixel[i][j]/width;
		int col=Spixel[i][j]%width;
		int location=(row-Vertices[1])*(Rec_width)+col-Vertices[2];
		Rec[location]=1;
	}
	CumSum=new int [Rec_width*Rec_height];

	for(int row=0;row<Rec_height;row++)
	{
		for (int col=0;col<Rec_width;col++)
		{
			int A,B,C;

			if(row-1>=0)
			{
				A=CumSum[(row-1)*Rec_width+col];
			}
			else 
				A=0;
			if(col-1>=0)
				B=CumSum[row*Rec_width+col-1];
			else
				B=0;
			if(row-1>=0&&col-1>=0)
				C=CumSum[(row-1)*Rec_width+col-1];
			else
				C=0;
			CumSum[row*Rec_width+col]=A+B-C+Rec[row*Rec_width+col];

		}
	}
	delete[] Rec;

}
void Image::PixelNum(int r)
{
	
	num=new int*[width*height];
	for(int i=0;i<width*height;i++)
	{
		
		num[i]=new int [Neibor[klabels[i]].size()];
		for(int j=0;j<Neibor[klabels[i]].size();j++)
			num[i][j]=0;
	
	}
	for(int row=0;row<height;row++)
	{
		for(int col=0;col<width;col++)
		{
			for(int y=max(row-r,0);y<=min(row+r,height-1);y++)
			{
				for(int x=max(col-r,0);x<=min(col+r,width-1);x++)
				{
					for(int k=0;k<Neibor[klabels[row*width+col]].size();k++)
						if(Neibor[klabels[row*width+col]][k]==klabels[y*width+x])
						{
							num[row*width+col][k]++;
							break;
						}
				}
			}
		}
	}
	

}
void Image::NeiborConnect(EDGE* Nei,int i)
{	
#if 1
	int de[CONNECT][2]={{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
	for(int nei=1;nei<Neibor[i].size();nei++)
	{
		float rem=1e10;
		 
		for(int j=0;j<Spixel[i].size();j++)
		{
			for(int z=0;z<CONNECT;z++)
			{
					int x=Spixel[i][j]%width+de[z][0];
					int y=Spixel[i][j]/width+de[z][1];
					if(x>=0&&x<width&&y>=0&&y<height)
						if(klabels[Spixel[Neibor[i][nei]][0]]==klabels[y*width+x])
						{
							float aa=fabs((float)RGB[Spixel[i][j]][0]-RGB[y*width+x][0])+
								fabs((float)RGB[Spixel[i][j]][1]-RGB[y*width+x][1])+
								fabs((float)RGB[Spixel[i][j]][2]-RGB[y*width+x][2]);
							if(aa<rem)
							{
								rem=aa;
								Nei[nei].b=y*width+x;
								Nei[nei].a=Spixel[i][j];
								Nei[nei].value=aa;
								Nei[nei].dst=sqrt((float)de[z][0]*de[z][0]+de[z][1]*de[z][1]);
								if(Nei[nei].a>=width*height||Nei[nei].b>=width*height)
								{
									//cout<<i<<' '<<nei<<' '<<j<<endl;
									//system("pause");
									exit(0);
								}
							}

						}
			}
		}
	}
#else
		
	int de[CONNECT][2]={{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
	for(int nei=1;nei<Neibor[i].size();nei++)
	{
		float rem=1e10;
		 
		for(int j=0;j<Spixel[i].size();j++)
		{
			for(int z=0;z<CONNECT;z++)
			{
					int x=Spixel[i][j]%width+de[z][0];
					int y=Spixel[i][j]/width+de[z][1];
					if(x>=0&&x<width&&y>=0&&y<height)
					{
						if(klabels[Spixel[Neibor[i][nei]][0]]==klabels[y*width+x])
						{
							int k=0;
							while(STRUCTURE[Spixel[i][j]][k].flag&&k<CONNECT)
							{
								if(y*width+x==STRUCTURE[Spixel[i][j]][k].b)
								{
									Nei[nei].push_back(STRUCTURE[Spixel[i][j]][k]);
									break;
								}
									
									k++;
							}

						}
					}
			}
		}
	}
#endif
}

void Image::LocalFilter(float*Cost,float *result)
{
	int start;
	int end;
	start=clock();
	float *temp1=new float [width*height];
#pragma omp parallel for
	for(int i=0;i<width*height;i++)
	{
		result[i]=0;
	}
	
#pragma omp parallel for
	for(int i=0;i<Spixel.size();i++)
	{
			float *dst;
			float *cost=new float[Spixel[i].size()];
			 dst=new float[Spixel[i].size()];
			for(int j=0;j<Spixel[i].size();j++)
				cost[j]=Cost[Spixel[i][j]];
			LocalAggregate(cost,dst,i);
			for(int j=0;j<Spixel[i].size();j++)
				temp1[Spixel[i][j]]=dst[j];
			delete[] dst;
			delete[] cost;
		
	}
#if 1
#pragma omp parallel for
	for(int i=0;i<width*height;i++)
		result[i]+=temp1[i]*num[i][0]/(float)Spixel[klabels[i]].size();
#endif
#pragma omp parallel for
	for(int i=0;i<Spixel.size();i++)
	{
		EDGE *Nei=new EDGE[Neibor[i].size()];
		NeiborConnect(Nei, i);
	
#if 1
		LocalDist(result,temp1,Nei,i);
		delete []Nei;
#else
			float **dst=new float*[Spixel[i].size()];
			float **cost=new float*[Spixel[i].size()];
			for(int j=0;j<Spixel[i].size();j++)
			{
				cost[j]=new float[Neibor[i].size()];
				dst[j]=new float[Neibor[i].size()];
				cost[j][0]=Cost[Spixel[i][j]];
				for(int nei=1;nei<Neibor[i].size();nei++)
					cost[j][nei]=0;
					
			}
			for(int nei=1;nei<Neibor[i].size();nei++)
			{
		
				if(Nei[nei].value<thresh)
					if(SGGF)
					{
						cost[index[Nei[nei].a]][nei]=temp1[Nei[nei].b]*exp(-Nei[nei].dst/eps);
					}
					else
					{
						cost[index[Nei[nei].a]][nei]=temp1[Nei[nei].b]*exp(-Nei[nei].value/eps);

					}
					
			}
			NeiborAggregate(cost,dst,i);

			for(int j=0;j<Spixel[i].size();j++)
			{
				
				for(int t=0;t<Neibor[i].size();t++)
				{
				
					result[Spixel[i][j]]+=dst[j][t]*num[Spixel[i][j]][t]/(float)Spixel[Neibor[i][t]].size();
				}
				delete [] dst[j];
				delete[] cost[j];
			}
			delete[] dst;
			delete[] cost;
		
			delete []Nei;
#endif
	}

	delete [] temp1;
	
}

void Image::LocalAggregate(float *cost,float *dst,int i)
{
	
	
	float *rem1=new float[Spixel[i].size()];
	float *rem2=dst;
	for(int j=0;j<Spixel[i].size();j++)
	{
		
		
			rem1[j]=0;
			rem2[j]=cost[j];
		
	}
	vector<int>p;
	vector<int>temp;
	int a=Spixel[i][0];
	int b;
	int count=1;
	p.push_back(a);
	temp.push_back(a);
	
	int *tag=new int[Spixel[i].size()];
	memset(tag,0,sizeof(int)*Spixel[i].size());
	
	tag[index[a]]=1;
	while(!p.empty())
	{
		a=p.back();
		p.pop_back();
		int k=0;
		while(structure[i][index[a]][k].flag&&k<CONNECT)
		{
			
			b=structure[i][index[a]][k].b;
			if(tag[index[b]]<1)
			{
				tag[index[b]]=1;
				p.push_back(b);
				temp.push_back(b);
				count++;
			}
				
			
			k++;
		}
	}
	float sum=0;
	memset(tag,0,sizeof(int)*Spixel[i].size());
	for(int ii=0;ii<Spixel[i].size();ii++)
		tag[ii]=-1;
	//int num=0;
	for(int ii=temp.size()-1;ii>=0;ii--)
	{
		a=temp[ii];
		int k=0;
		while(structure[i][index[a]][k].flag&&k<CONNECT)
		{
			b=structure[i][index[a]][k].b;
			if(tag[index[b]]<=0)
			{
					rem1[index[a]]=rem2[index[a]]*exp(-structure[i][index[a]][k].value/(eps));
					rem2[index[b]]+=rem1[index[a]];
			}
			k++;
		}
		tag[index[a]]=1;
			
	}
	memset(tag,0,sizeof(int)*Spixel[i].size());
	for(int ii=0;ii<Spixel[i].size();ii++)
		tag[ii]=-2;
	for(int ii=0;ii<temp.size();ii++)
	{
		a=temp[ii];
		int k=0;
		while(structure[i][index[a]][k].flag&&k<CONNECT)
		{
			b=structure[i][index[a]][k].b;
			if(tag[index[b]]<=0)
			{

				rem2[index[b]]=rem2[index[b]]+(rem2[index[a]]-rem1[index[b]])*exp(-structure[i][index[a]][k].value/(eps));
			}
			k++;
		}
		tag[index[a]]=1;
	}

	p.clear();
	vector<int>().swap(p);
	
	delete []rem1;
	delete []tag;
	tag=NULL;
}
void Image::LocalDist(float*&result,float* temp,EDGE *Nei,int i)
{
	float *dst;
	for(int k=1;k<Neibor[i].size();k++)
	{
		if(Nei[k].value<thresh)
		{
			dst=new float[Spixel[i].size()];
			LocalDist(dst,Nei[k].a,i);
			for(int j=0;j<Spixel[i].size();j++)
				
				{
					result[Spixel[i][j]]+=exp(-(Nei[k].value+dst[j])/eps)*temp[Nei[k].b]*num[Spixel[i][j]][k]/(float)Spixel[Neibor[i][k]].size();
				}
				
			delete[]dst;
		}

	}
	
}
void Image::LocalDist(float *&dst, int start,int i)
{
	vector<int>p;
	//vector<int>temp;
	int a=index[start];
	int b;
	int count=1;
	p.push_back(a);
	int *tag=new int[Spixel[i].size()];
	dst[a]=0;
	memset(tag,0,sizeof(int)*Spixel[i].size());

	tag[a]=1;
	while(!p.empty())
	{
		a=p.back();
		p.pop_back();
		int k=0;
		while(structure[i][a][k].flag&&k<CONNECT)
		{

			b=index[structure[i][a][k].b];
			if(tag[b]<1)
			{
				tag[b]=1;
				p.push_back(b);

					dst[b]=dst[a]+structure[i][a][k].value;
			}
			k++;
		}
	}
	delete []tag;
	tag=NULL;
	p.clear();
	vector<int>().swap(p);
	
}
void Image::NeiborAggregate(float **cost,float **dst,int i)
{
	
	int NUM=Neibor[i].size();
	float **rem1=new float*[Spixel[i].size()];
	float **rem2=dst;
	for(int j=0;j<Spixel[i].size();j++)
	{
		rem1[j]=new float[NUM];
		for(int k=0;k<NUM;k++)
		{
			rem1[j][k]=0;
			rem2[j][k]=cost[j][k];
		}
	}
	vector<int>p;
	vector<int>temp;
	int a=Spixel[i][0];
	int b;
	int count=1;
	p.push_back(a);
	temp.push_back(a);
	
	int *tag=new int[Spixel[i].size()];
	memset(tag,0,sizeof(int)*Spixel[i].size());
	
	tag[index[a]]=1;
	while(!p.empty())
	{
		a=p.back();
		p.pop_back();
		int k=0;
		while(structure[i][index[a]][k].flag&&k<CONNECT)
		{
			
			b=structure[i][index[a]][k].b;
			if(tag[index[b]]<1)
			{
				tag[index[b]]=1;
				p.push_back(b);
				temp.push_back(b);
				count++;
			}
				
			
			k++;
		}
	}
	float sum=0;
	memset(tag,0,sizeof(int)*Spixel[i].size());
	for(int ii=0;ii<Spixel[i].size();ii++)
		tag[ii]=-1;
	//int num=0;
	for(int ii=temp.size()-1;ii>=0;ii--)
	{
		a=temp[ii];
		int k=0;
		while(structure[i][index[a]][k].flag&&k<CONNECT)
		{
			b=structure[i][index[a]][k].b;
			if(tag[index[b]]<=0)
			{
			
				for(int z=0;z<NUM;z++)
				{

					rem1[index[a]][z]=rem2[index[a]][z]*exp(-structure[i][index[a]][k].value/(eps));
					rem2[index[b]][z]+=rem1[index[a]][z];
				}
			
			}
			k++;
		}
		tag[index[a]]=1;
			
	}

	memset(tag,0,sizeof(int)*Spixel[i].size());
	for(int ii=0;ii<Spixel[i].size();ii++)
		tag[ii]=-2;
	for(int ii=0;ii<temp.size();ii++)
	{
		a=temp[ii];
		int k=0;
		while(structure[i][index[a]][k].flag&&k<CONNECT)
		{
			b=structure[i][index[a]][k].b;
			if(tag[index[b]]<=0)
			{
				for(int z=0;z<NUM;z++)
				{
					rem2[index[b]][z]=rem2[index[b]][z]+(rem2[index[a]][z]-rem1[index[b]][z])*exp(-structure[i][index[a]][k].value/(eps));
				}

			}
			k++;
		}
		tag[index[a]]=1;
	}

	p.clear();
	vector<int>().swap(p);
	for(int j=0;j<Spixel[i].size();j++)
	{
		delete[] rem1[j];
		
	}
	delete []rem1;
	delete []tag;
	tag=NULL;
}

