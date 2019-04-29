% example: edge-preserving smoothing
% figure 1 in our paper

clear,close;

Original_image_dir = '../../dataset/origin_images';
fpath   = fullfile(Original_image_dir, '*.png');
im_dir  = dir(fpath);
im_num     = length(im_dir);

method = 'GF';
for i = 1:im_num
    I = double(imread(fullfile(Original_image_dir, im_dir(i).name))) / 255;
    S = regexp(im_dir(i).name, '\.', 'split');
    %p = I;
    %r = 4; % try r=2, 4, or 8
    %eps = 0.1^2; % try eps=0.1^2, 0.2^2, 0.4^2
    %q = guidedfilter_color(I, p, r, eps);
    q = imguidedfilter(I);
    fprintf('%s is done!\n', im_dir(i).name);
    outname = sprintf(['../../results/' S{1} '_' method '.png']);
    imwrite(q, outname);
end


%figure();
%imshow([I, q], [0, 1]);
