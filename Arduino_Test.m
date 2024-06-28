clc; clear variables; close all;

cycles = 3000;
distance = 0.4;
time(1) = 0;
total = 0;
n = 10;
errorCycles = 400;
startCycles = 30;
smoothSize = 15;


serialportlist("available")';
leader = serialport("COM6", 9600);
follower = serialport("COM4", 9600);

pause(5)

for i = 1:startCycles
    leaderStart = str2double(readline(leader));
    followerStart = str2double(readline(follower));
end

for i = 1:errorCycles
    leaderTOFCal(i) = str2double(readline(leader));
    followerTOFCal(i) = str2double(readline(follower));

    total = total + (leaderTOFCal(i) - followerTOFCal(i));
end
avgError = total / errorCycles;

fprintf("Calibration Complete... ")

pause(10)

fprintf("Starting")

tic
for i = 2:cycles + 1
    leaderTOF(i - 1) = str2double(readline(leader));
    followerTOF(i - 1) = str2double(readline(follower));

    time(i) = time(i - 1) + toc;
    tic
end

scatter(time(2:end), leaderTOF, ".")
title("leader")
figure

scatter(time(2:end), followerTOF, ".")
title("Follower")
figure

for i = 1:length(leaderTOF)
    velocity(i) = (distance / 2) * ((1 / (leaderTOF(i) / 1000000)) - (1 / (followerTOF(i) / 1000000)));
    velocityCal(i) = (distance / 2) * ((1 / ((leaderTOF(i) - avgError) / 1000000)) - (1 / (followerTOF(i) / 1000000)));
end

scatter(time(2:end), velocity, ".")
title("Velocity")
xlabel("Time (s)")
ylabel("Velocity (m/s)")
figure

scatter(time(2:end), velocityCal, ".")
title("Velocity Calibrated")
xlabel("Time (s)")
ylabel("Velocity (m/s)")
figure

counter = 1;
for i = 1:smoothSize:length(velocity) - smoothSize
    velocitySmoothed(counter) = sum(velocity(i:i+smoothSize)) / smoothSize;
    velocityCalSmoothed(counter) = sum(velocityCal(i:i+smoothSize)) / smoothSize;
    timeSmoothed(counter) = sum(time(i+1:i+smoothSize+1)) / smoothSize;

    counter = counter + 1;
end

scatter(timeSmoothed(1:end), velocitySmoothed, ".")
title("Velocity Smoothed")
xlabel("Time (s)")
ylabel("Velocity (m/s)")
figure

scatter(timeSmoothed(1:end), velocityCalSmoothed, ".")
title("Velocity Calibrated Smoothed")
xlabel("Time (s)")
ylabel("Velocity (m/s)")


