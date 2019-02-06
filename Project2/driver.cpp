#pragma warning(disable: 4996)
#include "Map.h"
#include "Campaign.h"
#include "MapObserver.h"
#include <vector>
#include <iostream>
#include "InputManager.h"
#include "Windows.h"
#include "MapEditor.h"
#include "Dice.h"
#include "Item.h"
#include <ctime>
#include <conio.h>
#include <string>
#include "Fighter.h"
#include"Character.h"
#include "CharacterDecorator.h"
#include "FighterDirector.h"
#include "BullyFighterBuilder.h"
#include "NimbleFighterBuilder.h"
#include "TankFighterBuilder.h"
#include"ConsoleLogger.h"
#include<cstdlib>

using namespace std;

void moveOnMap(Map m) {
	bool end = false;
	cout << "Now try moving around the map." << endl;
	showMap(m);
	cout << "Use the arrow keys or w, a, s, d to move your character '@'." << endl;
	//cout << m.showMap() << "Use the arrow keys or w, a, s, d to move your character '@'." << endl;
	vector<InputEvent> events;
	// Map w, a, s, d keypresses to Input Events
	events.push_back(InputEvent("w", 0x57));
	events.push_back(InputEvent("s", 0x53));
	events.push_back(InputEvent("a", 0x41));
	events.push_back(InputEvent("d", 0x44));
	// Map arrow keypresses to Input Events
	events.push_back(InputEvent("w", VK_UP));
	events.push_back(InputEvent("s", VK_DOWN));
	events.push_back(InputEvent("a", VK_LEFT));
	events.push_back(InputEvent("d", VK_RIGHT));
	//This one should always be last
	events.push_back(InputEvent("q", VK_ESCAPE));

	string dir;

	while (end == false && dir != "q")
	{
		dir = InputManager::getInput(events);
		end = m.move(dir.at(0), m);
		showMap(m);

	}
	if (end == true)
	{
		cout << "You've reached the door. press q to quit" << endl;
		//Finding where character is located, then opening corresponding map associated to that door spot.

	}

	cin.get();
	cin.get();

}
int main()
{	
	srand(time(NULL));
	CConsoleLoggerEx items;
	items.Create("Backpack and equipped items");
	items.cls(CConsoleLoggerEx::COLOR_BACKGROUND_BLUE);
	/*int a;

	Character *c = new Fighter("Ahmed", 1);		//Creating a fighter.
	cout << c->printCharDetailsSheet() << endl;
	c = new Item(c, "weapon", { 5,3 }, { "DMGBONUS","ATKBONUS" });
	c->wear("weapon");	//Equipping the fighter with a weapon.
	c = new Item(c, "shield", { 10 }, { "ARMORCLASS" });
	c->wear("shield");	//Equipping the fighter with a shield.
	cout << c->printCharDetailsSheet() << "weapon equipped" << endl;
	cout << "Displaying equipped items." << endl;
	c->displayEquipped();
	c->remove("weapon");	//Unequipping the fighter's weapon.
	c = new Item(c, "shield", { 10 }, { "ARMORCLASS" });
	c->wear("shield");	//Trying to equip 2 shields on the fighter. Stats should remain the same.
	cout << c->printCharDetailsSheet() << "ARMORCLASS stat remains unchanged. weapon removed." << endl;
	cout << "Displaying equipped items after removal." << endl;
	c->displayEquipped();
	cin >> a;
	*/
	MapEditor me = MapEditor();
	bool end = false;
	Map m;
	Character *c = new Fighter();
	Campaign camp = Campaign();
	int choice;	//Used for user input.
	string str;	//Used for user input.
	do {
		//system("CLS");
		cout << "Welcome to the menu! Please select an option and hit enter." << endl;
		cout << "1.Load a character." << endl;
		cout << "2.Load a map." << endl;
		cout << "3.Load a campaign." << endl;
		cout << "4.Play a test campaign." << endl;
		cout << "5.Create and save a character." << endl;
		cout << "6.Create/Edit maps." << endl;
		cout << "7.Create/Edit campaigns." << endl;
		cout << "8.Play!" << endl;
		cin >> choice;

		//If statements represent each menu choice.
		if (choice == 1) {	//Load a character.
			//me.createMap(m);
			c->LoadCharacter();
			cout << c->printCharDetailsSheet();
		}
		else if (choice == 2) {	//Load a map.
			//vector<Map> maps;
			/*me.createMap(m);
			m.name = "spawn";
			me.createMap(m2);
			m2.name = "forest";
			me.createMap(m3);
			m3.name = "dungeon";
			me.createMap(m4);
			m4.name = "last";
			c.addMaptoCampaign("spawn", m);
			c.addMaptoCampaign("forest", m2);
			c.addMaptoCampaign("dungeon", m3);
			c.addMaptoCampaign("last", m4);
			c.saveCampaign();
			*/
			//	me.createCampaign(camp);
				//m = camp.mapOfGameMaps.find("spawn.txt")->second;
			m = me.loadMap();
			camp.addMaptoCampaign(m.name, m);
			cout << "The map has been loaded!" << endl;
		}

		else if (choice == 3) {	//Load a campaign.
			cout << "What is the name of the campaign you want to load? (ex:Campaign.txt)" << endl;
			cin >> str;
			camp.loadCampaign(str);
			m = camp.mapOfGameMaps.find("spawn.txt")->second;
			cout << "Campaign has been loaded!";
		}
		else if (choice == 4) {	//Play a test campaign.
			camp.loadCampaign("testCampaign.txt");
			m = camp.mapOfGameMaps.find("spawn.txt")->second;
		}
		else if (choice == 5) {	//Create and save a character.
			FighterDirector director;
			FighterBuilder* bullyBuilder;
			FighterBuilder* nimbleBuilder;
			FighterBuilder* tankBuilder;
		//	Character *bully;		//Creating a fighter.
		//	Character *nimble;
		//	Character *tank;
		//	Character *c;
			//bullyBuilder = new BullyFighterBuilder;
		//	director.setFighterBuilder(bullyBuilder);
		//	director.constructFighter();
		//	c = director.getFighter();
		//	c = new Item(c);



			cout << "What type of fighter would you like to create?" << endl
				<< "Press 1 for Bully, 2 for Nimble or 3 for Tank." << endl;
			int fighterType;
			cin >> fighterType;
			if (fighterType == 1)
			{
				bullyBuilder = new BullyFighterBuilder;
				director.setFighterBuilder(bullyBuilder);
				director.constructFighter();
				//Fighter* bully = director.getFighter();
				c = director.getFighter();
				cout << "Enter a name: ";
				std::string name;
				cin >> name;
				c->name = "Bully Fighter " + name;
				cout << c->printCharDetailsSheet() << endl;
				c->gainExp(300);
				cout << c->printCharDetailsSheet() << endl;
				c->gainExp(100000);
				cout << c->printCharDetailsSheet() << endl;
			/*	cout << "LEVELING UP.." << endl;
				c->levelUp();
				cout << c->printCharDetailsSheet() << endl;
				cout << "LEVELING UP.." << endl;
				c->levelUp();
				cout << c->printCharDetailsSheet() << endl;
				cout << "LEVELING UP.." << endl;
				bully->levelUp();
				cout << bully->printCharDetailsSheet() << endl;
				cout << "LEVELING UP.." << endl;
				bully->levelUp();
				cout << bully->printCharDetailsSheet() << endl;

				bully = new Item(bully, "shield", { 10 }, { "ARMORCLASS" });
				bully->wear("shield");

				cout << bully->printCharDetailsSheet() << endl;
				*/
			}
			if (fighterType == 2)
			{
				nimbleBuilder = new NimbleFighterBuilder;
				director.setFighterBuilder(nimbleBuilder);
				director.constructFighter();
				c= director.getFighter();
				cout << "Enter a name: ";
				std::string name;
				cin >> name;
				c->name = "Nimble Fighter " + name;
				cout << c->printCharDetailsSheet() << endl;
			/*	cout << "LEVELING UP.." << endl;
				nimble->levelUp();
				cout << nimble->printCharDetailsSheet() << endl;
				cout << "LEVELING UP.." << endl;
				nimble->levelUp();
				cout << nimble->printCharDetailsSheet() << endl;
				cout << "LEVELING UP.." << endl;
				nimble->levelUp();
				cout << nimble->printCharDetailsSheet() << endl;
				cout << "LEVELING UP.." << endl;
				nimble->levelUp();
				cout << nimble->printCharDetailsSheet() << endl;
				nimble->levelUp();
				cout << nimble->printCharDetailsSheet() << endl;
				nimble = new Item(nimble, "weapon", { 5,3 }, { "DMGBONUS","ATKBONUS" });
				nimble->wear("weapon");
				cout << "WEARING ITEM WEAPON.. " << endl;
				cout << nimble->printCharDetailsSheet() << endl;
				nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp(); nimble->levelUp();
				cout << nimble->printCharDetailsSheet() << endl;
				nimble->remove("weapon");
				cout << nimble->printCharDetailsSheet() << endl;
				*/

			}
			if (fighterType == 3)
			{
				tankBuilder = new TankFighterBuilder;
				director.setFighterBuilder(tankBuilder);
				director.constructFighter();
				c = director.getFighter();
				cout << "Enter a name: ";
				std::string name;
				cin >> name;
				c->name = "Tank Fighter " + name;
				cout << c->printCharDetailsSheet() << endl;
			/*	cout << "LEVELING UP.." << endl;
				tank->levelUp();
				cout << tank->printCharDetailsSheet() << endl;
				cout << "LEVELING UP.." << endl;
				tank->levelUp();
				cout << tank->printCharDetailsSheet() << endl;
				cout << "LEVELING UP.." << endl;
				tank->levelUp();
				cout << tank->printCharDetailsSheet() << endl;
				cout << "LEVELING UP.." << endl;
				tank->levelUp();
				cout << tank->printCharDetailsSheet() << endl;
				*/
			}

			cout << "Do you want to save your character? Press 1 to save or 2 to go back to the menu." << endl;
			cin >> choice;
			if (choice == 1)
				c->saveCharacter();
		}
		else if (choice == 6) {	//Create/Edit maps.
			m = me.createMap(m);
		}
		else if (choice == 7) {	//Create/Edit campaigns.
			me.createCampaign(camp);
		}
		else if (choice == 8) {	//Play the game with the loaded characters and maps.

		}
	} while (choice != 8);
	cout << "Outputting campaign maps" << endl;
	// Iterate through all elements in std::map
	std::map<std::string, Map>::iterator it = camp.mapOfGameMaps.begin();
	while (it != camp.mapOfGameMaps.end())
	{
		std::cout << it->first << " :: " << it->second << std::endl;
		it++;
	}

	/*
	cout << "Now creating a fighter" << endl;


	// Make a new Fighter
	//Character* fighter1 = new Fighter("Manuel");
	Fighter f("Manuel", 1);
//	CharacterObserver o1(f);
//	CharacterObserver o2(f);
	Item i1 = Item("weapon", { 5 }, { "DMGBONUS" });
	Item i2 = Item("helmet", { 1 }, { "INT" });
	ItemContainer bag = ItemContainer("bag");
	addItem(bag,i1);
	addItem(bag,i2);
	displayInventory(bag);
		f.printCharDetailsSheet();
	//f.wearItem(i1);


	//	_getch();
	//	f.wearItem(*i2);
	cout << f.printCharDetailsSheet() << endl;
	// Some input so the window doesn't close right away
	*/
	int currentMap = 0;
	bool continueGame = true;
	do {
		//showMap(c.mapOfGameMaps.find("spawn")->second);
		showMap(m);
		cout << m.name << endl;
		cout << "Use the arrow keys or w, a, s, d to move your character '@'." << endl;
		//cout << m.showMap() << "Use the arrow keys or w, a, s, d to move your character '@'." << endl;
		vector<InputEvent> events;
		// Map w, a, s, d keypresses to Input Events
		events.push_back(InputEvent("w", 0x57));
		events.push_back(InputEvent("s", 0x53));
		events.push_back(InputEvent("a", 0x41));
		events.push_back(InputEvent("d", 0x44));
		events.push_back(InputEvent("i", 0x49));
		// Map arrow keypresses to Input Events
		events.push_back(InputEvent("w", VK_UP));
		events.push_back(InputEvent("s", VK_DOWN));
		events.push_back(InputEvent("a", VK_LEFT));
		events.push_back(InputEvent("d", VK_RIGHT));
		//events.push_back(InputEvent("i", VK_EXECUTE));
		//This one should always be last
		events.push_back(InputEvent("q", VK_ESCAPE));
		

		string dir;

		while (end == false && dir != "q")
		{
			dir = InputManager::getInput(events);
			end = m.move(dir.at(0), m);
			showMap(m);
		}
		if (end == true)
		{
			cout << "You've reached the door. Moving onto the next map." << endl;
/*			if (c.numberOfMaps != currentMap) {
				if (c.mapNames[currentMap] == "last")
					continueGame = false;
				else {
					cout << c.mapNames[currentMap + 1] << endl;
					m = c.mapOfGameMaps.find(c.mapNames[currentMap + 1])->second;
					end = false;
					currentMap += 1;
				}
			}*/
			//Finding where character is located, then opening corresponding map associated to that door spot.
		/*	if (m.name == "spawn") {
				m = c.mapOfGameMaps.find("forest")->second;
				end = false;
			}
			else if (m.name == "forest") {
				m = c.mapOfGameMaps.find("dungeon")->second;
				end = false;
			}
			else if (m.name == "dungeon") {
				m = c.mapOfGameMaps.find("last")->second;
				end = false;
			}
			else if (m.name == "last") {
				cout << "Congratulations! You beat the game." << endl;
				continueGame = false;
			}
			*/

			if (currentMap == camp.mapNames.size() - 1) {
				cout << "Congratulations! You beat the game." << endl;
				cin >> choice;
				continueGame = false;
				
			}

			else {
				currentMap += 1;
				m = camp.mapOfGameMaps.find(camp.mapNames[currentMap])->second;
				end = false;
			}
		}

		cin.get();
		cin.get();
	} while (continueGame);
	cin >> choice;
	return 0;
}





/*
int main() {

	int n;

	srand(static_cast<unsigned int>(time(0))); //reset srand to give a different number everytime
	Dice d;

	std::cout << "Rolling a d100 4 times." << endl;
	n = d.roll("4d100");
	std::cout << "Result: " << n << endl;

	std::cout << "Rolling a d10 5 times." << endl;
	n = d.roll("5d10");
	std::cout << "Result: " << n << endl;

	std::cout << "Rolling a d20 9 times." << endl;
	n = d.roll("9d20");
	std::cout << "Result: " << n << endl;

	std::cout << "Rolling a d6 1 time." << endl;
	n = d.roll("1d6");
	std::cout << "Result: " << n << endl;


	system("PAUSE");

	return 0;

};

*/

