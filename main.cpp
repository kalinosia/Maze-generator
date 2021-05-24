#include <SFML/Graphics.hpp>

#include <iostream>
#include <stack>
#include <time.h>
#include <stdlib.h> 
#include <windows.h> 
#include <vector>
#include <fstream>

#include "RecBacktrack.h"

const int size = 10;
//const int width = 40;
//const int height = 25;
sf::RenderWindow window(sf::VideoMode((size* width * 2 + (size )), (size* height * 2 + (size ))), "Maze Generator!", sf::Style::Titlebar | sf::Style::Close);

void draw_maze(sf::RectangleShape shape, bool maze_walls[2*height+1][2*width+1], int x, int y) {
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
    shape.setPosition(x * size, y * size);
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);
    
    window.display();
    //Sleep(100);
}


int main() {
	
    //rand...
    srand(time(NULL));

    //shape to draw it
    sf::RectangleShape shape{ (sf::Vector2f(size, size)) };
    //shape.setFillColor(sf::Color::Yellow);
    //shape.setPosition(0,0);

    RecBacktrack maze;
    int x, y;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (!maze.maze_end()) maze.make_maze();
        
        x = maze.get_posx();
        y = maze.get_posy();

        draw_maze(shape, maze.maze_walls,x,y); //draw maze on every stage

        
       
    }//While window is open

   
	return 0;
}