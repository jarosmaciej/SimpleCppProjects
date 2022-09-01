#include "Cell.h"

Cell::Cell(int x_, int y_, const int width_, const int height_)
    :x(x_), y(y_), width(width_), height(height_), hasFlag(false), hasMine(false), neighboursWithMine(0), revealed(false) {

    if (!font.loadFromFile("arial.ttf")) {}
    number.setFont(font);
    number.setCharacterSize(height);
    sf::FloatRect textRect = number.getLocalBounds();
    number.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    number.setPosition(sf::Vector2f(x * width + width / 4, y * height - height / 6));

    mine.setRadius(float(height) / 3);
    mine.setFillColor(sf::Color::Black);
    mine.setPosition(x * width + (width - float(2 * height) / 3) / 2, y * height + (height - float(2 * height) / 3) / 2);
}

int Cell::getX() {
    return x;
}

int Cell::getY() {
    return y;
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape shape(sf::Vector2f(width, height)); // Sets a rectangle shape
    shape.setPosition(x * width, y * height); // Moves shape to cell coordinates

    if (hasFlag && !revealed) // If cell "has flag" so is marked by a player fills a cell with color red
        shape.setFillColor(sf::Color::Red);
    else if (!revealed)
        shape.setFillColor(sf::Color(142, 142, 142)); // or with grey if not revealed
    else shape.setFillColor(sf::Color(120, 120, 120)); // or with dark grey if revealed

    target.draw(shape); // Draws created shape in a window

    /* Creates a four walls around the cell as a lines */

    sf::VertexArray wall(sf::Lines, 8);
    wall[0].position = sf::Vector2f(x * width, y * height - 1);
    wall[0].color = sf::Color::White;
    wall[1].position = sf::Vector2f((x + 1) * width, y * height - 1);
    wall[1].color = sf::Color::White;
    wall[2].position = sf::Vector2f((x + 1) * width, y * height);
    wall[2].color = sf::Color::White;
    wall[3].position = sf::Vector2f((x + 1) * width, (y + 1) * height);
    wall[3].color = sf::Color::White;
    wall[4].position = sf::Vector2f(x * width, (y + 1) * height);
    wall[4].color = sf::Color::White;
    wall[5].position = sf::Vector2f((x + 1) * width, (y + 1) * height);
    wall[5].color = sf::Color::White;
    wall[6].position = sf::Vector2f(x * width + 1, y * height);
    wall[6].color = sf::Color::White;
    wall[7].position = sf::Vector2f(x * width + 1, (y + 1) * height);
    wall[7].color = sf::Color::White;

    target.draw(wall); // and draws them

    if (neighboursWithMine > 0 && revealed) { // If cell has more then zero neigoburs with mine draw on it a number in arial font 
        target.draw(number);
    }
    if (hasMine && revealed) { // If cell with mine is reveled draws a mine on a cell as a black circle
        target.draw(mine);
    }
}

void Cell::setNumber() { // Sets a drawable "number" variable
    if (neighboursWithMine == 1) {
        number.setFillColor(sf::Color::Blue);
        number.setString("1");
    }
    else if (neighboursWithMine == 2) {
        number.setFillColor(sf::Color(0, 120, 0)); // Dark green
        number.setString("2");
    }
    else if (neighboursWithMine == 3) {
        number.setFillColor(sf::Color::Red);
        number.setString("3");
    }
    else if (neighboursWithMine == 4) {
        number.setFillColor(sf::Color(0, 0, 120)); // Dark blue
        number.setString("4");
    }
    else if (neighboursWithMine == 5) {
        number.setFillColor(sf::Color(127, 23, 52)); // Claret 
        number.setString("5");
    }
    else if (neighboursWithMine == 6) {
        number.setFillColor(sf::Color::Cyan);
        number.setString("6");
    }
    else if (neighboursWithMine == 7) {
        number.setFillColor(sf::Color(170, 0, 255)); // Purple
        number.setString("7");
    }
    else if (neighboursWithMine == 8) {
        number.setFillColor(sf::Color::Black);
        number.setString("8");
    }
}

void Cell::setHasMine() {
    hasMine = true;
}

bool Cell::getHasMine() {
    return hasMine;
}

void Cell::addNeighbour() {
    neighboursWithMine++;
}

int Cell::getNeighbours() {
    return neighboursWithMine;
}

bool Cell::isRevealed() {
    return revealed;
}

void Cell::setRevealed() {
    revealed = true;
}

bool Cell::getHasFlag() {
    return hasFlag;
}

void Cell::invertHasFlag() {
    if (hasFlag == true)
        hasFlag = false;
    else hasFlag = true;
}