#include "Player.h"
#include "enemi.h"
#include "Character.h"
#include"sstream"
#include <SFML/Graphics.hpp>

const int COUNT = 391;
const int INFINITE = 9999;

vector<vector<int>> Dijkstra(int Graph[COUNT][COUNT], int startNode);

bool win( RectangleShape board[][COLUMNS-2], int arr[][COLUMNS], Player& pac, enemi& E1, enemi& E2, enemi& E3);

bool GameOver(Player& pac, enemi& E1, enemi& E2, enemi& E3, bool& over, bool& MODE);


///////////////////////// Start of the main function //////////////////////////////////
int main()
{
	int arr[ROWS][COLUMNS];
	// Reading from File
	ifstream inputFile;
	inputFile.open("Board.dat");
	if (inputFile.is_open())
	{
		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLUMNS; j++)
				if (!inputFile.eof())
					inputFile >> arr[i][j];
		inputFile.close();
	}
	else
		cout << "Error loading Board.txt ..." << endl;


	///////////////// flags /////////////////////////// 
	bool MODE = false;
	bool Over = false;
	bool start = false;
	bool READY = true;


	//////////////////////// SFML //////////////////////////////
	RenderWindow window;
	window.create(VideoMode(825, 1065), "Modern Pac-Man");

	Font font;
	font.loadFromFile("GEO_AB__.TTF");
	Text winner;
	Text gameOver;
	Text ready;

	////// Ready text will appear at the next phase ISA just press space to start the game //////////////////////////////
	ready.setFont(font);
	ready.setString("Ready");
	ready.setCharacterSize(120);
	ready.setFillColor(Color::Color(92, 165, 220));
	ready.setPosition(250, 500);

	winner.setFont(font);
	winner.setString("You Win");
	winner.setCharacterSize(120);
	winner.setFillColor(Color::Color(92, 165, 220));
	winner.setPosition(200, 500);

	gameOver.setFont(font);
	gameOver.setString("Game Over");
	gameOver.setCharacterSize(120);
	gameOver.setFillColor(Color::Color(92, 165, 220));
	gameOver.setPosition(80, 500);


	enemi e1(12.5, 16, 16, "G1.png");
	enemi e2(12.5, 16, 13, "G2.png");
	enemi e3(12.5, 16, 19, "G3.png");
	Player p(12.5, 27, 16, "pacman.png", 3);

	Texture bricksTexture, PelletTexture, BigPelletTexture;
	bricksTexture.loadFromFile("Bricks.png");
	PelletTexture.loadFromFile("pellet.png");
	BigPelletTexture.loadFromFile("BigP.png");
	RectangleShape board[ROWS-1][COLUMNS-2];
	for (int i = 0; i < ROWS-1; i++)
		for (int j = 0; j < COLUMNS-2; j++)
		{
			board[i][j].setSize(Vector2f(25, 25));
			board[i][j].setPosition(25 * j, 70 + 25 * i);
			if (arr[i+1][j+1] == -1)
			{
				board[i][j].setTexture(&bricksTexture);
				board[i][j].setFillColor(Color::Yellow);
			}
			else if (arr[i+1][j+1] > 002 && arr[i + 1][j + 1] < 365)
			{
				board[i][j].setTexture(&PelletTexture);
				board[i][j].setFillColor(Color::Yellow);
			}
			else if ((arr[i+1][j+1] == 001) || ((arr[i + 1][j + 1] < COUNT) && (arr[i + 1][j + 1] > 366)) )
				board[i][j].setFillColor(Color::Black);

			else if ((arr[i+1][j+1] == 002) || (arr[i+1][j+1] == 000) || (arr[i+1][j+1] == 365) || (arr[i+1][j+1] == 366))
			{
				board[i][j].setTexture(&BigPelletTexture);


			}

		}

	Event e;



	/////////////////////////////Graphs/////////////////////////////////
	

	int Graph[COUNT][COUNT];

	for (int i = 1; i < ROWS-1; i++)
		for (int j = 1; j < COLUMNS-1; j++)
			if (arr[i][j] >= 0)
			{
				if (arr[i - 1][j] >= 0)   // up
				{
					Graph[arr[i][j]][arr[i - 1][j]] = 1;

				}

				if (arr[i + 1][j] >= 0) // down 
				{
					Graph[arr[i][j]][arr[i + 1][j]] = 1;

				}

				if (arr[i][j + 1] >= 0) // right
				{
					Graph[arr[i][j]][arr[i][j + 1]] = 1;
				}

				if (arr[i][j - 1] >= 0)  //left
				{
					Graph[arr[i][j]][arr[i][j - 1]] = 1;
				}

			}

	for (int i = 0; i < COUNT; i++)
		for (int j = 0; j < COUNT; j++)
			if (Graph[i][j] != 1)
				Graph[i][j] = INFINITE;

	Graph[175][151] = 1;
	Graph[151][175] = 1;




	vector<vector<int>> paths1;
	vector<vector<int>> paths2;
	vector<vector<int>> paths3;
	
	//int damp =0;

