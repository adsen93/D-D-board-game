#include "Campaign.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include"MapEditor.h"
using namespace std;

Campaign::Campaign() {

}

Campaign::Campaign(string s) {
	name = s;
}

void Campaign::saveCampaign()
{
	string campaignFile;
	cout << "Please enter the name of the campaign that will be saved. (ex:Campaign.txt)";
	cin >> campaignFile;
	ofstream out(campaignFile);  // file.txt can be any name that your file might have
	

	for (unsigned int i = 0; i < mapNames.size(); i++)
	{
			out << mapNames[i]; // setw(n) -- n means that your string will have a field of 'n' spaces reserved
		out << "\n";
	}


}

void Campaign::loadCampaign()
{
	string campaignFile;
	cout << "Please enter name of campaign file. (ex:Campaign.txt)" << endl;
	cin >> campaignFile;
	std::ifstream input(campaignFile);
	std::string line;
	input.open(campaignFile,ios::in);
	input >> line;
	cout << "before while loop" << endl;

	std::ifstream file(campaignFile);
	std::string str;
	std::string file_contents;
	
	while (std::getline(file,str)) {
		file_contents += str;
		file_contents.push_back('\n');
		mapNames.push_back(str);
	//	cout << str<< "inside while" << endl;
	}
	for (unsigned int i = 0; i < mapNames.size(); i++) {
		cout << mapNames[i] << endl;
	}
	//while (!input.eof()) {
	//	mapNames.push_back(line);
	//	input >> line;
	//	cout << "inside while loop" << endl;
	//}
	//for (unsigned int i = 0; i < mapNames.size(); i++) {
	//	cout << mapNames[i] << endl;
	//}
	cout << mapNames.size();
	cin >> campaignFile;
	input.close();
	numberOfMaps = mapNames.size();
	Map m;
	MapEditor me;
	
	//for (unsigned int i = 0; i < mapNames.size(); i++) {
//		m = me.loadMap(mapNames[0]);
//		addMaptoCampaign(mapNames[0], m);
//		m = me.loadMap(mapNames[1]);
//		addMaptoCampaign(mapNames[1], m);
	//}
//	cout << mapOfGameMaps.find(mapNames[0])->second;
//	cout << mapOfGameMaps.find(mapNames[1])->second;
	for (unsigned int i = 0; i < mapNames.size(); i++) {
		m = me.loadMap(mapNames[i]);
		loadMaptoCampaign(mapNames[i], m);
		cout << mapOfGameMaps.find(mapNames[i])->second;
	}
	cin >> campaignFile;
	//getline(input, line);
	//for (int n; input >> n; ) {
	//	mapNames.push_back(n);
	//}
	//mapNames.push_back(line);
}

void Campaign::loadCampaign(string campaignFile)
{
	std::ifstream input(campaignFile);
	std::string line;
	input.open(campaignFile, ios::in);
	input >> line;

	std::ifstream file(campaignFile);
	std::string str;
	//std::string file_contents;

	while (std::getline(file, str)) {
	//	file_contents += str;
	//	file_contents.push_back('\n');
		mapNames.push_back(str);
		//	cout << str<< "inside while" << endl;
	}

	//while (!input.eof()) {
	//	mapNames.push_back(line);
	//	input >> line;
	//	cout << "inside while loop" << endl;
	//}
	//for (unsigned int i = 0; i < mapNames.size(); i++) {
	//	cout << mapNames[i] << endl;

	input.close();
	numberOfMaps = mapNames.size();
	Map m;
	MapEditor me;

	//for (unsigned int i = 0; i < mapNames.size(); i++) {
	//		m = me.loadMap(mapNames[0]);
	//		addMaptoCampaign(mapNames[0], m);
	//		m = me.loadMap(mapNames[1]);
	//		addMaptoCampaign(mapNames[1], m);
	//}
	//	cout << mapOfGameMaps.find(mapNames[0])->second;
	//	cout << mapOfGameMaps.find(mapNames[1])->second;
	for (unsigned int i = 0; i < mapNames.size(); i++) {
		m = me.loadMap(mapNames[i]);
		loadMaptoCampaign(mapNames[i], m);
	}
	//getline(input, line);
	//for (int n; input >> n; ) {
	//	mapNames.push_back(n);
	//}
	//mapNames.push_back(line);
}

void Campaign::loadMaptoCampaign(string mapName, Map m)
{
	mapOfGameMaps.insert(std::make_pair(mapName, m));
}

void Campaign::addMaptoCampaign(string mapName, Map m) {
	mapOfGameMaps.insert(std::make_pair(mapName, m));
	mapNames.push_back(mapName + ".txt");
}



