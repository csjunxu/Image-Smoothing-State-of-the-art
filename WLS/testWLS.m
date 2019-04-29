clear,close;

Original_image_dir = '/Users/xujun/Desktop/YingkunHou/dataset/origin_images';
fpath   = fullfile(Original_image_dir, '*.png');
im_dir  = dir(fpath);
im_num     = length(im_dir);

method = 'WLS';
for i = 1:im_num
    I = double(imread(fullfile(Original_image_dir, im_dir(i).name)));
    I = I./max(I(:));
    S = regexp(im_dir(i).name, '\.', 'split');
    [h,w,ch] = size(I);
    sI = zeros(h,w,ch);
    for c=1:ch
        sI(:,:,c) = wlsFilter(I(:,:,c));
    end
    fprintf('%s is done!\n', im_dir(i).name);
    outname = sprintf(['/Users/xujun/Desktop/YingkunHou/results/500images/' S{1} '_' method '.png']);
    imwrite(sI, outname);
end