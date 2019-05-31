#include "headers/problem.h"
#include<fstream>

void problem:: add_state(state* s){
	states.push_back(s);
	std::vector<successor_state*> successors;
	state_relations.push_back(successors);
}
void problem::add_successor(state* src, successor_state* scc){
	state_relations.at(src->ID).push_back(scc);
}
void problem:: set_initial(state* s){
	initial_state = s;
}
void problem:: read_heuristics(){
	heuristics.resize(states.size());
	std::ifstream ifs("peripherals/heuristics");
	std::string in;
	getline(ifs,in);
	while(!ifs.eof()){
		int space_index = in.find(" ");
		std::string state_name = in.substr(0,space_index);
		int heuristic = std::stoi(in.substr(space_index, in.length() - space_index));
		heuristics.at(get_state(state_name)->ID) = heuristic;
		getline(ifs,in);
	}
	ifs.close();
}
state* problem::get_state(std::string name){
	for(unsigned i =0; i<states.size(); i++)
		if(states.at(i)->name == name)
			return states.at(i);
	return NULL;
}

