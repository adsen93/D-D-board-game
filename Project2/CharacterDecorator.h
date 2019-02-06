#pragma once
#include "Character.h"

class CharacterDecorator : public Character {
protected:
	Character *decoratedCharacter;

public:
	CharacterDecorator() {};
	CharacterDecorator(Character *decoratedCharacter) {
		this->decoratedCharacter = decoratedCharacter;
		this->name = decoratedCharacter->name;
		this->currentHitPoints = decoratedCharacter->currentHitPoints;
		this->armorClass = decoratedCharacter->armorClass;
		this->attackBonus = decoratedCharacter->attackBonus;
		this->attackBonus2 = decoratedCharacter->attackBonus2;
	    this->attackBonus3 = decoratedCharacter->attackBonus3;
		this->attackBonus4 = decoratedCharacter->attackBonus4;
		this->exp = decoratedCharacter->exp;
		this->damageBonus = decoratedCharacter->damageBonus;
		this->level = decoratedCharacter->level;

		this->curStr = decoratedCharacter->curStr;
		this->curDex = decoratedCharacter->curDex;
		this->curCon = decoratedCharacter->curCon;
		this->curInt = decoratedCharacter->curInt;
		this->curWis = decoratedCharacter->curWis;
		this->curCha = decoratedCharacter->curCha;

		this->aModStr = decoratedCharacter->aModStr;
		this->aModDex = decoratedCharacter->aModDex;
		this->aModCon = decoratedCharacter->aModCon;
		this->aModInt = decoratedCharacter->aModInt;
		this->aModWis = decoratedCharacter->aModWis;
		this->aModCha = decoratedCharacter->aModCha;

	}

	void generateAttributes() {};
	void wear(string itemType) {
		decoratedCharacter->wear(itemType);
	}

	void remove(string itemType) {
		decoratedCharacter->remove(itemType);
	}

	void displayBackPack() {
		decoratedCharacter->displayBackPack();
	}

	void displayEquipped() {
		decoratedCharacter->displayEquipped();
	}
};