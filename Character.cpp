#include "Character.h"

Character::Character(float radius, int initialRow, int initialColumn, string fileName)
{
	circle.setRadius(radius);
	circle.setPosition(25 * initialColumn, 70 + 25 * initialRow);
	texture.loadFromFile(fileName);
	circle.setTexture(&texture);
	row = initialRow+1;
	column = initialColumn+1;
}

int Character::getRow() const{

	return row;
}
int Character::getCol() const{

	return column;

}