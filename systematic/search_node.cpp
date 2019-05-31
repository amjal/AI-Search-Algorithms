#include"headers/search_node.h"
search_node::search_node(search_node* parent, successor_state* scc){
	this->parent = parent;
	depth = parent->depth+1;
	path_cost = parent->path_cost + scc->cost;
	s = scc->next_state;
	action = scc->action;
}
search_node::search_node(state* initial_state){
	parent = NULL;
	depth = 0;
	path_cost = 0;
	s = initial_state;
	action = "";
}
