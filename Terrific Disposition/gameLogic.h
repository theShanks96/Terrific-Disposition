#pragma once

#include <SFML\Audio.hpp>

#include <algorithm>
#include <vector>
#include <string>

#include "ResourceManager.h"
#include "PythonManager.h"
#include "World.h"
#include "RoomEscape.h"

#include "Player.h"


//! This essentially holds the game loop, and is designed to manage the flow of gameplay
class GameLogic {
private:
	int c_failedCommandCountInt;

	sf::Music c_activeMusic;

	World* ptr_gameWorld;
	RoomEscape* ptr_roomEscape;

	std::vector<std::string> v_commandHistoryStrings;
	std::vector<std::string> v_semanticFieldStrings;

	std::vector<std::string> v_notesVector;
	std::vector<std::string> v_journalVector;

	float c_timeFromFailureFloat;
	float c_timeToActionFloat;
	float c_successRatioFloat;

	float c_successCountFloat;
	float c_failureCountFloat;

	
public:
	static constexpr int const_mainMenuInt = 0;
	static constexpr int const_escapeCalibrationInt = 100;
	static constexpr int const_proceduralContentInt = 200;

	GameLogic();
	~GameLogic();

	std::string c_chosenThemeString;


	Player* ptr_player;
	ResourceManager* ptr_resourceManager;
	PythonManager* ptr_pythonManager;
	//SFML_Window* ptr_gameWindow;
	
	int c_currentGameState;
	int c_mapSizeInt;

	std::vector<std::string> v_pendingInput;
	std::vector<std::string> v_pendingOutputStrings;

	int Update();

	//void enterCommand();
	std::string commandPreprocess(std::string& command_in);

	std::vector<std::string> getNotesVector();
	std::vector<std::string> getJournalVector();

	std::vector<std::string> getSemanticField();
	void setSemanticField(std::vector<std::string>& semanticField_in);

	float getTimeFromFailue();
	void setTimeFromFailure(float& timeFromFailure_in);

	float getTimeToAction();
	void setTimeToAction(float& timeToAction_in);

	float getSuccessRatio();
	void setSuccessCount(float& successCount_in);
	void setFailureCount(float& failureCount_in);

	void updateSuccessRatio();

	//	Starting the game
	void startGameWorld(int mapSize_in);
	void startRoomEscape(int mapSize_in);
	void handleCommand(std::string command_in);

private:
	void playTileMusic();
};