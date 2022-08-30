%function input_vector = BB_NMPC(current_state,system_function,stage_cost,...
%    terminal_cost,nonlinear_constraint,possible_inputs,horizon)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

function [final_input_vector,final_cost] = BB_NMPC(cost_vec,weight_vec,max_w,possible_u)
current_best_node=create_node(0,0,inf,[]);
number_of_uncheck_nodes=1;
horizon = length(cost_vec);
unchecked_nodes=  arrayfun(@(x)create_node(0,0,0,zeros(horizon,1)),1:1000);

while number_of_uncheck_nodes~=0
    current_node = unchecked_nodes(1);
    for i=possible_u
        weight = current_node.weight+i*weight_vec(current_node.level+1);
        if weight>max_w 
            continue; 
        end
        cost = current_node.cost+i*cost_vec(current_node.level+1);
        %if current_best_node.cost<cost
        %    continue;
        %end
        new_inputs=current_node.inputs;
        new_inputs(current_node.level+1) = i;
        new_node = create_node(current_node.level+1,weight,cost,new_inputs);
        if new_node.level == horizon
            if current_best_node.cost > new_node.cost
                current_best_node = new_node;
            end
        else
            number_of_uncheck_nodes=number_of_uncheck_nodes+1;
            unchecked_nodes(number_of_uncheck_nodes)=new_node;
        end
    end
    unchecked_nodes(1).cost=inf;
    [~,idx]=sort([unchecked_nodes(1:number_of_uncheck_nodes).cost]);
    unchecked_nodes(1:number_of_uncheck_nodes)=unchecked_nodes(idx);
    number_of_uncheck_nodes=number_of_uncheck_nodes-1;
    

end
final_input_vector=current_best_node.inputs;
final_cost = current_best_node.cost;

end