clear,close;

Original_image_dir = '/Users/xujun/Desktop/YingkunHou/dataset/origin_images';
fpath   = fullfile(Original_image_dir, '*.png');
im_dir  = dir(fpath);
im_num     = length(im_dir);

method = 'L0';
for i = 1:im_num
    I = imread(fullfile(Original_image_dir, im_dir(i).name));
    S = regexp(im_dir(i).name, '\.', 'split');
    sI = L0Smoothing(I,0.01);
    fprintf('%s is done!\n', im_dir(i).name);
    outname = sprintf(['/Users/xujun/Desktop/YingkunHou/results/500images/' S{1} '_' method '.png']);
    imwrite(sI, outname);
end