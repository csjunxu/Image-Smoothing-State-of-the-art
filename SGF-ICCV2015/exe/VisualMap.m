function VisualMap(data,Title)


data=double(data(:,:,1));
data=flipud(data);
Handle = pcolor( data );
%figure;
%set('name',title,'Numbertitle','off');
title(Title);
set( Handle , 'EdgeColor' , 'none');
caxis([min(data(:)),max(data(:))]);
colormap jet;
