#include "GameLogic.h"


GameLogic::GameLogic() {

	c_currentGameStateInt = const_mainMenuInt;
#ifdef DEPLOYMENT
	ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationDeployment.json");
#else
	ptr_resourceManager = new ResourceManager("../Assets/AssetConfigurationDevelopment.json");
#endif // DEPLOYMENT

	
	ptr_naturalLogicManager = new NaturalLogicManager(ptr_resourceManager);

	c_activeMusic.openFromFile(ptr_resourceManager->getAudioPath("menu_background"));
	c_activeMusic.setLoop(true);
	c_activeMusic.setVolume(80.0f);
	c_activeMusic.play();

	v_pendingOutputStrings.push_back("Output: This will display useful information from the game.");
	v_pendingOutputStrings.push_back("Journal: This will display information to help you in the game.");
	v_pendingOutputStrings.push_back("Notes: add note <note>, remove note <note>, change note <note> <new text>");
	v_pendingOutputStrings.push_back("");
	v_pendingOutputStrings.push_back("Commands: Look, Pickup, Equip, Inspect, Discard, Interact <person/thing>");
	v_pendingOutputStrings.push_back("Commands: Move <North/East/South/West> ");
	v_pendingOutputStrings.push_back("");
	v_pendingOutputStrings.push_back("World Size 16x16 32x32 64x64: start game <16/32/64>");
	v_pendingOutputStrings.push_back("");
	
}

GameLogic::~GameLogic() {
	delete this;

}

void GameLogic::restartGameLogic() {
	c_currentGameStateInt = const_mainMenuInt;
	
	ptr_resourceManager->clearThematicVectors();

	c_activeMusic.openFromFile(ptr_resourceManager->getAudioPath("menu_background"));
	c_activeMusic.setLoop(true);
	c_activeMusic.setVolume(80.0f);
	c_activeMusic.play();

	v_pendingOutputStrings.push_back("Output: This will display useful information from the game.");
	v_pendingOutputStrings.push_back("Journal: This will display information to help you in the game.");
	v_pendingOutputStrings.push_back("Notes: add note <note>, remove note <note>, change note <note> <new text>");
	v_pendingOutputStrings.push_back("");
	v_pendingOutputStrings.push_back("Commands: Look, Pickup, Equip, Inspect, Discard, Interact <person/thing>");
	v_pendingOutputStrings.push_back("Commands: Move <North/East/South/West> ");
	v_pendingOutputStrings.push_back("");
	v_pendingOutputStrings.push_back("World Size 16x16 32x32 64x64: start game <16/32/64>");
	v_pendingOutputStrings.push_back("");
	
}

void GameLogic::loadProfile(std::string name_in) {	
	saveProfile m_save = ptr_resourceManager->loadSavefile(name_in);

	c_chosenThemeString = m_save.s_worldTheme;
	ptr_resourceManager->loadThematicDictionaries(c_chosenThemeString);
	ptr_player = new Player(m_save.s_playerName);
	ptr_player->c_themeString = c_chosenThemeString;
	ptr_player->c_healthFloat = m_save.s_playerHealth;

	ptr_player->c_positionInt2d = m_save.s_playerCurrentLocation;

	ptr_player->c_interactionsInt = m_save.s_interactionsInt;
	ptr_player->c_hostilityInt = m_save.s_hostilityInt;
	ptr_player->c_recentPleasantryInt = m_save.s_recentPleasantryInt;
	ptr_player->c_totalInteractionWordsInt = m_save.s_totalInteractionWordsInt;

	ptr_player->c_playStyle = m_save.s_playStyle;
	ptr_player->v_inventoryItems.reserve(m_save.v_playerInventory.size());
	for (int i = 0; i < m_save.v_playerInventory.size(); i++) {
		ptr_player->v_inventoryItems.push_back(m_save.v_playerInventory.at(i));
	}
	ptr_player->c_attireHeadString = m_save.s_playerHeadAttire;
	ptr_player->c_attireTorsoString = m_save.s_playerTorsoAttire;
	ptr_player->c_equipmentString = m_save.s_playerEquipment;

	c_mapSizeInt = m_save.s_mapSize;

	ptr_gameWorld = new World(m_save.s_mapSize, ptr_player, m_save.s_playerStartLocation);

	c_currentGameStateInt = const_proceduralContentInt;

	ptr_gameWorld->linkResourceManager(ptr_resourceManager);
	ptr_gameWorld->linkNaturalLogicManager(ptr_naturalLogicManager);

	ptr_gameWorld->v_plotPositions.reserve(m_save.v_plotPoints.size());
	for (int i = 0; i < m_save.v_plotPoints.size(); i++) {
		ptr_gameWorld->v_plotPositions.push_back(m_save.v_plotPoints.at(i));
	}
	ptr_gameWorld->c_totalHonestReliableInt = m_save.s_totalHonestReliableInt;
	ptr_gameWorld->c_totalHonestUnreliableInt = m_save.s_totalHonestUnreliableInt;
	ptr_gameWorld->c_totalDishonestReliableInt = m_save.s_totalDishonestReliableInt;


	while (ptr_gameWorld->v_pendingOutputStrings.size() > 0) {
		v_pendingOutputStrings.push_back(ptr_gameWorld->v_pendingOutputStrings.front());
		ptr_gameWorld->v_pendingOutputStrings.erase(ptr_gameWorld->v_pendingOutputStrings.begin());
	}
	playTileMusic();
	ptr_gameWorld->processTile();
}


