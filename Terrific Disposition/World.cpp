#include "World.h"

World::World(int mapSize_in, Player* player_in) {
	
	c_mapSizeInt = mapSize_in;
	c_plotMaxInt = (int)(c_mapSizeInt * 0.75f);
	ptr_player = player_in;
	c_commandProfile = commandProfile(0, 0, 0, 0, 0, 0);

	/*
	v_worldTiles.reserve(mapSize_in);
	for (int i = 0; i < v_worldTiles.size(); i++) {
		v_worldTiles.at(i).reserve(mapSize_in);
	}
	*/

	//	Creating the map, although empty for the moment
	std::vector<Tile*> m_temp;
	m_temp.reserve(c_mapSizeInt);
	for (int i = 0; i < c_mapSizeInt; i++)
		m_temp.push_back(nullptr);

	v_worldTiles.reserve(c_mapSizeInt);
	for (int i = 0; i < c_mapSizeInt; i++)
		v_worldTiles.push_back(m_temp);

	//	Generating the danger zones for the map
	if (c_mapSizeInt == 16) {
		std::vector<int2d> v_positions;
		v_positions.reserve(4);
		v_positions.push_back(int2d(7, 3));
		v_positions.push_back(int2d(7, 11));
		v_positions.push_back(int2d(3, 7));
		v_positions.push_back(int2d(11, 7));

		for (int2d l_position : v_positions) {
			v_worldTiles.at(l_position.s_firstInt).at(l_position.s_secondInt) = new DeadlyTile();

			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					//	Ensure that the DeadlyTile is skipped over
					if(v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) == nullptr)
						v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) = new CautiousTile();
				}
			}
		}

	}
	else if (c_mapSizeInt == 32) {

		std::vector<int2d> v_positions;
		v_positions.reserve(4);
		v_positions.push_back(int2d(15, 7));
		v_positions.push_back(int2d(15, 23));
		v_positions.push_back(int2d(7, 15));
		v_positions.push_back(int2d(23, 15));

		for (int2d l_position : v_positions) {

			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
						v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) = new DeadlyTile();
				}
			}

			for (int i = -3; i < 4; i++) {
				for (int j = -3; j < 4; j++) {
					//	Ensure that the DeadlyTiles are skipped over
					if (v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) == nullptr )
						v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) = new CautiousTile();
				}
			}
		}

	}
	else if (c_mapSizeInt == 64) {

		std::vector<int2d> v_positions;
		v_positions.reserve(4);
		v_positions.push_back(int2d(31, 15));
		v_positions.push_back(int2d(31, 47));
		v_positions.push_back(int2d(15, 31));
		v_positions.push_back(int2d(47, 31));

		for (int2d l_position : v_positions) {

			for (int i = -4; i < 5; i++) {
				for (int j = -4; j < 5; j++) {
					v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) = new DeadlyTile();
				}
			}

			for (int i = -8; i < 9; i++) {
				for (int j = -8; j < 9; j++) {
					//	Ensure that the DeadlyTiles are skipped over
					if (v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) == nullptr)
						v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) = new CautiousTile();
				}
			}
		}

	}
		
	//	Picking the player's start location
	bool m_success = false;
	while (!m_success) {

		//srand(time(NULL));
		//int2d m_startQuadrant = int2d((rand() % 2), (rand() % 2));
		//srand(time(NULL));
		//int2d m_startPosition = int2d((rand() % 4) + (m_startQuadrant.s_firstString * (mapSize_in - 4)),
		//	(rand() % 4) + (m_startQuadrant.s_secondString * (mapSize_in - 4))	);


		std::random_device m_randomDevice;
		std::mt19937 m_mt(m_randomDevice());
		std::uniform_int_distribution<int> m_quadDist(0, 1);
		int2d m_startQuadrant(m_quadDist(m_mt), m_quadDist(m_mt));
		std::uniform_int_distribution<int> m_startDist(0, 3);
		int2d m_startPosition = int2d((m_startDist(m_mt)) + (m_startQuadrant.s_firstInt * (mapSize_in - 4)),
										(m_startDist(m_mt)) + (m_startQuadrant.s_secondInt * (mapSize_in - 4))	);

		if (v_worldTiles.at(m_startPosition.s_firstInt).at(m_startPosition.s_secondInt) == nullptr) {
			c_playerStartPosition = m_startPosition;
			m_success = true;
		}

	}

	
	ptr_player->c_positionInt2d = c_playerStartPosition;
	v_plotPositions.reserve(c_plotMaxInt);

	v_pendingOutputStrings.push_back("");
	v_pendingOutputStrings.push_back("Commands: Look, Equip, Inspect, Interact <person>");
	v_pendingOutputStrings.push_back("Commands: Move <North/East/South/West> ");
	v_pendingOutputStrings.push_back("");
	v_pendingOutputStrings.push_back("To interact with a person/thing, refer to them by their name.");
	v_pendingOutputStrings.push_back("Don't recognise a word? Inspect <word> might help define it for you.");
	v_pendingOutputStrings.push_back("");
	
	v_worldTiles.at(c_playerStartPosition.s_firstInt).at(c_playerStartPosition.s_secondInt) = new CautiousTile(true);
	v_pendingOutputStrings.push_back(ptr_player->c_nameString + ", you've left the hideout and your journey begins");

	// Initialise the remainder of the map with acceptable tiles
	for (int i = 0; i < c_mapSizeInt; i++) {
		for (int j = 0; j < c_mapSizeInt; j++) {
			if (v_worldTiles.at(i).at(j) == nullptr)
				v_worldTiles.at(i).at(j) = new AcceptableTile();
		}
	}

	//	Using the current player's position, set up where the first plot point will be.
	addPlotPoint();


	c_lastClassificationString = currentTileClassification();
	c_currentClassificationString = c_lastClassificationString;
}

