function abstraction(imgname,radius,eps,thresh,iter)
 
 format=imgname(length(imgname)-3:length(imgname));
 file=imgname(1:length(imgname)-4);
 outfile=strcat(file,'_smooth',format);
 
%%%%%%if you use windows please use the following command.
%command=sprintf('SGF.exe %s %s %s %d %.2f %.2f %d',imgname, imgname,outfile, radius,eps,thresh,iter);
%%%%%%for linux
command=sprintf('./SGF %s %s %s %d %.2f %.2f %d',imgname, imgname,outfile, radius,eps,thresh,iter);
dos(command);
scale=6;
I=imread(outfile); 
if(size(I,3)>1)                  
II=double(rgb2gray(I));
else
II=double(I);
end
[Gx,Gy]=gradient(II);               
G=sqrt(Gx.*Gx+Gy.*Gy);
J=zeros(size(II,1),size(II,2));
J(:)=255;
%K=find(G>=70);               
%J(K)=0;


J=uint8(J-G*scale);
imwrite(J,strcat(file,'_grad',format));  
%e=edge(II,'canny');
e=double(J)<180;
%temp=imfilter(double(e),ones(5,5),'same');
e=imfilter(double(e),ones(2,1),'same');
tag=e>0;
for i=1:size(I,3)
p=I(:,:,i);
p(tag)=0;
I(:,:,i)=p;
end
imwrite(I,strcat(file,'_abs',format));
return;