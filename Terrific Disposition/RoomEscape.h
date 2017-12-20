#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <utility>

#include <json/json.h>

#include "DataStructs.h"
#include "Player.h"

class RoomEscape {
public:

	RoomEscape();
	~RoomEscape();

	std::vector<std::string> v_pendingOutput;
	int c_incorrectAnswers;
	int c_correctAnswers;

	void readFromConfiguration(std::string configPath_in);
	void linkPlayer(Player* player_in);

	void handleCommand(std::string& command_in);

	bool addPlotPoint(std::string name_in, std::string text_in);
	std::string getPlotPoint(std::string textTitle_in);

	bool addEscapeQuestion(std::string name_in, std::string question_in, std::string answer_in);
	namedString getEscapeQuestion(std::string name_in);

	bool addCyberpunkItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in);
	inventoryItem getCyberpunkItem(std::string name_in);

	bool addNuclearWinterItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in);
	inventoryItem getNuclearWinterItem(std::string name_in);

	bool addPassiveInvasionItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in);
	inventoryItem getPassiveInvasionItem(std::string name_in);

	bool handleAnswerKeys(std::string& keys_in);
	bool checkKeywordPresence(std::string& string_in);
	std::string checkSolved();

private:
	std::vector<std::string> v_answerExpectedKeys;
	int c_answeredQuestions;
	int c_presentedQuestions;
	std::string c_chosenTheme;

	Player* ptr_player;

	std::vector<inventoryItem> v_cyberpunkItems;
	std::vector<inventoryItem> v_nuclearWinterItems;
	std::vector<inventoryItem> v_passiveInvasionItems;

	std::vector<namedDoubleString> v_escapeQuestions;
	std::vector<namedString> v_escapePlot;



};