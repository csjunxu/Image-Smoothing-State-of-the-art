# SOTA Image Smoothing Methods

0. "WLS-TOG2008": Edge-Preserving Decompositions for Multi-Scale Tone and Detail Manipulation. Zeev Farbman, Raanan Fattal, Dani Lischinski, Richard Szeliski. ACM TOG 2008. (http://www.cs.huji.ac.il/~danix/epd/)

00. "EAW-TOG2009": Edge-Avoiding Wavelets and their Applications. Raanan Fattal. ACM TOG (SIGGRAPH) 2009. (http://www.cs.huji.ac.il/~raananf/projects/eaw/)

000. Diffusion Maps for Edge-Aware Image Editing. Zeev Farbman, Raanan Fattal, and Dani Lischinski. SIGGRAPH Asia, 2010. (http://www.cs.huji.ac.il/labs/cglab/projects/diffmaps/)

1. "GF-ECCV2010TPAMI2013": Guided Image Filtering, by Kaiming He, Jian Sun, and Xiaoou Tang. ECCV 2010, TPAMI 2013. (http://kaiminghe.com/eccv10/)

2. "L0-TOG2011": Image Smoothing via L0 Gradient Minimization. Li Xu, Cewu Lu, Yi Xu, Jiaya Jia. ACM TOG (SIGGRAPH Asia), 2011. (http://www.cse.cuhk.edu.hk/leojia/projects/L0smoothing/index.html)

3. "RTV-TOG2012": Structure Extraction from Texture via Relative Total Variation. Li Xu, Qiong Yan, Yang Xia, Jiaya Jia. ACM TOG 2012. (http://www.cse.cuhk.edu.hk/~leojia/projects/texturesep/)

4. "FGS-TIP2014": Fast Global Image Smoothing Based on Weighted Least Squares. Dongbo Min, Sunghwan Choi, Jiangbo Lu, Bumsub Ham, Kwanghoon Sohn, and Minh N. Do. TIP 2014. (https://sites.google.com/site/globalsmoothing/)

5. "UL-TOG2018": Image Smoothing via Unsupervised Learning, ACM TOG (SIGGRAPH Asia), 2018. (https://github.com/fqnchina/ImageSmoothing)

6. "FastABF-TIP2019": Fast Adaptive Bilateral Filtering. R. G. Gavaskar and K. N. Chaudhury. TIP, 2019. (https://github.com/rgavaska/Fast-Adaptive-Bilateral-Filtering)


### [Local Laplacian Filters: Edge-aware Image Processing with a Laplacian Pyramid](http://people.csail.mit.edu/sparis/publi/2011/siggraph/)
```
R = lapfilter(I,sigma_r,alpha,beta,colorRemapping,domain)
```
### [A Fast Approximation of the Bilateral Filter using a Signal Processing Approach](http://people.csail.mit.edu/sparis/bf/)
```
B = bfilter2(A,w,sigma)
```
### [Tree Filtering: Efficient Structure-Preserving Smoothing With a Minimum Spanning Tree](https://sites.google.com/site/linchaobao/home)
```
OUT = TreeFilterRGB_Uint8(uint8_rgbimg,sigma,sig_s[,sig_r=0.05[,num_iter=1]])
```
