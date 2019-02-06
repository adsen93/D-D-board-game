#pragma once
#include<string>
#include <iostream>
#include<vector>
#include"Dice.h"
using namespace std;

class Character {
public:
	virtual ~Character();
	virtual void wear(string itemType) = 0;
	virtual void remove(string itemType) = 0;
	virtual void generateAttributes() = 0;
	virtual void displayBackPack() = 0;
	virtual void displayEquipped() = 0;
	virtual void levelUp() = 0;
	int modifyAbility(int mod);
	void generateAbilityScores();
	int generateRollAbilityScores();
	Character(string name = "Default Name", int level = 1);
	void hit(int);
	bool validateNewCharacter();
	std::string printCharDetailsSheet();
	void increaseStat(int enh, string bonus);
	//bool Character::saveCharacter(std::string filename);
	//bool Character::loadCharacter(std::string filename);
	void saveCharacter();
	void LoadCharacter();
	void gainExp(int experience);

	std::string name;
	int currentHitPoints;
	int armorClass;
	int attackBonus;
	int attackBonus2=0;
	int attackBonus3=0;
	int attackBonus4=0;
//	std::vector<int> attackBonusPerRound;
	int exp = 0;
	int damageBonus;
	int level;

	int curStr,
		curDex,
		curCon,
		curInt,
		curWis,
		curCha;

	int aModStr,
		aModDex,
		aModCon,
		aModInt,
		aModWis,
		aModCha;
	
};
