clc; clear variables;

d = 0.3;

serialportlist("available")';
leader = serialport("COM6", 9600);
follower = serialport("COM4", 9600);

pause(5)

for i = 1:5
    leaderCal = str2double(readline(leader));
    followerCal = str2double(readline(follower));
end

for i = 1:300
    leaderTOF(i) = str2double(readline(leader));
    followerTOF(i) = str2double(readline(follower));
    velocity(i) = (d / 2) * ((1 / leaderTOF(i)) - (1 / followerTOF(i)));
end

plot(leaderTOF)
title("leader")
figure

plot(followerTOF)
title("Follower")
figure

plot(velocity)
title("Velocity")





