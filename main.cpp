#include <SFML/Graphics.hpp>

#include <iostream>
#include <stack>
#include <time.h>
#include <stdlib.h> 
#include <windows.h> 

int size = 10;
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
	const int width = 40;
	const int height = 25;

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


	//memset(maze_walls, true, sizeof(maze_walls)); //?? better way
	//std::stack <std::pair<int, int>> maze_stack;
	

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode((size*width*2+(size*2)), (size * height * 2 + (size * 2))), "Maze Generator!", sf::Style::Titlebar | sf::Style::Close);

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
            Sleep(10);
            entry=rand() % width;
            maze_walls[i][j]
            while (true) {

            }
        }
    }//Sleep(10);

	return 0;
}