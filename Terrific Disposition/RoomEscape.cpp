#include "RoomEscape.h"

RoomEscape::RoomEscape() {
	c_answeredQuestions = 0;
	c_presentedQuestions = 0;
	c_chosenTheme = "none";
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


void RoomEscape::handleCommand(std::string& command_in) {

	std::string m_command = command_in;
	std::transform(m_command.begin(), m_command.end(), m_command.begin(), ::tolower);

	if (m_command.compare(0, 14, "look attempt: ") == 0) {
		if (m_command.find("room") != std::string::npos
			|| m_command.find("around") != std::string::npos
			|| m_command.find("wall") != std::string::npos
			|| m_command.find("surround") != std::string::npos) {

			v_pendingOutput.push_back(getPlotPoint("one_look_room"));
		}
		else if (m_command.find("clutter") != std::string::npos
			|| m_command.find("floor") != std::string::npos
			|| m_command.find("down") != std::string::npos) {

			v_pendingOutput.push_back(getPlotPoint("two_look_clutter"));
		}
		else if (m_command.find("headgear") != std::string::npos) {
			v_pendingOutput.push_back("Three pieces of headgear: ");
			v_pendingOutput.push_back("[" + getCyberpunkItem("attire_head").s_quality + "] " + getCyberpunkItem("attire_head").s_title + ": " + getCyberpunkItem("attire_head").s_body);
			v_pendingOutput.push_back("[" + getNuclearWinterItem("attire_head").s_quality + "] " + getNuclearWinterItem("attire_head").s_title + ": " + getNuclearWinterItem("attire_head").s_body);
			v_pendingOutput.push_back("[" + getPassiveInvasionItem("attire_head").s_quality + "] " + getPassiveInvasionItem("attire_head").s_title + ": " + getPassiveInvasionItem("attire_head").s_body);

		}
		else if (m_command.find("jacket") != std::string::npos) {
			v_pendingOutput.push_back("Three jackets: ");
			v_pendingOutput.push_back("[" + getCyberpunkItem("attire_torso").s_quality + "] " + getCyberpunkItem("attire_torso").s_title + ": " + getCyberpunkItem("attire_torso").s_body);
			v_pendingOutput.push_back("[" + getNuclearWinterItem("attire_torso").s_quality + "] " + getNuclearWinterItem("attire_torso").s_title + ": " + getNuclearWinterItem("attire_torso").s_body);
			v_pendingOutput.push_back("[" + getPassiveInvasionItem("attire_torso").s_quality + "] " + getPassiveInvasionItem("attire_torso").s_title + ": " + getPassiveInvasionItem("attire_torso").s_body);

		}
		else if (m_command.find("odd") != std::string::npos) {
			v_pendingOutput.push_back("Three odd items: ");
			v_pendingOutput.push_back("[" + getCyberpunkItem("equipment").s_quality + "] " + getCyberpunkItem("equipment").s_title + ": " + getCyberpunkItem("equipment").s_body);
			v_pendingOutput.push_back("[" + getNuclearWinterItem("equipment").s_quality + "] " + getNuclearWinterItem("equipment").s_title + ": " + getNuclearWinterItem("equipment").s_body);
			v_pendingOutput.push_back("[" + getPassiveInvasionItem("equipment").s_quality + "] " + getPassiveInvasionItem("equipment").s_title + ": " + getPassiveInvasionItem("equipment").s_body);

		}
		else if (m_command.find("light") != std::string::npos
			|| m_command.find("red") != std::string::npos
			|| m_command.find("green") != std::string::npos
			|| m_command.find("corner") != std::string::npos) {

			v_pendingOutput.push_back(getPlotPoint("three_look_light"));
		}
		else if (m_command.find("door") != std::string::npos
			|| m_command.find("metal") != std::string::npos
			|| m_command.find("exit") != std::string::npos
			|| m_command.find("entrance") != std::string::npos) {

			v_pendingOutput.push_back(getPlotPoint("four_look_door"));
		}
		else if (m_command.find("console") != std::string::npos
			|| m_command.find("keypad") != std::string::npos
			|| m_command.find("monitor") != std::string::npos
			|| m_command.find("keryboard") != std::string::npos) {

			v_pendingOutput.push_back(getPlotPoint("five_look_console"));
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

		if (ptr_player->v_inventory.size() == 0) {
			for (inventoryItem item : v_items) {
				if (m_item == item.s_title) {
					v_pendingOutput.push_back("You picked up " + m_item + " and placed it in your inventory.");
					ptr_player->addItem(item);
				}
			}
		}
		else if (ptr_player->v_inventory.size() > 0) {
			int m_theme = 0;

			for (int i = 0; i < v_items.size(); i++) {
				if (ptr_player->v_inventory.front().s_title == v_items.at(i).s_title) {
					m_theme = (int)(i / 3);
				}
			}

			for (int i = 0; i < v_items.size(); i++) {
				if (m_item == v_items.at(i).s_title) {
					if ((int)(i / 3) == m_theme) {
						v_pendingOutput.push_back("You picked up " + m_item + " and placed it in your inventory.");
						ptr_player->addItem(v_items.at(i));
					}
					else {
						v_pendingOutput.push_back("That doesn't seem to go with the item you picked up before.");
					}
				}
			}

		}

	}
	else if (m_command.compare(0, 15, "equip attempt: ") == 0) {
		int m_equipCount = 0;
		bool m_result = ptr_player->equipItem(command_in.substr(15, command_in.size()));
		if (m_result) {
			v_pendingOutput.push_back("You equiped " + command_in.substr(15, command_in.size()));

			(ptr_player->c_attireHead != "Empty") ? (m_equipCount++) : (m_equipCount = m_equipCount);
			(ptr_player->c_attireTorso != "Empty") ? (m_equipCount++) : (m_equipCount = m_equipCount);
			(ptr_player->c_equipment != "Empty") ? (m_equipCount++) : (m_equipCount = m_equipCount);

			if (m_equipCount >= 2 && (ptr_player->c_attireHead == getCyberpunkItem("attire_head").s_title
				|| ptr_player->c_attireTorso == getCyberpunkItem("attire_torso").s_title
				|| ptr_player->c_equipment == getCyberpunkItem("equipment").s_title)) {
				c_chosenTheme = "cyberpunk";
			}
			else if (m_equipCount >= 2 && (ptr_player->c_attireHead == getNuclearWinterItem("attire_head").s_title
				|| ptr_player->c_attireTorso == getNuclearWinterItem("attire_torso").s_title
				|| ptr_player->c_equipment == getNuclearWinterItem("equipment").s_title)) {
				c_chosenTheme = "nuclearwinter";
			}
			else if (m_equipCount >= 2 && (ptr_player->c_attireHead == getPassiveInvasionItem("attire_head").s_title
				|| ptr_player->c_attireTorso == getPassiveInvasionItem("attire_torso").s_title
				|| ptr_player->c_equipment == getPassiveInvasionItem("equipment").s_title)) {
				c_chosenTheme = "passiveinvasion";
			}
			else if (m_equipCount >= 1 ) {
				c_chosenTheme = "none";
			}
		}
		else {
			v_pendingOutput.push_back(command_in.substr(15, command_in.size()) + " wasn't found in your inventory.");
		}
		}
	else if (m_command.compare(0, 17, "inspect attempt: ") == 0) {

	}
	else if (m_command.compare(0, 17, "dispose attempt: ") == 0) {
		if (command_in.substr(17, command_in.size()) == ptr_player->c_attireHead ||
			command_in.substr(17, command_in.size()) == ptr_player->c_attireTorso ||
			command_in.substr(17, command_in.size()) == ptr_player->c_equipment) {
			ptr_player->unequipItem(command_in.substr(17, command_in.size()));
		}

		if (!ptr_player->removeItem(command_in.substr(17, command_in.size())))
			v_pendingOutput.push_back(command_in.substr(17, command_in.size()) + " wasn't found in your inventory");
		else
			v_pendingOutput.push_back("You removed " + command_in.substr(17, command_in.size()) + " from your inventory");
	}

	else if (m_command.compare(0, 15, "solve attempt: ") == 0) {
		if (m_command.find("console") != std::string::npos && c_answeredQuestions == 0 && c_presentedQuestions == 0) {
			
			if (c_chosenTheme == "cyberpunk") {
				v_pendingOutput.push_back(getEscapeQuestion("cyberpunk_question_zero").s_name);
				c_presentedQuestions++;
			}
			else if (c_chosenTheme == "nuclearwinter") {
				v_pendingOutput.push_back(getEscapeQuestion("nuclearwinter_question_zero").s_name);
				c_presentedQuestions++;
			}
			else if (c_chosenTheme == "passiveinvasion") {
				v_pendingOutput.push_back(getEscapeQuestion("passiveinvasion_question_zero").s_name);
				c_presentedQuestions++;
			}
			else {
				v_pendingOutput.push_back("Make sure you've equiped yourself before leaving.");
			}
		}
		else if (c_answeredQuestions == 0 && c_presentedQuestions == 1) {
			if (checkKeywordPresence(m_command)) {
				v_pendingOutput.push_back(getPlotPoint("zero_answer"));
				c_answeredQuestions++;

				if (c_chosenTheme == "cyberpunk")
					v_pendingOutput.push_back(getEscapeQuestion("cyberpunk_question_one").s_name);
				else if (c_chosenTheme == "nuclearwinter")
					v_pendingOutput.push_back(getEscapeQuestion("nuclearwinter_question_one").s_name);
				else if (c_chosenTheme == "passiveinvasion")
					v_pendingOutput.push_back(getEscapeQuestion("passiveinvasion_question_one").s_name);
				
				c_presentedQuestions++;
			}
			else {
				v_pendingOutput.push_back("Seems that was incorrect.");
			}
		}

		else if (c_answeredQuestions == 1 && c_presentedQuestions == 2) {
			if (checkKeywordPresence(m_command)) {
				v_pendingOutput.push_back(getPlotPoint("one_answer"));
				c_answeredQuestions++;

				if (c_chosenTheme == "cyberpunk")
					v_pendingOutput.push_back(getEscapeQuestion("cyberpunk_question_two").s_name);
				else if (c_chosenTheme == "nuclearwinter")
					v_pendingOutput.push_back(getEscapeQuestion("nuclearwinter_question_two").s_name);
				else if (c_chosenTheme == "passiveinvasion")
					v_pendingOutput.push_back(getEscapeQuestion("passiveinvasion_question_two").s_name);

				c_presentedQuestions++;
			}
			else {
				v_pendingOutput.push_back("Seems that was incorrect.");
			}
		}

		else if (c_answeredQuestions == 2 && c_presentedQuestions == 3) {
			if (checkKeywordPresence(m_command)) {
				v_pendingOutput.push_back(getPlotPoint("two_answer"));
				c_answeredQuestions++;
			}
			else {
				v_pendingOutput.push_back("Seems that was incorrect.");
			}
		}

	}
}

bool RoomEscape::addPlotPoint(std::string name_in, std::string text_in) {
	for (namedString l_escapePlot : v_escapePlot) {
		if (l_escapePlot.s_name == name_in)
			return true;
	}
	v_escapePlot.push_back(namedString(name_in, text_in));
	return true;
}
std::string RoomEscape::getPlotPoint(std::string name_in) {
	for (namedString l_escapePlot : v_escapePlot) {
		if (l_escapePlot.s_name == name_in)
			return l_escapePlot.s_string;
	}
	return false;
}

bool RoomEscape::addEscapeQuestion(std::string name_in, std::string question_in, std::string answer_in) {
	for (namedDoubleString l_escapeQuestion : v_escapeQuestions) {
		if (l_escapeQuestion.s_name == name_in)
			return true;
	}
	v_escapeQuestions.push_back(namedDoubleString(name_in, question_in, answer_in));
	return true;
}
namedString RoomEscape::getEscapeQuestion(std::string name_in) {
	for (namedDoubleString l_escapeQuestion : v_escapeQuestions) {
		if (l_escapeQuestion.s_name == name_in) {
			handleAnswerKeys(l_escapeQuestion.s_two);
			return namedString(l_escapeQuestion.s_one, l_escapeQuestion.s_two);
		}
	}
	return namedString(false, false);
}

bool RoomEscape::addCyberpunkItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in) {
	for (inventoryItem l_cyberpunkItem : v_cyberpunkItems) {
		if (l_cyberpunkItem.s_name == name_in)
			return true;
	}
	v_cyberpunkItems.push_back(inventoryItem(name_in, title_in, quality_in, body_in));
	return true;
}
inventoryItem RoomEscape::getCyberpunkItem(std::string name_in) {
	for (inventoryItem l_cyberpunkItem : v_cyberpunkItems) {
		if (l_cyberpunkItem.s_name == name_in)
			return inventoryItem(l_cyberpunkItem.s_name, l_cyberpunkItem.s_title, l_cyberpunkItem.s_quality, l_cyberpunkItem.s_body);
	}
	return inventoryItem(false, false, false, false);
}

bool RoomEscape::addNuclearWinterItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in) {
	for (inventoryItem l_nuclearWinterItem : v_nuclearWinterItems) {
		if (l_nuclearWinterItem.s_name == name_in)
			return true;
	}
	v_nuclearWinterItems.push_back(inventoryItem(name_in, title_in, quality_in, body_in));
	return true;
}
inventoryItem RoomEscape::getNuclearWinterItem(std::string name_in) {
	for (inventoryItem l_nuclearWinterItem : v_nuclearWinterItems) {
		if (l_nuclearWinterItem.s_name == name_in)
			return inventoryItem(l_nuclearWinterItem.s_name, l_nuclearWinterItem.s_title, l_nuclearWinterItem.s_quality, l_nuclearWinterItem.s_body);
	}
	return inventoryItem(false, false, false, false);
}

bool RoomEscape::addPassiveInvasionItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in) {
	for (inventoryItem l_passiveInvasionItem : v_passiveInvasionItems) {
		if (l_passiveInvasionItem.s_name == name_in)
			return true;
	}
	v_passiveInvasionItems.push_back(inventoryItem(name_in, title_in, quality_in, body_in));
	return true;
}
inventoryItem RoomEscape::getPassiveInvasionItem(std::string name_in) {
	for (inventoryItem l_passiveInvasionItem : v_passiveInvasionItems) {
		if (l_passiveInvasionItem.s_name == name_in)
			return inventoryItem(l_passiveInvasionItem.s_name, l_passiveInvasionItem.s_title, l_passiveInvasionItem.s_quality, l_passiveInvasionItem.s_body);
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

std::string RoomEscape::checkSolved() {
	if(c_answeredQuestions == 3 && c_presentedQuestions == 3 && c_chosenTheme != "none"){
		return c_chosenTheme;
	}
	else {
		return "none";
	}
}
