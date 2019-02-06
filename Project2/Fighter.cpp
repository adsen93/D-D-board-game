#include "Fighter.h"

const int Fighter::HP_START = 15;
const int Fighter::HP_PER_LEVEL = 6;

Fighter::Fighter(std::string name, int level) : Character(name, level)
{
	generateAttributes();
}

Fighter::~Fighter()
{
}

void Fighter::generateAttributes()
{
	currentHitPoints = HP_START + ((level - 1) * HP_PER_LEVEL) + curCon;

	armorClass = 10 + aModDex;

	attackBonus = aModStr + static_cast<int>(Character::level / 2);

	damageBonus = aModStr;
}

void Fighter::levelUp()
{
	Dice *d = new Dice();
	currentHitPoints += d->roll("1d10") + aModCon;
	++level;

	if (level >= 16)
	{
		attackBonus4 += 1;
		attackBonus3 += 1;
		attackBonus2 += 1;
		attackBonus += 1;
	}
	else if (level >= 11)
	{
		attackBonus3 += 1;
		attackBonus2 += 1;
		attackBonus += 1;
	}
	else if (level >= 6)
	{
		attackBonus2 += 1;
		attackBonus += 1;

	}
	else
		attackBonus += 1;

	
	
	
	
	/*
	for (size_t i = 0; i < attackBonusPerRound.size(); i++)
	{
		attackBonusPerRound[i] += 1;
	}
	if (level == 6 || level == 11 || level == 16)
	{
		attackBonusPerRound.push_back(1);
	}
	*/
}