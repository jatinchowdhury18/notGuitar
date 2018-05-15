%Test Sliding DFT
x1 = [0.1, 0.65, -0.23, 0.45, -0.3, -0.12, -0.05, 0.01, 0.09, 0.11];
x1 = x1*1000;
y1 = fft(x1);
%disp(y1);

x2 = [0.65, -0.23, 0.45, -0.3, -0.12, -0.05, 0.01, 0.09, 0.11, 0.2];
x2 = x2*1000;
y2a = fft(x2);

for k = 1:length(x2)
    %0.1 is the value dropped from x1 to x2, 0.2 is the value added
    y2b(k) = (y1(k) - 100 + 200)*(cos(2*pi*(k-1)/10) + 1i*sin(2*pi*(k-1)/10));%exp(1i*2*pi*(k-1)/10);
    %y2b_IM(k) = (y1(k) - 0.1 + 0.2)*sin(2*pi*(k-1)/10);
    %careful, in C this loop is gonna start at index zero
end

%If these are tne same, then using the Sliding DFT works
%disp(y2a);
%disp(y2b);


%Test Inverse Sliding DFT
%t = ()*exp(-1i*2*pi*(k-1)/10);
%t = y2b(1) - y1(1) + 0.1; %Use k=0 values of FFT's, 0.1 = value dropped from x1 to x2
t = real(y2b(1)) - real(y2b(6));
for k = 2:5
    %t = t + real(y2b(k))*cos(2*pi*(k-1)/10) + imag(y2b(k))*sin(x12*pi*(k-1)/10) - y1(k) + 0.1;%y2b(k);
    t = t + 2*(real(y2b(k))*cos(2*pi*(k-1)/10) + imag(y2b(k))*sin(2*pi*(k-1)/10)); 
end
%t = t - real(y2b(1))/(length(x2)/2);
%t = t - real(y2b((length(x2)/2)))/(length(x2)/2);
t = t/length(x2);
%disp(t); %If this is equal to 0.2 (the value I added to the end of x2) then it works!


%y_new = [-2, -1, 0, 0, -1, -2, -2, -1, 0, -1, -2, 0, -1, -1, -1, 0, 0, 0];
%Y_new = fft(y_new);
%disp(Y_new);
x1 = ones(1,10);
Z = ifft(x1);
disp(Z);

