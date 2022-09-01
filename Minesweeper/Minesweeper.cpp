#include "Minesweeper.h"
#include <iostream>

/* This constructor creates a window, grid of cells, sets "cellsUnrevealed" variable as number of unrevealed cells excluding ones with mines and generates whole minefield */

Minesweeper::Minesweeper(): window(sf::VideoMode(scr_width, scr_height), "Minesweeper", sf::Style::Titlebar | sf::Style::Close) {
    grid = new Cell **[cols];
    for (int i = 0; i < cols; ++i) {
        grid[i] = new Cell * [rows];
        for (int j = 0; j < rows; ++j) {
            grid[i][j] = new Cell(i, j, scr_width / cols, scr_height / rows);
        }
    }

    cellsUnrevealed = cols * rows - mines;

    minefieldGen();
}

void Minesweeper::run() { 
    while (window.isOpen()) {
        if (cellsUnrevealed == 0) { // If player revealed all cells excluding ones with mine program prints "You Won!" and closes a window
            std::cout << "You Won!";
            window.close();
        }
        else processEvents();
        render();
        
    }
}

/* Method checks events such as clicking on close icon or unrevealed cells and then doing intended actions */

void Minesweeper::processEvents() {
    sf::Event event;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int x = mousePos.x / (scr_width / cols); // Calculates in which column and row mouse cursor is
    int y = mousePos.y / (scr_height / rows);
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) // If close icon clicked close a game
            window.close();
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) // If escape key released close game
                window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.key.code == sf::Mouse::Left)
                /* Player can't reveal a cell that has been marked by him using right click */
                /* If player left clicked on a cell with mine program reveals all cells and prints that player lost */
                if (grid[x][y]->getHasMine() && !grid[x][y]->getHasFlag() && !grid[x][y]->isRevealed()) {
                    revealAll();
                    std::cout << "You lost!";
                }
                /* Else if player left clicked on a cell without mine */
                else if (!grid[x][y]->getHasFlag() && !grid[x][y]->isRevealed()) {
                    
                    if (grid[x][y]->getNeighbours() > 0) { // If clicked cell has neighbour mine program reveals clicked cell and subtracts one from variable "cellsUnrevealed"
                        cellsUnrevealed--;
                        grid[x][y]->setRevealed();
                    }
                    else revealSafe(x, y); // So if cell has no neigbour mines, reveals all cells that player can easily reveal without really thinking much about it
                }
            if (event.key.code == sf::Mouse::Right) { // If player right clicked on unrevealed cell marks or unmarks a cell - marked cell can't be reaveled
                if (!grid[x][y]->isRevealed())
                    grid[x][y]->invertHasFlag();
            }
        }
    }
}

/* Method draws a minefield */

void Minesweeper::render() {
    window.clear();
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            window.draw(*grid[j][i]);
    window.display();
}

/* Minefield generator that randomly sets a mines position and then sets a "neighboursWithMine" variable for cells without mines */

void Minesweeper::minefieldGen() {
    srand(time(NULL)); // This function initialize the seed of random so in each run of the code we get a different random results
    std::vector <int> minesCoord;

    int x, y;

    for (int i = 0; i < cols * rows; i++) // Creates a vector of numbers that represents cells' coordinates
        minesCoord.push_back(i);

    std::random_shuffle(minesCoord.begin(), minesCoord.end()); // Randomly shuffles the vector

    for (int i = 0; i < mines; i++) {
        x = minesCoord[i] % cols;
        y = minesCoord[i] / cols;
        grid[x][y]->setHasMine(); // First "mines" elements of vector have coordinates of cells with mines
    }
    /* This loop sets a "neighboursWithMine" variable to all cells that don't have a mine */

    for (int i = 0; i < mines; i++) {
        x = minesCoord[i] % cols;
        y = minesCoord[i] / cols;
        if (validIndex(x, y - 1)) // top neighbour
            if (!grid[x][y - 1]->getHasMine())
                grid[x][y - 1]->addNeighbour();
        if (validIndex(x + 1, y - 1)) // top-right neighbour
            if (!grid[x + 1][y - 1]->getHasMine())
                grid[x + 1][y - 1]->addNeighbour();
        if (validIndex(x + 1, y)) // right neighbour
            if (!grid[x + 1][y]->getHasMine())
                grid[x + 1][y]->addNeighbour();
        if (validIndex(x + 1, y + 1)) // bottom-right neighbour
            if (!grid[x + 1][y + 1]->getHasMine())
                grid[x + 1][y + 1]->addNeighbour();
        if (validIndex(x, y + 1)) // bottom neighbour
            if (!grid[x][y + 1]->getHasMine())
                grid[x][y + 1]->addNeighbour();
        if (validIndex(x - 1, y + 1)) // bottom-left neighbour
            if (!grid[x - 1][y + 1]->getHasMine())
                grid[x - 1][y + 1]->addNeighbour();
        if (validIndex(x - 1, y)) // left neighbour
            if (!grid[x - 1][y]->getHasMine())
                grid[x - 1][y]->addNeighbour();
        if (validIndex(x - 1, y - 1)) // top-left neighbour
            if (!grid[x - 1][y - 1]->getHasMine())
                grid[x - 1][y - 1]->addNeighbour();
    }

    /* Sets a "number" variable for drawing a number on cell after reveal */

    for (int i = 0; i < cols; ++i)
        for (int j = 0; j < rows; ++j) {
            if (grid[i][j]->getNeighbours() == 0)
                continue;
            else grid[i][j]->setNumber();
        }
}