World::World(int mapSize_in, Player* player_in, int2d startPos_in) {


	//	This is used when loading a saved game

	c_mapSizeInt = mapSize_in;
	c_plotMaxInt = (int)(c_mapSizeInt * 0.75f);
	ptr_player = player_in;
	c_commandProfile = commandProfile(0, 0, 0, 0, 0, 0);
	
	//	Creating the map, although empty for the moment
	std::vector<Tile*> m_temp;
	m_temp.reserve(c_mapSizeInt);
	for (int i = 0; i < c_mapSizeInt; i++)
		m_temp.push_back(nullptr);

	v_worldTiles.reserve(c_mapSizeInt);
	for (int i = 0; i < c_mapSizeInt; i++)
		v_worldTiles.push_back(m_temp);

	//	Generating the danger zones for the map
	if (c_mapSizeInt == 16) {
		std::vector<int2d> v_positions;
		v_positions.reserve(4);
		v_positions.push_back(int2d(7, 3));
		v_positions.push_back(int2d(7, 11));
		v_positions.push_back(int2d(3, 7));
		v_positions.push_back(int2d(11, 7));

		for (int2d l_position : v_positions) {
			v_worldTiles.at(l_position.s_firstInt).at(l_position.s_secondInt) = new DeadlyTile();

			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					//	Ensure that the DeadlyTile is skipped over
					if (v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) == nullptr)
						v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) = new CautiousTile();
				}
			}
		}

	}
	else if (c_mapSizeInt == 32) {

		std::vector<int2d> v_positions;
		v_positions.reserve(4);
		v_positions.push_back(int2d(15, 7));
		v_positions.push_back(int2d(15, 23));
		v_positions.push_back(int2d(7, 15));
		v_positions.push_back(int2d(23, 15));

		for (int2d l_position : v_positions) {

			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) = new DeadlyTile();
				}
			}

			for (int i = -3; i < 4; i++) {
				for (int j = -3; j < 4; j++) {
					//	Ensure that the DeadlyTiles are skipped over
					if (v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) == nullptr)
						v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) = new CautiousTile();
				}
			}
		}

	}
	else if (c_mapSizeInt == 64) {

		std::vector<int2d> v_positions;
		v_positions.reserve(4);
		v_positions.push_back(int2d(31, 15));
		v_positions.push_back(int2d(31, 47));
		v_positions.push_back(int2d(15, 31));
		v_positions.push_back(int2d(47, 31));

		for (int2d l_position : v_positions) {

			for (int i = -4; i < 5; i++) {
				for (int j = -4; j < 5; j++) {
					v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) = new DeadlyTile();
				}
			}

			for (int i = -8; i < 9; i++) {
				for (int j = -8; j < 9; j++) {
					//	Ensure that the DeadlyTiles are skipped over
					if (v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) == nullptr)
						v_worldTiles.at(l_position.s_firstInt + i).at(l_position.s_secondInt + j) = new CautiousTile();
				}
			}
		}

	}

	//	Setting the player's start location	
	c_playerStartPosition = startPos_in;
	v_plotPositions.reserve(c_plotMaxInt);

	v_pendingOutputStrings.push_back("");
	v_pendingOutputStrings.push_back("Commands: Look, Equip, Inspect, Interact <person>");
	v_pendingOutputStrings.push_back("Commands: Move <North/East/South/West> ");
	v_pendingOutputStrings.push_back("");
	v_pendingOutputStrings.push_back("To interact with a person/thing, refer to them by their name.");
	v_pendingOutputStrings.push_back("Don't recognise a word? Inspect <word> might help define it for you.");
	v_pendingOutputStrings.push_back("");

	v_worldTiles.at(c_playerStartPosition.s_firstInt).at(c_playerStartPosition.s_secondInt) = new CautiousTile(true);
	//v_pendingOutputStrings.push_back(ptr_player->c_nameString + ", you've left the hideout and your journey begins");
	
	v_pendingOutputStrings.push_back("Loading Successful: Welcome back " + ptr_player->c_nameString);

	// Initialise the remainder of the map with acceptable tiles
	for (int i = 0; i < c_mapSizeInt; i++) {
		for (int j = 0; j < c_mapSizeInt; j++) {
			if (v_worldTiles.at(i).at(j) == nullptr)
				v_worldTiles.at(i).at(j) = new AcceptableTile();
		}
	}
	c_lastClassificationString = currentTileClassification();
	c_currentClassificationString = c_lastClassificationString;
}

