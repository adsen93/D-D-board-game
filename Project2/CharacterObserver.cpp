#include "CharacterObserver.h"

#include <iostream>


CharacterObserver::CharacterObserver(Character& c)
{
	subject = &c;
	subject->attach(this);
	name = "View " + std::to_string(serial);
	++serial;
}


CharacterObserver::~CharacterObserver()
{
	subject->detach(this);
	subject = NULL;
}

void CharacterObserver::Update(Observable* o)
{
	if (subject == o)
	{
		std::cout << "****************Update " + name + "****************" << std::endl
			<< subject->printCharDetailsSheet();
	}
}

int CharacterObserver::serial = 0;