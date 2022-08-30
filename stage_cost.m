function cost = stage_cost(u,x,more_arguments)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
Q=more_arguments{1};
R = more_arguments{2};
cost = u'*R*u+x'*Q*x;
end