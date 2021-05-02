#ifndef _A
#define _A
#include "Character.h"
#include"sstream"

class Player: public Character 
{
public:
	Player(float radius, int initialRow, int initialColumn, string fileName, int L );
    void drawOnWindow(RenderWindow& window);
	void moveOnWindow(Event e, int arr[][COLUMNS], RectangleShape board[][COLUMNS-2], bool &MODE);
	void changeTexture(string fName);
	int getLives();
	void setLives();
	void incrScore();
	void DisplayScore();
	void incScore50();
	void DisplayMode(bool& MODE);
	void DisplayLives();
	void resetPosition();
	Text Score;
	Text gameMode;
	Text Lives;
private:
	sf::Clock pac;
	sf::Clock mode;

	string GM;
	int lives;
	int score;
	Font font;
};

#endif