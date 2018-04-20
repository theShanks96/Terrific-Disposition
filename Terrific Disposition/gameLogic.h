#pragma once

#include <SFML\Audio.hpp>

#include <algorithm>
#include <vector>
#include <string>

#include "ResourceManager.h"
#include "NaturalLogicManager.h"
#include "World.h"
#include "RoomEscape.h"

#include "Player.h"

//	Might already be defined in ResourceManager.h, remember to check
//#define DEPLOYMENT


//! This essentially holds the game loop, and is designed to manage the flow of gameplay
class GameLogic {
private:
	int c_failedCommandCountInt;

	sf::Music c_activeMusic;

	World* ptr_gameWorld;
	RoomEscape* ptr_roomEscape;
	
public:
	static constexpr int const_mainMenuInt = 0;
	static constexpr int const_escapeCalibrationInt = 100;
	static constexpr int const_proceduralContentInt = 200;

	GameLogic();
	~GameLogic();

	void restartGameLogic();

	std::string c_chosenThemeString;


	Player* ptr_player;
	ResourceManager* ptr_resourceManager;
	NaturalLogicManager* ptr_naturalLogicManager;
	//SFML_Window* ptr_gameWindow;
	
	int c_currentGameStateInt;
	int c_mapSizeInt;

	std::vector<std::string> v_pendingOutputStrings;

	int Update();

	//void enterCommand();
	std::string commandPreprocess(std::string& command_in);	
	void handleCommand(std::string command_in);

	//	Starting the game
	void startGameWorld(int mapSize_in);
	void startRoomEscape(int mapSize_in);

private:
	void loadProfile(std::string name_in);
	void playTileMusic();
};