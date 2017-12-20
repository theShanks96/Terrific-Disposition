#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <json/json.h>

#include "DataStructs.h"

//!	Manages the majority of the resources by way of json config files
class ResourceManager {
private:
	
	std::vector<namedString> v_configPaths;			//!<	Holds the filepaths for the other configuration files
	std::vector<std::string> v_audioPaths;			//!<	Holds the filepaths for the audio files
	std::vector<std::string> v_fontPaths;			//!<	Holds the filepaths for the font styles

	std::vector<std::string> v_acceptableBoards;	//!<	Holds the templates for the acceptable tiles
	std::vector<std::string> v_cautiousBoards;		//!<	Holds the templates for the cautious tiles
	std::vector<std::string> v_deadlyBoards;		//!<	Holds the templates for the deadly tiles

	std::vector<std::string> v_cyberpunkTheme;		//!<	Holds thematic text for the cyberpunk playthrough
	std::vector<std::string> v_nuclearWinterTheme;	//!<	Holds the thematic text for the nuclear winter playthrough
	std::vector<std::string> v_passiveInvasionTheme;//!<	Holds the thematic text for the passive invasion playthrough

	std::vector<namedString> v_pseudonymOne;		//!<	Holds the text for the first half of a pseudonym
	std::vector<namedString> v_pseudonymTwo;		//!<	Holds the text for the second half of a pseudonym

public:
	
	//!	Constructor for the resource manager
	/*!
		Opens the master configuration file, populating the v_configPaths with the filepaths of the other configuration files
	*/
	//! @param masterConfigFilepath_in Location of the file that holds the filepaths of all other configuration files
	ResourceManager(std::string masterConfigFilepath_in) {
		std::fstream jsonData;
		Json::Value root;
		Json::Reader reader;
		jsonData.open(masterConfigFilepath_in.c_str());

		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << masterConfigFilepath_in << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_configurationPaths = root["ConfigurationPaths"];
			v_configPaths.reserve(m_configurationPaths.size());

			for (int i = 0; i < m_configurationPaths.size(); i++) {
				addConfigPath(m_configurationPaths[i]["name"].asString(), m_configurationPaths[i]["filepath"].asString());
			}			
		}	jsonData.close();

		jsonData.open(getConfigPath("AudioPaths").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getConfigPath("AudioPaths").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_configurationPaths = root["AudioConfiguration"];
			v_configPaths.reserve(m_configurationPaths.size());

			for (int i = 0; i < m_configurationPaths.size(); i++) {
				addConfigPath(m_configurationPaths[i]["name"].asString(), m_configurationPaths[i]["filepath"].asString());
			}
		}	jsonData.close();

		
		jsonData.open(getConfigPath("GenerationConfiguration").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getConfigPath("GenerationConfiguration").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_pseudonymsOne = root["PseudonymOne"];
			v_pseudonymOne.reserve(m_pseudonymsOne.size());

			for (int i = 0; i < m_pseudonymsOne.size(); i++) {
				addPseudonymOne(m_pseudonymsOne[i]["string"].asString());
			}

			const Json::Value m_pseudonymsTwo = root["PseudonymTwo"];
			v_pseudonymTwo.reserve(m_pseudonymsTwo.size());

			for (int i = 0; i < m_pseudonymsTwo.size(); i++) {
				addPseudonymTwo(m_pseudonymsTwo[i]["string"].asString());
			}
		}	jsonData.close();
		
	}

	//	Destructor
	~ResourceManager(){}

	//	Adding and getting the configuration file paths
	bool addConfigPath(std::string textTitle_in, std::string text_in) {
		for (namedString l_configPath : v_configPaths) {
			if (l_configPath.s_name == textTitle_in)
				return true;
		}
		v_configPaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	std::string getConfigPath(std::string textTitle_in) {
		for (namedString l_configPath : v_configPaths) {
			if (l_configPath.s_name == textTitle_in)
				return l_configPath.s_string;
		}
		return false;
	}

	//	Adding and getting the saved texts
	bool addAudioPath(std::string textTitle_in, std::string text_in) {
		
		return true;
	}
	std::string getAudioPath(std::string textTitle_in) {
		
		return "";
	}

	//	Adding and getting the pseudonyms
	bool addPseudonymOne( std::string pseudonym_in ) {
		for (namedString l_pseudonymOne : v_pseudonymOne) {
			if (l_pseudonymOne.s_name == pseudonym_in)
				return true;
		}
		v_pseudonymOne.push_back(namedString(pseudonym_in, "none"));
		return true;
	}
	namedString getPseudonymOne(std::string pseudonym_in) {
		for (namedString l_pseudonymOne : v_pseudonymOne) {
			if (l_pseudonymOne.s_name == pseudonym_in)
				return l_pseudonymOne;
		}
		return namedString("false", "false");
	}
	namedString getRandomPseudonymOne(bool player_in) {
		srand(time(NULL));
		int m_position = rand() % v_pseudonymOne.size();
		namedString m_result = v_pseudonymOne.at(m_position);

		if (player_in) {
			v_pseudonymOne.at(m_position).s_string = "player";
		}
		else {
			std::string m_condition = m_result.s_string;
			while (m_condition == "player") {
				m_position = rand() % v_pseudonymOne.size();
				m_result = v_pseudonymOne.at(m_position);
				m_condition = m_result.s_string;
			}
		}
		return m_result;
	}

	bool addPseudonymTwo(std::string pseudonym_in) {
		for (namedString l_pseudonymTwo : v_pseudonymTwo) {
			if (l_pseudonymTwo.s_name == pseudonym_in)
				return true;
		}
		v_pseudonymTwo.push_back(namedString(pseudonym_in, "none"));
		return true;
	}
	namedString getPseudonymTwo(std::string pseudonym_in) {
		for (namedString l_pseudonymTwo : v_pseudonymTwo) {
			if (l_pseudonymTwo.s_name == pseudonym_in)
				return l_pseudonymTwo;
		}
		return namedString("false", "false");
	}
	namedString getRandomPseudonymTwo(bool player_in) {
		srand(time(NULL));
		int m_position = rand() % v_pseudonymTwo.size();
		namedString m_result = v_pseudonymTwo.at(m_position);

		if (player_in) {
			v_pseudonymTwo.at(m_position).s_string = "player";
		}
		else {
			std::string m_condition = m_result.s_string;
			while (m_condition == "player") {
				m_position = rand() % v_pseudonymTwo.size();
				m_result = v_pseudonymTwo.at(m_position);
				m_condition = m_result.s_string;
			}
		}
		return m_result;
	}


};