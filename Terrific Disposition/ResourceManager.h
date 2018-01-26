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
public:
	std::vector<std::string> v_vulgarities;
	
	std::vector<std::string> v_hostileAdjectives;
	std::vector<std::string> v_hostileNouns;
	std::vector<std::string> v_hostileVerbs;

	std::vector<std::string> v_pleasantAdjectives;
	std::vector<std::string> v_pleasantNouns;
	std::vector<std::string> v_pleasantVerbs;

	std::vector<std::string> v_acceptableBoards;					//!<	Holds the templates for the acceptable tiles
	std::vector<std::string> v_cautiousBoards;						//!<	Holds the templates for the cautious tiles
	std::vector<std::string> v_deadlyBoards;						//!<	Holds the templates for the deadly tiles

	std::vector<std::string> v_thematicAdjectives;					//!<	Holds thematic text for the cyberpunk playthrough
	std::vector<std::string> v_thematicNouns;						//!<	Holds the thematic text for the nuclear winter playthrough
	std::vector<std::string> v_thematicVerbs;						//!<	Holds the thematic text for the passive invasion playthrough

private:
	std::vector<namedString> v_configPaths;							//!<	Holds the filepaths for the other configuration files
	std::vector<namedString> v_audioPaths;							//!<	Holds the filepaths for the audio files
	//std::vector<std::string> v_fontPaths;							//!<	Holds the filepaths for the font styles
	std::vector<namedString> v_themePaths;
	std::vector<namedString> v_storyboardPaths;
	std::vector<namedString> v_dictionaryPaths;

	std::vector<namedString> v_pseudonymOne;						//!<	Holds the text for the first half of a pseudonym
	std::vector<namedString> v_pseudonymTwo;						//!<	Holds the text for the second half of a pseudonym

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

		//	Master configuration paths
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

		//	Audio paths
		jsonData.open(getConfigPath("AudioPaths").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getConfigPath("AudioPaths").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_configurationPaths = root["AudioConfiguration"];
			v_configPaths.reserve(m_configurationPaths.size());

			for (int i = 0; i < m_configurationPaths.size(); i++) {
				addAudioPath(m_configurationPaths[i]["name"].asString(), m_configurationPaths[i]["filepath"].asString());
			}
		}	jsonData.close();

		//	Themes paths
		jsonData.open(getConfigPath("ThemesConfiguration").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getConfigPath("ThemesConfiguration").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_themePaths = root["ThemesConfiguration"];
			v_themePaths.reserve(m_themePaths.size());

			for (int i = 0; i < m_themePaths.size(); i++) {
				addThemePath(m_themePaths[i]["name"].asString(), m_themePaths[i]["filepath"].asString());
			}
		}	jsonData.close();

		//	Storyboard paths
		jsonData.open(getConfigPath("StoryboardsConfiguration").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getConfigPath("StoryboardsConfiguration").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_storyboardPaths = root["StoryboardsConfiguration"];
			v_storyboardPaths.reserve(m_storyboardPaths.size());

			for (int i = 0; i < m_storyboardPaths.size(); i++) {
				addStoryboardPath(m_storyboardPaths[i]["name"].asString(), m_storyboardPaths[i]["filepath"].asString());
			}
		}	jsonData.close();

		//	Dictionary paths
		jsonData.open(getConfigPath("DictionariesConfiguration").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getConfigPath("DictionariesConfiguration").c_str() << reader.getFormattedErrorMessages();
		}
		else {
		
			const Json::Value m_dictionaryPaths = root["DictionariesConfiguration"];
			v_dictionaryPaths.reserve(m_dictionaryPaths.size());
		
			for (int i = 0; i < m_dictionaryPaths.size(); i++) {
				addDictionaryPath(m_dictionaryPaths[i]["name"].asString(), m_dictionaryPaths[i]["filepath"].asString());
			}
		}	jsonData.close();

		//	Populate specific dictionaries
		//	Vulgarities
		jsonData.open(getDictionaryPath("Vulgarities").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getDictionaryPath("Vulgarities").c_str() << reader.getFormattedErrorMessages();
		}
		else {
			const Json::Value m_vulgarities = root["Vulgarities"];
			v_vulgarities.reserve(m_vulgarities.size());

			for (int i = 0; i < m_vulgarities.size(); i++)
				v_vulgarities.push_back(m_vulgarities[i]["entry"].asString());
			
		}	jsonData.close();

		//	HostileAdjectives
		jsonData.open(getDictionaryPath("HostileAdjectives").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getDictionaryPath("HostileAdjectives").c_str() << reader.getFormattedErrorMessages();
		}
		else {
			const Json::Value m_entries = root["HostileAdjectives"];
			v_hostileAdjectives.reserve(m_entries.size());

			for (int i = 0; i < m_entries.size(); i++)
				v_hostileAdjectives.push_back(m_entries[i]["entry"].asString());

		}	jsonData.close();
		//	HostileNouns
		jsonData.open(getDictionaryPath("HostileNouns").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getDictionaryPath("HostileNouns").c_str() << reader.getFormattedErrorMessages();
		}
		else {
			const Json::Value m_entries = root["HostileNouns"];
			v_hostileNouns.reserve(m_entries.size());

			for (int i = 0; i < m_entries.size(); i++)
				v_hostileNouns.push_back(m_entries[i]["entry"].asString());

		}	jsonData.close();
		//	HostileVerbs
		jsonData.open(getDictionaryPath("HostileVerbs").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getDictionaryPath("HostileVerbs").c_str() << reader.getFormattedErrorMessages();
		}
		else {
			const Json::Value m_entries = root["HostileVerbs"];
			v_hostileVerbs.reserve(m_entries.size());

			for (int i = 0; i < m_entries.size(); i++)
				v_hostileVerbs.push_back(m_entries[i]["entry"].asString());

		}	jsonData.close();

		//	PleasantAdjectives
		jsonData.open(getDictionaryPath("PleasantAdjectives").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getDictionaryPath("PleasantAdjectives").c_str() << reader.getFormattedErrorMessages();
		}
		else {
			const Json::Value m_entries = root["PleasantAdjectives"];
			v_pleasantAdjectives.reserve(m_entries.size());

			for (int i = 0; i < m_entries.size(); i++)
				v_pleasantAdjectives.push_back(m_entries[i]["entry"].asString());

		}	jsonData.close();
		//	PleasantNouns
		jsonData.open(getDictionaryPath("PleasantNouns").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getDictionaryPath("PleasantNouns").c_str() << reader.getFormattedErrorMessages();
		}
		else {
			const Json::Value m_entries = root["PleasantNouns"];
			v_pleasantNouns.reserve(m_entries.size());

			for (int i = 0; i < m_entries.size(); i++)
				v_pleasantNouns.push_back(m_entries[i]["entry"].asString());

		}	jsonData.close();
		//	PleasantVerbs
		jsonData.open(getDictionaryPath("PleasantVerbs").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getDictionaryPath("PleasantVerbs").c_str() << reader.getFormattedErrorMessages();
		}
		else {
			const Json::Value m_entries = root["PleasantVerbs"];
			v_pleasantVerbs.reserve(m_entries.size());

			for (int i = 0; i < m_entries.size(); i++)
				v_pleasantVerbs.push_back(m_entries[i]["entry"].asString());

		}	jsonData.close();

		//	GenerationConfiguration text
		jsonData.open(getThemePath("GenerationConfiguration").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getThemePath("GenerationConfiguration").c_str() << reader.getFormattedErrorMessages();
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

	//!	Loading the theme information
	bool loadThemeSemanticField(std::string theme_in) {
		std::fstream jsonData;
		Json::Value root;
		Json::Reader reader;
		
		//	Loading the chosen theme words
		jsonData.open(getThemePath(theme_in + "Theme"));
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getThemePath(theme_in + "Theme") << reader.getFormattedErrorMessages();
			return false;
		}
		else {
			//	Adjectives being loaded
			const Json::Value m_adjectives = root["Adjectives"];
			v_thematicAdjectives.reserve(m_adjectives.size());
			for (int i = 0; i < m_adjectives.size(); i++)
				v_thematicAdjectives.push_back(m_adjectives[i]["entry"].asString());

			//	Nouns being loaded
			const Json::Value m_nouns = root["Nouns"];
			v_thematicNouns.reserve(m_nouns.size());
			for (int i = 0; i < m_nouns.size(); i++)
				v_thematicNouns.push_back(m_nouns[i]["entry"].asString());

			//	Verbs being loaded
			const Json::Value m_verbs = root["Verbs"];
			v_thematicVerbs.reserve(m_verbs.size());
			for (int i = 0; i < m_verbs.size(); i++)
				v_thematicVerbs.push_back(m_verbs[i]["entry"].asString());

		}	jsonData.close();
		return true;
	}

	//	Adding and getting the configuration file paths
	bool addConfigPath(std::string textTitle_in, std::string text_in) {
		for (namedString l_configPath : v_configPaths) {
			if (l_configPath.s_nameString == textTitle_in)
				return true;
		}
		v_configPaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	std::string getConfigPath(std::string textTitle_in) {
		for (namedString l_configPath : v_configPaths) {
			if (l_configPath.s_nameString == textTitle_in)
				return l_configPath.s_string;
		}

		// if it was not found, return first entry
		return v_configPaths.at(0).s_string;
	}

	//	Adding and getting the saved texts
	bool addAudioPath(std::string textTitle_in, std::string text_in) {
		for (namedString l_audioPath : v_audioPaths) {
			if (l_audioPath.s_nameString == textTitle_in)
				return true;
		}
		v_audioPaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	std::string getAudioPath(std::string textTitle_in) {
		for (namedString l_audioPath : v_audioPaths) {
			if (l_audioPath.s_nameString == textTitle_in)
				return l_audioPath.s_string;
		}

		// if it was not found, return first entry
		return v_audioPaths.at(0).s_string;
	}
	
	//	Adding and getting the theme file paths
	bool addThemePath(std::string textTitle_in, std::string text_in) {
		for (namedString l_themePath : v_themePaths) {
			if (l_themePath.s_nameString == textTitle_in)
				return true;
		}
		v_themePaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	std::string getThemePath(std::string textTitle_in) {
		for (namedString l_themePath : v_themePaths) {
			if (l_themePath.s_nameString == textTitle_in)
				return l_themePath.s_string;
		}

		// if it was not found, return first entry
		return v_themePaths.at(0).s_string;
	}

	//	Adding and getting the storyboard file paths
	bool addStoryboardPath(std::string textTitle_in, std::string text_in) {
		for (namedString l_storyboardPath : v_storyboardPaths) {
			if (l_storyboardPath.s_nameString == textTitle_in)
				return true;
		}
		v_storyboardPaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	std::string getStoryboardPath(std::string textTitle_in) {
		for (namedString l_storyboardPath : v_storyboardPaths) {
			if (l_storyboardPath.s_nameString == textTitle_in)
				return l_storyboardPath.s_string;
		}

		// if it was not found, return first entry
		return v_storyboardPaths.at(0).s_string;
	}

	//	Adding and getting the dictionary file paths
	bool addDictionaryPath(std::string textTitle_in, std::string text_in) {
		for (namedString l_dictionaryPath : v_dictionaryPaths) {
			if (l_dictionaryPath.s_nameString == textTitle_in)
				return true;
		}
		v_dictionaryPaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	std::string getDictionaryPath(std::string textTitle_in) {
		for (namedString l_dictionaryPath : v_dictionaryPaths) {
			if (l_dictionaryPath.s_nameString == textTitle_in)
				return l_dictionaryPath.s_string;
		}

		// if it was not found, return first entry
		return v_dictionaryPaths.at(0).s_string;
	}

	//	Adding and getting the pseudonyms
	bool addPseudonymOne( std::string pseudonym_in ) {
		for (namedString l_pseudonymOne : v_pseudonymOne) {
			if (l_pseudonymOne.s_nameString == pseudonym_in)
				return true;
		}
		v_pseudonymOne.push_back(namedString(pseudonym_in, "none"));
		return true;
	}
	namedString getPseudonymOne(std::string pseudonym_in) {
		for (namedString l_pseudonymOne : v_pseudonymOne) {
			if (l_pseudonymOne.s_nameString == pseudonym_in)
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
			if (l_pseudonymTwo.s_nameString == pseudonym_in)
				return true;
		}
		v_pseudonymTwo.push_back(namedString(pseudonym_in, "none"));
		return true;
	}
	namedString getPseudonymTwo(std::string pseudonym_in) {
		for (namedString l_pseudonymTwo : v_pseudonymTwo) {
			if (l_pseudonymTwo.s_nameString == pseudonym_in)
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