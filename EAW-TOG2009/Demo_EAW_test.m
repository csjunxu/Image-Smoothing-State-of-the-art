% Egde-Avoiding Wavelets demo
%
% comparison to regular (1st generation) wavelets is implemnented
% by setting sigma=0
%
% Shows (Guided) Edge-Aware Interpolation by colorization, detail
% enhacement and edge-preservign detail suppression.
%
% This code implements the paper "Edge-Avoiding Wavelets and their
% Applications" SIGGRAPH 2009.
%
% Code written by Raanan Fattal 



%%%%%%% Speed Check

clear

wave_type = 1 ;

figure(1)
clf
colormap(gray(256)) ;

I = imread('pflower.jpg');
I = double(I) / 255 ;
[w, h, c] = size(I) ;
nlevels = floor(log2(min(size(I(:,:,1)))))-2 ;

figure(1)


A = cell(nlevels+1,3) ;
W = cell(nlevels,3) ;

nc = 3 ;

for k=1:3
R=I ;
for i=1:nlevels
    [tA, tW] = EAW(R,1,wave_type,1,1) ; % process a single level at a time
                                       % (not really needed - it's just for
                                       % this demo)
    for c=1:nc
        A{i,c} = tA{1,c} ;
        W{i,c} = tW{1,c} ;
    end
    
    R = reshape([tA{2,1} tA{2,2} tA{2,3}],size(tA{2,1},1),size(tA{2,1},2),3) ;
    
    R(R>1)=1;
    R(R<0)=0;
    imagesc(R)
    drawnow
end
title('Forward Transform Speed Check')
drawnow
end
pause(0.1)
