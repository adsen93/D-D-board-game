#include <iostream>
#include "ItemContainer.h"
//#include "Item.h"
#include <string>

using namespace std;

ItemContainer::ItemContainer() {

}

ItemContainer::ItemContainer(string name) {
	this->name = name;
	vector<Item> v;
}

string getName(ItemContainer &i) {
	return i.name;
}

vector<Item> getAllItems(ItemContainer &i) {
	return i.v;
}

//Method that returns an item from the container.
Item getItem(ItemContainer &i, unsigned int slot) {
	return i.v[slot];
}

//Method that adds items to the container.
void addItem(ItemContainer &i, Item a) {
	i.v.push_back(a);
}
void removeItem(ItemContainer & i, unsigned int slot)
{
	i.v.erase(i.v.begin() + slot);
}
//Displays items from the inventory.
void displayInventory(ItemContainer &i) {
	for (unsigned j = 0; j < i.v.size(); j++)
		cout << "Item slot " << j << " " << i.v[j] << endl;
}

