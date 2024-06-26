clc; clear variables; close all;

d = 0.5;
time(1) = 0;
n = 10;

serialportlist("available")';
leader = serialport("COM6", 9600);
follower = serialport("COM4", 9600);

pause(5)

for i = 1:20
    leaderCal = str2double(readline(leader));
    followerCal = str2double(readline(follower));
end

tic
for i = 2:1001
    leaderTOF(i - 1) = str2double(readline(leader));
    followerTOF(i - 1) = str2double(readline(follower));
    velocity(i - 1) = (d / 2) * ((1 / (leaderTOF(i - 1) / 1000000)) - (1 / (followerTOF(i - 1) / 1000000)));

    time(i) = time(i - 1) + toc;
    tic
end

scatter(time(2:end), leaderTOF, ".")
title("leader")
figure

scatter(time(2:end), followerTOF, ".")
title("Follower")
figure

scatter(time(2:end), velocity, ".")
title("Velocity")
xlabel("Time (s)")
ylabel("Velocity (m/s)")



