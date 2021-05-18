#include "RecBacktrack.h"
#include <iostream>



RecBacktrack::RecBacktrack(){
    make_maze_end = false;//define

	//start position
    entry = rand() % width;
    posy = 0;
    posx = entry;
	
	//visited every not
    memset(visited, false, sizeof(visited));
	//matrix of walls(1) and empty squres(0), later connected squares, wall=0
	for (int i = 0; i < 2 * width + 1; i++) {
		for (int j = 0; j < 2 * height + 1; j++) {
			if (i == 0 or j == 0 or i == 2 * width or j == 2 * height) maze_walls[j][i] = 1;//side walls
			else if (i % 2 == 0) maze_walls[j][i] = 1;
			else if (i % 2 == 1) {
				if (j % 2 == 0) maze_walls[j][i] = 1;
				else if (j % 2 == 1) maze_walls[j][i] = 0;
			}
			else maze_walls[j][i] = 1;
		}
	}
    
	//change first square
    maze_walls[posWalls(posy) - 1][posWalls(posx)] = 0; //-1 because in side wall entry is
    visited[posy][posx] = 1;

	//0 up, 1 right, 2 down, 3 left; look for every sqares/area
	ifcross.reserve(4); //capacity =4
	ifcross.clear();

	//stack of sqares where we been and it have more than one way to go
	//std::stack <std::pair<int, int>> maze_stack;
}
/// //////////////////////////////////////////////////////////////////////////////////////////end 
RecBacktrack::~RecBacktrack() {
	exit = rand() % width;
	if (maze_walls[2 * height - 1][posWalls(h)] == 0) {
		maze_walls[2 * height][posWalls(h)] = 0;
	}
	//and save maze matrix ???
}
int RecBacktrack::posWalls(int pos) {
    return 2 * pos + 1;
}
///CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS 
int RecBacktrack::get_posx() {
    return posWalls(posx);
}
int RecBacktrack::get_posy() {
    return posWalls(posy);
}
// ///CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS CHNGE THIS 
/// ///////////////////////////////////////////     loop

void RecBacktrack::make_maze() {

    if (posy > 0) {
        if (visited[posy - 1][posx] == 0) { ifcross.push_back(0); }// if up is not visited
    }
    if (posx < width - 1) {
        if (visited[posy][posx + 1] == 0) { ifcross.push_back(1); }//right
    }
    if (posy < height - 1) {
        if (visited[posy + 1][posx] == 0) { ifcross.push_back(2); }//down
    }
    if (posx > 0) {
        if (visited[posy][posx - 1] == 0) { ifcross.push_back(3); }//left
    }

    //If more than one way to go
    if (ifcross.size() > 1) maze_stack.push({ posx, posy });


    if (ifcross.size() >= 1) {
        h = rand() % ifcross.size(); //0,1,2,3 //0,2,3 //h=0, h=2; //DRAW FROM OUR WAYS...

        if (ifcross.at(h) == 0 and posy - 1 >= 0) {
            posy -= 1;
            maze_walls[posWalls(posy) + 1][posWalls(posx)] = 0; //erase the wall
        }//go up
        else if (ifcross.at(h) == 1 and posx + 1 < width) {
            posx += 1;
            maze_walls[posWalls(posy)][posWalls(posx) - 1] = 0;
        }//go right
        else if (ifcross.at(h) == 2 and posy + 1 < height) {
            posy += 1;
            maze_walls[posWalls(posy) - 1][posWalls(posx)] = 0;
        }//go down
        else if (ifcross.at(h) == 3 and posx - 1 >= 0) {
            posx -= 1;
            maze_walls[posWalls(posy)][posWalls(posx) + 1] = 0;
        }//go left
        else std::cout << "ERROR"; //needed?.............

        visited[posy][posx] = 1;

    }
    else if (ifcross.size() < 1) { //if we can do anyway
        if (maze_stack.size() <= 1) {//if in stack nothing we cant undo 
            make_maze_end = true; //end of loop
            // MORE CHECK IF REALLY EVERY SQUARE VISITED
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (visited[i][j] == 0) make_maze_end = false;
                }
            }
        }
        else if (posx == maze_stack.top().first and posy == maze_stack.top().second) {
            maze_stack.pop();
            posx = maze_stack.top().first;
            posy = maze_stack.top().second;
        }
        else {
            posx = maze_stack.top().first;
            posy = maze_stack.top().second;
        }
    }

    ifcross.clear();//every time clear stock od ways to go on our position

}




