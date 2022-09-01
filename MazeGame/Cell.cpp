#include "Cell.h"

/* Constructor sets cell coordinates, size, default color as dark grey, all four walls as existing and that the cell was not visited yet */

Cell::Cell(int x_, int y_, const int width_, const int height_)
    :x(x_), y(y_), width(width_), height(height_),col (sf::Color(25, 25, 35)), walls{ true, true, true, true }, visited(false) {}

int Cell::getX() {
    return x;
}

int Cell::getY() {
    return y;
}

void Cell::setCol(sf::Color newCol) {
    col = newCol;
}

/* Method draws cell as a rectangle with walls */

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape shape(sf::Vector2f(width, height)); // Sets a rectangle shape
    shape.move(sf::Vector2f(x * width, y * height)); // Moves shape to cell coordinates
    shape.setFillColor(sf::Color(col)); // Fills a rectangle with color depending on cell's "col" variable
    target.draw(shape); // Draws created shape in a window

    /* Draws a walls that are set as existing */

    if (walls[0]) { // Top wall
        sf::VertexArray wall(sf::Lines, 2);
        wall[0].position = sf::Vector2f(x * width, y * height);
        wall[0].color = sf::Color::White;
        wall[1].position = sf::Vector2f((x + 1) * width, y * height);
        wall[1].color = sf::Color::White;
        target.draw(wall);
    }
    if (walls[1]) { // Right wall
        sf::VertexArray wall(sf::Lines, 2);
        wall[0].position = sf::Vector2f((x + 1) * width, y * height);
        wall[0].color = sf::Color::White;
        wall[1].position = sf::Vector2f((x + 1) * width, (y + 1) * height);
        wall[1].color = sf::Color::White;
        target.draw(wall);
    }
    if (walls[2]) { // Bottom wall
        sf::VertexArray wall(sf::Lines, 2);
        wall[0].position = sf::Vector2f(x * width, (y + 1) * height);
        wall[0].color = sf::Color::White;
        wall[1].position = sf::Vector2f((x + 1) * width, (y + 1) * height);
        wall[1].color = sf::Color::White;
        target.draw(wall);
    }
    if (walls[3]) { // Left wall
        sf::VertexArray wall(sf::Lines, 2);
        wall[0].position = sf::Vector2f(x * width, y * height);
        wall[0].color = sf::Color::White;
        wall[1].position = sf::Vector2f(x * width, (y + 1) * height);
        wall[1].color = sf::Color::White;
        target.draw(wall);
    }
}

void Cell::removeWall(int wallNumber) {
    if (wallNumber > -1 && wallNumber < 4)
        walls[wallNumber] = false;
}

bool Cell::checkWall(int wallNumber) {
    return walls[wallNumber];
}

bool Cell::isVisited() {
    return visited;
}

void Cell::setVisited(bool visited_) {
    visited = visited_;
}