int GameLogic::Update() {
	int updateErrorCode = 0;

	switch (c_currentGameStateInt) {
	case const_mainMenuInt:
		// Set up information to display and let the user know how the game will function

		

		//	End of main menu
		break;
	case const_escapeCalibrationInt:
		//	Logic for the "Escape the Room" scenario that will serve to calibrate user data for the game

		//	End of escape calibration
		break;
	case const_proceduralContentInt:
		//	Main game logic dealing with procedural generation and story progression

		//	End of procedural content
		break;
	}

	return updateErrorCode;
}
std::string GameLogic::commandPreprocess(std::string& command_in) {

	std::string m_command = command_in;
	std::transform(m_command.begin(), m_command.end(), m_command.begin(), ::tolower);

	if (c_currentGameStateInt == const_mainMenuInt) {
		if (m_command.compare(0, 11, "start game ") == 0) {
			c_failedCommandCountInt = 0;
			return "Starting Game: " + command_in.substr(11, 13) + "x" + command_in.substr(11, 13);
		}

		else if (m_command.find("load game ") != std::string::npos) {
			if (ptr_resourceManager->checkSavefilePaths(m_command.substr(10, m_command.size()))) {
				loadProfile(m_command.substr(10, m_command.size()));
				return "Success";
			}
			else {
				v_pendingOutputStrings.push_back("No save file by that name was found.");
				v_pendingOutputStrings.push_back("Command Reminder: load game first second");
				v_pendingOutputStrings.push_back("Command Example: load game verd llagosta");
				return "Try again";
			}
		}
	}
	else if (c_currentGameStateInt == const_escapeCalibrationInt) {
		if (m_command.compare(0, 5, "look ") == 0) {
			c_failedCommandCountInt = 0;
			return "Look Attempt: " + command_in.substr(5, command_in.size());
		}
		else if (m_command.compare(0, 5, "move ") == 0) {
			c_failedCommandCountInt = 0;
			return "The room is too small to move in any significant way.";
		}
		else if (m_command.compare(0, 7, "pickup ") == 0) {
			c_failedCommandCountInt = 0;
			return "Pickup Attempt: " + command_in.substr(7, command_in.size());
		}
		else if (m_command.compare(0, 6, "equip ") == 0) {
			c_failedCommandCountInt = 0;
			return "Equip Attempt: " + command_in.substr(6, command_in.size());
		}
		else if (m_command.compare(0, 8, "inspect ") == 0) {
			c_failedCommandCountInt = 0;
			return "Inspect Attempt: " + command_in.substr(8, command_in.size());
		}
		else if (m_command.compare(0, 9, "interact ") == 0) {
			c_failedCommandCountInt = 0;
			return "Interact Attempt: " + command_in.substr(8, command_in.size());
		}
		else if (m_command.compare(0, 8, "dispose ") == 0) {
			c_failedCommandCountInt = 0;
			return "Dipose Attempt: " + command_in.substr(8, command_in.size());
		}
	}

	else if (c_currentGameStateInt == const_proceduralContentInt) {
		if (m_command.compare(0, 5, "look ") == 0) {
			c_failedCommandCountInt = 0;
			return "Look Attempt: " + command_in.substr(5, command_in.size());
		}
		else if (m_command.compare(0, 5, "move ") == 0) {
			c_failedCommandCountInt = 0;
			return "Move Attempt: " + command_in.substr(5, command_in.size());
		}
		else if (m_command.compare(0, 7, "pickup ") == 0) {
			c_failedCommandCountInt = 0;
			return "Pickup Attempt: " + command_in.substr(7, command_in.size());
		}
		else if (m_command.compare(0, 6, "equip ") == 0) {
			c_failedCommandCountInt = 0;
			return "Equip Attempt: " + command_in.substr(6, command_in.size());
		}
		else if (m_command.compare(0, 8, "inspect ") == 0) {
			c_failedCommandCountInt = 0;
			return "Inspect Attempt: " + command_in.substr(8, command_in.size());
		}
		else if (m_command.compare(0, 9, "interact ") == 0) {
			c_failedCommandCountInt = 0;
			return "Interact Attempt: " + command_in.substr(8, command_in.size());
		}
		else if (m_command.compare(0, 8, "discard ") == 0) {
			c_failedCommandCountInt = 0;
			return "Discard Attempt: " + command_in.substr(8, command_in.size());
		}
	}

	//	These handle the notes displayed
	if (m_command.compare(0, 8, "add note") == 0) {
		c_failedCommandCountInt = 0;
		return "Entered Note: " + command_in.substr(8, command_in.size());
	}
	else if (m_command.compare(0, 11, "remove note") == 0) {
		c_failedCommandCountInt = 0;
		return "Removed Note: " + command_in.substr(11, command_in.size());
	}
	else if (m_command.compare(0, 11, "change note") == 0) {
		c_failedCommandCountInt = 0;
		return "Changed Note: " + command_in.substr(11, command_in.size());
	}
	//	This clears both the input and the output frames
	else if (m_command == "cls" || m_command == "clear") {
		c_failedCommandCountInt = 0;
		return "65536 Initiate Screen Clear 65536";
	}

	//	This handles if the user inputs something that does not make sense
	else {

		if (c_failedCommandCountInt <= 3) {
			c_failedCommandCountInt++;
			return command_in + " was said to the winds, but they seemed not to understand.";
		}
		else if (c_failedCommandCountInt > 3 && c_failedCommandCountInt <= 6) {
			c_failedCommandCountInt++;
			return command_in + " was said, turning the winds restless.";
		}
		else if (c_failedCommandCountInt > 6 && c_failedCommandCountInt <= 12) {
			c_failedCommandCountInt++;
			return command_in + " was heard by the tumultuous winds, their patience is thinning.";
		}
		else if (c_failedCommandCountInt > 12) {
			return "The winds are tired of your nonsense and have cast you to the heavens, killing you.";
		}
	}
}

