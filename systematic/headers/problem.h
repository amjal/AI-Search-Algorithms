#ifndef __problem_h__
#define __problem_h__
#include<iostream>
#include<vector>
class state{
	public:
		std::string name;
		int ID;
		bool is_goal = false;
		inline state(std::string name, int ID):name(name), ID(ID){}
};
class successor_state{
	public:
		std::string action;
		state* next_state;
		int cost;
		inline successor_state(std::string action, state* next_state,int cost):action(action),next_state(next_state),cost(cost){}
};
class problem{
	public:
		std::vector<std::vector<successor_state*>> state_relations;
		std::vector<state*> states;
		std::vector<int> heuristics;
		state* initial_state;
		void add_successor(state* src, successor_state* scc); 
		void set_initial(state* s);
		void add_state(state* s);
		void read_heuristics();
		inline void make_goal(state* s){s->is_goal = true;}
		state* get_state(std::string name);
		inline std::vector<successor_state*> get_successors(state* s){
			return state_relations.at(s->ID);
		}
};
#endif
