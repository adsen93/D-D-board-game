#pragma once
#include <list>
//#include "Map.h"
using namespace std;

class Observer;

class Subject {
public:
	virtual ~Subject() {};
	virtual void attach(Observer* o);
	virtual void detach(Observer*  o);
	virtual void notify();

protected:
	Subject() {};

private:
	list<Observer*> observers;
};
