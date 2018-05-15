N = 90;
numBands = 90;
MaxFreq = 11500;

OvertoneWidths = zeros(1,25);
Multipliers = zeros(N,25);
OvertoneFreqs = zeros(N,25);

% Run scrips and store data in matrices
train1;
OvertoneWidths(1) = peakWidthHz;
Multipliers(:,1) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,1) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train2;
OvertoneWidths(2) = peakWidthHz;
Multipliers(:,2) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,2) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train3;
OvertoneWidths(3) = peakWidthHz;
Multipliers(:,3) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,3) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train4;
OvertoneWidths(4) = peakWidthHz;
Multipliers(:,4) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,4) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train5;
OvertoneWidths(5) = peakWidthHz;
Multipliers(:,5) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,5) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train6;
OvertoneWidths(6) = peakWidthHz;
Multipliers(:,6) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,6) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train7;
OvertoneWidths(7) = peakWidthHz;
Multipliers(:,7) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,7) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train8;
OvertoneWidths(8) = peakWidthHz;
Multipliers(:,8) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,8) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train9;
OvertoneWidths(9) = peakWidthHz;
Multipliers(:,9) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,9) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train10;
OvertoneWidths(10) = peakWidthHz;
Multipliers(:,10) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,10) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train11;
OvertoneWidths(11) = peakWidthHz;
Multipliers(:,11) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,11) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train12;
OvertoneWidths(12) = peakWidthHz;
Multipliers(:,12) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,12) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train13;
OvertoneWidths(13) = peakWidthHz;
Multipliers(:,13) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,13) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train14;
OvertoneWidths(14) = peakWidthHz;
Multipliers(:,14) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,14) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train15;
OvertoneWidths(15) = peakWidthHz;
Multipliers(:,15) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,15) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train16;
OvertoneWidths(16) = peakWidthHz;
Multipliers(:,16) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,16) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train17;
OvertoneWidths(17) = peakWidthHz;
Multipliers(:,17) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,17) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train18;
OvertoneWidths(18) = peakWidthHz;
Multipliers(:,18) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,18) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train19;
OvertoneWidths(19) = peakWidthHz;
Multipliers(:,19) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,19) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train20;
OvertoneWidths(20) = peakWidthHz;
Multipliers(:,20) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,20) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train21;
OvertoneWidths(21) = peakWidthHz;
Multipliers(:,21) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,21) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train22;
OvertoneWidths(22) = peakWidthHz;
Multipliers(:,22) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,22) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train23;
OvertoneWidths(23) = peakWidthHz;
Multipliers(:,23) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,23) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train24;
OvertoneWidths(24) = peakWidthHz;
Multipliers(:,24) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,24) = [locG(1:minLoc) zeros(1,N-minLoc)].';

train25;
OvertoneWidths(25) = peakWidthHz;
Multipliers(:,25) = [mult zeros(1,N-minLoc)].';
OvertoneFreqs(:,25) = [locG(1:minLoc) zeros(1,N-minLoc)].';



%MaxFreq = max(OvertoneFreqs(:));
%Bands = zeros(ceil(MaxFreq/128)+1,1);


Bands = zeros(numBands+1,1);

% Generate bands from minimum overtone bandwidth
m = 1;
val = 0;
while val < MaxFreq
    Bands(m) = val;
    m = m+1;
    val = val+128;
end
Bands(numBands+1) = val;


% Average multipliers from all training signals
BandMultAvgTot = zeros((numBands),1);

for z = 1:(numBands)
    BandMult = 0;
    Count = 0;
    for x = 1:25
        for y = 1:N
            if OvertoneFreqs(y,x) > Bands(z) && OvertoneFreqs(y,x) < Bands(z+1)
                BandMult = BandMult + Multipliers(y,x);
                Count = Count+1;
            end
        end
    end
    BandMultAvgTot(z) = BandMult/Count;
end