World::~World() {
	for (int i = 0; i < v_worldTiles.size(); i++) {
		v_worldTiles.at(i).erase(v_worldTiles.at(i).begin(), v_worldTiles.at(i).end());
	}
	v_worldTiles.erase(v_worldTiles.begin(), v_worldTiles.end());
	delete this;
}


void World::linkResourceManager(ResourceManager* resource_in) {
	ptr_resourceManager = resource_in;
}
void World::linkNaturalLogicManager(NaturalLogicManager* natural_in) {
	ptr_naturalLogicManager = natural_in;
}

void World::handleCommand(std::string& command_in) {


	std::string m_command = command_in;
	std::transform(m_command.begin(), m_command.end(), m_command.begin(), ::tolower);

	if (m_command.compare(0, 14, "look attempt: ") == 0) {


		if (m_command.find("around") != std::string::npos) {
			v_pendingOutputStrings.push_back(v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->getTileInformation());
		}
		else {
			v_pendingOutputStrings.push_back("Look attempt failed.");
		}
		
	}
	else if (m_command.compare(0, 14, "move attempt: ") == 0) {
		//	The world map has its origin at the bottom-left

		bool m_successfulMove = false;

		//	Attempt to move north or in the positive y-axis
		if (m_command.find("north") != std::string::npos
			|| m_command.find("forward") != std::string::npos
			|| m_command.find("front") != std::string::npos) {

			//	If the player may move in that direction
			if (ptr_player->c_positionInt2d.s_secondInt < c_mapSizeInt - 1) {
				ptr_player->c_positionInt2d.s_secondInt++;
				v_pendingOutputStrings.push_back("You moved north.");
				m_successfulMove = true;
			}
			
		}

		//	Attempt to move east or in the positive x-axis
		else if (m_command.find("east") != std::string::npos
			|| m_command.find("right") != std::string::npos) {

			//	If the player may move in that direction
			if (ptr_player->c_positionInt2d.s_firstInt < c_mapSizeInt - 1) {
				ptr_player->c_positionInt2d.s_firstInt++;
				v_pendingOutputStrings.push_back("You moved east.");
				m_successfulMove = true;
			}
		}

		//	Attempt to move north or in the negative y-axis
		else if (m_command.find("south") != std::string::npos
			|| m_command.find("backward") != std::string::npos
			|| m_command.find("back") != std::string::npos) {

			//	If the player may move in that direction
			if (ptr_player->c_positionInt2d.s_secondInt > 0) {
				ptr_player->c_positionInt2d.s_secondInt--;
				v_pendingOutputStrings.push_back("You moved south.");
				m_successfulMove = true;
			}
		}

		//	Attempt to move north or in the negative x-axis
		else if (m_command.find("west") != std::string::npos
			|| m_command.find("left") != std::string::npos) {

			//	If the player may move in that direction
			if (ptr_player->c_positionInt2d.s_firstInt > 0) {
				ptr_player->c_positionInt2d.s_firstInt--;
				v_pendingOutputStrings.push_back("You moved west.");
				m_successfulMove = true;
			}
		}

		//	Display the flavour text for the current tile
		if (m_successfulMove) {
			//	Process arriving at the tile
			processTile();
		}
		
		//	Inform the player that they failed to move
		else
			v_pendingOutputStrings.push_back("You cannot move in that direction.");
	}
	else if (m_command.compare(0, 16, "pickup attempt: ") == 0) {
		v_pendingOutputStrings.push_back("There is nothing to pickup.");
	}
	else if (m_command.compare(0, 15, "equip attempt: ") == 0) {
		v_pendingOutputStrings.push_back("There is nothing to equip.");
	}
	else if (m_command.compare(0, 17, "inspect attempt: ") == 0) {
		std::string m_temp = m_command.substr(17, m_command.size());
		bool m_itemFound = false;
		//	First check the inventory items
		for (int i = 0; i < ptr_player->v_inventoryItems.size(); i++) {
			if (!m_itemFound && m_temp.find(ptr_player->v_inventoryItems.at(i).s_titleString) != std::string::npos) {
				v_pendingOutputStrings.push_back("[" + ptr_player->v_inventoryItems.at(i).s_qualityString + "] " + ptr_player->v_inventoryItems.at(i).s_bodyString);
				m_itemFound = true;
			}
		}

		//	Then check for a definition
		if (!m_itemFound) {
			v_pendingOutputStrings.push_back(ptr_naturalLogicManager->nltkDictionaryDefinition(m_temp));
		}
	}
	else if (m_command.compare(0, 18, "interact attempt: ") == 0) {
		bool m_interactableFound = false;
		//	Mechanism to quit the game
		if (m_command.find("quit game") != std::string::npos) {
			v_pendingOutputStrings.push_back("");
			v_pendingOutputStrings.push_back("End of game");
			v_pendingOutputStrings.push_back("To play again: Restart Game");
			ptr_player->c_healthFloat = 0.0f;
		}

		//	Saving mechanism
		else if (m_command.find("save game") != std::string::npos) {
			bool m_saveConfirmed = false;
			if (m_command.find("overwrite") != std::string::npos) {
				m_saveConfirmed = true;
			}
			else {
				if (ptr_resourceManager->checkSavefilePaths(ptr_player->c_nameString)) {
					v_pendingOutputStrings.push_back("A previous save with the same name was found.");
					v_pendingOutputStrings.push_back("To overwrite this save: interact save game overwrite");
					v_pendingOutputStrings.push_back("At this time the game has not been saved.");
				}
				else {
					m_saveConfirmed = true;
				}
			}

			if (m_saveConfirmed) {
				v_pendingOutputStrings.push_back("Game is being saved ...");
				saveProfile m_save = saveProfile();
				m_save.s_playerName = ptr_player->c_nameString;
				m_save.s_playerHealth = ptr_player->c_healthFloat;

				m_save.s_playerCurrentLocation = ptr_player->c_positionInt2d;
				m_save.s_playerStartLocation = c_playerStartPosition;

				m_save.s_interactionsInt = ptr_player->c_interactionsInt;
				m_save.s_hostilityInt = ptr_player->c_hostilityInt;
				m_save.s_recentPleasantryInt = ptr_player->c_recentPleasantryInt;
				m_save.s_totalInteractionWordsInt = ptr_player->c_totalInteractionWordsInt;

				m_save.s_playStyle = ptr_player->c_playStyle;
				m_save.v_playerInventory.clear();
				m_save.v_playerInventory.reserve(ptr_player->v_inventoryItems.size());
				for (int i = 0; i < ptr_player->v_inventoryItems.size(); i++) {
					m_save.v_playerInventory.push_back(ptr_player->v_inventoryItems.at(i));
				}
				m_save.s_playerHeadAttire = ptr_player->c_attireHeadString;
				m_save.s_playerTorsoAttire = ptr_player->c_attireTorsoString;
				m_save.s_playerEquipment = ptr_player->c_equipmentString;

				m_save.s_mapSize = c_mapSizeInt;
				m_save.s_worldTheme = ptr_player->c_themeString;
				m_save.v_plotPoints.clear();
				m_save.v_plotPoints.reserve(v_plotPositions.size());
				for (int i = 0; i < v_plotPositions.size(); i++) {
					m_save.v_plotPoints.push_back(v_plotPositions.at(i));
				}

				m_save.s_totalHonestReliableInt = c_totalHonestReliableInt;
				m_save.s_totalHonestUnreliableInt = c_totalHonestUnreliableInt;
				m_save.s_totalDishonestReliableInt = c_totalDishonestReliableInt;

				ptr_resourceManager->writeSavefile(m_save);

				v_pendingOutputStrings.push_back("Save procedure complete.");
			}
		}

		//	Attempt to interact with an interactable
		else if(v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->c_classificationString == "acceptable"
			&& v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->getInteractablePresence(m_command.substr(17, m_command.size()))) {
			
			std::string m_tempString = v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->interactByName(m_command.substr(17, m_command.size()));			
			v_pendingOutputStrings.push_back(m_tempString);
			float m_temp = m_tempString.size() / 100.0f;
			for (int i = 0; i < ceil(m_temp); i++) {
				v_pendingOutputStrings.push_back("");
			}
		}
		else if (v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->c_classificationString == "cautious"
			&& v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->getInteractablePresence(m_command.substr(17, m_command.size()))) {

			std::string m_tempString = v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->interactByName(m_command.substr(17, m_command.size()));
			v_pendingOutputStrings.push_back(m_tempString);
			float m_temp = m_tempString.size() / 100.0f;
			for (int i = 0; i < ceil(m_temp); i++) {
				v_pendingOutputStrings.push_back("");
			}
		}
		else {
			v_pendingOutputStrings.push_back(m_command.substr(17, m_command.size()) + " doesn't seem to be within reach.");
		}

		//	This will send the entered interact command to the natural language processor
		c_commandProfile = ptr_naturalLogicManager->nltkEntryProcessing(m_command.substr(17, m_command.size()));
		
		//	The player's hostility is cumulative through the entire game
		ptr_player->c_hostilityInt += c_commandProfile.s_hostilityInt;
		//	The player's pleasantry is cumulative with each interactable
		ptr_player->c_recentPleasantryInt = c_commandProfile.s_pleasantryInt;
		//The player's total number of words processed
		ptr_player->c_totalInteractionWordsInt += c_commandProfile.s_processedWordsInt;


	}
	else if (m_command.compare(0, 17, "dispose attempt: ") == 0) {
		if (command_in.substr(17, command_in.size()) == ptr_player->c_attireHeadString ||
			command_in.substr(17, command_in.size()) == ptr_player->c_attireTorsoString ||
			command_in.substr(17, command_in.size()) == ptr_player->c_equipmentString) {
			ptr_player->unequipItem(command_in.substr(17, command_in.size()));
		}

		if (!ptr_player->removeItem(command_in.substr(17, command_in.size())))
			v_pendingOutputStrings.push_back(command_in.substr(17, command_in.size()) + " wasn't found in your inventory");
		else
			v_pendingOutputStrings.push_back("You removed " + command_in.substr(17, command_in.size()) + " from your inventory");
	}




}

