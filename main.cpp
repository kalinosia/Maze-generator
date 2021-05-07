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
    for (int i = 0; i < 2 * height + 1; i++) {
        for (int j = 0; j < 2 * width + 1; j++) {
            shape.setPosition(j * size, i * size);
            if (maze_walls[i][j] == 1)shape.setFillColor(sf::Color::Red);
            if (maze_walls[i][j] == 0)shape.setFillColor(sf::Color::White);
            window.draw(shape);
            window.display();
            //Sleep(1);

        }
    }
}
int pos_y_walls(int posx) {
    return 2 * posx + 1;
}
int pos_x_walls(int posy) {
    return 2 * posy + 1;
}
/*
class Square {
protected:
    int x, y;
	//int size = 10;
public:
    sf::RectangleShape shape{ (sf::Vector2f(size, size)) };

    Square() {
        x = 0;
        y = 0;
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(x, y);
    }
    Square(int x, int y) {
        this->x = x*size;
        this->y = y*size;
        //square=(sf::Vector2f(10, 10));
        shape.setFillColor(sf::Color::White);
        shape.setPosition(this->x, this->y);
    }
    void square_color(bool defcol) {
        if (defcol == 0) shape.setFillColor(sf::Color::White);
        if (defcol == 1) shape.setFillColor(sf::Color::Red);
    }
};
*/
int main() {
	//const int width = 40;
	//const int height = 25;

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

    std::vector<int> ifcross(4);

	//memset(maze_walls, true, sizeof(maze_walls)); //?? better way
	std::stack <std::pair<int, int>> maze_stack;
	

    srand(time(NULL));

    //sf::RenderWindow window(sf::VideoMode((size*width*2+(size*2)), (size * height * 2 + (size * 2))), "Maze Generator!", sf::Style::Titlebar | sf::Style::Close);

    sf::RectangleShape shape{ (sf::Vector2f(10, 10)) };
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(0,0);

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
            draw_maze(shape, maze_walls);
            Sleep(10);

            int entry=rand() % width;
            //maze[y][x]
            posy = 0;
            posx = entry;

            //pos_y_walls = 2 * posx+1;
            //pos_x_walls = 2 * posy + 1;

            maze_walls[pos_y_walls(posy)][pos_x_walls(posx)] = 0;
            maze_walls[pos_y_walls(posy) + 1][pos_x_walls(posx)] = 0;
            visited[posy][posx]=1;
            if (posy>0) if (visited[posy-1][posx]==0) ifcross.push_back(0);
            if (posx>0) if (visited[posy][posx-1] == 0) ifcross.push_back(1);
            if (posy<height-1) if (visited[posy+1][posx] == 0) ifcross.push_back(2);
            if (posx<width-1) if (visited[posy][posx+1] == 0) ifcross.push_back(3);
            //visited[posy][posx]
            
            if (ifcross.size() > 1) {
                int h = rand() % ifcross.size(); //0,1,2,3 //0,2,3
                
                if (ifcross.at(h) == 0) posy--; //go up
                if (ifcross.at(h) == 0) posx++;//go right
                if (ifcross.at(h) == 0) posy++; //go down
                if (ifcross.at(h) == 0) posx--; //go left
            }

            //if (ifcross.size()<1) cofamy siê bo nie ma gdzie iœæ

            ifcross.clear();
            //while (true) {

            //}
        }
    }//Sleep(10);

	return 0;
}