index = strfind(isnan(BandMultAvgTot.'), true(1,5));
if isempty(index) == 0
    BandMultAvgTot(index) = 1;
end

BandMultAvgTot = fillmissing(BandMultAvgTot,'linear');

for i = 1:length(BandMultAvgTot)
    if BandMultAvgTot(i) < 0
        BandMultAvgTot(i) = 0;
    end
end

%{
index = strfind(isnan(BandMultAvgTot.'), true(1,3));
if isempty(index) == 0
    BandMultAvgTot(index+1) = (BandMultAvgTot(index-1)+BandMultAvgTot(index+3))/2;
end

for z = 1:(length(Bands)-1)
    if (isnan(BandMultAvgTot(z)) == 1) && (z == 1)
        BandMultAvgTot(1) = BandMultAvgTot(2);
    elseif (isnan(BandMultAvgTot(z)) == 1) && (z == (length(Bands)-1))
        BandMultAvgTot(length(Bands)-1) = BandMultAvgTot(length(Bands)-2);
    elseif (isnan(BandMultAvgTot(z)) == 1)
        BandMultAvgTot(z) = (BandMultAvgTot(z-1)+BandMultAvgTot(z+1))/2;
    end
end
%}

figure;
stairs(Bands(1:length(Bands)-1),BandMultAvgTot);
title('Average Multipliers: All Signals');



% Average multipliers from first and second band of training signals
BandMultAvg1and2 = zeros((length(Bands)-1),1);

for z = 1:(length(Bands)-1)
    BandMult = 0;
    Count = 0;
    for x = 1:12
        for y = 1:N
            if OvertoneFreqs(y,x) > Bands(z) && OvertoneFreqs(y,x) < Bands(z+1)
                BandMult = BandMult + Multipliers(y,x);
                Count = Count+1;
            end
        end
    end
    BandMultAvg1and2(z) = BandMult/Count;
end

index = strfind(isnan(BandMultAvg1and2.'), true(1,5));
if isempty(index) == 0
    BandMultAvg1and2(index) = 1;
end

BandMultAvg1and2 = fillmissing(BandMultAvg1and2,'linear');

for i = 1:length(BandMultAvg1and2)
    if BandMultAvg1and2(i) < 0
        BandMultAvg1and2(i) = 0;
    end
end


%{
index = strfind(isnan(BandMultAvgLow.'), true(1,3));
if isempty(index) == 0
    BandMultAvgLow(index+1) = (BandMultAvgLow(index-1)+BandMultAvgLow(index+3))/2;
end

for z = 1:(length(Bands)-1)
    if (isnan(BandMultAvgLow(z)) == 1) && (z == 1)
        BandMultAvgLow(1) = BandMultAvgLow(2);
    elseif (isnan(BandMultAvgLow(z)) == 1) && (z == (length(Bands)-1))
        BandMultAvgLow(length(Bands)-1) = BandMultAvgLow(length(Bands)-2);
    elseif (isnan(BandMultAvgLow(z)) == 1)
        BandMultAvgLow(z) = (BandMultAvgLow(z-1)+BandMultAvgLow(z+1))/2;
    end
end
%}

figure;
stairs(Bands(1:length(Bands)-1),BandMultAvg1and2);
title('Average Multipliers: First and Second Band');


% Average multipliers from third band of training signals
BandMultAvg3 = zeros((length(Bands)-1),1);

for z = 1:(length(Bands)-1)
    BandMult = 0;
    Count = 0;
    for x = 13:19
        for y = 1:N
            if OvertoneFreqs(y,x) > Bands(z) && OvertoneFreqs(y,x) < Bands(z+1)
                BandMult = BandMult + Multipliers(y,x);
                Count = Count+1;
            end
        end
    end
    BandMultAvg3(z) = BandMult/Count;
end

index = strfind(isnan(BandMultAvg3.'), true(1,5));
if isempty(index) == 0
    BandMultAvg3(index) = 1;
end

BandMultAvg3 = fillmissing(BandMultAvg3,'linear');

for i = 1:length(BandMultAvg3)
    if BandMultAvg3(i) < 0
        BandMultAvg3(i) = 0;
    end
end

figure;
stairs(Bands(1:length(Bands)-1),BandMultAvg3);
title('Average Multipliers: Third Band');


% Average multipliers from fourth band of training signals
BandMultAvg4 = zeros((length(Bands)-1),1);

for z = 1:(length(Bands)-1)
    BandMult = 0;
    Count = 0;
    for x = 20:25
        for y = 1:N
            if OvertoneFreqs(y,x) > Bands(z) && OvertoneFreqs(y,x) < Bands(z+1)
                BandMult = BandMult + Multipliers(y,x);
                Count = Count+1;
            end
        end
    end
    BandMultAvg4(z) = BandMult/Count;
end

index = strfind(isnan(BandMultAvg4.'), true(1,5));
if isempty(index) == 0
    BandMultAvg4(index) = 1;
end

BandMultAvg4 = fillmissing(BandMultAvg4,'linear');

for i = 1:length(BandMultAvg4)
    if BandMultAvg4(i) < 0
        BandMultAvg4(i) = 0;
    end
end



%{
index = strfind(isnan(BandMultAvgHigh.'), true(1,3));
if isempty(index) == 0
    BandMultAvgHigh(index+1) = (BandMultAvgHigh(index-1)+BandMultAvgHigh(index+3))/2;
end

for z = 1:(length(Bands)-1)
    if (isnan(BandMultAvgHigh(z)) == 1) && (z == 1)
        BandMultAvgHigh(1) = BandMultAvgHigh(2);
    elseif (isnan(BandMultAvgHigh(z)) == 1) && (z == (length(Bands)-1))
        BandMultAvgHigh(length(Bands)-1) = BandMultAvgHigh(length(Bands)-2);
    elseif (isnan(BandMultAvgHigh(z)) == 1)
        BandMultAvgHigh(z) = (BandMultAvgHigh(z-1)+BandMultAvgHigh(z+1))/2;
    end
end
%}

figure;
stairs(Bands(1:length(Bands)-1),BandMultAvg4);
title('Average Multipliers: Fourth Band');


outFile = fopen('altMultTot.txt', 'w');
fprintf(outFile, '%f\r\n', BandMultAvgTot(1:length(BandMultAvgTot)));
fclose(outFile);

outFile = fopen('altMult1and2.txt', 'w');
fprintf(outFile, '%f\r\n', BandMultAvg1and2(1:length(BandMultAvg1and2)));
fclose(outFile);

outFile = fopen('altMult3.txt', 'w');
fprintf(outFile, '%f\r\n', BandMultAvg3(1:length(BandMultAvg3)));
fclose(outFile);

outFile = fopen('altMult4.txt', 'w');
fprintf(outFile, '%f\r\n', BandMultAvg4(1:length(BandMultAvg4)));
fclose(outFile);