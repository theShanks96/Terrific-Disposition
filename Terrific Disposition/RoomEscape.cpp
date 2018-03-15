#include "RoomEscape.h"

RoomEscape::RoomEscape() {
	
	c_answeredQuestions = 0;
	c_presentedQuestions = 0;
	c_chosenThemeString = "none";
	c_commandProfile = commandProfile(0, 0, 0, 0, 0, 0);

}
RoomEscape::~RoomEscape() {
}

void RoomEscape::readFromConfiguration(std::string configPath_in) {
	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;
	jsonData.open(configPath_in.c_str());

	if (!reader.parse(jsonData, root)) {
		std::cout << "Failed to open config file: " << configPath_in << reader.getFormattedErrorMessages();
	}
	else {
		//	This will look up the items for the cyberpunk theme and load them
		const Json::Value m_cyberpunkItems = root["CyberpunkItems"];
		v_cyberpunkItems.reserve(m_cyberpunkItems.size());

		for (int i = 0; i < m_cyberpunkItems.size(); i++) {
			addCyberpunkItem(m_cyberpunkItems[i]["name"].asString(), m_cyberpunkItems[i]["title"].asString(), m_cyberpunkItems[i]["quality"].asString(), m_cyberpunkItems[i]["body"].asString());
		}

		//	This will look up the items for the nuclear winter theme and load them
		const Json::Value m_nuclearWinterItems = root["NuclearWinterItems"];
		v_nuclearWinterItems.reserve(m_nuclearWinterItems.size());

		for (int i = 0; i < m_nuclearWinterItems.size(); i++) {
			addNuclearWinterItem(m_nuclearWinterItems[i]["name"].asString(), m_nuclearWinterItems[i]["title"].asString(), m_nuclearWinterItems[i]["quality"].asString(), m_nuclearWinterItems[i]["body"].asString());
		}

		//	This will look up the items for the passive invasion theme and load them
		const Json::Value m_passiveInvasionItems = root["PassiveInvasionItems"];
		v_nuclearWinterItems.reserve(m_passiveInvasionItems.size());

		for (int i = 0; i < m_passiveInvasionItems.size(); i++) {
			addPassiveInvasionItem(m_passiveInvasionItems[i]["name"].asString(), m_passiveInvasionItems[i]["title"].asString(), m_passiveInvasionItems[i]["quality"].asString(), m_passiveInvasionItems[i]["body"].asString());
		}
		//	This will load the questions that must be answered to start the game proper
		const Json::Value m_escapeQuestions = root["EscapeQuestions"];
		v_escapeQuestions.reserve(m_escapeQuestions.size());

		for (int i = 0; i < m_escapeQuestions.size(); i++) {
			addEscapeQuestion(m_escapeQuestions[i]["name"].asString(), m_escapeQuestions[i]["question"].asString(), m_escapeQuestions[i]["answer"].asString());
		}

		//	This will load the minimal plot for this segment
		const Json::Value m_escapePlot = root["EscapePlot"];
		v_escapePlot.reserve(m_escapePlot.size());

		for (int i = 0; i < m_escapePlot.size(); i++) {
			addPlotPoint(m_escapePlot[i]["name"].asString(), m_escapePlot[i]["content"].asString());
		}

	}
	jsonData.close();
}

void RoomEscape::linkPlayer(Player* player_in) {
	ptr_player = player_in;
}

void RoomEscape::linkNaturalLogicManager(NaturalLogicManager* natural_in) {
	ptr_naturalLogicManager = natural_in;
}


