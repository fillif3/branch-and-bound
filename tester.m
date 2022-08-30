costs=[-40,-50,-100,-95,-30];
weights =[2,3.14,1.98,5,3];
max_w = 10;
possible_u = [0,1];
p=Polyhedron([1,2]);
new_helper = @(x)helper();
tic
%for i=1:100
%[x,fval,test] = simple_BB(costs,weights,max_w,possible_u,new_helper);
%end
toc

[x,fval] = BB_NMPC(costs,weights,max_w,possible_u);