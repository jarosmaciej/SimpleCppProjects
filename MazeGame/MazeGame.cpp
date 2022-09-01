#include "MazeGame.h"
#include <iostream>
#include <vector>
#include <stack>

/* This constructor creates a window and a grid of cells, marks starting and meta position, also sets variable "currentCell" as meta and makes it visited for maze generation algorithm */

MazeGame::MazeGame(): window(sf::VideoMode(scr_width, scr_height), "Maze Game", sf::Style::Titlebar | sf::Style::Close) {
    grid = new Cell **[cols];
    for (int i = 0; i < cols; ++i) {
        grid[i] = new Cell * [rows];
        for (int j = 0; j < rows; ++j) {
            grid[i][j] = new Cell(i, j, scr_width / cols, scr_height / rows);
        }
    }

    start = grid[0][0];
    start->setCol(sf::Color(11, 11, 69));
    meta = grid[cols - 1][rows - 1];
    meta->setCol(sf::Color(138, 3, 3));

    currentCell = meta; // Maze is generated from the meta's cell to be sure that player is able to visit every cell
    currentCell->setVisited(true);
}

void MazeGame::run() {
    mazeGen();
    currentCell = start; // Maze is already generated so now "currnetCell" changes its purpose - tracks player position in maze
    
    while (window.isOpen()) {
        processEvents();
        render();
        if (currentCell == meta) { // After player reaches a meta, console prints "You won!" and a window closes
            std::cout << "You Won!";
            window.close();
        }
    }
}

/* Method checks events such as clicking on close icon or pressing buttons on keyboard and then doing intended actions */

void MazeGame::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) // If close icon clicked close a game
            window.close();
        if (event.type == sf::Event::KeyReleased) 
        {
            if (event.key.code == sf::Keyboard::Escape) // If escape key released close game
                window.close();
            else if (event.key.code == sf::Keyboard::Up) // If up key released move "currentCell" pointer up in the grid
                moveCurrent(0);
            else if (event.key.code == sf::Keyboard::Right) // If right key released move "currentCell" pointer right in the grid
                moveCurrent(1);
            else if (event.key.code == sf::Keyboard::Down) // If right key released move "currentCell" pointer down in the grid
                moveCurrent(2);
            else if (event.key.code == sf::Keyboard::Left) // If left key released move "currentCell" pointer left in the grid
                moveCurrent(3);
        }
    }
}

/* Method draws a maze */

void MazeGame::render() {
    window.clear();
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            window.draw(*grid[j][i]);
    window.display();
}

/* Method changes "currentPosition"'s pointed cell to the neighbour one in the grid, depending on a given "direction" variable. If there's a wall on a way, nothing changes */

void MazeGame::moveCurrent(int direction) {
    if (currentCell->checkWall(direction))
        return;
    int x = currentCell->getX();
    int y = currentCell->getY();
    if (direction == 0) {
        if (validIndex(x, y - 1)) {
            currentCell->setCol(sf::Color(25, 25, 35));
            currentCell = grid[x][y - 1];
            currentCell->setCol(sf::Color(11, 11, 69));
        }
    }
    else if (direction == 1) {
        if (validIndex(x + 1, y)) {
            currentCell->setCol(sf::Color(25, 25, 35));
            currentCell = grid[x + 1][y];
            currentCell->setCol(sf::Color(11, 11, 69));
        }
    }
    else if (direction == 2) {
        if (validIndex(x, y + 1)) {
            currentCell->setCol(sf::Color(25, 25, 35));
            currentCell = grid[x][y + 1];
            currentCell->setCol(sf::Color(11, 11, 69));
        }
    }
    else if (validIndex(x - 1, y)) {
        currentCell->setCol(sf::Color(25, 25, 35));
        currentCell = grid[x - 1][y];
        currentCell->setCol(sf::Color(11, 11, 69));
    }
}


/* Maze generator's functions */

/* Randomized depth-first search algorithm - iterative implementation */

void MazeGame::mazeGen() {
    std::stack<Cell*> stk;
    stk.push(currentCell);
    srand(time(NULL)); // This function initialize the seed of random so in each run of the code we get a different random results
    Cell* next;
    while (!stk.empty()) {
        currentCell = stk.top();
        next = chooseNeighbour();
        if (next != nullptr) {
            next->setVisited(true);
            removeWall(currentCell, next);
            stk.push(next);
        }
        else stk.pop();
    }
}

/* Method is randomly choosing a current cell's neighbour that haven't been visited yet and returns pointer to it */

Cell* MazeGame::chooseNeighbour() {
    std::vector<Cell*> neighbours;
    int x = currentCell->getX();
    int y = currentCell->getY();
    if (validIndex(x, y - 1))
        if (!grid[x][y - 1]->isVisited())
            neighbours.push_back(grid[x][y - 1]);
    if (validIndex(x + 1, y))
        if (!grid[x + 1][y]->isVisited())
            neighbours.push_back(grid[x + 1][y]);
    if (validIndex(x, y + 1))
        if (!grid[x][y + 1]->isVisited())
            neighbours.push_back(grid[x][y + 1]);
    if (validIndex(x - 1, y))
        if (!grid[x - 1][y]->isVisited())
            neighbours.push_back(grid[x - 1][y]);
    if (neighbours.size() > 0)
        return neighbours[rand() % neighbours.size()];
    return nullptr;
}

/* Method checks if a cell with given x and y can exist */

bool MazeGame::validIndex(int x, int y) {
    if (x < 0 || y < 0 || x > cols - 1 || y > rows - 1)
        return false;
    return true;
}

/* Method removes wall between two cells */

void MazeGame::removeWall(Cell* A, Cell* B) {
    if (A->getX() - B-> getX()  == 1) {
        A->removeWall(3);
        B->removeWall(1);
    }
    if (A->getX() - B->getX() == -1) {
        A->removeWall(1);
        B->removeWall(3);
    }
    if (A->getY() - B->getY() == 1) {
        A->removeWall(0);
        B->removeWall(2);
    }
    if (A->getY() - B->getY() == -1) {
        A->removeWall(2);
        B->removeWall(0);
    }
}

MazeGame::~MazeGame() {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            delete grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
}