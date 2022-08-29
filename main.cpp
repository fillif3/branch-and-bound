#include <iostream>
#include <limits>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <set>
#include <utility>

using namespace std;


#define TABSIZE 5


//void BranchAndBound(bool* content, float* cost, float* utility, float maxCost, unsigned int size);

/*
 *	MAIN
 */

class Node {       // The class
public:             // Access specifier
    unsigned int	lev;
    float			weight;
    float			cost;
    vector<int>     inputs;
    Node (unsigned int l,float w,float c,vector<int> i){
        lev=l;
        weight=w;
        cost=c;
        inputs=std::move(i);
    }
    bool operator <(const Node &n) const{
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


int main() {


    float cost_tab[TABSIZE] = {-40.f, -50.f, -100.f, -95.f, -30.f};
    float weight_tab[TABSIZE] = {2.f, 3.14, 1.98, 5.f, 3.f};
    const float max_weight =10;
    int possible_inputs[2]={0,1};
    const int max_level =5;
    multiset<Node>::iterator iter;

    Node* current_best= nullptr;
    bool if_find_first_solution_flag = false;


    Node parent(0,0,0, {});
    multiset<Node> unchecked_nodes={parent};

    int iterations = 0;

    while (!unchecked_nodes.empty()){
        iterations++;
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

    cout << current_best->cost << endl;
    for (int cb : current_best->inputs) cout << cb << endl;



    return 0;
}
	/*for(int i = 0; i < TABSIZE; i++){
		std::cout << content[i] << endl;
	}std::cout << '\n';

	float fcost = 0.f;
	for(int i = 0; i < TABSIZE; i++){
		fcost += content[i] * cost[i];
	}std::cout << "Cost = " << fcost << endl;/*


}

/*
 *	ALGOS
 */

/*struct uc{
	float ucRatio;
	unsigned int index;
};*/

/*int cmp(const void* elm1, const void* elm2){
	int a = ((uc*)elm1)->ucRatio;
	int b = ((uc*)elm2)->ucRatio;
	return a > b ? -1 : a < b;
}*/

/*
 *	BRANCH & BOUND
 */



/*float calculateBound(bbNode nd, float* cost, float* utility, uc* ucTab, float maxCost, unsigned int size){
	float addCost = 0.f;
	float addBenef = 0.f;

	for(int i = nd.lev; i < size; i++){
		if(nd.cost + addCost + cost[ucTab[i].index] > maxCost){
			//	Partial add of the best c/u object
			float partialBenefit = ((maxCost - addCost) / cost[ucTab[i].index]) * utility[ucTab[i].index];
			return nd.benef + addBenef + partialBenefit;
		}
		addCost += cost[ucTab[i].index];
		addBenef += utility[ucTab[i].index];
	}
	return nd.cost + addCost;
}

float calculateBenefit(bbNode nd, float* utility, unsigned int size){
	float res = 0.f;
	for(int i = 0; i < size; i++)
		if(nd.set[i])
			res+=utility[i];
	return res;
}

void cpyNode(bbNode* dest, bbNode src, unsigned int size){
	*dest = src;
	dest->set = (bool*)malloc(size * sizeof(bool));
	memcpy(dest->set, src.set, size * sizeof(bool));
}

void setNextObject(bbNode* nd, bool val, float* cost, uc* ucTab){
	nd->set[ucTab[nd->lev].index] = val;
	nd->cost += val * cost[ucTab[nd->lev].index];
	nd->lev++;
}*/