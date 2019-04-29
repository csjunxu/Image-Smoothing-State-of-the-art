%%%%%%% Detail Enhacement


clear

wave_type = 1 ;

figure(1)
clf
colormap(gray(256)) ;

I = imread('pflower.jpg');
I = double(I) / 255 ;
[w, h, c] = size(I) ;
nlevels = floor(log2(min(size(I(:,:,1)))))-1 ;

figure(1)

subplot(2,3,1), imagesc(I), title('Input'), axis off ;  drawnow
I = rgb2hsv(I) ;

R = I ;
[A, W] = EAW(R(:,:,3),nlevels,wave_type,1,0) ; % sigma = 0
for i=1:nlevels
    A{i,1} = A{i,1} * 1.5^(nlevels-i) ;  % enhance fine detail  
end
R(:,:,3) = iEAW(A,W,wave_type) ;

R = hsv2rgb(R) ;

R(R<0) = 0 ;
R(R>1) = 1 ;

subplot(2,3,2), imagesc(R), title('Regular Wavelets'), axis off ; drawnow

R = I ;
[A, W] = EAW(R(:,:,3),nlevels,wave_type,1,1) ;
for i=1:nlevels
    A{i,1} = A{i,1} * 1.4^(nlevels-i) ;
    
end
R(:,:,3) = iEAW(A,W,wave_type) ;

R = hsv2rgb(R) ;

R(R<0) = 0 ;
R(R>1) = 1 ;

subplot(2,3,3), imagesc(R), title('Edge-Avoiding Wavelets'), axis off ;  drawnow
nlevels = floor(log2(min(size(I(:,:,1)))))-2 ;

R = I ;
[A, W] = EAW(R(:,:,3),nlevels,wave_type,1,0) ;
for i=1:nlevels
    A{i,1} = A{i,1} * 0.7^(nlevels+1-i) ;  % attenuate fine detail
end
R(:,:,3) = iEAW(A,W,wave_type) ;

R = hsv2rgb(R) ;

R(R<0) = 0 ;
R(R>1) = 1 ;

subplot(2,3,5), imagesc(R), title('Regular Wavelets'), axis off ;  drawnow


R = I ;
[A, W] = EAW(R(:,:,3),nlevels,wave_type,1,1) ;
for i=1:nlevels
    A{i,1} = A{i,1} * 0.7^(nlevels+1-i) ;  
end
R(:,:,3) = iEAW(A,W,wave_type) ;

R = hsv2rgb(R) ;

R(R<0) = 0 ;
R(R>1) = 1 ;

subplot(2,3,6), imagesc(R), title('Edge-Avoiding Wavelets'), axis off ;  drawnow