void World::addPlotPoint() {

	//	First we check if the maximum number of plot positions has been met
	if (v_plotPositions.size() < c_plotMaxInt) {
		int2d m_plotTemp(0, 0);
		int2d m_plotPosition(-5, -5);
		bool m_success = false;

		//	Due to randomisation, it has to be done repeatedly until it functions properly
		while (!m_success) {			

			//	This creates the plot position, and checks to see if it is within bounds
			do {
				//	randomising between -1 or 1, but 0 is not acceptable, this is done just for the signed component
				while (m_plotTemp.s_firstInt == 0 || m_plotTemp.s_secondInt == 0) {
					std::random_device m_randomDevice;
					std::mt19937 m_mt(m_randomDevice());
					std::uniform_int_distribution<int> m_dist(-1, 1);
					m_plotTemp.s_firstInt = m_dist(m_mt);
					m_plotTemp.s_secondInt = m_dist(m_mt);

				}

				std::random_device m_randomDevice;
				std::mt19937 m_mt(m_randomDevice());
				std::uniform_int_distribution<int> m_dist(0, (c_mapSizeInt / 4));
				m_plotPosition.s_firstInt = (int)(((int)m_plotTemp.s_firstInt * (m_dist(m_mt))) + ptr_player->c_positionInt2d.s_firstInt);

				if (std::abs(m_plotPosition.s_firstInt - ptr_player->c_positionInt2d.s_firstInt) == (c_mapSizeInt / 4))
					m_plotPosition.s_secondInt = (int)(((int)m_plotTemp.s_secondInt * (m_dist(m_mt)) ) + ptr_player->c_positionInt2d.s_secondInt);			
				else
					m_plotPosition.s_secondInt = (int)(((int)m_plotTemp.s_secondInt * (c_mapSizeInt / 4)) + ptr_player->c_positionInt2d.s_secondInt);

				if (m_plotPosition.s_firstInt < 0)
					m_plotPosition.s_firstInt *= -1;
				else if (m_plotPosition.s_firstInt >= c_mapSizeInt)
					m_plotPosition.s_firstInt -= (c_mapSizeInt / 2);

				if (m_plotPosition.s_secondInt < 0)
					m_plotPosition.s_secondInt *= -1;
				else if (m_plotPosition.s_secondInt >= c_mapSizeInt)
					m_plotPosition.s_secondInt -= (c_mapSizeInt / 2);
				//srand(time(NULL));
				//m_plotPosition.s_firstString = (int)(((int)m_plotPosition.s_firstString * rand() % (c_mapSizeInt / 4)) + ptr_player->c_positionInt2d.s_firstString);
				//srand(time(NULL));
				//m_plotPosition.s_secondString = (int)(((int)m_plotPosition.s_secondString * rand() % (c_mapSizeInt / 4)) + ptr_player->c_positionInt2d.s_secondString);
			} while (m_plotPosition.s_firstInt >= c_mapSizeInt || m_plotPosition.s_secondInt >= c_mapSizeInt
					||	m_plotPosition.s_firstInt < 0 || m_plotPosition.s_secondInt < 0 );


			//	Creates a new AcceptableTile if there was none at the location and sets it as a plot position
			//if (v_worldTiles.at(m_plotPosition.s_firstString).at(m_plotPosition.s_secondString) == nullptr) {
			//	v_worldTiles.at(m_plotPosition.s_firstString).at(m_plotPosition.s_secondString) = new AcceptableTile();
			//	v_worldTiles.at(m_plotPosition.s_firstString).at(m_plotPosition.s_secondString)->c_availablePlotPosBool = false;
			//	m_success = true;
			//}
			//	If there is a tile at the location, it alters it somewhat
			//else 


			// Check to see that the prospective plot position is not too close to other plot positions
			bool m_noProximityIssuesBool = true;
			for (int2d l_plotPosition : v_plotPositions) {
				if (std::abs(m_plotPosition.s_firstInt - l_plotPosition.s_firstInt) == (c_mapSizeInt / 8)
					|| std::abs(m_plotPosition.s_secondInt - l_plotPosition.s_secondInt) == (c_mapSizeInt / 8) ) {
					m_noProximityIssuesBool == false;
					break;
				}
			}


			if (v_worldTiles.at(m_plotPosition.s_firstInt).at(m_plotPosition.s_secondInt)->c_availablePlotPosBool 				
				&& m_noProximityIssuesBool) {
				
				//	It overwrites the present tile in order to serve the purposes of this plot point
				if(v_worldTiles.at(m_plotPosition.s_firstInt).at(m_plotPosition.s_secondInt)->c_classificationString == "acceptable")
					v_worldTiles.at(m_plotPosition.s_firstInt).at(m_plotPosition.s_secondInt) = new AcceptableTile();
				else if (v_worldTiles.at(m_plotPosition.s_firstInt).at(m_plotPosition.s_secondInt)->c_classificationString == "cautious")
					v_worldTiles.at(m_plotPosition.s_firstInt).at(m_plotPosition.s_secondInt) = new CautiousTile();
					
				v_worldTiles.at(m_plotPosition.s_firstInt).at(m_plotPosition.s_secondInt)->c_availablePlotPosBool = false;
				m_success = true;
			}
		}

		//	Add the successful plot position to the appropriate vector
		v_plotPositions.push_back(m_plotPosition);
		std::cout << "Next plot point: " + std::to_string(m_plotPosition.s_firstInt) + "," + std::to_string(m_plotPosition.s_secondInt) << std::endl;
	}
}


