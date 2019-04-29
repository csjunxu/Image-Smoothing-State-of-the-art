% Demo script
% Uncomment each case to see the results 

clear,close;

Original_image_dir = '/Users/xujun/Desktop/YingkunHou/dataset/origin_images';
fpath   = fullfile(Original_image_dir, '*.png');
im_dir  = dir(fpath);
im_num     = length(im_dir);

method = 'RTV';
for i = 1:im_num
    I = imread(fullfile(Original_image_dir, im_dir(i).name));
    S = regexp(im_dir(i).name, '\.', 'split');
    sI = tsmooth(I,0.015,3);
    fprintf('%s is done!\n', im_dir(i).name);
    outname = sprintf(['/Users/xujun/Desktop/YingkunHou/results/500images' S{1} '_' method '.png']);
    imwrite(sI, outname);
end

% I = (imread('imgs/crossstitch.jpg'));
% S = tsmooth(I,0.015,3);
% figure, imshow(I), figure, imshow(S);

% I = (imread('imgs/graffiti.jpg'));
% S = tsmooth(I,0.015,3);
% figure, imshow(I), figure, imshow(S);

% I = (imread('imgs/crossstitch.jpg'));
% S = tsmooth(I,0.015,3);
% figure, imshow(I), figure, imshow(S);

% I = (imread('imgs/mosaicfloor.jpg'));
% S = tsmooth(I, 0.01, 3, 0.02, 5); 
% figure, imshow(I), figure, imshow(S);






