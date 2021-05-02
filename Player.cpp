#include "Player.h"

Player::Player(float radius, int initialRow, int initialColumn, string fileName, int L): Character(radius, initialRow, initialColumn, fileName),
 lives(L), score(0)
{	
	GM = "Normal";
}

void Player::changeTexture(string fName) {
	texture.loadFromFile(fName);
	circle.setTexture(&texture);


}

void Player::moveOnWindow(Event e, int arr[][COLUMNS], RectangleShape board[][COLUMNS-2], bool& MODE)
{
	
	switch (e.key.code)
	{
		
	case Keyboard::Up:
		if (pac.getElapsedTime().asSeconds() >= 0.15)
		{
			if ((arr[row - 1][column] >= 0))
			{
				circle.move(0, -25);
				row--;
				changeTexture("pacmanUp.png");
				if (board[row - 1][column - 1].getFillColor() != Color::Black)
				{
					if ((arr[row][column] == 002) || (arr[row][column] == 000) || (arr[row][column] == 365) || (arr[row][column] == 366))
					{
						MODE = true;
						incScore50();
					}
					else
					{
						incrScore();
					}
				}
				board[row - 1][column - 1].setFillColor(Color::Black);

			}
			pac.restart();
		}
		break;
	case Keyboard::Down:
		if (pac.getElapsedTime().asSeconds() >= 0.15)
		{
			if (arr[row + 1][column] >= 0)
			{
				circle.move(0, 25);
				row++;
				changeTexture("pacmanDown.png");
				if (board[row - 1][column - 1].getFillColor() != Color::Black)
				{
					if ((arr[row][column] == 002) || (arr[row][column] == 000) || (arr[row][column] == 365) || (arr[row][column] == 366))
					{
						MODE = true;
						incScore50();

					}
					else
					{
						incrScore();

					}
				}
				board[row - 1][column - 1].setFillColor(Color::Black);

			}
			pac.restart();
		}
		break;
	case Keyboard::Right:
		if (pac.getElapsedTime().asSeconds() >= 0.15)
		{
			if (arr[row][column] == 175)
			{
				column = 1;
				circle.move(-(25*(COLUMNS-3)), 0);
				board[row - 1][0].setFillColor(Color::Black);
				
			}

			if (arr[row][column + 1] >= 0)
			{

				circle.move(25, 0);
				column++;
				changeTexture("pacman.png");
				if (board[row-1][column-1].getFillColor() != Color::Black)
				{
					if ((arr[row][column] == 002) || (arr[row][column] == 000) || (arr[row][column] == 365) || (arr[row][column] == 366))
					{
						MODE = true;
						incScore50();

					}
					else
					{
						incrScore();
					}
				}
				board[row-1][column-1].setFillColor(Color::Black);


			}
			pac.restart();
		}
		break;
	case Keyboard::Left:
		if (pac.getElapsedTime().asSeconds() >= 0.15)
		{
			if (arr[row][column] == 151)
			{
				column = (COLUMNS - 2);
				circle.move((25 * (COLUMNS-3)), 0);
				board[row - 1][COLUMNS-3].setFillColor(Color::Black);
			}
			if (arr[row][column - 1] >= 0)
			{
				circle.move(-25, 0);
				column--;
				changeTexture("pacmanLeft.png");
				if (board[row - 1][column - 1].getFillColor() != Color::Black)
				{
					if ((arr[row][column] == 002) || (arr[row][column] == 000) || (arr[row][column] == 365) || (arr[row][column] == 366))
					{
						MODE = true;
						incScore50();

					}
					else
					{
						incrScore();

					}
				}
				board[row - 1][column - 1].setFillColor(Color::Black);

			}
			pac.restart();
		}
		break;
		}
	}

void Player::drawOnWindow(RenderWindow& window)
{
	window.draw(circle);
}

int Player::getLives() {
	return lives;

}
void Player::setLives() {

	lives--;
}

void Player::incrScore() {

	score += 10;
	DisplayScore();
}

void Player::incScore50() {
	GM = "invincible";
	score += 50;
	DisplayScore();

}

void Player::DisplayScore()
{
	Score.setFont(font);
	font.loadFromFile("GEO_AB__.TTF");
	Score.setCharacterSize(30);
	Score.setFillColor(Color::Color(92, 165, 220));
	Score.setPosition(30, 10); stringstream ss;
	ss << "Score: " << score;
	Score.setString(ss.str());
}

void Player::DisplayLives() {

	Lives.setFont(font);
	font.loadFromFile("GEO_AB__.TTF");
	Lives.setCharacterSize(30);
	Lives.setFillColor(Color::Color(92, 165, 220));
	Lives.setPosition(340, 10); stringstream ss;
	ss << "Lives: " << lives;
	Lives.setString(ss.str());
	
}

void Player::DisplayMode(bool& MODE)
{
	if (mode.getElapsedTime().asSeconds() >= 20)
		 {GM = "Normal";
			MODE = false;
			mode.restart(); }

	gameMode.setFont(font);
	font.loadFromFile("GEO_AB__.TTF");
	gameMode.setCharacterSize(30);
	gameMode.setFillColor(Color::Color(92, 165, 220));
	gameMode.setPosition(580, 10); stringstream DM;
	DM << "Mode:" << GM;
	gameMode.setString(DM.str());

}

void Player::resetPosition() {

	circle.setPosition(25 * 16, 70 + 25 * 27);
	row = 27+1;
	column = 16+1;

}
