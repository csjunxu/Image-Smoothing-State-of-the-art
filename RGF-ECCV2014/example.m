
clear,close;

Original_image_dir = '/Users/xujun/Desktop/YingkunHou/dataset/origin_images';
fpath   = fullfile(Original_image_dir, '*.png');
im_dir  = dir(fpath);
im_num     = length(im_dir);

method = 'RGF';
for i = 1:im_num
    I = im2double(imread(fullfile(Original_image_dir, im_dir(i).name)));
    S = regexp(im_dir(i).name, '\.', 'split');
    sI = RollingGuidanceFilter(I,3,0.05,4);
    fprintf('%s is done!\n', im_dir(i).name);
    outname = sprintf(['/Users/xujun/Desktop/YingkunHou/results/500images' S{1} '_' method '.png']);
    imwrite(sI, outname);
end