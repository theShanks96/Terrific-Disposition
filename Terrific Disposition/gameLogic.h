#pragma once

#include <algorithm>
#include <vector>
#include <string>

#include "ResourceManager.h"
#include "World.h"
#include "RoomEscape.h"

#include "Player.h"


//! This essentially holds the game loop, and is designed to manage the flow of gameplay
class GameLogic {
private:
	int c_failedCommandCount;

	static constexpr int MAIN_MENU = 0;
	static constexpr int ESCAPE_CALIBRATION = 100;
	static constexpr int PROCEDURAL_CONTENT = 200;

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
	GameLogic();
	~GameLogic();

	Player* ptr_player;
	ResourceManager* ptr_resourceManager;
	//SFML_Window* ptr_gameWindow;
	
	int c_currentGameState;
	int c_mapSize;

	std::vector<std::string> v_pendingInput;
	std::vector<std::string> v_pendingOutput;

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
	void handleRoomEscape(std::string& command_in);
	void handleGameWorld(std::string& command_in);
};