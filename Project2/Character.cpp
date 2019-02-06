#include "Character.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;



Character::Character(string name, int level)
{
	Character::level = level;
	Character::name = name;
	/*
	if (level >= 16)
	{
		attackBonusPerRound.push_back(level);
		attackBonusPerRound.push_back(level - 5);
		attackBonusPerRound.push_back(level - 10);
		attackBonusPerRound.push_back(level - 15);
	}
	else if (level >= 11)
	{
		attackBonusPerRound.push_back(level);
		attackBonusPerRound.push_back(level - 5);
		attackBonusPerRound.push_back(level - 10);
	}
	else if (level >= 6)
	{
		attackBonusPerRound.push_back(level);
		attackBonusPerRound.push_back(level - 5);
	}
	else
	{
		attackBonusPerRound.push_back(level);
	}
	*/
	generateAbilityScores();

}

Character::~Character()
{

}

bool Character::validateNewCharacter()
{

	if ((curStr < 3 || curStr > 18) || (curDex < 3 || curDex > 18) || (curCon < 3 || curCon > 18) ||
		(curInt < 3 || curInt > 18) || (curWis < 3 || curWis > 18) || (curCha < 3 || curCha > 18))
		return false;
	return true;

}

void Character::hit(int damage)
{
	currentHitPoints = currentHitPoints - damage;
}


int Character::modifyAbility(int modifier)
{
	return static_cast<int>(floor((modifier - 10) / 2));
}

void Character::generateAbilityScores()
{
	/*
	curStr = rand() % (18 - 3 + 1) + 3;
	curDex = rand() % (18 - 3 + 1) + 3;
	curCon = rand() % (18 - 3 + 1) + 3;
	curInt = rand() % (18 - 3 + 1) + 3;
	curWis = rand() % (18 - 3 + 1) + 3;
	curCha = rand() % (18 - 3 + 1) + 3;
	*/

	curStr = generateRollAbilityScores();
	curDex = generateRollAbilityScores();
	curCon = generateRollAbilityScores();
	curInt = generateRollAbilityScores();
	curWis = generateRollAbilityScores();
	curCha = generateRollAbilityScores();

	aModStr = modifyAbility(curStr);
	aModDex = modifyAbility(curDex);
	aModCon = modifyAbility(curCon);
	aModInt = modifyAbility(curInt);
	aModWis = modifyAbility(curWis);
	aModCha = modifyAbility(curCha);

}

int Character::generateRollAbilityScores()
{
	Dice *d = new Dice();
	int rolls[4];
	int smallestIndex = 0; //Index of the smallest roll
	int smallestVal = 24; //Biggest possible roll with 4d6
	int sum = 0;

	for(int i = 0; i < 4; i++)
	{
		rolls[i] = d->roll("1d6");
		if(rolls[i] < smallestVal)
		{
			smallestIndex = i;
			smallestVal = rolls[i];
		}
	}

	rolls[smallestIndex] = 0;

	for(int i = 0; i < 4; i++)
	{
		sum += rolls[i];
	}

	return sum;
}

std::string Character::printCharDetailsSheet()
{
	std::stringstream s;

	s << "Name: " << name << " level: " << level << std::endl << std::endl
		<< "STR: " << curStr << std::endl
		<< "DEX: " << curDex << std::endl
		<< "CON: " << curCon << std::endl
		<< "INT: " << curInt << std::endl
		<< "WIS: " << curWis << std::endl
		<< "CHA: " << curCha << std::endl
		<< "HP: " << currentHitPoints << std::endl
		<< "Attack Bonus: " << attackBonus << std::endl
		<< "Attack Bonus 2: " << attackBonus2 << std::endl
		<< "Attack Bonus 3: " << attackBonus3 << std::endl
		<< "Attack Bonus 4: " << attackBonus4 << std::endl
	/*
	for (size_t i = 0; i < attackBonusPerRound.size() - 1; i++)
	{
		s << attackBonusPerRound[i] << "/";
	}
	s << attackBonusPerRound[attackBonusPerRound.size() - 1] << std::endl;
	*/
		<< "Damage Bonus: " << damageBonus << std::endl
		<< "Armor Class: " << armorClass << std::endl;

	return s.str();

}




void Character::increaseStat(int enh, string bonus)
{
	if (bonus == "STR") {
		curStr += enh;
	}
	if (bonus == "DEX") {
		curDex += enh;
	}
	if (bonus == "CON") {
		curCon += enh;
	}
	if (bonus == "INT") {
		curInt += enh;
	}
	if (bonus == "WIS") {
		curWis += enh;
	}
	if (bonus == "CHA") {
		curCha += enh;
	}
	if (bonus == "DMGBONUS") {
		damageBonus += enh;
	}


}

