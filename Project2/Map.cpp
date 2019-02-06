#include "Map.h"
#include "Dice.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include<vector>
using namespace std;

static const int MAX_DOOR = 1;		//Number of maximum doors generated by the random map
Map::Map()
{
}

Map::Map(int l, int h) {
	// Initialize variables
	length = l + 2;
	height = h + 2;


	// Create 2D array
	mArr = new char*[length];
	for (int i = 0; i < length; i++)
		mArr[i] = new char[length];

	// Fill the array with empty spaces (=)
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < height; j++)
			mArr[i][j] = '=';
		// Set up initial walls around
		for (int i = 0; i < height; i++) {
			mArr[i][0] = '|';
			mArr[i][height - 1] = '|';
		}
		for (int j = 0; j < length; j++) {
			mArr[0][j] = '-';
			mArr[length - 1][j] = '-';
		}
		// Set up corners
		mArr[0][0] = '+';
		mArr[length - 1][0] = '+';
		mArr[0][height - 1] = '+';
		mArr[length - 1][height - 1] = '+';
	}


}

void showMap(Map m)
{
	for (int i = 0; i < m.length; i++)
	{
		for (int j = 0; j < m.height; j++)
		{
			cout << m.mArr[i][j];
		}
		cout << endl;
	}
}


string Map::showMap() {
	// Create string stream to create data
	stringstream sstream;
	for (int i = 0; i < length; i++)
		sstream << endl << endl << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < length; j++)
			sstream << mArr[i][j] << " ";
		sstream << endl << endl;
	}

	return sstream.str();
}

bool validatePath(Map m)
{
	for (int i = 0; i < m.length; i++)
	{
		for (int j = 0; j < m.height; j++)
		{
			if (m.mArr[i][j] == 'd') // 'd' is for door
			{
				return true;
			}
		}
	}
	return false;
}

void fillCell(int x, int y, char obj, Map &m)
{
	if (obj == 'd') {
		Pair doorIndices;
		doorIndices.x = x;
		doorIndices.y = y;
		m.insertDoorIndices(doorIndices);
	}
	m.mArr[x][y] = obj;
}

bool isOccupied(int x, int y, Map m)
{
	if (m.mArr[x][y] != '=')
	{
		return true;
	}
	return false;
}

int getLength(Map m)
{
	return m.length;
}
int getHeight(Map m)
{
	return m.height;
}

char** getMapElements(Map map)
{
	return map.mArr;
}

void setLength(int x, Map map) {
	map.length = x;
}

void setHeight(int y, Map map) {
	map.height = y;
}


void makeRandomMap(Map &m)
{	
	int characterStart = 0;
	int maxDoor = 0;
	srand(time(NULL));
	for (int i = 1; i < getLength(m) - 1; i++)
	{

		for (int j = 1; j < getHeight(m) - 1; j++)
		{

			int num = (rand() % 100);
			if (num < 80)
			{
				fillCell(i, j, '=', m); //'=' is free space
			}
			else if (num >= 80 && num < 85)
			{
				if (characterStart == 0) {
					fillCell(i, j, '@', m);	//'@' is for character
					characterStart++;
				}
				else if (maxDoor < MAX_DOOR)	
				{
					fillCell(i, j, 'd', m); // 'd' is for door
					maxDoor++;
				}
				else
					fillCell(i, j, '=', m); // free space for limit door
			}

			else if (num >= 85 && num < 90) {
				fillCell(i, j, 'c', m);	//'c' is for chest
			}

			else if (num >= 90 && num < 95) {
				fillCell(i, j, 'm', m);	//m is for monster
			}

			else
			{
				fillCell(i, j, '*', m);	//* is for wall
			}

		}

	}
}

ostream & operator<<(ostream &stream, Map &m)
{
	// TODO: insert return statement here
	stream << m.showMap();
	return stream;
}




