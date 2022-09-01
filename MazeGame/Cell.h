#pragma once
#include <SFML/Graphics.hpp>

class Cell : public sf::Drawable {
	bool visited; // Variable refers if the cell was visited during maze generation, not by a player
	bool walls[4]; // Shows which walls exist | [0] top | [1] right | [2] bottom | [3] left
	int x, y; // Coordinates
	const int width, height;
	sf::Color col;
public:
	Cell(int, int, const int, const int);

	int getX();
	int getY();

	void setCol(sf::Color);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	void removeWall(int);
	bool checkWall(int);

	bool isVisited();
	void setVisited(bool);
};