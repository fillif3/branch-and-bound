/* C++ MEX file for MATLAB
*  [x,fval] = simple_BB(cost_vec,weight_vec,max_weight,possible_inputs));
*/

#include "mex.hpp"
#include "mexAdapter.hpp"
#include <iostream>
#include <queue>
#include <set>
#include <utility>

using matlab::mex::ArgumentList;
using namespace matlab::data;

struct Node {
    unsigned int	lev;
    float			weight;
    float			cost;
    std::vector<int>     inputs;
    Node (unsigned int l,float w,float c,std::vector<int> i){
        lev=l;
        weight=w;
        cost=c;
        inputs=std::move(i);
        //state= move(s);
    }
    bool operator <(const Node &n) const{
        // We compare the cost. If costs are equal we need to find another way because otherwise both would be deleted from mutliset.
        if (cost==n.cost){
            if (inputs.size()==n.inputs.size()){
                for(auto it1 = inputs.begin(), it2 = n.inputs.begin();
                    it1!=inputs.end() && it2!=n.inputs.end();
                    ++it1, ++it2) {
                    if (*it1 != *it2) return *it1<*it2;
                }
            }
            return inputs.size()>n.inputs.size();
        }
        return cost<n.cost;
    }
};



class MexFunction : public matlab::mex::Function {

matlab::data::ArrayFactory factory;

    public:
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
        matlab::data::TypedArray<double> cost_vec = std::move(inputs[0]);
        matlab::data::TypedArray<double> weight_vec = std::move(inputs[1]);
        matlab::data::TypedArray<double> max_weight = std::move(inputs[2]);
        matlab::data::TypedArray<double> possible_inputs = std::move(inputs[3]);

        std::multiset<Node>::iterator iter;
        Node* current_best= nullptr; // The final node, currently empty
        bool if_find_first_solution_flag = false;
        Node parent(0,0,0, {});
        std::multiset<Node> unchecked_nodes={parent}; // List of nodes to check
        ArrayDimensions dim = cost_vec.getDimensions();
        int max_level = std::max(dim[0],dim[1]);
    
        while (!unchecked_nodes.empty()){
            Node current_node = (*unchecked_nodes.begin());
            //if ((if_find_first_solution_flag)&&current_best->cost>current_node.cost) break;
            for (auto& x : possible_inputs){
                double weight = current_node.weight+x*weight_vec[current_node.lev];
                if (weight>max_weight[0]) continue;
                double cost = current_node.cost+x*cost_vec[current_node.lev];
                if ((if_find_first_solution_flag)&&(current_best->cost<cost)) continue;
                std::vector<int> new_vec = current_node.inputs;
                new_vec.push_back(x);
                Node *new_node = new Node(current_node.lev+1,weight,cost,new_vec);
                if (new_node->lev==max_level){
                    if (if_find_first_solution_flag){
                        if (current_best->cost>new_node->cost) current_best=new_node;
                    }else{
                        if_find_first_solution_flag= true;
                        current_best=new_node;
                    }
                } else{
                    unchecked_nodes.insert(*new_node);
                }
    
    
            }
            unchecked_nodes.erase(current_node);
            //delete current_node;
        }
        matlab::data::TypedArray<double> solution=factory.createArray<double>({ 1, max_level });
        int i=0;
        for(int & input : current_best->inputs) {
            solution[0][i]=input;
            i++;
        }
        outputs[0] = std::move(solution);
        matlab::data::TypedArray<double> final_cost=factory.createArray<double>({ 1,1 });
        final_cost[0][0]=current_best->cost;
        outputs[1]=final_cost;
        matlab::data::Array args({
        factory.createArray<double>({ 2, 4 },{ 1, 2, 3, 4,5,6,7,8 }) });
        //outputs[2] = matlabPtr->feval(inputs[4],args);
        for (int i =0;i<1000;i++)
        outputs[2] =matlabPtr->feval(u"Polyhedron",args);
        //outputs[2]=args;
        //outputs[2] = inputs[4]();

    }
};