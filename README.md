# A Collection of Image Smoothing Algorithms





1. "GF-ECCV2010TPAMI2013": Guided Image Filtering, by Kaiming He, Jian Sun, and Xiaoou Tang. ECCV 2010, TPAMI 2013. (http://kaiminghe.com/eccv10/)
2. "RTV-TOG2012": Structure Extraction from Texture via Relative Total Variation. Li Xu, Qiong Yan, Yang Xia, Jiaya Jia. ACM TOG 2012. (http://www.cse.cuhk.edu.hk/~leojia/projects/texturesep/)

### Image Smoothing via Unsupervised Learning, Siggraph Asia, 2018. 

Code: https://github.com/fqnchina/ImageSmoothing




### [Image Smoothing via L0 Gradient Minimization](http://www.cse.cuhk.edu.hk/leojia/projects/L0smoothing/index.html)
```
S = L0Smoothing(Im, lambda, kappa)
```
### [Local Laplacian Filters: Edge-aware Image Processing with a Laplacian Pyramid](http://people.csail.mit.edu/sparis/publi/2011/siggraph/)
```
R = lapfilter(I,sigma_r,alpha,beta,colorRemapping,domain)
```
### [Edge-Preserving Decompositions for Multi-Scale Tone and Detail Manipulation](http://www.cs.huji.ac.il/~danix/epd/)

### [A Fast Approximation of the Bilateral Filter using a Signal Processing Approach](http://people.csail.mit.edu/sparis/bf/)
```
B = bfilter2(A,w,sigma)
```

### [Nonlinear total variation based noise removal algorithms](http://en.wikipedia.org/wiki/Total_variation_denoising)
```
out = SplitBregmanROF(image,mu,tol)
```

### [Fast Global Image Smoothing Based on Weighted Least Squares](https://sites.google.com/site/globalsmoothing/)
```
F = FGS(img, sigma, lambda, joint_image, num_iterations, attenuation)
```

### [Tree Filtering: Efficient Structure-Preserving Smoothing With a Minimum Spanning Tree](https://sites.google.com/site/linchaobao/home)
```
OUT = TreeFilterRGB_Uint8(uint8_rgbimg,sigma,sig_s[,sig_r=0.05[,num_iter=1]])
```
### [Edge-Avoiding Wavelets and their Applications](http://www.cs.huji.ac.il/~raananf/projects/eaw/)
```
[A W] = EAW(I, nlevels, wavelet_type, dist_func, sigma)
```
### [Diffusion Maps for Edge-Aware Image Editing](http://www.cs.huji.ac.il/labs/cglab/projects/diffmaps/)
```
