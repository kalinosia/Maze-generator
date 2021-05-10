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
sf::RenderWindow window(sf::VideoMode((size* width * 2 + (size * 2)), (size* height * 2 + (size * 2))), "Maze Generator!", sf::Style::Titlebar | sf::Style::Close);

void draw_maze(sf::RectangleShape shape, bool maze_walls[2*height+1][2*width+1]) {
    window.clear();
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
	
	bool visited[height][width]; //without new, add, add, empty first.
    memset(visited, false, sizeof(visited));

	bool maze_walls[2 * height + 1][2 * width + 1];
// Matrix of walls (1) and empty squares (0)
	for (int i = 0; i < 2 * width + 1; i++) {
		for (int j = 0; j < 2 * height + 1; j++){
			if (i == 0 or j == 0 or i == 2 * width or j == 2 * height) maze_walls[j][i] = 1;//œciany boczne
			else if (i % 2 == 0) maze_walls[j][i] = 1;
			else if (i % 2 == 1) {
				if (j%2==0) maze_walls[j][i] = 1;
				else if(j%2==1) maze_walls[j][i] = 0;
			}
			else maze_walls[j][i] = 1;
		}
	}

    int posx = 0;
    int posy = 0;

    //int direction; //0 up, 1 right, 2 down, 3 left

    std::vector<int> ifcross(4); //capacity =4
    ifcross.clear();

	//memset(maze_walls, true, sizeof(maze_walls)); //?? better way
	std::stack <std::pair<int, int>> maze_stack;
	

    srand(time(NULL));

    //sf::RenderWindow window(sf::VideoMode((size*width*2+(size*2)), (size * height * 2 + (size * 2))), "Maze Generator!", sf::Style::Titlebar | sf::Style::Close);

    sf::RectangleShape shape{ (sf::Vector2f(10, 10)) };
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(0,0);

    bool maze_end = false;
    int h;////////////////////////////////////////////////////

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            /*
            for (int i = 0; i < 2 * height + 1; i++) {
                for (int j = 0; j < 2 * width + 1; j++) {
                    shape.setPosition(j * size, i * size);
                    if (maze_walls[i][j] == 1)shape.setFillColor(sf::Color::Red);
                    if (maze_walls[i][j] == 0)shape.setFillColor(sf::Color::White);
                    window.draw(shape);
                    window.display();
                    Sleep(1);

                }
            }
            */
            //draw_maze(shape, maze_walls);
            //Sleep(10);

            int entry=rand() % width;
            //maze[y][x]
            posy = 0;
            posx = entry;
            
            //pos_y_walls = 2 * posx+1;
            //pos_x_walls = 2 * posy + 1;

            //maze_walls[posWalls(posy)][posWalls(posx)] = 0;
            maze_walls[posWalls(posy) - 1][posWalls(posx)] = 0;
            visited[posy][posx]=1;

            

            draw_maze(shape, maze_walls);

            //break;
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
                
                
                //visited[posy][posx]
                std::cout << ifcross.size()<<"\n";

                if (ifcross.size() > 1) maze_stack.push({ posx, posy });


                if (ifcross.size() >= 1) {
                    h = rand() % ifcross.size(); //0,1,2,3 //0,2,3 //h=0, h=2;
                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    if (ifcross.at(h) == 0 and posy - 1 >= 0) {
                        posy -= 1;
                        maze_walls[posWalls(posy) + 1][posWalls(posx)] = 0;
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
                    else std::cout << "ERROR";
                    
                    visited[posy][posx] = 1;
                    /*
                    if (direction == 0) maze_walls[pos_y_walls(posy) - 1][pos_x_walls(posx)] = 0;
                    if (direction == 1) maze_walls[pos_y_walls(posy)][pos_x_walls(posx)+1] = 0;
                    if (direction == 2) maze_walls[pos_y_walls(posy) + 1][pos_x_walls(posx)] = 0;
                    if (direction == 3) maze_walls[pos_y_walls(posy) ][pos_x_walls(posx)-1] = 0;
                    */
                }
                else if (ifcross.size() < 1) {
                //what happend in here
                //we go back to place where cross was
                //maze_stack.top.... and then once again
                    if (maze_stack.size() <=1) {
                        maze_end = true;
                        for (int i = 0; i < 2 * height + 1; i++) {
                            for (int j = 0; j < 2 * width + 1; j++) {
                                if (visited[i][j] == 0) maze_end = false;;
                            }
                        }
                        std::cout << "END";
                        break;//if no cross up is end of maze or check if visited every???
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
                ifcross.clear();


                draw_maze(shape, maze_walls);
                //if (posx == entry and posy == 0) break;
            /*
            std::cout << "Posx: "<<posx<<" Posy: " <<posy<<"\n";
            for (int i = 0; i < height; i++){
                for (int j = 0; j < width; j++){
                    std::cout << visited[i][j] << " ";
                }
                std::cout << std::endl;
            }
            */
            //Sleep(1000);
            
            /*
            shape.setPosition((posx*2+1)*size, (posy*2+1)*size);
            shape.setFillColor(sf::Color::Red);
            window.draw(shape);
            window.draw(shape);
            window.display();
            */

            }

        }
        Sleep(1000);
    }//Sleep(10);

	return 0;
}