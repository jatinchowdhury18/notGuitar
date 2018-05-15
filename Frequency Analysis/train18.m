[gtr,FsG] = audioread('g18.wav');
[sax,FsS] = audioread('s18.wav');

LG = length(gtr);
LS = length(sax);

s = sign(gtr);
for x = 1:LG
    if s(x) == 1
        gtr(x) = gtr(x) + 32*(gtr(x)^2);
    elseif s(x) == -1
        gtr(x) = gtr(x) - 32*(gtr(x)^2);
    end
end

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
title('Single-Sided Amplitude Spectrum of Guitar');
xlabel('f (Hz)');
ylabel('|P1(f)|');


[peaksG, locG] = findpeaks(P1G,fG, 'MinPeakDistance', 300, 'MinPeakHeight', 1e-4);
peaksG(1) = [];
locG(1) = [];
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


[peaksS, locS] = findpeaks(P1S,fS, 'MinPeakDistance', 300, 'MinPeakHeight', 2e-5);
peaksS(1) = [];
locS(1) = [];
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
peakTest = zeros(1,minLoc);

for i = 1:minLoc
    mult(i) = peaksS(i)/peaksG(i);
    peakTest(i) = peaksG(i)*mult(i);
end

if numLocG > numLocS
    loc = locS;
else
    loc = locG;
end

subplot(3,2,6);
scatter(loc,peakTest);
xlim([0,6000]);
title('Multiplier Test');
xlabel('f (Hz)');
ylabel('Multiplied Guitar Peaks');



P2Test = FreqG/LG;
fGTest = FsG*(0:(LG))/LG;


GAlt = zeros(length(FreqG),1);
test = ones(length(FreqG),1);

diff = zeros(1,numLocG-1);
for n = 1:numLocG-1
    diff(n) = locG(n+1) - locG(n);
end
peakWidthHz = sum(diff)/(numLocG-1);
fundWinHz = locG(1) - (peakWidthHz/2);
fundWinLoc = find(fG > fundWinHz,1);


counter = 1;
iter = 1;
for j = fundWinLoc:length(fG)
    currentFreq = fG(j);
    if currentFreq-fundWinHz > (peakWidthHz*iter)
        iter = iter+1;
    end
    
    if iter > minLoc
        k = j;
        for k = j:LG
            GAlt(k) = P2Test(k);
        end
        break
    end
    
    GAlt(j) = P2Test(j)*(32*(mult(iter)));
    GAlt(length(FreqG)-j) = GAlt(j);
    test(j) = test(j)*mult(iter);
end

AbsP2Test = abs(GAlt);
P1Test = AbsP2Test(1:LG/2+1);
P1Test(2:end-1) = 2*P1Test(2:end-1);

%
subplot(3,2,5);
plot(fG,P1Test);
xlim([0,6000]);
title('Overtone Synthesis of Sax from Guitar');
xlabel('f (Hz)');
ylabel('|P1(f)| * Multiplier');
%}

%{
inc = 0:length(fG);
dup = GAlt*2;
dup(inc > length(fG)/2-1) = 0;
dupOut = ifft(dup);
%}

outAlt = ifft(GAlt);
re = real(outAlt);
re = re/(max(re)*1.1);

outTest = fft(re);
P2outTest = abs(outTest/LG);
P1outTest = P2outTest(1:LG/2+1);
P1outTest(2:end-1) = 2*P1outTest(2:end-1);
foutTest = FsG*(0:(LG/2))/LG;
%{
subplot(3,2,6);
plot(foutTest,P1outTest);
xlim([0,6000]);
title('Single-Sided Amplitude Spectrum of Output');
xlabel('f (Hz)');
ylabel('|P1(f)|');
%}

%audiowrite('GtrOut1.wav',re,FsG);
%soundsc(re,FsG);
%}