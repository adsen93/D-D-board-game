#include "MapEditor.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

MapEditor::MapEditor() {

}

Map MapEditor::createMap(Map &m) {
	int choice;	//This is used to accept general input from the user.
	int mapSize;	//The size of the map.
	int mapX, mapY;	//These will be used to determine which map spot the user would like to edit.
	char mapElement;	//This will be used to determine which map element the user would like to place in the selected spot (door, chest, monster, wall).
	//Map m;	//Map that is being created.
	cout << "Welcome to the map builder.Please enter 1 to create a new map or 2 to load a map" << endl;
	cin >> choice;
	if (choice == 2) {
		m = loadMap();
		cout << "The map is loaded!" << endl;
		showMap(m);
		//m.showMap();
		mapSize = getLength(m) - 2;
	}
	//if (choice == 1) {
	else {
		cout << "Would you like to start from scratch (1) or from a randomly generated map (2)? " << endl;
		cin >> choice;
		cout << "Please enter the map size nxn" << endl;
		cin >> mapSize;
		m = Map(mapSize, mapSize);
		if (choice == 2)
			makeRandomMap(m);
		cout << "The map is created!" << endl;
		showMap(m);
		//m.showMap();
	}	
	cout << "Do you want to edit the map?Press 1 to edit or 2 to exit the map builder." << endl;
	cin >> choice;
	if (choice == 1)
		do {
			cout << "Please enter the indices (pair of x,y) for which map space you would like to edit" << endl;
			do {
				cin >> mapX;
				cin >> mapY;
				if (mapX > mapSize || mapY > mapSize)
					cout << "The indices given are too big. Please stay within the size of the map " << mapSize << "x" << mapSize << endl;
			} while (mapX > mapSize || mapY > mapSize);

			cout << "Please enter the element that you want to enter in the cell :@(character) d(door), c(chest), =(free space), m(monster), *(wall) " << endl;
			do {
				cin >> mapElement;
				if (!(mapElement == '@' || mapElement == 'd' || mapElement == 'c' || mapElement == '=' || mapElement == 'm' || mapElement == '*'))
					cout << "Invalid map element. Please enter one of the valid choices : d(door), c(chest), =(free space), m(monster), *(wall)" << endl;
			} while (!(mapElement == '@' || mapElement == 'd' || mapElement == 'c' || mapElement == '=' || mapElement == 'm' || mapElement == '*'));

			fillCell(mapX, mapY, mapElement, m);
			cout << "Element added to the map. Press 1 to view the map." << endl;
			cin >> choice;
			if (choice == 1)
			{showMap(m);
			//	m.showMap();
			}
			cout << "Would you like to continue editing the map? Press 1 to continue or 2 to stop." << endl;
			cin >> choice;
			

		} while (choice == 1);
	//}
		cout << "Do you want to save the map?Press 1 to save or 2 to exit." << endl;
		cin >> choice;
		if (choice == 1)
			saveMap(m);
		if (validatePath(m))
			return m;
		else {
			int x, y;
			cout << "The map does not have a door. Please select the indices (x,y) to add the door." << endl;
			cin >> x;
			cin >> y;
			fillCell(x, y, 'd', m);
			return m;
		}
}

void MapEditor::saveMap(Map m) {
	char** temp;
	string mapFile;
	temp = getMapElements(m);
	cout << "Please enter the name of the map that will be saved. (ex:Maps.txt)";
	cin >> mapFile;
	ofstream out(mapFile);  // file.txt can be any name that your file might have
	if (!(validatePath(m)))		//Checking to see if the map is valid. If it is not then it is not saved.
	{
		showMap(m);
		cout << "saving map" << endl;
		return;
	}

	for (int i = 0; i < getLength(m); i++)
	{
		for (int j = 0; j < getHeight(m); j++)
			out << setw(1) << temp[i][j]; // setw(n) -- n means that your string will have a field of 'n' spaces reserved
		out << "\n";
	}



}