// Move the character in the game
bool Map::move(char dir, Map m)
{
	bool firstMove = true;
	for (int i = 1; i < getLength(m) - 1; i++)
	{

		for (int j = 1; j < getHeight(m) - 1; j++)
		{
			if (m.mArr[i][j] == '@')
			{
				tempX = i;
				tempY = j;
			}
			if (m.mArr[i][j] == 'm')
			{
				tempsX = i;
				tempsY = j;
			}
		}
	}
	playerX = tempX;
	playerY = tempY;
	monsterX = tempsX;
	monsterY = tempsY;
	cout << "monster " << monsterX << " " << monsterY << endl;
	mArr[tempX][tempY] = current;
	//mArr[tempsX][tempsY] = currents;


	//srand(time(NULL));
//	int nums= (rand() % 100);

	if (dir == 'd' || dir == 'D')
	{

		tempY = tempY + 1;

	}
	else if (dir == 'w' || dir == 'W')
	{

		tempX = tempX - 1;

	}
	else if (dir == 'a' || dir == 'A')
	{

		tempY = tempY - 1;

	}
	else if (dir == 's' || dir == 'S')
	{
		tempX = tempX + 1;

	}
	else if (dir == 'i' || dir == 'I') {

	}
	//	cout << nums << endl;
		// Moveable location
	if (mArr[tempX][tempY] == '=') {
		playerX = tempX;
		playerY = tempY;
		if (firstMove)
			fillCell(playerX, playerY, '=', m);
		/*if (mArr[tempsX][tempsY] == '=') {
			monsterX = tempsX;
			monsterY = tempsY;
			cout << "X : " << tempsX << "  Y: " << tempsY << endl;
		}*/
	}
	else if (mArr[tempX][tempY] == 'm')
	{
		char mchoice;
		
			do
			{
				cout << " Monster is engaging, What do you want to do ?" << endl;
				cout << "(f)igth  or (r)un?  // to escape need a roll of d20 and higher than 13" << endl;
				cout << " What do you want to do ?" << endl;
				cin >> mchoice;
				if (mchoice == 'f')
				{
					int n;
					Dice d = Dice();
					std::cout << "Rolling a d10 1 times." << endl;
					n = d.roll("1d10");
					std::cout << "Result: " << n << endl;
					if (n > 6)
					{
						mArr[tempX][tempY] = '=';
						cout << " You defeated the monster !!" << endl;
						break;
					}
					else
					{
						cout << "You damage the monster." << endl;
					}

					cout << " Keep figthing ? press (f) else (r) to run  " << endl;
					cin >> mchoice;
				}
				else if (mchoice == 'r')
				{
					int n;
					Dice d = Dice();
					std::cout << "Rolling a d20 1 times." << endl;
					n = d.roll("1d20");
					std::cout << "Result: " << n << endl;
					if (n > 13)
					{
						cout << " You escaped the monster." << endl;
						break;
					}
					else
					{
						cout << " You didn't escape, need to roll higher than 13, now engage with monster !" << endl;
						mchoice = 'f';
					}
				}

			} while (mchoice == 'f');
		}
	/*	else if (mchoice == 'r')
		{
			int n;
			Dice d = Dice();
			std::cout << "Rolling a d10 1 times." << endl;
			n = d.roll("1d20");
			std::cout << "Result: " << n << endl;
			if (n > 13)
			{
				cout << " You escaped the monster." << endl;
			}
			else
			{
				cout << " You didn't escape, need to roll higher than 13, now engage with monster !" << endl;
				mchoice = 'f';
			}
		}

	}*/
	else if (mArr[tempX][tempY] == 'c')
	{
		openChest(dir);
	}
		
	// Moved onto door goes to next map.
	else if (mArr[tempX][tempY] == 'd') {
		playerX = tempX;
		playerY = tempY;
		current = mArr[playerX][playerY];
		mArr[playerX][playerY] = '@';
		notify();
		//for (unsigned int i = 0; i < m.doorIndices.size(); i++) {	//Finding the door, which will open the next map.
		//	if (playerX == m.doorIndices[i].x && playerY == m.doorIndices[i].y) {
		//	}
		//}
		return true;
	}
	/*if (dir == 'a' || dir == 's' || dir == 'd' || dir == 'w')
	{	
		srand(time(NULL));
		int nums= (rand() % 100);
		if (nums < 25)
		{
			tempsY = tempsY + 1;
		}
		else if (nums >= 25 && nums < 50)
		{
			tempsY = tempsY - 1;
		}
		else if (nums >= 50 && nums < 75)
		{
			tempsX = tempsX + 1;
		}
		else if (nums >= 75 && nums < 100)
		{
			tempsX = tempsX - 1;
		}

	}*/
	
	current = mArr[playerX][playerY];
	//currents = mArr[monsterX][monsterY];
	mArr[playerX][playerY] = '@';
	//mArr[monsterX][monsterY] = 'm';
	notify();
	return false;
}

void Map::insertDoorIndices(Pair doorIndices1)
{
	doorIndices.push_back(doorIndices1);
}

Item Map::openChest(char dir)
{

		cout << " Open the chest?  (Y)es/(N)o" << endl;
		
		char choice;
		cin >> choice;
		if (choice == 'N' || choice == 'n')
		{
			cout << "Left without the opening the chest" <<endl;
		}
		else if (choice == 'Y' || choice == 'y')
		{
			cout << "chestX: " << tempX << "  chestY:  " << tempY << endl;
			if (dir == 'd' || dir == 's' || dir == 'a' || dir == 'w')
			{
				mArr[tempX][tempY] = 'o';
				cout << "Chest opened" << endl;
				Dice d = Dice();
				std::cout << "Rolling a d100 1 times." << endl;
				int n = d.roll("1d100");
				std::cout << "Result: " << n << endl;

				if (n < 50)
				{
					cout << " SHIT ITEM !!" << endl;
				}
				else if (n >= 50 && n < 75)
				{
					cout << " OKAY ITEM !!" << endl;
				}
				else if (n >= 75 && n < 98)
				{
					cout << " GREAT ITEM !!" << endl;
				}
				else if (n >= 98 && n < 100)
				{
					cout << " LEGENDARY ITEM !!" << endl;
				}
			}
			
			
			
		}
		return Item();
}