/*
bool Character::saveCharacter(std::string filename)
{
	std::ofstream f(filename, std::ios::out);

	if (f.is_open())
	{
		f << name << std::endl
			<< level << std::endl
			<< curStr << std::endl
			<< curDex << std::endl
			<< curCon << std::endl
			<< curInt << std::endl
			<< curWis << std::endl
			<< curCha << std::endl
			<< currentHitPoints << std::endl
			<< attackBonus << std::endl
			<< attackBonus2 << std::endl
			<< attackBonus3 << std::endl
			<< attackBonus4 << std::endl
			<< damageBonus << std::endl
			<< armorClass << std::endl;

		f.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool Character::loadCharacter(std::string filename)
{
	std::ifstream f(filename, std::ios::in);

	if (f.is_open())
	{
		f >> name;
		f >> level;
		f >> curStr;
		f >> curDex;
		f >> curCon;
		f >> curInt;
		f >> curWis;
		f >> curCha;
		f >> currentHitPoints;
		f >> attackBonus;
		f >> attackBonus2;
		f >> attackBonus3;
		f >> attackBonus4;
		f >> damageBonus;
		f >> armorClass;
		
		f.close();
		return true;
	}
	else
	{
		return false;
	}
}
*/

void Character::saveCharacter()
{
	string characterName;
	cout << "Please enter the name of the character that will be saved. (ex:Character.txt)";
	cin >> characterName;
	ofstream out(characterName);
	out << name << endl;
	out << currentHitPoints << endl;
	out << armorClass << endl;
	out << attackBonus << endl;
	out << attackBonus2 << endl;
	out << attackBonus3 << endl;
	out << attackBonus4 << endl;
	out << exp << endl;
	out << damageBonus << endl;
	out << level << endl;
	out << curStr << endl;
	out << curDex << endl;
	out << curCon << endl;
	out << curInt << endl;
	out << curWis << endl;
	out << curCha << endl;
	/*out << aModStr << endl;
	out << aModDex << endl;
	out << aModCon << endl;
	out << aModInt << endl;
	out << aModWis << endl;
	out << aModCha << endl;*/
}

void Character::LoadCharacter()
{
	string characterFile;

	cout << "Please enter name of the character file. (ex:Character.txt)" << endl;
	cin >> characterFile;
	/*std::ifstream input(characterFile);
	std::string line;
	getline(input, line);

	ifstream input(characterFile);
	string characterName;

	input.open(characterFile, ios::in);
	input >> line;
	*/
	ifstream file(characterFile);
	string str;
	//std::string file_contents;
	getline(file, str);
	name = str;
	getline(file, str);
	currentHitPoints = stoi(str);
	getline(file, str);
	armorClass = stoi(str);
	getline(file, str);
	attackBonus = stoi(str);
	getline(file, str);
	attackBonus2 = stoi(str);
	getline(file, str);
	attackBonus3 = stoi(str);
	getline(file, str);
	attackBonus4 = stoi(str);
	getline(file, str);
	exp = stoi(str);
	getline(file, str);
	damageBonus = stoi(str);
	getline(file, str);
	level = stoi(str);
	getline(file, str);
	curStr = stoi(str);
	getline(file, str);
	curDex = stoi(str);
	getline(file, str);
	curCon = stoi(str);
	getline(file, str);
	curInt = stoi(str);
	getline(file, str);
	curWis = stoi(str);
	getline(file, str);
	curCha = stoi(str);
	getline(file, str);
/*	aModStr = stoi(str);
	getline(file, str);
	aModDex = stoi(str);
	getline(file, str);
	aModCon = stoi(str);
	getline(file, str);
	aModInt = stoi(str);
	getline(file, str);
	aModWis = stoi(str);
	getline(file, str);
	aModCha = stoi(str);
	//while (getline(file, str)) {
	//	file_contents += str;
	//	file_contents.push_back('\n');

	//	cout << str<< "inside while" << endl;
	//	}
	cout << "end of load" << endl;
	*/
}

void Character::gainExp(int experience)
{
	exp += experience;
	if (exp >= 300)
	{
		if (level < 2)
			levelUp();
	}
	if (exp >= 900)
	{
		if (level < 3)
			levelUp();
	}
	if (exp >= 2700)
	{
		if (level < 4)
			levelUp();
	}
	if (exp >= 6500)
	{
		if (level < 5)
			levelUp();
	}
	if (exp >= 14000)
	{
		if (level < 6)
			levelUp();
	}
	if (exp >= 23000)
	{
		if (level < 7)
			levelUp();
	}
	if (exp >= 34000)
	{
		if (level < 8)
			levelUp();
	}
	if (exp >= 48000)
	{
		if (level < 9)
			levelUp();
	}
	if (exp >= 64000)
	{
		if (level < 10)
			levelUp();
	}
	if (exp >= 85000)
	{
		if (level < 11)
			levelUp();
	}
	if (exp >= 100000)
	{
		if (level < 12)
			levelUp();
	}
	if (exp >= 120000)
	{
		if (level < 13)
			levelUp();
	}
	if (exp >= 140000)
	{
		if (level < 14)
			levelUp();
	}
	if (exp >= 165000)
	{
		if (level < 15)
			levelUp();
	}
	if (exp >= 195000)
	{
		if (level < 16)
			levelUp();
	}
	if (exp >= 225000)
	{
		if (level < 17)
			levelUp();
	}
	if (exp >= 265000)
	{
		if (level < 18)
			levelUp();
	}
	if (exp >= 305000)
	{
		if (level < 19)
			levelUp();
	}
	if (exp >= 335000)
	{
		if (level < 20)
			levelUp();
	}
}
