#pragma once
#include "Cell.h"

class MazeGame {
	Cell*** grid; // Later becomes a maze
	Cell* currentCell;
	Cell* start;
	Cell* meta;
	
	/* Screen height and width */

	const int scr_height = 800;
	const int scr_width = 800;

	sf::RenderWindow window;

	/* Number of columns and rows */

	const int cols = 20;
	const int rows = 20;
	
public:
	MazeGame();

	void run();
	void processEvents();
	void moveCurrent(int);
	void render();

	void mazeGen();
	Cell* chooseNeighbour();
	bool validIndex(int, int);
	void removeWall(Cell*, Cell*);
	
	~MazeGame();
};