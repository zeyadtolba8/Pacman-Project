#ifndef _B
#define _B
#include "Character.h"


class enemi : public Character
{
private:
	sf::Clock Ghost;

public:
	enemi(float radius, int initialRow, int initialColumn, string fileName);
	void drawOnWindow(RenderWindow& window);
	void moveEnemiAttack(int arr[][COLUMNS], int path);
	void moveUpAttack();
	void moveDownAttack();
	void moveRightAttack();
	void moveLeftAttack();
	void resetPos(int index);

};

#endif