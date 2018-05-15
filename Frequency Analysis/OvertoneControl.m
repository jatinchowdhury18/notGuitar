[gtr,FsG] = audioread('GuitarCut.wav');
[sax,FsS] = audioread('SaxCut.wav');

LG = length(gtr);
LS = length(sax);

FreqG = fft(gtr);
FreqS = fft(sax);

%Adapted from Mathworks fft example code
P2G = abs(FreqG/LG);
P1G = P2G(1:LG/2+1);
P1G(2:end-1) = 2*P1G(2:end-1);
fG = FsG*(0:(LG/2))/LG;
subplot(3,2,1);
plot(fG,P1G);
xlim([0,6000]);
title('Single-Sided Amplitude Spectrum of Gutiar');
xlabel('f (Hz)');
ylabel('|P1(f)|');


[peaksG, locG] = findpeaks(P1G,fG, 'MinPeakDistance', 100, 'MinPeakHeight', 4e-4);
subplot(3,2,2);
scatter(locG, peaksG);
xlim([0,6000]);
title('Gutiar Peaks');
xlabel('f (Hz)');
ylabel('|P1(f)|');


P2S = abs(FreqS/LS);
P1S = P2S(1:LS/2+1);
P1S(2:end-1) = 2*P1S(2:end-1);
fS = FsS*(0:(LS/2))/LS;
subplot(3,2,3);
plot(fS,P1S);
xlim([0,6000]);
title('Single-Sided Amplitude Spectrum of Sax');
xlabel('f (Hz)');
ylabel('|P1(f)|');


[peaksS, locS] = findpeaks(P1S,fS, 'MinPeakDistance', 100, 'MinPeakHeight', 4e-4);
subplot(3,2,4);
scatter(locS, peaksS);
xlim([0,6000]);
title('Sax Peaks');
xlabel('f (Hz)');
ylabel('|P1(f)|');

numLocG = length(locG);
numLocS = length(locS);
minLoc = min(numLocG, numLocS);

mult = zeros(1,minLoc);

for i = 1:minLoc
    mult(i) = peaksS(i)/peaksG(i);
end

GAlt = zeros(length(fG),1);
test = ones(length(fG),1);
peakWidth = 147;
peakOffset = 172;
counter = 1;
iter = 1;
for j = peakOffset:length(fG)
    currentFreq = fG(j);
    if currentFreq-74 > (147*iter)
        iter = iter+1;
    end
    
    if iter > minLoc
        k = j;
        for k = j:length(fG)
            GAlt(k) = P1G(k);
        end
        break
    end
    
    GAlt(j) = P1G(j)*mult(iter);
    test(i) = test(i)*mult(iter);
end

subplot(3,2,5);
plot(fG,GAlt);
xlim([0,6000]);
title('Overtone Synthesis of Sax from Gutiar');
xlabel('f (Hz)');
ylabel('|P1(f)| * Multiplier');

%{
inc = 0:length(fG);
dup = GAlt*2;
dup(inc > length(fG)/2-1) = 0;
dupOut = ifft(dup);
%}


outAlt = ifft(GAlt);
re = real(outAlt);
re = re/(1.845e-05);
%audiowrite('GuitarOutput2.wav',dupOut,FsG);
soundsc(re,FsG);