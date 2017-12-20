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

class World {
public:
	World(int mapSize, Player* player_in);
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