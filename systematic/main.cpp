#include"headers/problem.h"
#include"headers/search_algorithm.h"
#include<string>
#include<fstream>
problem* p = new problem();
int id = 0;	
int process_command(std::string in){
	std::string args[5];
	int c=0;
	for(int i=0; i < in.length(); i++){
		if(in.at(i) == ' '){
			args[c++] = in.substr(0,i);
			in.erase(0,i+1);
			i = -1;
		}
	}
	args[c] = in;
	if(args[0] == "exit")
		return 0;
	if(args[0] == "state"){
		p->add_state(new state(args[1], id++));
		return 1;
	}	
	if(args[0] == "action"){
		state* src = p->get_state(args[1]);
		state* des = p->get_state(args[4]);
		if(src == NULL || des == NULL){
			std:: cout <<"state not found\n";
			return -1;
		}
		successor_state* scc = new successor_state(args[2], des, std::stoi(args[3]));
		p->add_successor(src, scc);
		return 1;
	}
	if(args[0] == "list" && args[1] == "states"){
		for(unsigned i =0; i < p->states.size(); i ++)
			std:: cout << p->states.at(i)->name<<"\n";
		return 1;
	}
	if(args[0] == "list" && args[1] == "successors"){
		std::vector<successor_state*> successors = p->get_successors(p->get_state(args[2]));
		for(unsigned i =0; i < successors.size(); i++){
			successor_state* scc = successors.at(i);
			std::cout << scc->action<<" "<<scc->cost<<" "<<scc->next_state->name<<"\n";
		}
		return 1;
	}
	if(args[0] == "initial"){
		p->set_initial(p->get_state(args[1]));
		return 1;
	}
	if(args[0] == "goal"){
		p->make_goal(p->get_state(args[1]));
		return 1;
	}
	if(args[0] == "bfs"){
		bfs engine(p);
		if(args[1] == "graph")
			engine.set_type(graph);
		engine.search();
		engine.print_path();
		if(engine.answer != NULL){
			std::cout<<"path length: "<<engine.answer->depth<<'\n';
			std::cout<<"path cost: "<<engine.answer->path_cost<<'\n';
			std::cout<<"expanded: "<<engine.expanded_num<<'\n';
			std::cout<<"visisted: "<<engine.visited_num<<'\n';
		}
		std::cout << "max nodes in memory: "<< engine.max_memory<<'\n';
		std::cout<<'\n';
		return 1;
	}
	if(args[0] == "uniform"){
		uniform_cost engine(p);
		if(args[1] == "graph")
			engine.set_type(graph);
		engine.search();
		engine.print_path();
		if(engine.answer != NULL){
			std::cout<<"path length: "<<engine.answer->depth<<'\n';
			std::cout<<"path cost: "<<engine.answer->path_cost<<'\n';
			std::cout<<"expanded: "<<engine.expanded_num<<'\n';
			std::cout<<"visisted: "<<engine.visited_num<<'\n';
		}
		std::cout << "max nodes in memory: "<< engine.max_memory<<'\n';
		std::cout<<'\n';
		return 1;
	}
	if(args[0] == "best-first"){
		greedy_best_first engine(p);
		if(args[1] == "graph")
			engine.set_type(graph);
		engine.search();
		engine.print_path();
		if(engine.answer != NULL){
			std::cout<<"path length: "<<engine.answer->depth<<'\n';
			std::cout<<"path cost: "<<engine.answer->path_cost<<'\n';
			std::cout<<"expanded: "<<engine.expanded_num<<'\n';
			std::cout<<"visisted: "<<engine.visited_num<<'\n';
		}
		std::cout << "max nodes in memory: "<< engine.max_memory<<'\n';
		std::cout<<'\n';
		return 1;
	}
	if(args[0] == "A*"){
		A_star engine(p);
		if(args[1] == "graph")
			engine.set_type(graph);
		engine.search();
		engine.print_path();
		if(engine.answer != NULL){
			std::cout<<"path length: "<<engine.answer->depth<<'\n';
			std::cout<<"path cost: "<<engine.answer->path_cost<<'\n';
			std::cout<<"expanded: "<<engine.expanded_num<<'\n';
			std::cout<<"visisted: "<<engine.visited_num<<'\n';
		}
		std::cout << "max nodes in memory: "<< engine.max_memory<<'\n';
		std::cout<<'\n';
		return 1;
	}
	if(args[0] == "dfs"){
		dfs engine(p);
		if(args[1] == "graph")
			engine.set_type(graph);
		if(args[2] == "deepening")
			engine.iterative_deepening_search();
		else if(args[2] == "limited")
			engine.depth_limited_search(std::stoi(args[3]));
		else if(args[2] == "normal")
			engine.search();
		engine.print_path();
		if(engine.answer != NULL){
			std::cout<<"path length: "<<engine.answer->depth<<'\n';
			std::cout<<"path cost: "<<engine.answer->path_cost<<'\n';
			std::cout<<"expanded: "<<engine.expanded_num<<'\n';
			std::cout<<"visisted(backtracking algorithm): "<<engine.visited_num<<'\n';
		}
		std::cout << "max nodes in memory(backtracking algorithm): "<< engine.max_memory<<'\n';
		std::cout <<'\n';
		return 1;
	}
	std::cout <<"invalid command\n";
	return -1;
}
void get_commands(){
	std::string in;
	int process_code;
	do{
		getline(std::cin, in);
		process_code = process_command(in);
	}while(process_code);
}
void read_file(){//reads problem specification from a file and returns a problem
	std::ifstream ifs("peripherals/input");
	std::string in;
	getline(ifs,in);//The first line is read so that I won't need to use 
					//break; statement in the while loop
	while(!ifs.eof()){
		process_command(in);
		getline(ifs, in);
	}	
	ifs.close();
}
int main(){
	read_file();
	p->read_heuristics();
	get_commands();
	return 0;
}
