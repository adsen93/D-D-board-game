#include "Dice.h"



Dice::Dice()
{
}

int Dice::roll(string expression)
{
	string expr = expression;
	int total = 0;
	int num = 0;
	int x, y;
	char d;

	//parsing expression for the attributes nedded
	std::istringstream iss(expression);
	iss >> x;
	iss >> d;
	iss >> y;

	//roll and add total
	for (int i = 0; i < x; i++) {
		num = (rand() % y) + 1;
		total += num;
	}

	return total;
}


Dice::~Dice()
{
}
