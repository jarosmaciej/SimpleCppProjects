#pragma once
#include <SFML/Graphics.hpp>

class Cell : public sf::Drawable {
	int x, y; // Coordiantes of the cell

	bool revealed;
	bool hasMine;
	bool hasFlag;

	int neighboursWithMine;

	const int width, height;

	sf::Font font;
	sf::Text number; // Basically a "neigboursWithMine" but drawable
	sf::CircleShape mine;
public:
	Cell(int, int, const int, const int);
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

	int getX();
	int getY();

	void setHasMine();
	bool getHasMine();

	void addNeighbour();
	int getNeighbours();

	bool isRevealed();
	void setRevealed();

	bool getHasFlag();
	void invertHasFlag();

	void setNumber();
};