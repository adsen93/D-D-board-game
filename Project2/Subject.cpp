#include <list>
#include <iterator>
#include "Observer.h"
#include"Subject.h"
#include "Map.h"
using namespace std;

void Subject::attach(Observer* o)
{
	observers.push_back(o);
}

void Subject::detach(Observer* o)
{
	observers.remove(o);
}

void Subject::notify()
{
	list<Observer*>::iterator iter;
	for (iter = observers.begin(); iter != observers.end(); ++iter)
	{
		(*iter)->update(this);
	}//cause we just craete like a random map we dont give it the map we are using
}