#include"headers/search_algorithm.h"

search_node* bfs:: choose_expanded(){
	search_node* chosen  = fringe.back();
	fringe.pop_back();
	return chosen;
}
void bfs::search(){
	search_algorithm::search_init();
	while(fringe.size()){
		expanded = choose_expanded();
		if(expanded->s->is_goal){
			answer = expanded;
			return;
		}
		expand(expanded);
	}
}
search_node* uniform_cost:: choose_expanded(){
	search_node* chosen = fringe.front();
	int chosen_index = 0;
	for(unsigned i = 0; i < fringe.size(); i++)
		if(fringe.at(i)->path_cost < chosen->path_cost){
			chosen = fringe.at(i);
			chosen_index = i;
		}
	fringe.erase(fringe.begin()+chosen_index);
	return chosen;
}
void uniform_cost::search(){
	search_algorithm::search_init();
	while(fringe.size()){
		expanded = choose_expanded();
		if(expanded->s->is_goal){
			answer = expanded;
			return;
		}
		expand(expanded);
	}
}
search_node* greedy_best_first:: choose_expanded(){
	search_node* chosen = fringe.front();
	int chosen_index = 0;
	for(unsigned i = 0; i < fringe.size(); i++)
		if(p->heuristics.at(fringe.at(i)->s->ID) < p->heuristics.at(chosen->s->ID)){
			chosen = fringe.at(i);
			chosen_index = i;
		}
	fringe.erase(fringe.begin()+chosen_index);
	return chosen;
}
void greedy_best_first:: search(){
	search_algorithm::search_init();
	while(fringe.size()){
		expanded = choose_expanded();
		if(expanded->s->is_goal){
			answer = expanded;
			return;
		}
		expand(expanded);
	}
}
search_node* A_star:: choose_expanded(){
	search_node* chosen = fringe.front();
	int chosen_index = 0;
	for(unsigned i = 0; i < fringe.size(); i++)
		if(p->heuristics.at(fringe.at(i)->s->ID) + fringe.at(i)->path_cost < p->heuristics.at(chosen->s->ID) + chosen->path_cost){
			chosen = fringe.at(i);
			chosen_index = i;
		}
	fringe.erase(fringe.begin()+chosen_index);
	return chosen;
}

void A_star::search(){
	search_algorithm::search_init();
	while(fringe.size()){
		expanded = choose_expanded();
		if(expanded->s->is_goal){
			answer = expanded;
			return;
		}
		expand(expanded);
	}
}
bool dfs::search(search_node* node,int next_sibling_index){
	if(node->depth > max_memory)
		max_memory = node->depth;
	if(node->s->is_goal){//first do the goal test obviously
		answer = node;
		return true;
	}
	/* now that we are not in the goal state we gotta continue searching and 
	 * get deeper so we'll get all the adjacents + actions leading to 
	 * them(meaning successors vector) of the current search_node's 
	 * correspoding state(which are current search_node's chilren in the search
	 * tree)
	 */
	std::vector<successor_state*> successors = p->get_successors(node->s);
	/*now if the current search_node has children, we'll do the search for the 
	 * first child and tell it where its next sibling is located in the successor
	 * list because search_nodes don't know where they belong in that list
	 * and also when a node is at depth limit it won't call search for its
	 * children but will call search for its siblings */
	if(type == tree || !is_in_closed_list(node->s)){// the real expansion is done here
		expanded_num++;
		visited_num++;
		/*only do the search for children if the state is not in closed list
		 * for states that are in closed lists we don't expand them and jump to 
		 * the next thing(siblings)*/
		if(type == graph) closed_list.push_back(node->s);
		if(successors.size() != 0 && node->depth != depth_limit){
			search_node* first_child = new search_node(node,successors.at(0));
			if(search(first_child,1))
				return true;
		}
	}
	/*so all the children did the search and nothing was found, now the current
	 * search_node has to call the search upon its next sibling, the root of 
	 * the tree has no siblings so this is done for the rest of the nodes only*/
	if(node->parent != NULL){//check if the search_node is not the root
		std::vector<successor_state*> siblings = p->get_successors(node->parent->s);
		if(next_sibling_index < siblings.size())
			return search(new search_node(node->parent,siblings.at(next_sibling_index)), next_sibling_index+1);
	}
	if(type == graph){
	/*when we retreat from a path and turn to a new one, the descendants 
	 * in the path delete themselves from the closed list so they can be reached 
	 */
		for(unsigned i =0; i < closed_list.size() ; i++){
			if(closed_list.at(i) == node->s)
				closed_list.erase(closed_list.begin()+i);
		}
	}
	return false;
}
void dfs::search(){
	search_node* initial_node = new search_node(p->initial_state);
	depth_limit = -1;
	dfs::search(initial_node,1);//depth_limit = -1 means search with no limit
}
void dfs::iterative_deepening_search(){
	search_node* initial_node = new search_node(p->initial_state);
	depth_limit = 0;
	while(!search(initial_node,1)){
		clear_lists();
		depth_limit++;
	}
	//increments depth_limit and 
	//searches until something is found and search returns true
}
void dfs::depth_limited_search(int d_limit){
	search_node* initial_node = new search_node(p->initial_state);
	depth_limit = d_limit;
	search(initial_node,1);
}

void search_algorithm::expand(search_node* node){
	state* s = node->s;
	if(type == tree || !is_in_closed_list(s)){
		expanded_num ++;
		if(type == graph)
			closed_list.push_back(s);
		std::vector<successor_state*> successors = p->get_successors(s);
		visited_num += successors.size();
		for(unsigned i=0; i < successors.size(); i ++){
			search_node* new_node = new search_node(node ,successors.at(i)); 
			fringe.push_back(new_node);
		}
		if(fringe.size() > max_memory)
			max_memory = fringe.size();
	}
}
void search_algorithm::search_init(){
	answer = NULL;
	clear_lists();
	search_node* initial_node = new search_node(p->initial_state);
	fringe.push_back(initial_node);
}

void search_algorithm::print_path(){
	if(answer == NULL)
		std::cout <<"no path found";
	else print_path(answer);
	std::cout <<'\n';
}

void search_algorithm::print_path(search_node* node){
	if(node->parent == NULL)
		std::cout<< node->s->name;
	else {
		print_path(node->parent);
		std::cout <<','<< node->s->name;
	}
}
bool search_algorithm::is_in_closed_list(state* s){
	for(unsigned i=0; i < closed_list.size(); i++)
		if(closed_list.at(i) == s)
			return true;
	return false;
}

void search_algorithm::clear_lists()
{
   std::deque<search_node*> empty1;
   std::swap( fringe, empty1);
   std::deque<state*> empty2;
   std::swap( closed_list, empty2);
}
