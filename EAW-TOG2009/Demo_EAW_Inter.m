%%%%%%% Guided Edge-Aware Interpolation

clear
figure(2)

S = imread('pflower.jpg');
S = double(S) / 255 ;
G = imread('pflower.jpg');
G = double(G) / 255 ;
[w, h, c] = size(S) ;
nlevels = floor(log2(min(size(S(:,:,1))))) ;

figure(2)
subplot(2,2,1), imagesc(G), title('Input Image'), axis off, drawnow
subplot(2,2,2), imagesc(S), title('Input Scribbles'), axis off, drawnow

smth_factor = 0.125 ;

wave_type = 1 ;

[A, W] = EAW(G(:,:,1),nlevels,wave_type,1,0) ; % construction wavelets weights based on guiding BW image (A not needed)

N = (abs(S(:,:,1) - S(:,:,2)) > 0.01) ; % extract scribbles 

for c=1:3
    tS = S(:,:,c) ;
    tS(~N) = 0;
    S(:,:,c) = tS ;
end

yuv = rgb2yuv(S) ; % operating on the UV of the YUV color space
U = yuv(:,:,2) ;
V = yuv(:,:,3) ;

N = double(N) ;  % normalization field

Au = gEAW(U,W,wave_type) ; % Forward transform using weights W
Av = gEAW(V,W,wave_type) ; 
An = gEAW(N,W,wave_type) ; 

for i=1:nlevels+1
    Au{i,1} = Au{i,1} * smth_factor^i ;
    Av{i,1} = Av{i,1} * smth_factor^i ;
    An{i,1} = An{i,1} * smth_factor^i ;
end

yuv(:,:,2) = igEAW(Au,W,wave_type) ; % inv transform using weight W
yuv(:,:,3) = igEAW(Av,W,wave_type) ;
N = igEAW(An,W,wave_type) ;


N(N<1e-8) = 1 ;
    
yuv(:,:,2) = yuv(:,:,2)./N;  % normalize (like Shepard method)
yuv(:,:,3) = yuv(:,:,3)./N;

Y = rgb2yuv(G) ;
yuv(:,:,1) = Y(:,:,1) ; % retrieve old Y channel
C = yuv2rgb(yuv) ;

C(C<0) = 0 ;
C(C>1) = 1 ;

subplot(2,2,3), imagesc(C), title('Regular Wavelets'), axis off, drawnow

[A W] = EAW(G(:,:,1),nlevels,wave_type,1,1) ; 

N = (abs(S(:,:,1) - S(:,:,2)) > 0.01) ; % extracting scribbles 

for c=1:3
    tS = S(:,:,c) ;
    tS(~N) = 0;
    S(:,:,c) = tS ;
end

yuv = rgb2yuv(S) ; % operating on the UV of the YUV color space
U = yuv(:,:,2) ;
V = yuv(:,:,3) ;

N = double(N) ;  % normalization field

Au = gEAW(U,W,wave_type) ; 
Av = gEAW(V,W,wave_type) ; 
An = gEAW(N,W,wave_type) ; 

for i=1:nlevels+1
    Au{i,1} = Au{i,1} * smth_factor^i ;
    Av{i,1} = Av{i,1} * smth_factor^i ;
    An{i,1} = An{i,1} * smth_factor^i ;
end

yuv(:,:,2) = igEAW(Au,W,wave_type) ;
yuv(:,:,3) = igEAW(Av,W,wave_type) ;
N = igEAW(An,W,wave_type) ;

N(N<1e-8) = 1 ;
    
yuv(:,:,2) = yuv(:,:,2)./N;  % normalize (like Shepard method)
yuv(:,:,3) = yuv(:,:,3)./N;


Y = rgb2yuv(G) ;
yuv(:,:,1) = Y(:,:,1) ; % retrieve old Y channel
C = yuv2rgb(yuv) ;

C(C<0) = 0 ;
C(C>1) = 1 ;

subplot(2,2,4), imagesc(C), title('Edge-Avoiding Wavelets'), axis off, drawnow