///////////////////////// render loop ////////////////////////

	while (window.isOpen())
	{   
		paths1 = Dijkstra(Graph, arr[e1.getRow()][e1.getCol()]);
		 paths2 = Dijkstra(Graph, arr[e2.getRow()][e2.getCol()]);
		 paths3 = Dijkstra(Graph, arr[e3.getRow()][e3.getCol()]);


		 for (int i = 0; i < COUNT; i++)
		 { 
			 if (paths1[i][0] == arr[p.getRow()][p.getCol()] && start == true && Over == false)
				 e1.moveEnemiAttack(arr, paths1[i][paths1[i].size()-2]);
			 //if (path1[i][])
			 if (paths2[i][0] == arr[p.getRow()][p.getCol()] && start == true && Over == false)
				 e2.moveEnemiAttack(arr, paths2[i][paths2[i].size() - 2]);

			 if (paths3[i][0] == arr[p.getRow()][p.getCol()] && start == true && Over == false)
				 e3.moveEnemiAttack(arr, paths3[i][paths3[i].size() - 2]);
		 }

		

		p.DisplayScore();
		p.DisplayMode(MODE);
		p.DisplayLives();

			
		////////////////////// Events

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			if (e.key.code == Keyboard::Space)
				start = true;
			
		}

		if (start == true && Over == false)
			p.moveOnWindow(e, arr, board,MODE);

		if ((p.getRow() == e1.getRow()) && (p.getCol() == e1.getCol()) && (!Over))
				GameOver(p, e1, e2, e3, Over, MODE);
		
		if ((p.getRow() == e2.getRow()) && (p.getCol() == e2.getCol()) && (!Over))
			GameOver(p, e1, e2, e3, Over, MODE);
		
		if ((p.getRow() == e3.getRow()) && (p.getCol() == e3.getCol()) && (!Over))
			GameOver(p, e1, e2, e3, Over, MODE);
		


///////////////////////////// Clear - Draw - Display ///////////////////////////////
		window.clear();
		for (int i = 0; i < ROWS-1; i++)
			for (int j = 0; j < COLUMNS-2; j++)
				window.draw(board[i][j]);
		p.drawOnWindow(window);
		e1.drawOnWindow(window);
		e2.drawOnWindow(window);
		e3.drawOnWindow(window);

		window.draw(p.Score);
		window.draw(p.gameMode);
		window.draw(p.Lives);
		if (win(board, arr, p, e1, e2, e3))
		{
			window.draw(winner);
			start = false;
			READY = false;
		}
		if (Over)
		  window.draw(gameOver);
		if ((!start) && (!Over) && (READY))
			window.draw(ready);

		window.display();
	}
	return 0;
}

///////////////////////// End of the main function //////////////////////////////////

bool win(RectangleShape b[][COLUMNS-2], int arr[][COLUMNS], Player& pac, enemi& E1, enemi& E2, enemi& E3) {
	
	for (int i = 0; i < ROWS-1; i++)
		for (int j = 0; j < COLUMNS-2; j++)
		{
			if (arr[i+1][j+1] >= 0)
			{
				
				if (b[i][j].getFillColor() != Color::Black)
				{
					return false;
				}
			}
		}
	pac.resetPosition();
	E1.resetPos(16);
	E2.resetPos(14);
	E3.resetPos(18);
	return true;
};


bool GameOver(Player& pac, enemi& E1, enemi& E2, enemi& E3, bool& over, bool& MODE) {
	if (!MODE)
	{
		pac.setLives();
		pac.resetPosition();
	}

	
	E1.resetPos(16);
	E2.resetPos(14);
	E3.resetPos(18);
	if (pac.getLives() == 0)
	{
		over = true;
		return true;
	}
	else
		return false;

}

/////////////////////////// Dijkstra///////////////////

vector<vector<int>> Dijkstra(int Graph[COUNT][COUNT], int startNode)
{
	int costs[COUNT], previous[COUNT];
	bool visited[COUNT];
	
	// costs, previous, and visited
	for (int i = 0; i < COUNT; i++)
	{
		costs[i] = Graph[startNode][i];
		previous[i] = startNode;
		visited[i] = false;
	}
	// startNode
	costs[startNode] = 0;
	visited[startNode] = true;

	int count = 1, nextNode, minimumCost;
	while (count < COUNT)
	{
		// Find the minimum cost in order to visit a node.
		minimumCost = INFINITE;
		for (int i = 0; i < COUNT; i++)
			if ((costs[i] < minimumCost) && (visited[i] == false))
			{
				minimumCost = costs[i];
				nextNode = i;
			}
		// Visit the node.
		visited[nextNode] = true;
		// Update the costs of the children of the visited node.
		for (int i = 0; i < COUNT; i++)
			if ((minimumCost + Graph[nextNode][i] < costs[i]) && (visited[i] == false))
			{
				costs[i] = minimumCost + Graph[nextNode][i];
				previous[i] = nextNode;
			}
		count++;
	}
	// Fill the paths.
	int j;
	vector<vector<int>> paths;
	paths.resize(COUNT);
	for (int i = 0; i < COUNT; i++)
	{
		paths[i].push_back(i);
		if (i != startNode)
		{
			j = i;
			do
			{
				j = previous[j];
				paths[i].push_back(j);
			} while (j != startNode);
		}
	}
	return paths;
}