void GameLogic::startGameWorld(int mapSize_in) {
	c_currentGameStateInt = const_proceduralContentInt;

	//	Starting a 64x64 game
	if (mapSize_in > 48 && mapSize_in < 80) {
		ptr_gameWorld = new World(64, ptr_player);
	}
	//	Starting a 32x32 game
	else if (mapSize_in > 24 && mapSize_in < 40) {
		ptr_gameWorld = new World(32, ptr_player);
	}
	//	Starting a 16x16 game
	else {
		ptr_gameWorld = new World(16, ptr_player);
	}

	//	Load the information for the chosen theme
	ptr_resourceManager->loadThematicDictionaries(c_chosenThemeString);
	ptr_gameWorld->linkResourceManager(ptr_resourceManager);
	ptr_gameWorld->linkNaturalLogicManager(ptr_naturalLogicManager);
	
	ptr_player->c_themeString = c_chosenThemeString;

	while (ptr_gameWorld->v_pendingOutputStrings.size() > 0) {
		v_pendingOutputStrings.push_back(ptr_gameWorld->v_pendingOutputStrings.front());
		ptr_gameWorld->v_pendingOutputStrings.erase(ptr_gameWorld->v_pendingOutputStrings.begin());
	}
	playTileMusic();

}
void GameLogic::startRoomEscape(int mapSize_in) {
	c_currentGameStateInt = const_escapeCalibrationInt;

	//c_activeMusic.stop();
	
	c_activeMusic.openFromFile(ptr_resourceManager->getAudioPath("roomescape_background"));
	c_activeMusic.setLoop(true);
	c_activeMusic.setVolume(80.0f);
	c_activeMusic.play();

	std::string m_playerName = ptr_resourceManager->getRandomPseudonymOne(true).s_nameString + " " + ptr_resourceManager->getRandomPseudonymTwo(true).s_nameString;
	ptr_player = new Player(m_playerName);

	c_mapSizeInt = mapSize_in;
	ptr_roomEscape = new RoomEscape();
	ptr_roomEscape->readFromConfiguration(ptr_resourceManager->getThemePath("RoomEscapeConfiguration"));
	ptr_roomEscape->linkPlayer(ptr_player);
	ptr_roomEscape->linkNaturalLogicManager(ptr_naturalLogicManager);

	v_pendingOutputStrings.push_back("You remember going by " + m_playerName);
	v_pendingOutputStrings.push_back(ptr_roomEscape->getPlotPoint("zero_awake"));
}

