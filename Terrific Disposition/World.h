#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

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

	int c_mapSize;
	int c_plotMax;

	int2d c_playerStartPosition;
	std::vector<int2d> v_plotPositions;
	std::vector<int2d> v_dangerousCentres;

	std::vector<std::string> v_pendingOutput;

	void handleCommand(std::string& command_in);
	void addPlotPoint();

private:

	Player* ptr_player;

	std::vector<std::vector<Tile*>> v_worldTiles;
	

	std::vector<namedString> v_thematicAdjectives;
	std::vector<namedString> v_thematicVerbs;
	std::vector<namedString> v_thematicNouns;
};