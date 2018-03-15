#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <iostream>
#include <algorithm>
#include <utility>
#include <math.h>

#include "Tile.h"
#include "AcceptableTile.h"
#include "CautiousTile.h"
#include "DeadlyTile.h"

#include "Player.h"
#include "DataStructs.h"

#include "ResourceManager.h"
#include "NaturalLogicManager.h"


//! The game proper, a world holding all the tiles that the player will come into contact
class World {
public:
	ResourceManager* ptr_resourceManager;
	NaturalLogicManager* ptr_naturalLogicManager;
	commandProfile c_commandProfile;
	Player* ptr_player;

	int c_mapSizeInt;
	int c_plotMaxInt;
	
	int2d c_playerStartPosition;
	std::vector<int2d> v_plotPositions;
	
	std::vector<std::string> v_pendingOutputStrings;
	
	int c_totalHonestReliableInt;
	int c_totalHonestUnreliableInt;
	int c_totalDishonestReliableInt;
	
private:
	std::string c_lastClassificationString;
	std::string c_currentClassificationString;

	std::vector<std::vector<Tile*>> v_worldTiles;	

public:
	//! Constructor for the World
	//! @param mapSize_in Used to insstantiate the side length of the square world
	//! @param player_in Used to keep track of player information
	World(int mapSize_in, Player* player_in);
	World(int mapSize_in, Player* player_in, int2d startPos_in);
	~World();
	

	void linkResourceManager(ResourceManager* resource_in);
	void linkNaturalLogicManager(NaturalLogicManager* natural_in);

	void handleCommand(std::string& command_in);
	void addPlotPoint();

	std::string currentTileClassification();
	bool isSameTileProgression();

	void processTile();
		
};