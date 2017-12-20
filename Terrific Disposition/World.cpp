#include "World.h"

World::World(int mapSize_in, Player* player_in) {
	c_mapSize = mapSize_in;
	c_plotMax = (int)(c_mapSize * 0.75f);
	ptr_player = player_in;

	/*
	v_worldTiles.reserve(mapSize_in);
	for (int i = 0; i < v_worldTiles.size(); i++) {
		v_worldTiles.at(i).reserve(mapSize_in);
	}
	*/

	//	Creating the map, although empty for the moment
	std::vector<Tile*> m_temp;
	m_temp.reserve(c_mapSize);
	for (int i = 0; i < c_mapSize; i++)
		m_temp.push_back(nullptr);

	v_worldTiles.reserve(c_mapSize);
	for (int i = 0; i < c_mapSize; i++)
		v_worldTiles.push_back(m_temp);

	//	Generating the danger zones for the map
	if (c_mapSize == 16) {
		std::vector<int2d> v_positions;
		v_positions.reserve(4);
		v_positions.push_back(int2d(7, 3));
		v_positions.push_back(int2d(7, 11));
		v_positions.push_back(int2d(3, 7));
		v_positions.push_back(int2d(11, 7));

		for (int2d l_position : v_positions) {
			v_worldTiles.at(l_position.s_first).at(l_position.s_second) = new DeadlyTile();

			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					//	Ensure that the DeadlyTile is skipped over
					if(v_worldTiles.at(l_position.s_first + i).at(l_position.s_second + j) == nullptr)
						v_worldTiles.at(l_position.s_first + i).at(l_position.s_second + j) = new CautiousTile();
				}
			}
		}

	}
	else if (c_mapSize == 32) {

		std::vector<int2d> v_positions;
		v_positions.reserve(4);
		v_positions.push_back(int2d(15, 7));
		v_positions.push_back(int2d(15, 23));
		v_positions.push_back(int2d(7, 15));
		v_positions.push_back(int2d(23, 15));

		for (int2d l_position : v_positions) {

			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
						v_worldTiles.at(l_position.s_first + i).at(l_position.s_second + j) = new DeadlyTile();
				}
			}

			for (int i = -3; i < 4; i++) {
				for (int j = -3; j < 4; j++) {
					//	Ensure that the DeadlyTiles are skipped over
					if (v_worldTiles.at(l_position.s_first + i).at(l_position.s_second + j) == nullptr )
						v_worldTiles.at(l_position.s_first + i).at(l_position.s_second + j) = new CautiousTile();
				}
			}
		}

	}
	else if (c_mapSize == 64) {

		std::vector<int2d> v_positions;
		v_positions.reserve(4);
		v_positions.push_back(int2d(31, 15));
		v_positions.push_back(int2d(31, 47));
		v_positions.push_back(int2d(15, 31));
		v_positions.push_back(int2d(47, 31));

		for (int2d l_position : v_positions) {

			for (int i = -4; i < 5; i++) {
				for (int j = -4; j < 5; j++) {
					v_worldTiles.at(l_position.s_first + i).at(l_position.s_second + j) = new DeadlyTile();
				}
			}

			for (int i = -8; i < 9; i++) {
				for (int j = -8; j < 9; j++) {
					//	Ensure that the DeadlyTiles are skipped over
					if (v_worldTiles.at(l_position.s_first + i).at(l_position.s_second + j) == nullptr)
						v_worldTiles.at(l_position.s_first + i).at(l_position.s_second + j) = new CautiousTile();
				}
			}
		}

	}
	
	//	Picking the player's start location
	bool m_success = false;
	while (!m_success) {

		srand(time(NULL));
		int2d m_startQuadrant = int2d((rand() % 2), (rand() % 2));
		srand(time(NULL));
		int2d m_startPosition = int2d((rand() % 4) + (m_startQuadrant.s_first * (mapSize_in - 4)),
			(rand() % 4) + (m_startQuadrant.s_second * (mapSize_in - 4))	);

		if (v_worldTiles.at(m_startPosition.s_first).at(m_startPosition.s_second) == nullptr) {
			c_playerStartPosition = m_startPosition;
			m_success = true;
		}

	}

	
	ptr_player->c_position = c_playerStartPosition;
	v_plotPositions.reserve(c_plotMax);

	v_worldTiles.at(c_playerStartPosition.s_first).at(c_playerStartPosition.s_second) = new CautiousTile("The compromised hideout from before.");
	v_pendingOutput.push_back(ptr_player->c_name + ", you've left the hideout and your journey begins");
}

World::~World() {
	for (int i = 0; i < v_worldTiles.size(); i++) {
		v_worldTiles.at(i).erase(v_worldTiles.at(i).begin(), v_worldTiles.at(i).end());
	}
	v_worldTiles.erase(v_worldTiles.begin(), v_worldTiles.end());
	delete this;
}

void World::handleCommand(std::string& command_in) {

}

void World::addPlotPoint() {
	if (v_plotPositions.size() < c_plotMax) {
		float2d m_plotPosition(0, 0);
		bool m_success = false;

		while (!m_success) {

			while (m_plotPosition.s_first == 0) {
				srand(time(NULL));
				m_plotPosition.s_first = rand() % 2 - 1;
			}

			while (m_plotPosition.s_second == 0) {
				srand(time(NULL));
				m_plotPosition.s_first = rand() % 2 - 1;
			}

			do {
				srand(time(NULL));
				m_plotPosition.s_first = (int)(((int)m_plotPosition.s_first * rand() % (c_mapSize / 4)) + ptr_player->c_position.s_first);
				srand(time(NULL));
				m_plotPosition.s_second = (int)(((int)m_plotPosition.s_second * rand() % (c_mapSize / 4)) + ptr_player->c_position.s_second);
			} while (m_plotPosition.s_first >= c_mapSize || m_plotPosition.s_second >= c_mapSize 
						&&	m_plotPosition.s_first < 0 || m_plotPosition.s_second < 0);



			if (v_worldTiles.at(m_plotPosition.s_first).at(m_plotPosition.s_second) == nullptr) {
				v_worldTiles.at(m_plotPosition.s_first).at(m_plotPosition.s_second) = new AcceptableTile();
				v_worldTiles.at(m_plotPosition.s_first).at(m_plotPosition.s_second)->c_availablePlot = false;
				m_success = true;
			}
			else if (v_worldTiles.at(m_plotPosition.s_first).at(m_plotPosition.s_second)->c_availablePlot) {
				
				if(v_worldTiles.at(m_plotPosition.s_first).at(m_plotPosition.s_second)->c_classification == "acceptable")
					v_worldTiles.at(m_plotPosition.s_first).at(m_plotPosition.s_second) = new AcceptableTile();
				else if (v_worldTiles.at(m_plotPosition.s_first).at(m_plotPosition.s_second)->c_classification == "cautious")
					v_worldTiles.at(m_plotPosition.s_first).at(m_plotPosition.s_second) = new CautiousTile();
					
				v_worldTiles.at(m_plotPosition.s_first).at(m_plotPosition.s_second)->c_availablePlot = false;
				m_success = true;
			}
		}
	}
}