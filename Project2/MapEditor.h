#include <iostream>
#include <string>
#include "Map.h"
#include "Campaign.h"
using namespace std;

class MapEditor {
public:
	MapEditor();
	Map createMap(Map& m);
	void saveMap(Map m);
	Map loadMap();
	Map loadMap(string mapName);
	void createCampaign(Campaign& c);
};