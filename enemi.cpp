#include "enemi.h"

enemi::enemi(float radius, int initialRow, int initialColumn, string fileName) : Character(radius, initialRow, initialColumn, fileName)

{	   }

void enemi::drawOnWindow(RenderWindow& window)
{
	window.draw(circle);
}
void enemi::moveEnemiAttack(int arr[][COLUMNS], int path)
{

		if (Ghost.getElapsedTime().asSeconds() > 0.28)
		{
	
		//cout << path << endl;
			if (path == 151)
			{ 
				column = (COLUMNS - 2);
				circle.move((25 * (COLUMNS - 4)), 0);
			}
			if (path == 175)
			{
				column = 1;
				circle.move(-(25 * (COLUMNS - 4)), 0);

			}
			if (path == arr[row - 1][column]) // up
			{
					//cout << "up";
					moveUpAttack();
					Ghost.restart();
			}

			else if (path == arr[row + 1][column]) // Down
			{
				//cout << "Down";
				moveDownAttack();
				Ghost.restart();
				
			}
			else if (path == arr[row][column + 1]) // Right
			{
					//cout << "Right";
					moveRightAttack();
					Ghost.restart();
			}
			else if (path == arr[row][column - 1]) // Left
			{
					//cout << "Left";
					moveLeftAttack();
					Ghost.restart();
			}
			
	}
		
	
}

void enemi::resetPos(int index) {

	circle.setPosition(25 * index, 70 + 25 * 16);
	row = 16+1;
	column = index+1;
}

void enemi::moveUpAttack() {
	circle.move(0, -25);
	row--;
}

void enemi::moveDownAttack() {
	circle.move(0, 25);
	row++;
}
void enemi::moveRightAttack() {
	circle.move(25, 0);
	column++;

}
void enemi::moveLeftAttack() {
	circle.move(-25, 0);
	column--;

}