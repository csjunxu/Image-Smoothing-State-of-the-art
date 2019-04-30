close all;

guidfile='depth/guid.png';

targetfile='depth/noise.png';
outfile='depth/denoise.png';
%%%%%%if you use windows please use the following command.
command=sprintf('SGF.exe %s %s %s %d %.2f %.2f %d',guidfile, targetfile,outfile, 32,0.04,0.4,1);
%%%%%%for linux
%command=sprintf('./SGF %s %s %s %d %.2f %.2f %d',guidfile, targetfile,outfile, 32,0.05,0.05,1);
dos(command);
img=imread(outfile);
img=img(:,:,1);
temp=medfilt2(img,[5,5]);
img(3:size(img,1)-2,3:size(img,2)-2)=temp(3:size(img,1)-2,3:size(img,2)-2);
imwrite(img,outfile);

temp=imread(targetfile);
VisualMap(temp,'noisy depth map as input');
figure;
VisualMap(img,'denoising result');
figure;

targetfile='depth/seedmap.png';
outfile='depth/upsampling.png';
%%%%%%if you use windows please use the following command.
command=sprintf('SGF.exe %s %s %s %d %.2f %.2f %d',guidfile, targetfile,outfile, 32,0.025,0.25,1);
%%%%%%for linux
%command=sprintf('./SGF %s %s %s %d %.2f %.2f %d',guidfile, targetfile,outfile, 32,0.05,0.05,1);
dos(command);
img=imread(outfile);
img=img(:,:,1);
temp=medfilt2(img,[5,5]);
img(3:size(img,1)-2,3:size(img,2)-2)=temp(3:size(img,1)-2,3:size(img,2)-2);
imwrite(img,outfile);
VisualMap(img,'8 times depth upsampling result');
figure;
temp=imread('depth/ground.png');
temp=medfilt2(img,[5,5]);
VisualMap(temp,'ground truth');




        
            
