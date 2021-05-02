#ifndef _p
#define _p
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
const int ROWS = 38, COLUMNS = 35;

class Character {

protected:
	CircleShape circle;
	Texture texture;
	int row;
	int column;

public:
	Character(float radius, int initialRow, int initialColumn, string fileName);
	int getRow() const;
	int getCol() const;

};
#endif