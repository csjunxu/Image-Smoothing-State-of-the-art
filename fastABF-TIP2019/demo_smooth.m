
clearvars; close all;
clc;

%% Edge-preserving smoothing example
clear,close;

Original_image_dir = '/home/csjunxu/Github/data/dataset/origin_images';
fpath   = fullfile(Original_image_dir, '*.png');
im_dir  = dir(fpath);
im_num     = length(im_dir);

method = 'fastABF';
addpath('./fastABF/');
rho_smooth = 2;    % Spatial kernel parameter for smoothing step

for i = 1:im_num
    I = imread(fullfile(Original_image_dir, im_dir(i).name));
    S = regexp(im_dir(i).name, '\.', 'split');
    I = double(I);
    
    % Set pixelwise sigma (range kernel parameters) for smoothing
    M = mrtv(I,5);
    sigma_smooth = linearMap(1-M,[0,1],[30,70]);
    sigma_smooth = imdilate(sigma_smooth,strel('disk',2,4));  % Clean up the fine noise
    % Apply fast algorithm to smooth textures
    sI = I;
    tic;
    for it = 1:2
        out = nan(size(I));
        for k = 1:size(I,3)
            out(:,:,k) = fastABF(sI(:,:,k),rho_smooth,sigma_smooth,[],4);
        end
        sI = out;
        sigma_smooth = sigma_smooth*0.8;
    end
    fprintf('%s is done!\n', im_dir(i).name);
    outname = sprintf(['/home/csjunxu/Github/data/dataset/results/' S{1} '_' method '.png']);
    imwrite(sI/255, outname);
end