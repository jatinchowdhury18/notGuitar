fileID = fopen('multipliers.txt','r');
M = fscanf(fileID,'%f\n');
fclose(fileID);


H = ones(1,188);
H(1) = M(1);

for i = 2:90
    H(i) = M(i);
    H(188-i+2) = M(i);
end

i = 1:188;

tf = issymmetric(H);

h = ifft(H);
plot(i,h);

%{
D = [6, -2, 2, -2];
tf = issymmetric(D);
d = ifft(D);

i = 1:7;
%plot(i,d);
%}

%fileID = fopen('multipliers_fourier.txt','w');
%fprintf(fileID,'%f\r\n', h);
%fclose(fileID);
