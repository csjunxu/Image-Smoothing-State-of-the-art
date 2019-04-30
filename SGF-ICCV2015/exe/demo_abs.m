for index=1:7
filename=sprintf('abs/%d.png',index);
eps=0.1;
radius=16;
if(index>4)
	eps=0.05;
	radius=8;
end
abstraction(filename,radius,eps,0.1,3);
end
