#include <iostream>
#include "Item.h"
#include"CharacterItemContainers.h"

using namespace std;

Item::Item() {

}
void Item::wear(string itemType)
{	//First check if item type is already equipped.
	for (unsigned int i = 0; i < equipped.v.size(); i++) {
		if (equipped.v[i].type == itemType) {
			cout << "Item slot is already occupied. Please remove it first to replace it." << endl;
			return;
		}
	}
	//This for loop goes through all of the item's enhancement bonuses and applies it to the character's stats.
	for (unsigned int i = 0; i < bonus.size(); i++) {
		if (bonus[i] == "STR") {
			curStr += enhancement[i];
		}
		if (bonus[i] == "DEX") {
			curDex += enhancement[i];
		}
		if (bonus[i] == "CON") {
			curCon += enhancement[i];
		}
		if (bonus[i] == "INT") {
			curInt += enhancement[i];
		}
		if (bonus[i] == "WIS") {
			curWis += enhancement[i];
		}
		if (bonus[i] == "CHA") {
			curCha += enhancement[i];
		}
		if (bonus[i] == "DMGBONUS") {
			damageBonus += enhancement[i];
		}
		if (bonus[i] == "ATKBONUS") {
			attackBonus += enhancement[i];
		}
		if (bonus[i] == "ARMORCLASS") {
			armorClass += enhancement[i];
		}

	}
	//After increasing the character's stats, add the item to the equipped item container.
	addItem(equipped, *this);
}
//Method that removes an equipped item.
void Item::remove(string itemType)
{	//Finds index i of the item which is stored in the equipped ItemContainer.
	for (unsigned int i = 0; i < equipped.v.size(); i++) {
		if (equipped.v[i].type == itemType) {
			//After the item has been found at index i, remove all associated enhancement bonuses with that item.
			for (unsigned int j = 0; j < equipped.v[i].bonus.size(); j++) {
				if (equipped.v[i].bonus[j] == "STR") {
					curStr -= equipped.v[i].enhancement[j];
				}
				if (equipped.v[i].bonus[j] == "DEX") {
					curDex -= equipped.v[i].enhancement[j];
				}
				if (equipped.v[i].bonus[j] == "CON") {
					curCon -= equipped.v[i].enhancement[j];
				}
				if (equipped.v[i].bonus[j] == "INT") {
					curInt -= equipped.v[i].enhancement[j];
				}
				if (equipped.v[i].bonus[j] == "WIS") {
					curWis -= equipped.v[i].enhancement[j];
				}
				if (equipped.v[i].bonus[j] == "CHA") {
					curCha -= equipped.v[i].enhancement[j];
				}
				if (equipped.v[i].bonus[j] == "DMGBONUS") {
					damageBonus -= equipped.v[i].enhancement[j];
				}
				if (equipped.v[i].bonus[j] == "ATKBONUS") {
					attackBonus -= equipped.v[i].enhancement[j];
				}
				if (equipped.v[i].bonus[j] == "ARMORCLASS") {
					armorClass -= equipped.v[i].enhancement[j];
				}

			}
			//After removing all the increased stats, remove the item from the equipped item container.
			removeItem(equipped, i);
		}


	}

}

//Method that displays the items in the character's backpack.
void Item::displayBackPack()
{
	displayInventory(backpack);
}

//Method that displays the equipped items of the character.
void Item::displayEquipped()
{
	displayInventory(equipped);
}
Item::Item(string type, vector <int> enhancement, vector <string> bonus)
{
	this->type = type;
	this->enhancement = enhancement;
	this->bonus = bonus;
}

//Method that returns a vector of all the enhancement & bonus of an item.
vector <string> itemInfo(Item &i)
{
	vector <string> info;
	string s;
	for (unsigned int j = 0; j < i.enhancement.size(); j++) {
		s = i.enhancement[j];
		s = s + i.bonus[j];
		info.push_back(s);
	}
	return info;
}

//Method that adds an enhancement to an item.It also checks if the enhancement is legal.
void addEnhancement(Item &i, int enhancement, string bonus) {
	i.enhancement.push_back(enhancement);
	i.bonus.push_back(bonus);
	if (!(itemCheck(i))) {
		i.enhancement.pop_back();
		i.bonus.pop_back();

	}
}

string getType(Item &i) {
	return i.type;
}

vector<int> getEnhancement(Item &i) {
	return i.enhancement;
}

vector<string>getBonus(Item &i) {
	return i.bonus;
}
//Method that checks if an item is valid (gives a legal bonus).
bool itemCheck(Item &i) {
	int b = i.bonus.size();
	if (i.type == "helmet") {
		for (int j = 0; j < b; j++)
			if (i.bonus[j] == "INT" || i.bonus[j] == "WIS" || i.bonus[j] == "ARMORCLASS")
				return true;
	}

	if (i.type == "armor") {
		for (int j = 0; j < b; j++)
			if (i.bonus[j] == "ARMORCLASS")
				return true;
	}

	if (i.type == "shield") {
		for (int j = 0; j < b; j++)
			if (i.bonus[j] == "ARMORCLASS")
				return true;
	}

	if (i.type == "ring") {
		for (int j = 0; j < b; j++)
			if (i.bonus[j] == "ARMORCLASS" || i.bonus[j] == "STR" || i.bonus[j] == "CON" || i.bonus[j] == "WIS" || i.bonus[j] == "CHA")
				return true;
	}

	if (i.type == "belt") {
		for (int j = 0; j < b; j++)
			if (i.bonus[j] == "STR" || i.bonus[j] == "CON")
				return true;
	}

	if (i.type == "boots") {
		for (int j = 0; j < b; j++)
			if (i.bonus[j] == "ARMORCLASS" || i.bonus[j] == "DEX")
				return true;
	}

	if (i.type == "weapon") {
		for (int j = 0; j < b; j++)
			if (i.bonus[j] == "ATKBONUS" || i.bonus[j] == "DMGBONUS")
				return true;
	}
	return false;


}


ostream & operator<<(ostream &stream, Item &i) {
	stream << "Item: " << i.type << " ";
	for (unsigned int j = 0; j < i.enhancement.size(); j++) {
		stream << i.enhancement[j] << " " << i.bonus[j] << " ";
	}
	stream << endl;
	return stream;
}

void Item::levelUp()
{
	Dice *d = new Dice();
	currentHitPoints += d->roll("1d10") + aModCon;
	level++;

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
}


