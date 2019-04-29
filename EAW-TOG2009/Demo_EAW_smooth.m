clear,close;

Original_image_dir = '/Users/xujun/Desktop/YingkunHou/dataset/origin_images';
fpath   = fullfile(Original_image_dir, '*.png');
im_dir  = dir(fpath);
im_num     = length(im_dir);

method = 'EAW';
%%%%%%% Detail Enhacement
wave_type = 1;
for i = 1:im_num
    I = double(imread(fullfile(Original_image_dir, im_dir(i).name)))/255;
    S = regexp(im_dir(i).name, '\.', 'split');
    [w, h, c] = size(I) ;
    I = rgb2hsv(I) ;
    nlevels = floor(log2(min(size(I(:,:,1)))))-2 ;
    R = I ;
    [A, W] = EAW(R(:,:,3),nlevels,wave_type,1,1) ;
    for n=1:nlevels
        A{n,1} = A{n,1} * 0.7^(nlevels+1-n) ;
    end
    R(:,:,3) = iEAW(A,W,wave_type) ;
    R = hsv2rgb(R) ;
    R(R<0) = 0 ;
    R(R>1) = 1 ;
    fprintf('%s is done!\n', im_dir(i).name);
    outname = sprintf(['/Users/xujun/Desktop/YingkunHou/results/500images/' S{1} '_' method '.png']);
    imwrite(R, outname);
end