void GameLogic::handleCommand(std::string command_in) {

	if (c_currentGameStateInt == const_escapeCalibrationInt) {
		//handleRoomEscape(command_in);
		ptr_roomEscape->handleCommand(command_in);

		while (ptr_roomEscape->v_pendingOutputStrings.size() > 0) {
			v_pendingOutputStrings.push_back(ptr_roomEscape->v_pendingOutputStrings.front());
			ptr_roomEscape->v_pendingOutputStrings.erase(ptr_roomEscape->v_pendingOutputStrings.begin());
		}

		if (ptr_roomEscape->checkSolved()) {
			//	get the theme chosen in the room escape / calibration
			c_chosenThemeString = ptr_roomEscape->getChosenTheme();
			
			ptr_player->c_playStyle = (ptr_roomEscape->c_correctAnswers - ptr_roomEscape->c_incorrectAnswers) / 3;
			if (ptr_player->c_playStyle < 0.0f)
				ptr_player->c_playStyle = 0.0f;

			// start the gameworld
			startGameWorld(c_mapSizeInt);
			ptr_roomEscape->~RoomEscape();
			ptr_roomEscape = nullptr;
		}
	}
	else if (c_currentGameStateInt == const_proceduralContentInt) {
		//handleGameWorld(command_in);
		ptr_gameWorld->handleCommand(command_in);

		while (ptr_gameWorld->v_pendingOutputStrings.size() > 0) {
			v_pendingOutputStrings.push_back(ptr_gameWorld->v_pendingOutputStrings.front());
			ptr_gameWorld->v_pendingOutputStrings.erase(ptr_gameWorld->v_pendingOutputStrings.begin());
		}


		// This checks to see if a new classification of tile has been landed on
		// Without this check it would start playing music regardless if the player stayed on the same classification or moved to a new one
		if (!ptr_gameWorld->isSameTileProgression()) {
			playTileMusic();
		}
	}
}

void GameLogic::playTileMusic() {
	if (ptr_gameWorld != nullptr) {
		//	Plays the appropriate music for the tile/theme
		c_activeMusic.openFromFile(ptr_resourceManager->getAudioPath(c_chosenThemeString + "_" + ptr_gameWorld->currentTileClassification()));
		c_activeMusic.setLoop(true);
		c_activeMusic.setVolume(80.0f);
		c_activeMusic.play();
	}
}