std::string World::currentTileClassification() {
	return v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->c_classificationString;
}


bool World::isSameTileProgression() {
	return c_currentClassificationString == c_lastClassificationString;
}



void World::processTile() {

	//	This is to check if this tile is a plot tile
	if (ptr_player->c_positionInt2d.s_firstInt == v_plotPositions.back().s_firstInt
		&& ptr_player->c_positionInt2d.s_secondInt == v_plotPositions.back().s_secondInt
		&& v_plotPositions.size() < c_plotMaxInt) {

		v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->setDescription(ptr_naturalLogicManager->plotBoardProcessing(v_plotPositions.size() - 1, c_plotMaxInt));
		
		//	This will generate the next plot point
		addPlotPoint();

	}
	//	If it is not a plot point, check if it already has a description, if not assign one
	else if (v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->getDescription().size() == 0) {
		v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->setDescription(ptr_naturalLogicManager->tileBoardProcessing(v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->c_classificationString));
	}
	v_pendingOutputStrings.push_back(v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->getDescription());
	
	float m_temp = v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->getDescription().size() / 90.0f;

	//	Some of the assigned boards are multi-lined, to accomodate them additional empties have to be added
	for (int i = 0; i < roundf(m_temp); i++) {
		v_pendingOutputStrings.push_back("");
	}
	v_pendingOutputStrings.push_back(v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->getTypeFlavour());

	c_lastClassificationString = c_currentClassificationString;
	c_currentClassificationString = currentTileClassification();

	int m_honestyIndex;
	if (c_totalDishonestReliableInt == 0)
		m_honestyIndex = 100;
	else
		m_honestyIndex = (int)(((c_totalHonestReliableInt + c_totalHonestUnreliableInt) / c_totalDishonestReliableInt) * 100);
		
	int m_hostilityIndex;
	if (ptr_player->c_totalInteractionWordsInt == 0)
		m_hostilityIndex = 100;
	else
		m_hostilityIndex = (int)((ptr_player->c_hostilityInt / ptr_player->c_totalInteractionWordsInt) * 100);

	if(!v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->c_populated)
		v_worldTiles.at(ptr_player->c_positionInt2d.s_firstInt).at(ptr_player->c_positionInt2d.s_secondInt)->populateInteractables(v_plotPositions.back(), ptr_player->c_positionInt2d, m_honestyIndex, ptr_player->c_playStyle, m_hostilityIndex, ptr_resourceManager, ptr_naturalLogicManager);

	if (c_currentClassificationString == "deadly") {
		v_pendingOutputStrings.push_back("");
		v_pendingOutputStrings.push_back("End of game");
		v_pendingOutputStrings.push_back("To play again: Restart Game");
		ptr_player->c_healthFloat = 0.0f;
	}

	
	//	This will determine if the player has met the end of the game's plot
	else if ( ptr_player->c_positionInt2d.s_firstInt == v_plotPositions.back().s_firstInt
		&& ptr_player->c_positionInt2d.s_secondInt == v_plotPositions.back().s_secondInt
		&& v_plotPositions.size() >= c_plotMaxInt ) {

		v_pendingOutputStrings.push_back("");
		v_pendingOutputStrings.push_back("End of game");
		v_pendingOutputStrings.push_back("To play again: Restart Game");
		ptr_player->c_healthFloat = 0.0f;


	}

}