void RoomEscape::handleCommand(std::string& command_in) {

	std::string m_command = command_in;
	std::transform(m_command.begin(), m_command.end(), m_command.begin(), ::tolower);

	if (m_command.compare(0, 14, "look attempt: ") == 0) {
		if (m_command.find("room") != std::string::npos
			|| m_command.find("around") != std::string::npos
			|| m_command.find("wall") != std::string::npos
			|| m_command.find("surround") != std::string::npos) {

			v_pendingOutputStrings.push_back(getPlotPoint("one_look_room"));
		}
		else if (m_command.find("clutter") != std::string::npos
			|| m_command.find("floor") != std::string::npos
			|| m_command.find("down") != std::string::npos) {

			v_pendingOutputStrings.push_back(getPlotPoint("two_look_clutter"));
		}
		else if (m_command.find("headgear") != std::string::npos) {
			v_pendingOutputStrings.push_back("Three pieces of headgear: ");
			v_pendingOutputStrings.push_back("[" + getCyberpunkItem("attire_head").s_qualityString + "] " + getCyberpunkItem("attire_head").s_titleString + ": " + getCyberpunkItem("attire_head").s_bodyString);
			v_pendingOutputStrings.push_back("[" + getNuclearWinterItem("attire_head").s_qualityString + "] " + getNuclearWinterItem("attire_head").s_titleString + ": " + getNuclearWinterItem("attire_head").s_bodyString);
			v_pendingOutputStrings.push_back("[" + getPassiveInvasionItem("attire_head").s_qualityString + "] " + getPassiveInvasionItem("attire_head").s_titleString + ": " + getPassiveInvasionItem("attire_head").s_bodyString);

		}
		else if (m_command.find("jacket") != std::string::npos) {
			v_pendingOutputStrings.push_back("Three jackets: ");
			v_pendingOutputStrings.push_back("[" + getCyberpunkItem("attire_torso").s_qualityString + "] " + getCyberpunkItem("attire_torso").s_titleString + ": " + getCyberpunkItem("attire_torso").s_bodyString);
			v_pendingOutputStrings.push_back("[" + getNuclearWinterItem("attire_torso").s_qualityString + "] " + getNuclearWinterItem("attire_torso").s_titleString + ": " + getNuclearWinterItem("attire_torso").s_bodyString);
			v_pendingOutputStrings.push_back("[" + getPassiveInvasionItem("attire_torso").s_qualityString + "] " + getPassiveInvasionItem("attire_torso").s_titleString + ": " + getPassiveInvasionItem("attire_torso").s_bodyString);

		}
		else if (m_command.find("odd") != std::string::npos) {
			v_pendingOutputStrings.push_back("Three odd items: ");
			v_pendingOutputStrings.push_back("[" + getCyberpunkItem("equipment").s_qualityString + "] " + getCyberpunkItem("equipment").s_titleString + ": " + getCyberpunkItem("equipment").s_bodyString);
			v_pendingOutputStrings.push_back("[" + getNuclearWinterItem("equipment").s_qualityString + "] " + getNuclearWinterItem("equipment").s_titleString + ": " + getNuclearWinterItem("equipment").s_bodyString);
			v_pendingOutputStrings.push_back("[" + getPassiveInvasionItem("equipment").s_qualityString + "] " + getPassiveInvasionItem("equipment").s_titleString + ": " + getPassiveInvasionItem("equipment").s_bodyString);

		}
		else if (m_command.find("light") != std::string::npos
			|| m_command.find("red") != std::string::npos
			|| m_command.find("green") != std::string::npos
			|| m_command.find("corner") != std::string::npos) {

			v_pendingOutputStrings.push_back(getPlotPoint("three_look_light"));
		}
		else if (m_command.find("door") != std::string::npos
			|| m_command.find("metal") != std::string::npos
			|| m_command.find("exit") != std::string::npos
			|| m_command.find("entrance") != std::string::npos) {

			v_pendingOutputStrings.push_back(getPlotPoint("four_look_door"));
		}
		else if (m_command.find("console") != std::string::npos
			|| m_command.find("keypad") != std::string::npos
			|| m_command.find("monitor") != std::string::npos
			|| m_command.find("keryboard") != std::string::npos) {

			v_pendingOutputStrings.push_back(getPlotPoint("five_look_console"));
		}
	}
	/* else if (m_command.compare(0, 14, "move attempt: ") == 0) {
	This would be implemented if the player had room to move during this segment
	}*/
	else if (m_command.compare(0, 16, "pickup attempt: ") == 0) {
		std::string m_item = command_in.substr(16, command_in.size());
		std::vector<inventoryItem> v_items;
		v_items.reserve(9);

		v_items.push_back(getCyberpunkItem("attire_head"));
		v_items.push_back(getCyberpunkItem("attire_torso"));
		v_items.push_back(getCyberpunkItem("equipment"));
		v_items.push_back(getNuclearWinterItem("attire_head"));
		v_items.push_back(getNuclearWinterItem("attire_torso"));
		v_items.push_back(getNuclearWinterItem("equipment"));
		v_items.push_back(getPassiveInvasionItem("attire_head"));
		v_items.push_back(getPassiveInvasionItem("attire_torso"));
		v_items.push_back(getPassiveInvasionItem("equipment"));

		if (ptr_player->v_inventoryItems.size() == 0) {
			for (inventoryItem l_item : v_items) {
				if (m_item == l_item.s_titleString) {
					v_pendingOutputStrings.push_back("You picked up " + m_item + " and placed it in your inventory.");
					ptr_player->addItem(l_item);
				}
			}
		}
		else if (ptr_player->v_inventoryItems.size() > 0) {
			int m_theme = 0;

			for (int i = 0; i < v_items.size(); i++) {
				if (ptr_player->v_inventoryItems.front().s_titleString == v_items.at(i).s_titleString) {
					m_theme = (int)(i / 3);
				}
			}

			for (int i = 0; i < v_items.size(); i++) {
				if (m_item == v_items.at(i).s_titleString) {
					if ((int)(i / 3) == m_theme) {
						v_pendingOutputStrings.push_back("You picked up " + m_item + " and placed it in your inventory.");
						ptr_player->addItem(v_items.at(i));
					}
					else {
						v_pendingOutputStrings.push_back("That doesn't seem to go with the item you picked up before.");
					}
				}
			}

		}

	}
	else if (m_command.compare(0, 15, "equip attempt: ") == 0) {
		int m_equipCount = 0;
		bool m_result = ptr_player->equipItem(command_in.substr(15, command_in.size()));
		if (m_result) {
			v_pendingOutputStrings.push_back("You equiped " + command_in.substr(15, command_in.size()));

			(ptr_player->c_attireHeadString != "Empty") ? (m_equipCount++) : (m_equipCount = m_equipCount);
			(ptr_player->c_attireTorsoString != "Empty") ? (m_equipCount++) : (m_equipCount = m_equipCount);
			(ptr_player->c_equipmentString != "Empty") ? (m_equipCount++) : (m_equipCount = m_equipCount);

			if (m_equipCount >= 2 && (ptr_player->c_attireHeadString == getCyberpunkItem("attire_head").s_titleString
				|| ptr_player->c_attireTorsoString == getCyberpunkItem("attire_torso").s_titleString
				|| ptr_player->c_equipmentString == getCyberpunkItem("equipment").s_titleString)) {
				c_chosenThemeString = "cyberpunk";
			}
			else if (m_equipCount >= 2 && (ptr_player->c_attireHeadString == getNuclearWinterItem("attire_head").s_titleString
				|| ptr_player->c_attireTorsoString == getNuclearWinterItem("attire_torso").s_titleString
				|| ptr_player->c_equipmentString == getNuclearWinterItem("equipment").s_titleString)) {
				c_chosenThemeString = "nuclearwinter";
			}
			else if (m_equipCount >= 2 && (ptr_player->c_attireHeadString == getPassiveInvasionItem("attire_head").s_titleString
				|| ptr_player->c_attireTorsoString == getPassiveInvasionItem("attire_torso").s_titleString
				|| ptr_player->c_equipmentString == getPassiveInvasionItem("equipment").s_titleString)) {
				c_chosenThemeString = "passiveinvasion";
			}
			else if (m_equipCount >= 1 ) {
				c_chosenThemeString = "none";
			}
		}
		else {
			v_pendingOutputStrings.push_back(command_in.substr(15, command_in.size()) + " wasn't found in your inventory or was too damaged to equip.");
		}
		}
	else if (m_command.compare(0, 17, "inspect attempt: ") == 0) {
		std::string m_item = command_in.substr(17, command_in.size());
		std::vector<inventoryItem> v_items;
		v_items.reserve(9);

		v_items.push_back(getCyberpunkItem("attire_head"));
		v_items.push_back(getCyberpunkItem("attire_torso"));
		v_items.push_back(getCyberpunkItem("equipment"));
		v_items.push_back(getNuclearWinterItem("attire_head"));
		v_items.push_back(getNuclearWinterItem("attire_torso"));
		v_items.push_back(getNuclearWinterItem("equipment"));
		v_items.push_back(getPassiveInvasionItem("attire_head"));
		v_items.push_back(getPassiveInvasionItem("attire_torso"));
		v_items.push_back(getPassiveInvasionItem("equipment"));

		bool m_itemFound = false;
		for (inventoryItem l_item : v_items) {
			if (m_item == l_item.s_titleString) {
				// Display the item's information or body of content
				v_pendingOutputStrings.push_back("[" + l_item.s_qualityString + "] " + l_item.s_bodyString);
				m_itemFound = true;
			}
		}

		if( !m_itemFound ){
			v_pendingOutputStrings.push_back("That item does not seem to be near enough to inspect.");
		}
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

	else if (m_command.compare(0, 18, "interact attempt: ") == 0) {
		if (m_command.find("console") != std::string::npos && c_answeredQuestions == 0 && c_presentedQuestions == 0) {
			
			if (c_chosenThemeString == "cyberpunk") {
				v_pendingOutputStrings.push_back(getEscapeQuestion("cyberpunk_question_zero").s_nameString);
				c_presentedQuestions++;
			}
			else if (c_chosenThemeString == "nuclearwinter") {
				v_pendingOutputStrings.push_back(getEscapeQuestion("nuclearwinter_question_zero").s_nameString);
				c_presentedQuestions++;
			}
			else if (c_chosenThemeString == "passiveinvasion") {
				v_pendingOutputStrings.push_back(getEscapeQuestion("passiveinvasion_question_zero").s_nameString);
				c_presentedQuestions++;
			}
			else {
				v_pendingOutputStrings.push_back("Make sure you've equiped yourself before leaving.");
			}
		}
		else if (c_answeredQuestions == 0 && c_presentedQuestions == 1) {
			if (checkKeywordPresence(m_command)) {
				v_pendingOutputStrings.push_back(getPlotPoint("zero_answer"));
				c_answeredQuestions++;

				if (c_chosenThemeString == "cyberpunk")
					v_pendingOutputStrings.push_back(getEscapeQuestion("cyberpunk_question_one").s_nameString);
				else if (c_chosenThemeString == "nuclearwinter")
					v_pendingOutputStrings.push_back(getEscapeQuestion("nuclearwinter_question_one").s_nameString);
				else if (c_chosenThemeString == "passiveinvasion")
					v_pendingOutputStrings.push_back(getEscapeQuestion("passiveinvasion_question_one").s_nameString);
				
				c_presentedQuestions++;
			}
			else {
				v_pendingOutputStrings.push_back("Seems that was incorrect.");
			}
		}

		else if (c_answeredQuestions == 1 && c_presentedQuestions == 2) {
			if (checkKeywordPresence(m_command)) {
				v_pendingOutputStrings.push_back(getPlotPoint("one_answer"));
				c_answeredQuestions++;

				if (c_chosenThemeString == "cyberpunk")
					v_pendingOutputStrings.push_back(getEscapeQuestion("cyberpunk_question_two").s_nameString);
				else if (c_chosenThemeString == "nuclearwinter")
					v_pendingOutputStrings.push_back(getEscapeQuestion("nuclearwinter_question_two").s_nameString);
				else if (c_chosenThemeString == "passiveinvasion")
					v_pendingOutputStrings.push_back(getEscapeQuestion("passiveinvasion_question_two").s_nameString);

				c_presentedQuestions++;
			}
			else {
				v_pendingOutputStrings.push_back("Seems that was incorrect.");
			}
		}

		else if (c_answeredQuestions == 2 && c_presentedQuestions == 3) {
			if (checkKeywordPresence(m_command)) {
				v_pendingOutputStrings.push_back(getPlotPoint("two_answer"));

				c_answeredQuestions++;
			}
			else {
				v_pendingOutputStrings.push_back("Seems that was incorrect.");
			}
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
}

bool RoomEscape::addPlotPoint(std::string name_in, std::string text_in) {
	for (namedString l_escapePlot : v_escapePlot) {
		if (l_escapePlot.s_nameString == name_in)
			return true;
	}
	v_escapePlot.push_back(namedString(name_in, text_in));
	return true;
}
std::string RoomEscape::getPlotPoint(std::string name_in) {
	for (namedString l_escapePlot : v_escapePlot) {
		if (l_escapePlot.s_nameString == name_in)
			return l_escapePlot.s_string;
	}
	return false;
}

bool RoomEscape::addEscapeQuestion(std::string name_in, std::string question_in, std::string answer_in) {
	for (namedDoubleString l_escapeQuestion : v_escapeQuestions) {
		if (l_escapeQuestion.s_nameString == name_in)
			return true;
	}
	v_escapeQuestions.push_back(namedDoubleString(name_in, question_in, answer_in));
	return true;
}
namedString RoomEscape::getEscapeQuestion(std::string name_in) {
	for (namedDoubleString l_escapeQuestion : v_escapeQuestions) {
		if (l_escapeQuestion.s_nameString == name_in) {
			handleAnswerKeys(l_escapeQuestion.s_secondString);
			return namedString(l_escapeQuestion.s_firstString, l_escapeQuestion.s_secondString);
		}
	}
	return namedString(false, false);
}

bool RoomEscape::addCyberpunkItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in) {
	for (inventoryItem l_cyberpunkItem : v_cyberpunkItems) {
		if (l_cyberpunkItem.s_nameString == name_in)
			return true;
	}
	v_cyberpunkItems.push_back(inventoryItem(name_in, title_in, quality_in, body_in));
	return true;
}
inventoryItem RoomEscape::getCyberpunkItem(std::string name_in) {
	for (inventoryItem l_cyberpunkItem : v_cyberpunkItems) {
		if (l_cyberpunkItem.s_nameString == name_in)
			return inventoryItem(l_cyberpunkItem.s_nameString, l_cyberpunkItem.s_titleString, l_cyberpunkItem.s_qualityString, l_cyberpunkItem.s_bodyString);
	}
	return inventoryItem(false, false, false, false);
}

bool RoomEscape::addNuclearWinterItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in) {
	for (inventoryItem l_nuclearWinterItem : v_nuclearWinterItems) {
		if (l_nuclearWinterItem.s_nameString == name_in)
			return true;
	}
	v_nuclearWinterItems.push_back(inventoryItem(name_in, title_in, quality_in, body_in));
	return true;
}
inventoryItem RoomEscape::getNuclearWinterItem(std::string name_in) {
	for (inventoryItem l_nuclearWinterItem : v_nuclearWinterItems) {
		if (l_nuclearWinterItem.s_nameString == name_in)
			return inventoryItem(l_nuclearWinterItem.s_nameString, l_nuclearWinterItem.s_titleString, l_nuclearWinterItem.s_qualityString, l_nuclearWinterItem.s_bodyString);
	}
	return inventoryItem(false, false, false, false);
}

bool RoomEscape::addPassiveInvasionItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in) {
	for (inventoryItem l_passiveInvasionItem : v_passiveInvasionItems) {
		if (l_passiveInvasionItem.s_nameString == name_in)
			return true;
	}
	v_passiveInvasionItems.push_back(inventoryItem(name_in, title_in, quality_in, body_in));
	return true;
}
inventoryItem RoomEscape::getPassiveInvasionItem(std::string name_in) {
	for (inventoryItem l_passiveInvasionItem : v_passiveInvasionItems) {
		if (l_passiveInvasionItem.s_nameString == name_in)
			return inventoryItem(l_passiveInvasionItem.s_nameString, l_passiveInvasionItem.s_titleString, l_passiveInvasionItem.s_qualityString, l_passiveInvasionItem.s_bodyString);
	}
	return inventoryItem(false, false, false, false);
}

bool RoomEscape::handleAnswerKeys(std::string& keys_in) {
	std::istringstream iss(keys_in);

	if(!v_answerExpectedKeys.empty())
		v_answerExpectedKeys.erase(v_answerExpectedKeys.begin(), v_answerExpectedKeys.end());

	for (std::string token; std::getline(iss, token, ';'); ) {
		v_answerExpectedKeys.push_back(std::move(token));
	}

	if (!v_answerExpectedKeys.empty())
		return true;
	else
		return false;	
}

bool RoomEscape::checkKeywordPresence(std::string& string_in) {
	for (std::string keyword : v_answerExpectedKeys) {
		if (string_in.find(keyword) != std::string::npos)
			return true;
	}
	return false;
}

bool RoomEscape::checkSolved() {
	if(c_answeredQuestions == 3 && c_presentedQuestions == 3){
		return true;
	}
	else {
		return false;
	}
}

std::string RoomEscape::getChosenTheme() {

	return c_chosenThemeString;
}
