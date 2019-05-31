#include<iostream>
#include"problem.h"
class search_node{
	public:
		state* s;
		search_node* parent;
		std::string action;// the last action that took us here
		int depth;
		int path_cost;
		search_node(search_node* parent, successor_state* scc);
		search_node(state* initial_state);
};
