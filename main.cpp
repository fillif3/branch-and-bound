#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include <set>
#include <utility>

using namespace std;


#define TABSIZE 5


//void BranchAndBound(bool* content, float* cost, float* utility, float maxCost, unsigned int size);

/*
 *	MAIN
 */

struct Node {
    unsigned int	lev;
    float			weight;
    float			cost;
    vector<int>     inputs;
    Node (unsigned int l,float w,float c,vector<int> i){
        lev=l;
        weight=w;
        cost=c;
        inputs=move(i);
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

vector<float> bb(const vector<float>& cost_tab, const vector<float>& weight_tab, const float& max_weight, const vector<int>& possible_inputs);

int main() {


    vector<float> cost_tab = {-40.f, -50.f, -100.f, -95.f, -30.f};
    vector<float> weight_tab = {2.f, 3.14, 1.98, 5.f, 3.f};
    const float max_weight =10;
    vector<int> possible_inputs={0,1};

    auto  solution = bb(cost_tab,weight_tab,max_weight,possible_inputs);


    //cout << current_best->cost << endl;
    for (float cb : solution) cout << cb << endl;



    return 0;
}

vector<float> bb(const vector<float>& cost_tab, const vector<float>& weight_tab, const float& max_weight, const vector<int>& possible_inputs){
    // Prepare everything
    multiset<Node>::iterator iter;
    Node* current_best= nullptr; // The final node, currently empty
    bool if_find_first_solution_flag = false;
    Node parent(0,0,0, {});
    multiset<Node> unchecked_nodes={parent}; // List of nodes to check
    int max_level = cost_tab.size();

    while (!unchecked_nodes.empty()){
        Node current_node = (*unchecked_nodes.begin());
        //if ((if_find_first_solution_flag)&&current_best->cost>current_node.cost) break;
        for (int x : possible_inputs)
        {
            float weight = current_node.weight+x*weight_tab[current_node.lev];
            if (weight>max_weight) break;
            float cost = current_node.cost+x*cost_tab[current_node.lev];
            //if ((if_find_first_solution_flag)&&(current_best->cost<cost)) break;
            vector<int> new_vec = current_node.inputs;
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
    vector<float> solution;
    for(int & input : current_best->inputs) {
        solution.push_back(possible_inputs[input]);
    }
    return solution;
}
