#include<iostream>
#include<deque>
#include<iterator>
#include"problem.h"
#include"search_node.h"
enum search_type { graph, tree};
class search_algorithm{
	public:
		search_type type;
		std::deque<search_node*> fringe;
		std::deque<state*> closed_list;
		search_node* answer;// answer is the final state in the result path
		search_node* expanded;
		problem* p;
		int expanded_num;
		int visited_num;
		int max_memory;
		inline search_algorithm(problem *p):p(p),answer(NULL), type(tree),expanded_num(0), visited_num(0), max_memory(0){}
		void expand(search_node* node);
		void search_init();
		void print_path();
		void print_path(search_node* node);
		void clear_lists();
		bool is_in_closed_list(state* s);
		inline void set_type(search_type t){
			type = t;
		}
};

class bfs: public search_algorithm{
	public:
		inline bfs(problem *p):search_algorithm(p){}
		search_node* choose_expanded();
		void search();
};

class uniform_cost: public search_algorithm{
	public:
		inline uniform_cost(problem *p):search_algorithm(p){}
		search_node* choose_expanded();
		void search();
};

class dfs: public search_algorithm{
	public:
		int depth_limit;
		inline dfs(problem* p):search_algorithm(p){}
		void search();
		bool search(search_node* node,int next_sibling_index);
		void depth_limited_search(int d_limit);
		void iterative_deepening_search();
};

class greedy_best_first: public search_algorithm{
	public:
		inline greedy_best_first(problem* p):search_algorithm(p){}
		search_node* choose_expanded();
		void search();
};

class A_star: public search_algorithm{
	public:
		inline A_star(problem* p): search_algorithm(p){}
		search_node* choose_expanded();
		void search();
};
