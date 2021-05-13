#include <SFML/Graphics.hpp>

#include <iostream>
#include <stack>
#include <time.h>
#include <stdlib.h> 
#include <windows.h> 
#include <vector>

int size = 10;
const int width = 40;
const int height = 25;
sf::RenderWindow window(sf::VideoMode((size* width * 2 + (size )), (size* height * 2 + (size ))), "Maze Generator!", sf::Style::Titlebar | sf::Style::Close);

void draw_maze(sf::RectangleShape shape, bool maze_walls[2*height+1][2*width+1]) {
    window.clear(sf::Color::Yellow);
    for (int i = 0; i < 2 * height + 1; i++) {
        for (int j = 0; j < 2 * width + 1; j++) {
            shape.setPosition(j * size, i * size);
            if (maze_walls[i][j] == 1)shape.setFillColor(sf::Color::Black);
            if (maze_walls[i][j] == 0)shape.setFillColor(sf::Color::White);
            window.draw(shape);
            //window.display();
            //Sleep(1);

        }
    }
    window.display();
    //Sleep(100);
}
int posWalls(int pos) {
    return 2 * pos + 1;
}

int main() {
	//Matrix of empty squares, every =0 because not visited
	bool visited[height][width]; 
    memset(visited, false, sizeof(visited)); 

    //matrix of walls(1) and empty squres(0), later connected squares, wall=0
	bool maze_walls[2 * height + 1][2 * width + 1];
	for (int i = 0; i < 2 * width + 1; i++) {
		for (int j = 0; j < 2 * height + 1; j++){
			if (i == 0 or j == 0 or i == 2 * width or j == 2 * height) maze_walls[j][i] = 1;//side walls
			else if (i % 2 == 0) maze_walls[j][i] = 1;
			else if (i % 2 == 1) {
				if (j%2==0) maze_walls[j][i] = 1;
				else if(j%2==1) maze_walls[j][i] = 0;
			}
			else maze_walls[j][i] = 1;
		}
	}

    //point on x and y where now we are
    int posx = 0;
    int posy = 0;

    //0 up, 1 right, 2 down, 3 left; look for every sqares/area
    std::vector<int> ifcross(4); //capacity =4
    ifcross.clear();

	//stack of sqares where we been and it have more than one way to go
	std::stack <std::pair<int, int>> maze_stack;
	
    //rand...
    srand(time(NULL));

    //shape to draw it
    sf::RectangleShape shape{ (sf::Vector2f(size, size)) };
    //shape.setFillColor(sf::Color::Yellow);
    //shape.setPosition(0,0);

    //do maze, but once, only init and end
    bool maze_end = false;
    bool maze_init = true;
    bool maze_ended = true;
    //this variable we will use to have random variable
    int h;
    //this is our random entry on top of maze
    int entry = rand() % width;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        while (maze_init) {
            //maze[y][x]
            posy = 0;
            posx = entry;

            //pos_y_walls = 2 * posx+1;
            //pos_x_walls = 2 * posy + 1;
            maze_walls[posWalls(posy) - 1][posWalls(posx)] = 0; //-1 because in side wall entry is
            visited[posy][posx] = 1;

            draw_maze(shape, maze_walls);
            maze_init=false;
        }
        //........................................LOOP OF DOING MAZE...................................
            while(!maze_end){

                if (posy > 0) { 
                    if (visited[posy - 1][posx] == 0) {ifcross.push_back(0);}// if up is not visited
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
                    else if (ifcross.at(h) == 1 and posx+1<width) {
                        posx += 1;
                        maze_walls[posWalls(posy)][posWalls(posx) - 1] = 0;
                    }//go right
                    else if (ifcross.at(h) == 2 and posy+1<height) {
                        posy += 1;
                        maze_walls[posWalls(posy) - 1][posWalls(posx)] = 0;
                    }//go down
                    else if (ifcross.at(h) == 3 and posx-1>=0) {
                        posx -= 1;
                        maze_walls[posWalls(posy)][posWalls(posx) + 1] = 0;
                    }//go left
                    else std::cout << "ERROR"; //needed?.............
                    
                    visited[posy][posx] = 1; 
                    
                }
                else if (ifcross.size() < 1) { //if we can do anyway
                    if (maze_stack.size() <=1) {//if in stack nothing we cant undo 
                        maze_end = true; //end of loop
                        // MORE CHECK IF REALLY EVERY SQUARE VISITED
                        for (int i = 0; i < height ; i++) {
                            for (int j = 0; j < width ; j++) {
                                if (visited[i][j] == 0) maze_end = false;
                            }
                        }
                        break;
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


                draw_maze(shape, maze_walls); //draw maze on every stage
   
            }// while (!maze_end)
        while (maze_ended) {
            h= rand() % width;
            if (maze_walls[2 * height - 1][posWalls(h)] == 0) {
                maze_walls[2 * height ][posWalls(h)] = 0;
                maze_ended = false;
            }

            //////////////////////////////////////////////
            for (int i = 0; i < 2 * height + 1; i++) {
                for (int j = 0; j < 2 * width + 1; j++) {
                    std::cout << maze_walls[i][j] << " ";

                }
                std::cout << std::endl;
            }
            //////////////////////////////////////////////
            draw_maze(shape, maze_walls);
        }
        /*
        for (int i = 0; i < 2 * height + 1; i++) {
            for (int j = 0; j < 2 * width + 1; j++) {
                shape.setPosition(j * size, i * size);
                std::cout << maze_walls[i][j] << " ";

            }
            std::cout << std::endl;
        }
        draw_maze(shape, maze_walls);
        Sleep(10000);//???????????
        */
    }//While window is open

	return 0;
}