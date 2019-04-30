# SGF
Method 
=========
This is the implementation of 'Segment Graph Based Image Filtering: Fast Structure-Preserving Smoothing' as 
described in 

@inproceedings{zhang2015segment,

  title={Segment Graph Based Image Filtering: Fast Structure-Preserving Smoothing},
  
  author={Zhang, Feihu and Dai, Longquan and Xiang, Shiming and Zhang, Xiaopeng},
  
  booktitle={Proceedings of the IEEE International Conference on Computer Vision},
  
  pages={361--369},
  
  year={2015}
}

Compiling the code
==================
To compile the source code, you must have opencv installed (libpng is also necessary if you didn't install it along with opencv). Then,

$cmake .

$make

or directly 

$g++ -fopenmp src/*.cpp `pkg-config opencv --libs --cflags opencv` -o SGF -fpermissive

The code is already tested both on Linux and Windows. 
To recompile it on windows, you need to rebuild a project, add the source file and set the opencv environment.
Or, you can directly use the released win32 software in the exe folder.

Interface function
==================
If you want to use the code in your own project. You can directly add the SGF.cpp Image.cpp SLIC.cpp Image.h SLIC.h to your project.
4 interface functions are provided as follows: (You can view them in the SGF.cpp)

1) Mat Image::FilteringColor(Mat &guid, Mat &target, int Radius, float Eps, float Thresh)
	
  Parameters:
  
    guid:	can be CV_8UC3(color) or CV_8UC1(gray) image;
  
	target:	must be CV_8UC3(color) image and in the same size with guid;
  
	Radius:	radius of the filtering window;
  
	Eps:	just like the bilateral filter value. range: (0,1)
  
	Thresh:	As Described in the paper. range: (0,1)
  
2) Mat Image::FilteringGray(Mat guid, Mat target, int Radius,float Eps, float Thresh)

	Parameters:
  
    guid: can be CV_8UC3(color) or CV_8UC1(gray) image;
  
    target:	must be CV_8UC1(gray) image;
  
	Radius:	radius of the filtering window;
  
	Eps:	just like the bilateral filter value. range: (0,1)
  
	Thresh:	As Described in the paper. range: (0,1)
  
3) Mat Image::IterFiltering(Mat&guid,Mat &target,int radius, float eps, float thresh,int Iter)

	Parameters:
  
    guid and target must be	can be the same image, CV_8UC3(color) or CV_8UC1(gray);
  
	Radius:	radius of the filtering window;
  
	Eps:	just like the bilateral filter value. range: (0,1);
  
	Thresh:	As Described in the paper. range: (0,1);
  
	Iter:	Iterative times for iterative filtering.

4) Mat Image::Filtering(Mat target)

	Parameters:
  
	target:	must be CV_32FC1, one-channel float mat;
  
	To use this function, you must first initialize the SGF once using: 
  
	void Image::initial(Mat guid, int radius, float EPS, float Thresh);
  
	the four parameters are similar to these in FilteringGray and FilteringColor.

Running the Demo
================

You can directly run the exe file on windows by 

$SGF.exe [guid image] [target image] [output file] [radius] [eps] [thresh] [iterations]

value range: (see the paper for details about these parameters)

	eps:	 (0~0.3] float,
  
	thresh:	 (0~1] float
  
	iterations: iterative filtering times. guid image and target image must be same if >1.
	
The last two parameters can be neglected. Default: 1

Examples:

$SGF.exe 1.png 2.png 3.png 16 0.1 

$SGF.exe 1.png 1.png 3.png 16 0.1 0.1 3

Or on Linux:
$./SGF [guid image] [target image] [output file] [radius] [eps] [thresh] [iterations]

We provide some matlab scripts to run the demo in the paper.

1) demo_abs:	the image abstraction demo. Inputs and outputs are in the "abs"

2) demo_depth:	depth map denoising and depth map upsampling(8 times). Inputs and outputs are in the "depth". For the application of depth map upsampling, fistly, generate the seed map and then, use the guidance image to filter the seed map. "depth/shrink.m" provides an example to generate the seed map by just setting all the other pixels(except the seed pixel) to zero.

3) demo_iterative: demo super iterative SGF, the inputs will be filtering for 10~30 times. Inputs and outputs are in "iterative"

4) demo_smooth:	demo for image smooth (noise/details removing). Inputs and outputs are include in "smooth"

5) demo_texture: demo for texture removing. Inputs and outputs are in "texture".

Notice
========
1) Currently the implement is a slow version which can be sped up for 5 times. We will soon release the speed-up version.

2) The parameters used in the demo are slightly different with the paper. This is caused by the image size differences.

Citation
========

If you find this project, data or code useful, we would be happy if you cite us:

@inproceedings{zhang2015segment,

  title={Segment Graph Based Image Filtering: Fast Structure-Preserving Smoothing},
  
  author={Zhang, Feihu and Dai, Longquan and Xiang, Shiming and Zhang, Xiaopeng},
  
  booktitle={Proceedings of the IEEE International Conference on Computer Vision},
  
  pages={361--369},
  
  year={2015}
}
