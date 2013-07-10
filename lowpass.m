N =100;
I = zeros(N,1);

I(1:5:50) = 1;

I2 = repmat(I,2,1);
N2 = length(I2);

% d=fdesign.lowpass('N,Fc',1,6.42752,44100);
% hd = design(d,'IIR'); 
% fvtool(hd);
[b,a]=butter(2,0.05);

out = filter(b,a,I2);

plot(1:N2,I2,1:N2,out)