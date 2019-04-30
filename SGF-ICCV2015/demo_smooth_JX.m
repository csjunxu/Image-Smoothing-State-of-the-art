%% Edge-preserving smoothing example
close all;
clc;

Original_image_dir = '/home/csjunxu/Github/data/dataset/origin_images';
fpath   = fullfile(Original_image_dir, '*.png');
im_dir  = dir(fpath);
im_num     = length(im_dir);

method = 'SGF';
for i = 1:im_num
    I = imread(fullfile(Original_image_dir, im_dir(i).name));
    S = regexp(im_dir(i).name, '\.', 'split');
    file = S{1};
    format = S{2};
    outname = sprintf(['/home/csjunxu/Github/data/dataset/results/' S{1} '_' method '.png']);
    radius=12;
    eps=0.05;
    thresh=0.1;
    iter=3;
    %%%%%%for windows
    command=sprintf('SGF.exe %s %s %s %d %.2f %.2f %d',imgname, imgname, outname, radius,eps,thresh,iter);
    %%%%%%for linux
    %command=sprintf('./SGF %s %s %s %d %.2f %.2f %d',imgname, imgname,outfile, radius,eps,thresh,iter);
    dos(command);
    fprintf('%s is done!\n', im_dir(i).name);
    imwrite(sI, outname);
end
