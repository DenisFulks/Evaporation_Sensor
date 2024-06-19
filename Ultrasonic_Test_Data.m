clc
clear variables
close all

velocityData = csvread("Logs\Leader\Leader10010612.log");
atmoData = csvread("Logs\BME\BME020610.log");

npoints = 50;

for i = 1:4500
    time(i) = velocityData(i, 2);
    velocity(i) = velocityData(i, 6);
    mixingRatio(i) = atmoData(i, 5);
    density(i) = atmoData(i, 6);

    if velocity(i) == inf
        velocity(i) = 0;
    end
end

avg = mean(velocity);

plot(time, velocity)
title("Unsmoothed Plot of Velocity")
ylabel("Velocity (m/s)")

figure
plot(time, mixingRatio)
title("Unsmoothed Mixing Ratio Plot")
ylabel("Mixing Ratio (g/kg)")

figure
plot(time, density);
title("Unsmoothed Density Plot")
ylabel("Density (kg/m^3)")

index = 1;
for i = 1:npoints:floor(length(velocity / npoints)) - npoints
    smoothVeloSum = 0;
    smoothMRSum = 0;
    smoothDenSum = 0;
    for j = 1:npoints
        smoothVeloSum = smoothVeloSum + velocity(i + j);
        smoothMRSum = smoothMRSum + mixingRatio(i + j);
        smoothDenSum = smoothDenSum + density(i + j);
    end
    smoothVeloAvg(index) = smoothVeloSum / npoints;
    smoothMRAvg(index) = smoothMRSum / npoints;
    smoothDenAvg(index) = smoothDenSum / npoints;

    counter(index) = index;
    index = index + 1;
end

figure
plot(counter, smoothVeloAvg);
title("Smoothed Plot of Velocity")
ylabel("Velocity (m/s)")

figure
plot(counter, smoothMRAvg);
title("Smoothed Mixing Ratio Plot")
ylabel("Mixing Ratio (g/kg)")

figure
plot(counter, smoothDenAvg);
title("Smoothed Density Plot")
ylabel("Density (kg/m^3)")

temp = cov(smoothVeloAvg, smoothMRAvg);
for i = 1:length(smoothVeloAvg)
    flux(i) = smoothDenAvg(i) * temp(1, 2);
end

figure
plot(counter, flux);
title("Plot of Flux")
ylabel("Flux (g/m^2s)")




