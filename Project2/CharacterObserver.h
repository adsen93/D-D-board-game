#pragma once

#include "Observer.h"
#include "Character.h"


class CharacterObserver : public Observer
{
public:
	CharacterObserver(Character& c);
	virtual ~CharacterObserver();

	virtual void Update(Observable* o);

	static int serial;

private:
	std::string name;
	Character* subject;
};