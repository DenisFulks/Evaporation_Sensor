%% Capstone
% Date: 03/27/2023
% Name: Hu Jiabin
% Description: 
%% Setup
clc;clear;close all
%% read txt
% read ultrasonic
fileID = fopen('ultrasonic.txt');
Cult = textscan(fileID,'%f %s %f');
fclose(fileID);

% read ultrasonicamplified
fileID = fopen('ultrasonicamplified.txt');
Camp = textscan(fileID,'%f ,Pot Data:%f');
fclose(fileID);
%% plot
% plot(Cult{1, 1}(217:289),Cult{1, 3}(217:289))
% hold on
% first_element=find(Camp{1, 1}>Cult{1, 1}(217),1);
% second_element=find(Camp{1, 1}>Cult{1, 1}(289),1)-1;
% plot(Camp{1, 1}(first_element:second_element),Camp{1, 2}(first_element:second_element))
plot(Cult{1, 1},Cult{1, 3})
hold on
plot(Camp{1, 1},Camp{1, 2})
legend('distance','amp')
%xlim([8000 12000])

%% process
figure
first_element=find(Cult{1, 1}>28159952,1);
second_element=find(Cult{1, 1}>28330176,1)-1;

% yyaxis right
% plot(Cult{1, 1}(first_element:second_element),Cult{1, 3}(first_element:second_element))
% ylabel('Distance(cm)')
% hold on

% yyaxis left
first_element=find(Camp{1, 1}>28159952,1);
second_element=find(Camp{1, 1}>28330176,1)-1;
plot(Camp{1, 1}(first_element:second_element),Camp{1, 2}(first_element:second_element)*5/1024)
grid on
xlabel('Time(us)')
ylabel('Voltage(mv)')
% legend('Deistance Measured by Sensor','Raw data')
interval = floor((second_element-first_element)/7);
x = [1 1];

for i = 1:7
    figure(i+2)
    plot(Camp{1, 1}(first_element:first_element+interval),Camp{1, 2}(first_element:first_element+interval))
    
    [c,lags] = xcorr(Camp{1, 2}(first_element:first_element+interval),x);
    loc = find(c==max(c));
    if length(loc) ~= 1
        locs(i)= mean(loc);
    else
        locs(i)=loc;
    end
    stem(lags,c)
    first_element = first_element+interval;
end
figure
plot(locs*700e-6)
grid on
title('Time of Flight of Each Cycle')
xlabel('cycle')
ylabel('TOF(us)')


figure
first_element=find(Cult{1, 1}>28159952,1);
second_element=find(Cult{1, 1}>28330176,1)-1;
plot(Cult{1, 1}(first_element:second_element),Cult{1, 3}(first_element:second_element))
hold on
plot(Cult{1, 1}(first_element:second_element), (locs)*700e-6 * 340/2 * 10)
grid on
legend('rough method','Cross-corrlation')