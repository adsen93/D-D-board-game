#pragma once
#include "Map.h"
#include<string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;


class Campaign {
public: string name;
		 vector <string> mapNames;
		 int numberOfMaps = 0;
		 std::map<std::string, Map> mapOfGameMaps; 
	
	Campaign();
	Campaign(string s);
	void saveCampaign();
	void loadCampaign();
	void loadCampaign(string campaignName);
	void loadMaptoCampaign(string mapName, Map m);
	void addMaptoCampaign(string mapName, Map m);
};