Map MapEditor::loadMap() {
	string mapFile;
	cout << "Please enter name of map file. (ex:Maps.txt)" << endl;
	cin >> mapFile;
	std::ifstream input(mapFile);
	std::string line;
	getline(input, line);
	int size = line.length();
	Map m = Map(size - 2, size - 2);	//-2 because 2 spaces are added for the walls and corners.
	m.name = mapFile;
	
	//Creating map based on input from file.
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fillCell(i, j, line.at(j), m);	//Setting element into indice (i,j).
		}
		getline(input, line);
	}
	if (validatePath(m))		//Checking to see if the loaded map is valid. If it is not, then an empty map will be created.
		return m;
	else{
		cout << "The map was not valid and could not be loaded. An empty map will be created instead.";
		m = Map(size - 2, size - 2);
		return m;
	}

}

Map MapEditor::loadMap(string mapName)
{
	std::ifstream input(mapName);
	std::string line;
	getline(input, line);
	int size = line.length();
	Map m = Map(size - 2, size - 2);	//-2 because 2 spaces are added for the walls and corners.


										//Creating map based on input from file.
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fillCell(i, j, line.at(j), m);	//Setting element into indice (i,j).
		}
		getline(input, line);
	}
	if (validatePath(m))		//Checking to see if the loaded map is valid. If it is not, then an empty map will be created.
		return m;
	else {
		cout << "The map was not valid and could not be loaded. An empty map will be created instead.";
		m = Map(size - 2, size - 2);
		return m;
	}
}

void MapEditor::createCampaign(Campaign &c){
	int choice;
//	int x, y;
	//int /*numberOfMaps*/ = 0;
	string name;
	vector<Map> maps;
	maps.push_back(Map());
	Map m =  Map();
	//Campaign c;
	MapEditor me = MapEditor();
	cout << "Welcome to the campaign editor. Press 1 to create a new campaign or 2 to load a campaign." << endl;
	cin >> choice;
	if (choice == 1) {
		cout << "Please enter the name of the campaign.";
		cin >> name;
		c = Campaign(name);
		cout << "Creating the spawning map of the game." << endl;
		me.createMap(maps[0]);
		cout << "Now adding first map into the campaign." << endl;
		maps[0].name = "spawn";
		c.addMaptoCampaign("spawn", maps[0]);	//Adding the spawn map to the campaign. This is the first map that the player will see when the game starts.
		cout << c.mapOfGameMaps.find("spawn")->second <<  endl;
		
		cout << "Spawn map has been added! Press 1 to add the next map in the campaign or 2 to finish." << endl;
		cin >> choice;
	//	c./*numberOfMaps*/ += 1;
		c.mapNames.push_back("spawn");
		if (choice == 1) {
			maps.push_back(Map());
			cout << "What is the name of the map?" << endl;
			cin >> name;
			c.mapNames.push_back(name);
			maps[/*numberOfMaps*/1].name = name;
			me.createMap(maps[/*numberOfMaps*/1]);
			c.addMaptoCampaign(maps[/*numberOfMaps*/1].name, maps[/*numberOfMaps*/1]);
			cout << c.mapOfGameMaps.find(maps[/*numberOfMaps*/1].name)->second << endl;
		//	c./*numberOfMaps*/ += 1;
			
//			cout << c.mapOfGameMaps.find("forest")->second << "2nd map"<< endl;
		/*	Map m2 = Map();
			cout << "What is the name of the map?" << endl;
			cin >> name;
			m2.name = name;
			me.createMap(m2);
			c.addMaptoCampaign(m2.name,m2);
			cout << c.mapOfGameMaps.find(m2.name)->second << endl;
			*/
		}
		/*if (choice == 1) {
			cout << "These are the indices of the doors.Please enter the pair of (x,y) indices to pick the door." << endl; 
			for (unsigned int i = 0; i < m.doorIndices.size(); i++) {
				cout << "Door " << (i + 1) << " indices: " << m.doorIndices[i] << endl;
			}
			bool stop = false;
			do {
				cin >> x;
				cin >> y;
				for (unsigned int i = 0; i < m.doorIndices.size(); i++) {
					if (x == m.doorIndices[i].x && y == m.doorIndices[i].y) {
						stop = true;
						cout << "Door has been properly identified. Now creating new map for door." << endl;
						//delete &m;
						Map m2 = me.createMap(m2);
						cout << "Please enter the name of the map." << endl;
						cin >> name;
						m.name = name;
						m.doorIndices[i].mapName = name;
						c.addMaptoCampaign(m.name, m);
					}
				}
				cout << "Door indices not found.Please enter door indices from the list above." << endl;
			} while (!stop);
		
		}
			
			
		*/
		
	}

	else {
		c.loadCampaign();
	}
}

