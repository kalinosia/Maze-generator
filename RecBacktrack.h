#pragma once
#include <vector>
#include <stack>
#include <time.h>
#include <stdlib.h> 

constexpr auto width = 40;
constexpr auto  height = 25;



class RecBacktrack
{
	private:
		//const int width;
		//const int height;
		int h; //???? to random variable some time....
		int entry;
		int exit;
		int posy;
		int posx;
		//to check every way to go (up right down left =4)
		std::vector<int> ifcross;
		//stack of sqares where we been and it have more than one way to go
		std::stack <std::pair<int, int>> maze_stack;
		bool visited[height][width];
		int posWalls(int pos);
		bool make_maze_end = false;


	public:
		RecBacktrack();
		~RecBacktrack();
		void make_maze();
		///CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS 
		int get_posx();
		int get_posy();
		///CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS 

		bool maze_walls[2 * height + 1][2 * width + 1];

		bool maze_end() {
			if (make_maze_end) return true;
			else return false;
		};
		
};

