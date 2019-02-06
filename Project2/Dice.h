/*
The codes creates a dice class. the user inputs a regular expression xdy
where x is the number of rolls and dy the sides of the die. The program accepts the expression
and splits it so that the nedded values can be passed in the Rolled class. the total of the rolls
is added and returned to the user
*/

#pragma once

#include <iostream>
#include <cstdlib> //for random numbers generator
#include <sstream>  //string stream
#include <string>   //string library
#include <ctime>    //reset rand for a different number everytime

using namespace std;

class Dice
{

public:

	Dice();
	int roll(string expression);
	~Dice();


private:
	string expr;



};

