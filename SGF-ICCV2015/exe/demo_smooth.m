close all;
index=0;
imgname=sprintf('smooth/%d.png',index);
format=imgname(length(imgname)-3:length(imgname));
 file=imgname(1:length(imgname)-4);
 outfile=strcat(file,'_denoise',format);
 radius=12;
 eps=0.05;
 thresh=0.1;
 iter=3;
command=sprintf('SGF.exe %s %s %s %d %.2f %.2f %d',imgname, imgname,outfile, radius,eps,thresh,iter);
%%%%%%for linux
%command=sprintf('./SGF %s %s %s %d %.2f %.2f %d',imgname, imgname,outfile, radius,eps,thresh,iter);
dos(command);
img=imread(imgname);
VisualMap(img,'input');
figure;
img=imread(outfile);
VisualMap(img,'denoising result');
figure;
outfile=strcat(file,'_smooth',format);
 radius=25;
 eps=0.06;
 thresh=0.2;
 iter=8;
command=sprintf('SGF.exe %s %s %s %d %.2f %.2f %d',imgname, imgname,outfile, radius,eps,thresh,iter);
%%%%%%for linux
%command=sprintf('./SGF %s %s %s %d %.2f %.2f %d',imgname, imgname,outfile, radius,eps,thresh,iter);
dos(command);
img=imread(outfile);
VisualMap(img,'smooth effects');

command=sprintf('SGF.exe %s %s %s %d %.2f %.2f %d',imgname, imgname,outfile, radius,eps,thresh,iter);
%%%%%%for linux
%command=sprintf('./SGF %s %s %s %d %.2f %.2f %d',imgname, imgname,outfile, radius,eps,thresh,iter);
dos('SGF.exe smooth/1.png smooth/1.png smooth/1_smooth.png 12 0.1 0.2 3');
dos('SGF.exe smooth/2.png smooth/2.png smooth/2_smooth.png 16 0.05 0.1 3');
dos('SGF.exe smooth/3.png smooth/3.png smooth/3_smooth.png 8 0.05 0.2 3');
%}
