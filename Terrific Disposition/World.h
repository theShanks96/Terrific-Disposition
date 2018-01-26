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

#include "Tile.h"
#include "AcceptableTile.h"
#include "CautiousTile.h"
#include "DeadlyTile.h"

#include "Player.h"
#include "DataStructs.h"


//! The game proper, a world holding all the tiles that the player will come into contact
class World {
public:

	//! Constructor for the World
	//! @param mapSize_in Used to insstantiate the side length of the square world
	//! @param player_in Used to keep track of player information
	World(int mapSize_in, Player* player_in);
	~World();

	int c_mapSizeInt;
	int c_plotMaxInt;

	int2d c_playerStartPosition;
	std::vector<int2d> v_plotPositions;
	std::vector<int2d> v_dangerousCentres;

	std::vector<std::string> v_pendingOutputStrings;

	void handleCommand(std::string& command_in);
	void addPlotPoint();

	std::string currentTileClassification();
	bool isSameTileProgression();

	void processTile();

private:
	std::string c_lastClassificationString;
	std::string c_currentClassificationString;

	int c_totalHonestReliableInt;
	int c_totalHonestUnreliableInt;
	int c_totalDishonestReliableInt;

	Player* ptr_player;

	std::vector<std::vector<Tile*>> v_worldTiles;
	

	std::vector<namedString> v_thematicAdjectives;
	std::vector<namedString> v_thematicVerbs;
	std::vector<namedString> v_thematicNouns;
};