clc
clear variables
close all

leaderMat = xlsread("Leader.xlsx");
followerMat = xlsread("Follower.xlsx");

npoints = 200;
distance = 0.2;

%% Unsmoothed Data
for i = 1:length(leaderMat) - 3
    time(i) = leaderMat(i, 1);
    cycle(i) = i;
    if leaderMat(i, 3) == 0
        velocityInternal(i) = 0;
        velocityExternal(i) = 0;

        continue;
    end

    velocityInternal(i) = (distance / 2) * ((1 / (leaderMat(i, 3) / 1000000)) - (1 / (leaderMat(i, 2) / 1000000)));
    velocityExternal(i) = (distance / 2) * ((1 / (followerMat(i, 2) / 1000000)) - (1 / (leaderMat(i, 2) / 1000000)));
end

plot(time, velocityInternal, "b", time, velocityExternal, "r")

%% Smoothed Data For Internal Velocity
for i = npoints:length(leaderMat) - npoints
    velocityInternalSmoothed(i) = velocityInternal(i);
    timeSmoothed(i) = leaderMat(i, 1);
end

% Uses moving average to calculate the smoothed data
for i = 1 + npoints:length(velocityInternal) - npoints
    lsum = 0;
    rsum = 0;

    % Calculates the average of the previous 4 entries
    for j = 1:npoints
        lsum = lsum + velocityInternal(i - j);
    end
    lavg = lsum / npoints;

    % Calculates the average of the next 4 entries
    for k = 1 : npoints
        rsum = rsum + velocityInternal(i + k);
    end
    ravg = rsum / npoints;

    % Calculates the total average and replaces the data with the smoothed
    % data
    avg = (ravg + lavg + velocityInternal(i)) / 3; 
    velocityInternalSmoothed(i) = avg;      
end

figure;
plot(timeSmoothed, velocityInternalSmoothed);

%% Smoothed Data For External Velocity
for i = npoints:length(leaderMat) - npoints
    velocityExternalSmoothed(i) = velocityExternal(i);
end

% Uses moving average to calculate the smoothed data
for i = 1 + npoints:length(velocityExternal) - npoints
    lsum = 0;
    rsum = 0;

    % Calculates the average of the previous 4 entries
    for j = 1:npoints
        lsum = lsum + velocityExternal(i - j);
    end
    lavg = lsum / npoints;

    % Calculates the average of the next 4 entries
    for k = 1:npoints
        rsum = rsum + velocityExternal(i + k);
    end
    ravg = rsum / npoints;

    % Calculates the total average and replaces the data with the smoothed
    % data
    avg = (ravg + lavg + velocityExternal(i)) / 3; 
    velocityExternalSmoothed(i) = avg;      
end

figure;
plot(timeSmoothed, velocityExternalSmoothed);




