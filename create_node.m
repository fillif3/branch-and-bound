function node = create_node(level,weight,cost,inputs)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
node = struct('level',level,'weight',weight,'cost',cost,'inputs',inputs);
end