void Minesweeper::revealAll() {
    for (int i = 0; i < cols; ++i)
        for (int j = 0; j < rows; ++j)
            grid[i][j]->setRevealed();
}

/* Method is using iterative implementation of depth-search algorithm to reveal all "safe" cells */

void Minesweeper::revealSafe(int x, int y) {
    std::stack<Cell*> stk;
    Cell* A;
    stk.push(grid[x][y]);
    while (!stk.empty()) {
        A = stk.top();
        stk.pop();
        if (!A->isRevealed()) {
            A->setRevealed();
            cellsUnrevealed--;
            addNeighboursToStack(A, stk);
        }
    }
}

/* Method adds to given stack all unrevealed neighbours that has zero neighbours with mine and method reveals rest of the neighbours (if they aren't already revealed)  */

void Minesweeper::addNeighboursToStack(Cell* A, std::stack<Cell*> &stk) {
    int x = A->getX();
    int y = A->getY();
    if (validIndex(x, y - 1)) // top
        if (grid[x][y - 1]->getNeighbours() == 0 && !grid[x][y - 1]->isRevealed())
            stk.push(grid[x][y - 1]);
        else if (!grid[x][y - 1]->isRevealed()) {
            grid[x][y - 1]->setRevealed();
            cellsUnrevealed--;
        }
    if (validIndex(x + 1, y - 1)) // top-right
        if (grid[x + 1][y - 1]->getNeighbours() == 0 && !grid[x + 1][y - 1]->isRevealed())
            stk.push(grid[x + 1][y - 1]);
        else if (!grid[x + 1][y - 1]->isRevealed()) {
            grid[x + 1][y - 1]->setRevealed();
            cellsUnrevealed--;
        }
    if (validIndex(x + 1, y)) // right
        if (grid[x + 1][y]->getNeighbours() == 0 && !grid[x + 1][y]->isRevealed())
            stk.push(grid[x + 1][y]);
        else if (!grid[x + 1][y]->isRevealed()) {
            grid[x + 1][y]->setRevealed();
            cellsUnrevealed--;
        }
    if (validIndex(x + 1, y + 1)) // bottom-right
        if (grid[x + 1][y + 1]->getNeighbours() == 0 && !grid[x + 1][y + 1]->isRevealed())
            stk.push(grid[x + 1][y + 1]);
        else if (!grid[x + 1][y + 1]->isRevealed()) {
            grid[x + 1][y + 1]->setRevealed();
            cellsUnrevealed--;
        }
    if (validIndex(x, y + 1)) // bottom
        if (grid[x][y + 1]->getNeighbours() == 0 && !grid[x][y + 1]->isRevealed())
            stk.push(grid[x][y + 1]);
        else if (!grid[x][y + 1]->isRevealed()) {
            grid[x][y + 1]->setRevealed();
            cellsUnrevealed--;
        }
    if (validIndex(x - 1, y + 1)) // bottom-left
        if (grid[x - 1][y + 1]->getNeighbours() == 0 && !grid[x - 1][y + 1]->isRevealed())
            stk.push(grid[x - 1][y + 1]);
        else if (!grid[x - 1][y + 1]->isRevealed()) {
            grid[x - 1][y + 1]->setRevealed();
            cellsUnrevealed--;
        }
    if (validIndex(x - 1, y)) // left
        if (grid[x - 1][y]->getNeighbours() == 0 && !grid[x - 1][y]->isRevealed())
            stk.push(grid[x - 1][y]);
        else if (!grid[x - 1][y]->isRevealed()) {
            grid[x - 1][y]->setRevealed();
            cellsUnrevealed--;
        }
    if (validIndex(x - 1, y - 1)) // top-left
        if (grid[x - 1][y - 1]->getNeighbours() == 0 && !grid[x - 1][y - 1]->isRevealed())
            stk.push(grid[x - 1][y - 1]);
        else if (!grid[x - 1][y - 1]->isRevealed()) {
            grid[x - 1][y - 1]->setRevealed();
            cellsUnrevealed--;
        }
}

/* Method checks if a cell with given x and y can exist */

bool Minesweeper::validIndex(int x, int y) {
    if (x < 0 || y < 0 || x > cols - 1 || y > rows - 1)
        return false;
    return true;
}

Minesweeper::~Minesweeper() {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            delete grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
}