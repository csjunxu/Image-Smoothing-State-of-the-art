function shrink(file,scale)
img=imread(file);
[m,n,p]=size(img);
img=img(:,:,1);
m1=floor(m/scale);
n1=floor(n/scale);
I=uint8(zeros(m1,n1));
new=uint8(zeros(m,n));
for row=1:m
    for col=1:n
        if mod(row,scale)==0&mod(col,scale)==0
            I(row/scale,col/scale)=img(row,col);
            new(row,col)=img(row,col);
        end
    end
end
imwrite(I,'shrink.png');
imwrite(new,'seedmap.png');
        
            
