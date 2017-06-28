clear;clc;
img=zeros(128,128);
size=5;
for i=(64-size):(65+size)
    for j=(64-size):(65+size)
        img(i,j)=255;
    end
end
imshow(img);
imwrite(img,'dot5.jpg');
ftr=fft2(double(img));
A=log(abs(ftr)+1);
//imshow(log(abs(fftshift(fft2(double(img))))+1),[]);