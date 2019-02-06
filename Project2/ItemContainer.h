#pragma once
#include <iostream>
#include <vector>
#include"Item.h"


using namespace std;

class ItemContainer {
public:
	string name;
	vector<Item> v;



	ItemContainer(string name);
	ItemContainer();
	friend Item getItem(ItemContainer &i, unsigned int slot);
	friend void addItem(ItemContainer &i, Item a);
	friend void removeItem(ItemContainer &i, unsigned int slot);
	friend void displayInventory(ItemContainer &i);
	friend string getName(ItemContainer &i);
	friend vector<Item> getAllItems(ItemContainer &i);
};

