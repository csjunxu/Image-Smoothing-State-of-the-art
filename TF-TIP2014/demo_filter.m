clear,close;

Original_image_dir = '/home/csjunxu/Github/data/dataset/origin_images';
fpath   = fullfile(Original_image_dir, '*.png');
im_dir  = dir(fpath);
im_num     = length(im_dir);

method = 'TF';
for i = 1:im_num
    I = imread(fullfile(Original_image_dir, im_dir(i).name));
    S = regexp(im_dir(i).name, '\.', 'split');
    sI = TreeFilterRGB_Uint8(I, 0.01, 3, 0.08, 4);
    fprintf('%s is done!\n', im_dir(i).name);
    outname = sprintf(['/home/csjunxu/Github/data/dataset/results/' S{1} '_' method '.png']);
    imwrite(sI, outname);
end

% I1 = imread('baboon.png');
% tic;
% J1 = TreeFilterRGB_Uint8(I1, 0.1, 4);
% toc;
% figure;imshow([I1,J1]);

% I2 = imread('monalisamosaic.jpg');
% tic;
% J2 = TreeFilterRGB_Uint8(I2, 0.01, 3, 0.08, 4);
% toc;
% figure;imshow([I2,J2]);
