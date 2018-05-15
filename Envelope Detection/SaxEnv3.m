[y, Fs] = audioread('SaxSample1.wav');

dt = 1/Fs;
N = length(y);

t = 0:dt:dt*N-dt;

%rectify
y = abs(y);

x = y;

%peaking filter
win = 250;
i = 1;
while(i+win < N)
   y(i:i+win) = max(y(i:i+win));
   i = i+win+1; 
end

%LPF
LP_IIR = dsp.LowpassFilter('SampleRate',Fs,'FilterType','IIR',...
    'DesignForMinimumOrder',false,'FilterOrder',20,...
    'PassbandFrequency',60,'PassbandRipple',0.01,'StopbandAttenuation',60);
measure(LP_IIR);
%x = y;
y = LP_IIR(y);

figure(1);
plot(t,x); hold on;
plot(t,y,'LineWidth',1.5);