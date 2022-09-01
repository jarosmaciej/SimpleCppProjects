#pragma once
#include "Cell.h"
#include <stack>

class Minesweeper {
	Cell*** grid;

	const int mines = 50;
	int cellsUnrevealed; // number of unrevealed cells excluding ones with mines

	/* Screen height and width */

	const int scr_height = 600;
	const int scr_width = 600;

	sf::RenderWindow window;

	/* Number of columns and rows */

	const int cols = 20;
	const int rows = 20;
	
public:
	Minesweeper();

	void run();
	void processEvents();
	void render();

	void revealSafe(int, int);
	void revealAll();

	void minefieldGen();
	void addNeighboursToStack(Cell*, std::stack<Cell*>&);

	bool validIndex(int, int);
	

	
	~Minesweeper();
};