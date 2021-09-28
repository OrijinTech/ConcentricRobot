function [T] = arckinematics(c)
%ARCKINEMATICS Accepts a vector of k, s, theta and returns the corresponding
%homogenous transformation matrix T and (optionally) the arc link as a
%sequence of points

k   = c(1);
s   = c(2);
theta = c(3);

%Isn't this z rotation?
xRot = [0 -1 0 0;
        1 0 0 0;
        0 0 0 0;
        0 0 0 0];

%Unclear, isn't this z Inp?
xInp = @(k) [0 0 k 0;
             0 0 0 0;
            -k 0 0 1;
             0 0 0 0];

%This is the homogeneous transformation calculation
T = expm(xRot * theta) * expm(xInp(k) * s);
end