#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <iostream>
#include <algorithm>
#include <utility>

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
	
	std::vector<namedDoubleString> v_honestUnreliableBoards;		//<!	Holds the templates for the honestUnreliable Behaviours
	std::vector<namedDoubleString> v_honestReliableBoards;			//<!	Holds the templates for the honestReliable Behaviours
	std::vector<namedDoubleString> v_dishonestReliableBoards;				//<!	Holds the templates for the dishonestReliable Behaviours

	std::vector<namedString> v_acceptableTileBoards;					//!<	Holds the templates for the acceptable tiles
	std::vector<namedString> v_cautiousTileBoards;						//!<	Holds the templates for the cautious tiles
	std::vector<namedString> v_deadlyTileBoards;						//!<	Holds the templates for the deadly tiles
	std::vector<namedString> v_simpleBehaviourBoards;						//!<	Holds the templates for the simple behaviours

	//	thematic words used to fill in the templates
	std::vector<namedString> v_thematicNegativeAdjectives;			//!<	Holds negative thematic adjectives
	std::vector<namedString> v_thematicPositiveAdjectives;			//!<	Holds positive thematic adjectives
	
	std::vector<namedString> v_thematicNegativeVerbs;				//!<	Holds negative thematic verbs
	std::vector<namedString> v_thematicPositiveVerbs;				//!<	Holds positive thematic verbs

	std::vector<namedString> v_thematicNegativeObjectNouns;			//!<	Holds negative thematic object nouns
	std::vector<namedString> v_thematicNegativePersonNouns;			//!<	Holds negative thematic person nouns
	std::vector<namedString> v_thematicPositiveObjectNouns;			//!<	Holds positive thematic object nouns
	std::vector<namedString> v_thematicPositivePersonNouns;			//!<	Holds positive thematic person nouns

	std::vector<namedString> v_thematicPlotKeywords;				//!<	Holds the keywords important to the plot tiles

	std::vector<namedDoubleString> v_firstStageBoards;				//!<	Holds the first plot stage boards
	std::vector<namedDoubleString> v_primaryAllyBoards;				//!<	Holds the primary ally boards
	std::vector<namedDoubleString> v_secondStageBoards;				//!<	Holds the secondt plot stage boards
	std::vector<namedDoubleString> v_tertiaryVillainBoards;			//!<	Holds the tertiary villain boards
	std::vector<namedDoubleString> v_thirdStageBoards;				//!<	Holds the third plot stage boards
	std::vector<namedDoubleString> v_secondaryVillainBoards;		//!<	Holds the secondary villain boards
	std::vector<namedDoubleString> v_fourthStageBoards;				//!<	Holds the fourth plot stage boards
	std::vector<namedDoubleString> v_primaryVillainBoards;			//!<	Holds the primary villain boards

private:
	std::vector<namedString> v_configPaths;							//!<	Holds the filepaths for the other configuration files
	std::vector<namedString> v_audioPaths;							//!<	Holds the filepaths for the audio files
	//std::vector<std::string> v_fontPaths;							//!<	Holds the filepaths for the font styles
	std::vector<namedString> v_themePaths;
	std::vector<namedString> v_storyboardPaths;
	std::vector<namedString> v_savefiles;
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

		//	Savefile paths
		jsonData.open(getConfigPath("SavefilesConfiguration").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getConfigPath("SavefilesConfiguration").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_savefilePaths = root["SavefilesConfiguration"];
			v_savefiles.reserve(m_savefilePaths.size());

			for (int i = 0; i < m_savefilePaths.size(); i++) {
				addSavefilePath(m_savefilePaths[i]["name"].asString(), m_savefilePaths[i]["filepath"].asString());
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

		//	Loading the storyboards
		jsonData.open(getStoryboardPath("AcceptableBoards").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getStoryboardPath("AcceptableBoards").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_acceptable = root["AcceptableBoards"];
			v_acceptableTileBoards.reserve(m_acceptable.size());

			for (int i = 0; i < m_acceptable.size(); i++) {
				addAcceptableBoard(m_acceptable[i]["entry"].asString(), m_acceptable[i]["board"].asString());
			}

		}	jsonData.close();
		jsonData.open(getStoryboardPath("CautiousBoards").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getStoryboardPath("CautiousBoards").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_cautious = root["CautiousBoards"];
			v_cautiousTileBoards.reserve(m_cautious.size());

			for (int i = 0; i < m_cautious.size(); i++) {
				addCautiousBoard(m_cautious[i]["entry"].asString(), m_cautious[i]["board"].asString());
			}

		}	jsonData.close();
		jsonData.open(getStoryboardPath("DeadlyBoards").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getStoryboardPath("DeadlyBoards").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_deadly = root["DeadlyBoards"];
			v_deadlyTileBoards.reserve(m_deadly.size());

			for (int i = 0; i < m_deadly.size(); i++) {
				addDeadlyBoard(m_deadly[i]["entry"].asString(), m_deadly[i]["board"].asString());
			}

		}	jsonData.close();
		jsonData.open(getStoryboardPath("SimpleBoards").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getStoryboardPath("SimpleBoards").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_simple = root["SimpleBoards"];
			v_simpleBehaviourBoards.reserve(m_simple.size());

			for (int i = 0; i < m_simple.size(); i++) {
				v_simpleBehaviourBoards.push_back(namedString(m_simple[i]["entry"].asString(), m_simple[i]["board"].asString()));
			}

		}	jsonData.close();

		//	Loading the behaviour boards
		jsonData.open(getStoryboardPath("HonestUnreliableBoards").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getStoryboardPath("HonestUnreliableBoards").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_honestUnreliable = root["HonestUnreliableBoards"];
			v_honestUnreliableBoards.reserve(m_honestUnreliable.size());

			for (int i = 0; i < m_honestUnreliable.size(); i++) {
				v_honestUnreliableBoards.push_back(namedDoubleString(m_honestUnreliable[i]["low"].asString(), 
					m_honestUnreliable[i]["medium"].asString(), m_honestUnreliable[i]["high"].asString()));
			}

		}	jsonData.close();
		jsonData.open(getStoryboardPath("HonestReliableBoards").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getStoryboardPath("HonestReliableBoards").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_honestReliable = root["HonestReliableBoards"];
			v_honestReliableBoards.reserve(m_honestReliable.size());

			for (int i = 0; i < m_honestReliable.size(); i++) {
				v_honestReliableBoards.push_back(namedDoubleString(m_honestReliable[i]["low"].asString(),
					m_honestReliable[i]["medium"].asString(), m_honestReliable[i]["high"].asString()));
			}

		}	jsonData.close();
		jsonData.open(getStoryboardPath("DishonestReliableBoards").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getStoryboardPath("DishonestReliableBoards").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_dishonestReliable = root["DishonestReliableBoards"];
			v_dishonestReliableBoards.reserve(m_dishonestReliable.size());

			for (int i = 0; i < m_dishonestReliable.size(); i++) {
				v_honestReliableBoards.push_back(namedDoubleString(m_dishonestReliable[i]["low"].asString(),
					m_dishonestReliable[i]["medium"].asString(), m_dishonestReliable[i]["high"].asString()));
			}

		}	jsonData.close();

		//	Plotboard loading
		jsonData.open(getStoryboardPath("PlotBoards").c_str());
		if (!reader.parse(jsonData, root)) {
			std::cout << "Failed to open config file: " << getStoryboardPath("PlotBoards").c_str() << reader.getFormattedErrorMessages();
		}
		else {

			const Json::Value m_firstStage = root["FirstStageBoards"];
			v_firstStageBoards.reserve(m_firstStage.size());
			for (int i = 0; i < m_firstStage.size(); i++) {
				v_firstStageBoards.push_back(namedDoubleString(m_firstStage[i]["entry"].asString(),
					m_firstStage[i]["board"].asString(), "unselected"));
			}
			const Json::Value m_primaryAlly = root["PrimaryAllyBoards"];
			v_primaryAllyBoards.reserve(m_primaryAlly.size());
			for (int i = 0; i < m_primaryAlly.size(); i++) {
				v_primaryAllyBoards.push_back(namedDoubleString(m_primaryAlly[i]["entry"].asString(),
					m_primaryAlly[i]["board"].asString(), "unselected"));
			}

			const Json::Value m_secondStage = root["SecondStageBoards"];
			v_secondStageBoards.reserve(m_secondStage.size());
			for (int i = 0; i < m_secondStage.size(); i++) {
				v_secondStageBoards.push_back(namedDoubleString(m_secondStage[i]["entry"].asString(),
					m_secondStage[i]["board"].asString(), "unselected"));
			}
			const Json::Value m_tertiaryVillain = root["TertiaryVillainBoards"];
			v_tertiaryVillainBoards.reserve(m_tertiaryVillain.size());
			for (int i = 0; i < m_tertiaryVillain.size(); i++) {
				v_tertiaryVillainBoards.push_back(namedDoubleString(m_tertiaryVillain[i]["entry"].asString(),
					m_tertiaryVillain[i]["board"].asString(), "unselected"));
			}

			const Json::Value m_thirdStage = root["ThirdStageBoards"];
			v_thirdStageBoards.reserve(m_thirdStage.size());
			for (int i = 0; i < m_thirdStage.size(); i++) {
				v_thirdStageBoards.push_back(namedDoubleString(m_thirdStage[i]["entry"].asString(),
					m_thirdStage[i]["board"].asString(), "unselected"));
			}
			const Json::Value m_secondaryVillain = root["SecondaryVillainBoards"];
			v_secondaryVillainBoards.reserve(m_tertiaryVillain.size());
			for (int i = 0; i < m_secondaryVillain.size(); i++) {
				v_secondaryVillainBoards.push_back(namedDoubleString(m_secondaryVillain[i]["entry"].asString(),
					m_secondaryVillain[i]["board"].asString(), "unselected"));
			}

			const Json::Value m_fourthStage = root["FourthStageBoards"];
			v_fourthStageBoards.reserve(m_fourthStage.size());
			for (int i = 0; i < m_thirdStage.size(); i++) {
				v_fourthStageBoards.push_back(namedDoubleString(m_fourthStage[i]["entry"].asString(),
					m_fourthStage[i]["board"].asString(), "unselected"));
			}
			const Json::Value m_primaryVillain = root["PrimaryVillainBoards"];
			v_primaryVillainBoards.reserve(m_primaryVillain.size());
			for (int i = 0; i < m_primaryVillain.size(); i++) {
				v_primaryVillainBoards.push_back(namedDoubleString(m_primaryVillain[i]["entry"].asString(),
					m_primaryVillain[i]["board"].asString(), "unselected"));
			}

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

	//!	Loading the list of words that adhere to the chosen theme
	//! @param theme_in The theme chosen by the player
	//! @return Boolean on whether or not the loading suceeded
	bool loadThematicDictionaries(std::string theme_in) {
		
		clearThematicVectors();
		
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
			const Json::Value m_nadjectives = root["NegativeAdjectives"];
			v_thematicNegativeAdjectives.reserve(m_nadjectives.size());
			for (int i = 0; i < m_nadjectives.size(); i++)
				v_thematicNegativeAdjectives.push_back(namedString(m_nadjectives[i]["entry"].asString(), m_nadjectives[i]["definition"].asString()));

			const Json::Value m_padjectives = root["PositiveAdjectives"];
			v_thematicPositiveAdjectives.reserve(m_padjectives.size());
			for (int i = 0; i < m_padjectives.size(); i++)
				v_thematicPositiveAdjectives.push_back(namedString(m_padjectives[i]["entry"].asString(), m_padjectives[i]["definition"].asString()));
			
			//	Verbs being loaded
			const Json::Value m_nverbs = root["NegativeVerbs"];
			v_thematicNegativeVerbs.reserve(m_nverbs.size());
			for (int i = 0; i < m_nverbs.size(); i++)
				v_thematicNegativeVerbs.push_back(namedString(m_nverbs[i]["entry"].asString(), m_nverbs[i]["definition"].asString()));

			const Json::Value m_pverbs = root["PositiveVerbs"];
			v_thematicPositiveVerbs.reserve(m_pverbs.size());
			for (int i = 0; i < m_pverbs.size(); i++)
				v_thematicPositiveVerbs.push_back(namedString(m_pverbs[i]["entry"].asString(), m_pverbs[i]["definition"].asString()));

			//	Nouns being loaded
			const Json::Value m_nonouns = root["NegativeObjectNouns"];
			v_thematicPositiveObjectNouns.reserve(m_nonouns.size());
			for (int i = 0; i < m_nonouns.size(); i++)
				v_thematicNegativeObjectNouns.push_back(namedString(m_nonouns[i]["entry"].asString(), m_nonouns[i]["definition"].asString()));

			const Json::Value m_npnouns = root["NegativePersonNouns"];
			v_thematicPositiveObjectNouns.reserve(m_npnouns.size());
			for (int i = 0; i < m_npnouns.size(); i++)
				v_thematicNegativePersonNouns.push_back(namedString(m_npnouns[i]["entry"].asString(), m_npnouns[i]["definition"].asString()));

			const Json::Value m_ponouns = root["PositiveObjectNouns"];
			v_thematicPositiveObjectNouns.reserve(m_ponouns.size());
			for (int i = 0; i < m_ponouns.size(); i++)
				v_thematicPositiveObjectNouns.push_back(namedString(m_ponouns[i]["entry"].asString(), m_ponouns[i]["definition"].asString()));

			const Json::Value m_ppnouns = root["PositivePersonNouns"];
			v_thematicPositiveObjectNouns.reserve(m_ppnouns.size());
			for (int i = 0; i < m_ppnouns.size(); i++)
				v_thematicPositivePersonNouns.push_back(namedString(m_ppnouns[i]["entry"].asString(), m_ppnouns[i]["definition"].asString()));

			const Json::Value m_keywords = root["PlotKeywords"];
			v_thematicPlotKeywords.reserve(m_keywords.size());
			for (int i = 0; i < m_keywords.size(); i++)
				v_thematicPlotKeywords.push_back(namedString(m_keywords[i]["key"].asString(), m_keywords[i]["name"].asString()));


		}	jsonData.close();
		return true;
	}


	//!	Clear the vectors containing the thematic words
	void clearThematicVectors() {
		v_thematicNegativeAdjectives.clear();
		v_thematicPositiveAdjectives.clear();

		v_thematicNegativeVerbs.clear();
		v_thematicPositiveVerbs.clear();

		v_thematicNegativeObjectNouns.clear();
		v_thematicPositiveObjectNouns.clear();
		v_thematicNegativePersonNouns.clear();
		v_thematicPositivePersonNouns.clear();
	}

	//	Adding and getting the configuration file paths

	//! Add a new configuration path to the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @param text_in The actual filepath
	//! @return Boolean on whether or not the addition suceeded
	bool addConfigPath(std::string textTitle_in, std::string text_in) {
		for (namedString l_configPath : v_configPaths) {
			if (l_configPath.s_nameString == textTitle_in)
				return true;
		}
		v_configPaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	//! Get a configuration path from the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @return The requested filepath
	std::string getConfigPath(std::string textTitle_in) {
		for (namedString l_configPath : v_configPaths) {
			if (l_configPath.s_nameString == textTitle_in)
				return l_configPath.s_string;
		}

		// if it was not found, return first entry
		return v_configPaths.at(0).s_string;
	}

	//	Adding and getting the audio paths

	//! Add a new audio path to the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @param text_in The actual filepath
	//! @return Boolean on whether or not the addition suceeded
	bool addAudioPath(std::string textTitle_in, std::string text_in) {
		for (namedString l_audioPath : v_audioPaths) {
			if (l_audioPath.s_nameString == textTitle_in)
				return true;
		}
		v_audioPaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}

	//! Get an audio path from the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @return The requested filepath
	std::string getAudioPath(std::string textTitle_in) {
		for (namedString l_audioPath : v_audioPaths) {
			if (l_audioPath.s_nameString == textTitle_in)
				return l_audioPath.s_string;
		}

		// if it was not found, return first entry
		return v_audioPaths.at(0).s_string;
	}
	
	//	Adding and getting the theme file paths

	//! Add a new theme path to the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @param text_in The actual filepath
	//! @return Boolean on whether or not the addition suceeded
	bool addThemePath(std::string textTitle_in, std::string text_in) {
		for (namedString l_themePath : v_themePaths) {
			if (l_themePath.s_nameString == textTitle_in)
				return true;
		}
		v_themePaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	//! Get an theme path from the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @return The requested filepath
	std::string getThemePath(std::string textTitle_in) {
		for (namedString l_themePath : v_themePaths) {
			if (l_themePath.s_nameString == textTitle_in)
				return l_themePath.s_string;
		}

		// if it was not found, return first entry
		return v_themePaths.at(0).s_string;
	}

	//	Adding and getting the storyboard file paths
	//! Add a new storyboard path to the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @param text_in The actual filepath
	//! @return Boolean on whether or not the addition suceeded
	bool addStoryboardPath(std::string textTitle_in, std::string text_in) {
		for (namedString l_storyboardPath : v_storyboardPaths) {
			if (l_storyboardPath.s_nameString == textTitle_in)
				return true;
		}
		v_storyboardPaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	//! Get a stroyboard path from the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @return The requested filepath
	std::string getStoryboardPath(std::string textTitle_in) {
		for (namedString l_storyboardPath : v_storyboardPaths) {
			if (l_storyboardPath.s_nameString == textTitle_in)
				return l_storyboardPath.s_string;
		}

		// if it was not found, return first entry
		return v_storyboardPaths.at(0).s_string;
	}

	//	Adding and getting the dictionary file paths
	//! Add a new dictionary path to the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @param text_in The actual filepath
	//! @return Boolean on whether or not the addition suceeded
	bool addDictionaryPath(std::string textTitle_in, std::string text_in) {
		for (namedString l_dictionaryPath : v_dictionaryPaths) {
			if (l_dictionaryPath.s_nameString == textTitle_in)
				return true;
		}
		v_dictionaryPaths.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	//! Get a dictionary path from the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @return The requested filepath
	std::string getDictionaryPath(std::string textTitle_in) {
		for (namedString l_dictionaryPath : v_dictionaryPaths) {
			if (l_dictionaryPath.s_nameString == textTitle_in)
				return l_dictionaryPath.s_string;
		}

		// if it was not found, return first entry
		return v_dictionaryPaths.at(0).s_string;
	}

	//	Adding and getting the savefile paths
	//! Add a new savefile path to the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @param text_in The actual filepath
	//! @return Boolean on whether or not the addition suceeded
	bool addSavefilePath(std::string textTitle_in, std::string text_in) {
		for (namedString l_savefile : v_savefiles) {
			if (l_savefile.s_nameString == textTitle_in)
				return true;
		}
		v_savefiles.push_back(namedString(textTitle_in, text_in));
		return true;
	}
	//! Checks to see if a file path with the same name already exists
	//! @param textTitle_in The name of the player whose save file this belongs to
	//! @return Boolean wether or not it already exists
	bool checkSavefilePaths(std::string textTitle_in) {
		for (namedString l_savefile : v_savefiles) {
			std::string m_savedName = l_savefile.s_nameString;
			std::transform(m_savedName.begin(), m_savedName.end(), m_savedName.begin(), ::tolower);
			std::string m_givenName = textTitle_in;
			std::transform(m_givenName.begin(), m_givenName.end(), m_givenName.begin(), ::tolower);
			if (m_savedName == m_givenName)
				return true;
		}
		return false;
	}
	//! Get a dictionary path from the relevant vector
	//! @param textTitle_in The name of the filepath
	//! @return The requested filepath
	std::string getSavefilePath(std::string textTitle_in) {
		for (namedString l_savefile : v_savefiles) {
			std::string m_savedName = l_savefile.s_nameString;
			std::transform(m_savedName.begin(), m_savedName.end(), m_savedName.begin(), ::tolower);
			std::string m_givenName = textTitle_in;
			std::transform(m_givenName.begin(), m_givenName.end(), m_givenName.begin(), ::tolower);
			if (m_savedName == m_givenName)
				return l_savefile.s_string;
		}

		// if it was not found, return first entry
		return v_savefiles.at(0).s_string;
	}

	//	Adding and getting the pseudonyms
	//! Add a new portion of the first half of the pseudonym
	//! @param pseudonym_in The first half of the pseudonym
	//! @return Boolean on whether or not the addition suceeded
	bool addPseudonymOne( std::string pseudonym_in ) {
		for (namedString l_pseudonymOne : v_pseudonymOne) {
			if (l_pseudonymOne.s_nameString == pseudonym_in)
				return true;
		}
		v_pseudonymOne.push_back(namedString(pseudonym_in, "none"));
		return true;
	}
	//! Get a random first half portion of the pseudonym from the relevant vector
	//! @param player_in Boolean, if true then the returned name is tagged as the player pseudonym
	//! @return The requested pseudonym portion
	namedString getRandomPseudonymOne(bool player_in) {
		std::random_device m_randomDevice;
		std::mt19937 m_mt(m_randomDevice());
		std::uniform_int_distribution<int> m_pseudoDist(0, v_pseudonymOne.size() - 1);
		
		int m_position = m_pseudoDist(m_mt);
		namedString m_result = v_pseudonymOne.at(m_position);

		if (player_in) {
			v_pseudonymOne.at(m_position).s_string = "player";
		}
		else {
			std::string m_condition = m_result.s_string;
			while (m_condition == "player") {
				m_position = m_pseudoDist(m_mt);
				m_result = v_pseudonymOne.at(m_position);
				m_condition = m_result.s_string;
			}
		}
		return m_result;
	}

	//! Add a new portion of the second half of the pseudonym
	//! @param pseudonym_in The second half of the pseudonym
	//! @return Boolean on whether or not the addition suceeded
	bool addPseudonymTwo(std::string pseudonym_in) {
		for (namedString l_pseudonymTwo : v_pseudonymTwo) {
			if (l_pseudonymTwo.s_nameString == pseudonym_in)
				return true;
		}
		v_pseudonymTwo.push_back(namedString(pseudonym_in, "none"));
		return true;
	}
	//! Get a random second half portion of the pseudonym from the relevant vector
	//! @param player_in Boolean, if true then the returned name is tagged as the player pseudonym
	//! @return The requested pseudonym portion
	namedString getRandomPseudonymTwo(bool player_in) {
		std::random_device m_randomDevice;
		std::mt19937 m_mt(m_randomDevice());
		std::uniform_int_distribution<int> m_pseudoDist(0, v_pseudonymTwo.size() - 1);

		int m_position = m_pseudoDist(m_mt);
		namedString m_result = v_pseudonymTwo.at(m_position);

		if (player_in) {
			v_pseudonymTwo.at(m_position).s_string = "player";
		}
		else {
			std::string m_condition = m_result.s_string;
			while (m_condition == "player") {
				m_position = m_pseudoDist(m_mt);
				m_result = v_pseudonymTwo.at(m_position);
				m_condition = m_result.s_string;
			}
		}
		return m_result;
	}

	//	Adding and getting the storyboards
	//! Add a new acceptable board to the relevant vector
	//! @param entry_in The board name
	//! @param board_in The actual board text
	//! @return Boolean on whether or not the addition suceeded
	bool addAcceptableBoard(std::string entry_in, std::string board_in) {
		for (namedString l_acceptableBoard : v_acceptableTileBoards) {
			if (l_acceptableBoard.s_nameString == entry_in)
				return true;
		}
		v_acceptableTileBoards.push_back(namedString(entry_in, board_in));
		return true;
	}
	//! Get a random acceptable board
	//! @return The random board text
	std::string getRandomAcceptableBoard() {
		std::random_device m_randomDevice;
		std::mt19937 m_mt(m_randomDevice());
		std::uniform_int_distribution<int> m_boardDist(0, v_acceptableTileBoards.size());
		//	return the board template text
		return v_acceptableTileBoards.at(m_boardDist(m_mt)).s_string;
	}
	//! Add a new cautious board to the relevant vector
	//! @param entry_in The board name
	//! @param board_in The actual board text
	//! @return Boolean on whether or not the addition suceeded
	bool addCautiousBoard(std::string entry_in, std::string board_in) {
		for (namedString l_cautiousBoard : v_cautiousTileBoards) {
			if (l_cautiousBoard.s_nameString == entry_in)
				return true;
		}
		v_cautiousTileBoards.push_back(namedString(entry_in, board_in));
		return true;
	}
	//! Get a random cautious board
	//! @return The random board text
	std::string getRandomCautiousBoard() {
		std::random_device m_randomDevice;
		std::mt19937 m_mt(m_randomDevice());
		std::uniform_int_distribution<int> m_boardDist(0, v_cautiousTileBoards.size());
		//	return the board template text
		return v_cautiousTileBoards.at(m_boardDist(m_mt)).s_string;
	}
	//! Add a new deadly board to the relevant vector
	//! @param entry_in The board name
	//! @param board_in The actual board text
	//! @return Boolean on whether or not the addition suceeded
	bool addDeadlyBoard(std::string entry_in, std::string board_in) {
		for (namedString l_deadlyBoard : v_deadlyTileBoards) {
			if (l_deadlyBoard.s_nameString == entry_in)
				return true;
		}
		v_deadlyTileBoards.push_back(namedString(entry_in, board_in));
		return true;
	}
	//! Get a random deadly board
	//! @return The random board text
	std::string getRandomDeadlyBoard() {
		std::random_device m_randomDevice;
		std::mt19937 m_mt(m_randomDevice());
		std::uniform_int_distribution<int> m_boardDist(0, v_deadlyTileBoards.size());
		//	return the board template text
		return v_deadlyTileBoards.at(m_boardDist(m_mt)).s_string;
	}

	//! Get an first stage board
	//! @return The actual board text
	std::string getFirstStageBoard() {
		int m_count = 0;
		for (namedDoubleString l_firstStageBoard : v_firstStageBoards) {
			if (l_firstStageBoard.s_secondString == "selected" && m_count <= (v_firstStageBoards.size() / 2))
				m_count++;
			else if (l_firstStageBoard.s_secondString == "selected" && m_count > (v_firstStageBoards.size() / 2))
				return l_firstStageBoard.s_firstString;
			else if (l_firstStageBoard.s_secondString != "selected") {
				l_firstStageBoard.s_secondString = "selected";
				return l_firstStageBoard.s_firstString;
			}
		}

		// if it was not found, return first entry
		v_firstStageBoards.at(0).s_secondString = "selected";
		return v_firstStageBoards.at(0).s_firstString;
	}
	//! Get a primary ally board
	//! @return The actual board text
	std::string getPrimaryAllyBoard() {
		int m_count = 0;
		for (namedDoubleString l_primaryAllyBoard : v_primaryAllyBoards) {
			if (l_primaryAllyBoard.s_secondString == "selected" && m_count <= (v_primaryAllyBoards.size() / 2))
				m_count++;
			else if (l_primaryAllyBoard.s_secondString == "selected" && m_count > (v_primaryAllyBoards.size() / 2))
				return l_primaryAllyBoard.s_firstString;
			else if (l_primaryAllyBoard.s_secondString != "selected") {
				l_primaryAllyBoard.s_secondString = "selected";
				return l_primaryAllyBoard.s_firstString;
			}
		}

		// if it was not found, return first entry
		v_primaryAllyBoards.at(0).s_secondString = "selected";
		return v_primaryAllyBoards.at(0).s_firstString;
	}
	//! Get a second stage board
	//! @return The actual board text
	std::string getSecondStageBoard() {
		int m_count = 0;
		for (namedDoubleString l_secondStageBoard : v_secondStageBoards) {
			if (l_secondStageBoard.s_secondString == "selected" && m_count <= (v_secondStageBoards.size() / 2))
				m_count++;
			else if (l_secondStageBoard.s_secondString == "selected" && m_count > (v_secondStageBoards.size() / 2))
				return l_secondStageBoard.s_firstString;
			else if (l_secondStageBoard.s_secondString != "selected") {
				l_secondStageBoard.s_secondString = "selected";
				return l_secondStageBoard.s_firstString;
			}
		}

		// if it was not found, return second entry
		v_secondStageBoards.at(0).s_secondString = "selected";
		return v_secondStageBoards.at(0).s_firstString;
	}
	//! Get a tertiary villain board
	//! @return The actual board text
	std::string getTertiaryVillainBoard() {
		int m_count = 0;
		for (namedDoubleString l_tertiaryVillainBoard : v_tertiaryVillainBoards) {
			if (l_tertiaryVillainBoard.s_secondString == "selected" && m_count <= (v_tertiaryVillainBoards.size() / 2))
				m_count++;
			else if (l_tertiaryVillainBoard.s_secondString == "selected" && m_count > (v_tertiaryVillainBoards.size() / 2))
				return l_tertiaryVillainBoard.s_firstString;
			else if (l_tertiaryVillainBoard.s_secondString != "selected") {
				l_tertiaryVillainBoard.s_secondString = "selected";
				return l_tertiaryVillainBoard.s_firstString;
			}
		}

		// if it was not found, return first entry
		v_tertiaryVillainBoards.at(0).s_secondString = "selected";
		return v_tertiaryVillainBoards.at(0).s_firstString;
	}	
	//! Get a secondary villain board
	//! @return The actual board text
	std::string getThirdStageBoard() {
		int m_count = 0;
		for (namedDoubleString l_thirdStageBoard : v_thirdStageBoards) {
			if (l_thirdStageBoard.s_secondString == "selected" && m_count <= (v_thirdStageBoards.size() / 2))
				m_count++;
			else if (l_thirdStageBoard.s_secondString == "selected" && m_count > (v_thirdStageBoards.size() / 2))
				return l_thirdStageBoard.s_firstString;
			else if (l_thirdStageBoard.s_secondString != "selected") {
				l_thirdStageBoard.s_secondString = "selected";
				return l_thirdStageBoard.s_firstString;
			}
		}

		// if it was not found, return second entry
		v_thirdStageBoards.at(0).s_secondString = "selected";
		return v_thirdStageBoards.at(0).s_firstString;
	}
	//! Get a secondary villain board
	//! @return The actual board text
	std::string getSecondaryVillainBoard() {
		int m_count = 0;
		for (namedDoubleString l_secondaryVillainBoard : v_secondaryVillainBoards) {
			if (l_secondaryVillainBoard.s_secondString == "selected" && m_count <= (v_secondaryVillainBoards.size() / 2))
				m_count++;
			else if (l_secondaryVillainBoard.s_secondString == "selected" && m_count > (v_secondaryVillainBoards.size() / 2))
				return l_secondaryVillainBoard.s_firstString;
			else if (l_secondaryVillainBoard.s_secondString != "selected") {
				l_secondaryVillainBoard.s_secondString = "selected";
				return l_secondaryVillainBoard.s_firstString;
			}
		}

		// if it was not found, return first entry
		v_secondaryVillainBoards.at(0).s_secondString = "selected";
		return v_secondaryVillainBoards.at(0).s_firstString;
	}
			
	//! Get a fourth stage board
	//! @return The actual board text
	std::string getFourthStageBoard() {
		int m_count = 0;
		for (namedDoubleString l_fourthStageBoard : v_fourthStageBoards) {
			if (l_fourthStageBoard.s_secondString == "selected" && m_count <= (v_fourthStageBoards.size() / 2))
				m_count++;
			else if (l_fourthStageBoard.s_secondString == "selected" && m_count > (v_fourthStageBoards.size() / 2))
				return l_fourthStageBoard.s_firstString;
			else if (l_fourthStageBoard.s_secondString != "selected") {
				l_fourthStageBoard.s_secondString = "selected";
				return l_fourthStageBoard.s_firstString;
			}
		}

		// if it was not found, return second entry
		v_fourthStageBoards.at(0).s_secondString = "selected";
		return v_fourthStageBoards.at(0).s_firstString;
	}
	//! Get a primary villain board
	//! @return The actual board text
	std::string getPrimaryVillainBoard() {
		int m_count = 0;
		for (namedDoubleString l_primaryVillainBoard : v_primaryVillainBoards) {
			if (l_primaryVillainBoard.s_secondString == "selected" && m_count <= (v_primaryVillainBoards.size() / 2))
				m_count++;
			else if (l_primaryVillainBoard.s_secondString == "selected" && m_count > (v_primaryVillainBoards.size() / 2))
				return l_primaryVillainBoard.s_firstString;
			else if (l_primaryVillainBoard.s_secondString != "selected") {
				l_primaryVillainBoard.s_secondString = "selected";
				return l_primaryVillainBoard.s_firstString;
			}
		}

		// if it was not found, return first entry
		v_primaryVillainBoards.at(0).s_secondString = "selected";
		return v_primaryVillainBoards.at(0).s_firstString;
	}

	//! Get a plot keyword by name
	//! @param textTitle_in The key of the term that is needed
	//! @return The requested term
	std::string getPlotKeyword(std::string textTitle_in) {
		for (namedString thematicPlotKeyword : v_thematicPlotKeywords) {
			if (thematicPlotKeyword.s_nameString == textTitle_in)
				return thematicPlotKeyword.s_string;
		}

		// if it was not found, return first entry
		return v_thematicPlotKeywords.at(0).s_string;
	}

	void writeSavefile(saveProfile profile_in) {
		
		std::string m_filepath = "";

		if (checkSavefilePaths(profile_in.s_playerName))
			m_filepath = getSavefilePath(profile_in.s_playerName);
		else
			m_filepath = "../Assets/Savefiles/" + profile_in.s_playerName + ".json";

		Json::Value m_currentSave;
		m_currentSave[profile_in.s_playerName]["name"] = profile_in.s_playerName;
		m_currentSave[profile_in.s_playerName]["health"] = profile_in.s_playerHealth;

		m_currentSave[profile_in.s_playerName]["current_location"]["x"] = profile_in.s_playerCurrentLocation.s_firstInt;
		m_currentSave[profile_in.s_playerName]["current_location"]["y"] = profile_in.s_playerCurrentLocation.s_secondInt;
		m_currentSave[profile_in.s_playerName]["start_location"]["x"] = profile_in.s_playerStartLocation.s_firstInt;
		m_currentSave[profile_in.s_playerName]["start_location"]["y"] = profile_in.s_playerStartLocation.s_secondInt;

		m_currentSave[profile_in.s_playerName]["interactions"] = profile_in.s_interactionsInt;
		m_currentSave[profile_in.s_playerName]["hostility"] = profile_in.s_hostilityInt;
		m_currentSave[profile_in.s_playerName]["recent_pleasantry"] = profile_in.s_recentPleasantryInt;
		m_currentSave[profile_in.s_playerName]["total_interaction_words"] = profile_in.s_totalInteractionWordsInt;

		m_currentSave[profile_in.s_playerName]["player_style"] = profile_in.s_playStyle;

		Json::Value m_inventoryVector(Json::arrayValue);
		for (int i = 0; i < profile_in.v_playerInventory.size(); i++) {
			Json::Value l_item;
			l_item["name"] = (profile_in.v_playerInventory.at(i).s_nameString);
			l_item["title"] = (profile_in.v_playerInventory.at(i).s_titleString);
			l_item["quality"] = (profile_in.v_playerInventory.at(i).s_qualityString);
			l_item["body"] = (profile_in.v_playerInventory.at(i).s_bodyString);

			m_inventoryVector.append(l_item);
		}		m_currentSave[profile_in.s_playerName]["inventory"] = m_inventoryVector;
		m_currentSave[profile_in.s_playerName]["player_head"] = profile_in.s_playerHeadAttire;
		m_currentSave[profile_in.s_playerName]["player_torso"] = profile_in.s_playerTorsoAttire;
		m_currentSave[profile_in.s_playerName]["player_equipment"] = profile_in.s_playerEquipment;

		m_currentSave[profile_in.s_playerName]["map_size"] = profile_in.s_mapSize;
		m_currentSave[profile_in.s_playerName]["theme"] = profile_in.s_worldTheme;
		Json::Value m_plotPointsVector(Json::arrayValue);
		for (int i = 0; i < profile_in.v_plotPoints.size(); i++) {
			Json::Value l_plot;
			l_plot["x"] = (profile_in.v_plotPoints.at(i).s_firstInt);
			l_plot["y"] = (profile_in.v_plotPoints.at(i).s_secondInt);

			m_plotPointsVector.append(l_plot);
		}		m_currentSave[profile_in.s_playerName]["plot_points"] = m_plotPointsVector;

		m_currentSave[profile_in.s_playerName]["honest_reliable"] = profile_in.s_totalHonestReliableInt;
		m_currentSave[profile_in.s_playerName]["honest_unreliable"] = profile_in.s_totalHonestUnreliableInt;
		m_currentSave[profile_in.s_playerName]["dishonest_reliable"] = profile_in.s_totalDishonestReliableInt;

		std::ofstream m_savepath(m_filepath);
		Json::StyledStreamWriter m_saveWriter;
		m_saveWriter.write(m_savepath, m_currentSave);
		

		if(!checkSavefilePaths(profile_in.s_playerName))
			addSavefilePath(profile_in.s_playerName, m_filepath);
		
		Json::Value m_configurations;
		Json::Value m_paths(Json::arrayValue);
		for (int i = 0; i < v_savefiles.size(); i++) {
			Json::Value l_save;
			l_save["name"] = (v_savefiles.at(i).s_nameString);
			l_save["filepath"] = (v_savefiles.at(i).s_string);

			m_paths.append(l_save);
		}		m_configurations["SavefilesConfiguration"] = m_paths;

		std::ofstream m_savefiles(getConfigPath("SavefilesConfiguration"));
		Json::StyledStreamWriter m_configWriter;
		m_configWriter.write(m_savefiles, m_configurations);
	}

	saveProfile loadSavefile(std::string name_in) {
		//	It should be noted, that the savefile's presence will be checked beforehand
		saveProfile m_outgoingProfile = saveProfile();

		std::fstream jsonData;
		Json::Value m_currentSave;
		Json::Reader reader;
		jsonData.open(getSavefilePath(name_in));

		std::string m_properName = titleCase(name_in, ' ');

		for (int i = 0; i < v_pseudonymOne.size(); i++) {
			if (m_properName.find(v_pseudonymOne.at(i).s_nameString) != std::string::npos) {
				v_pseudonymOne.at(i).s_string = "player";
			}
		}
		for (int i = 0; i < v_pseudonymTwo.size(); i++) {
			if (m_properName.find(v_pseudonymTwo.at(i).s_nameString) != std::string::npos) {
				v_pseudonymTwo.at(i).s_string = "player";
			}
		}

		//	Master configuration paths
		if (!reader.parse(jsonData, m_currentSave)) {
			std::cout << "Failed to open config file: " << getSavefilePath(m_properName) << reader.getFormattedErrorMessages();
		}
		else {
			
			m_outgoingProfile.s_playerName = m_currentSave[m_properName]["name"].asString();
			m_outgoingProfile.s_playerHealth = m_currentSave[m_properName]["health"].asFloat();

			m_outgoingProfile.s_playerCurrentLocation.s_firstInt = m_currentSave[m_properName]["current_location"]["x"].asInt();
			m_outgoingProfile.s_playerCurrentLocation.s_secondInt = m_currentSave[m_properName]["current_location"]["y"].asInt();
			m_outgoingProfile.s_playerStartLocation.s_firstInt = m_currentSave[m_properName]["start_location"]["x"].asInt();
			m_outgoingProfile.s_playerStartLocation.s_secondInt = m_currentSave[m_properName]["start_location"]["y"].asInt();

			m_outgoingProfile.s_interactionsInt = m_currentSave[m_properName]["interactions"].asInt();
			m_outgoingProfile.s_hostilityInt = m_currentSave[m_properName]["hostility"].asInt();
			m_outgoingProfile.s_recentPleasantryInt = m_currentSave[m_properName]["recent_pleasantry"].asInt();
			m_outgoingProfile.s_totalInteractionWordsInt = m_currentSave[m_properName]["total_interaction_words"].asInt();

			m_outgoingProfile.s_playStyle = m_currentSave[m_properName]["player_style"].asFloat();

			const Json::Value m_inventory = m_currentSave[m_properName]["inventory"];
			m_outgoingProfile.v_playerInventory.clear();
			m_outgoingProfile.v_playerInventory.reserve(m_inventory.size());
			for (int i = 0; i < m_inventory.size(); i++) {
				m_outgoingProfile.v_playerInventory.push_back(inventoryItem(m_inventory[i]["name"].asString(),
					m_inventory[i]["title"].asString(), m_inventory[i]["quality"].asString(), m_inventory[i]["body"].asString()));
			}
			m_outgoingProfile.s_playerHeadAttire = m_currentSave[m_properName]["player_head"].asString();
			m_outgoingProfile.s_playerTorsoAttire = m_currentSave[m_properName]["player_torso"].asString();
			m_outgoingProfile.s_playerEquipment = m_currentSave[m_properName]["player_equipment"].asString();

			m_outgoingProfile.s_mapSize = m_currentSave[m_properName]["map_size"].asInt();
			m_outgoingProfile.s_worldTheme = m_currentSave[m_properName]["theme"].asString();
			const Json::Value m_plotPoints = m_currentSave[m_properName]["plot_points"];
			m_outgoingProfile.v_plotPoints.clear();
			m_outgoingProfile.v_plotPoints.reserve(m_plotPoints.size());
			for (int i = 0; i < m_plotPoints.size(); i++) {
				m_outgoingProfile.v_plotPoints.push_back(int2d(m_plotPoints[i]["x"].asInt(), m_plotPoints[i]["y"].asInt()));
			}

			m_outgoingProfile.s_totalHonestReliableInt = m_currentSave[m_properName]["honest_reliable"].asInt();
			m_outgoingProfile.s_totalHonestUnreliableInt = m_currentSave[m_properName]["honest_unreliable"].asInt();
			m_outgoingProfile.s_totalDishonestReliableInt = m_currentSave[m_properName]["dishonest_reliable"].asInt();
			
		}	jsonData.close();

		return m_outgoingProfile;
	}


	std::string titleCase(std::string str_in, char ch_in) {
		std::string m_next;
		std::vector<std::string> v_result;

		std::string m_temp = str_in;

		// For each character in the string
		for (std::string::const_iterator it = m_temp.begin(); it != m_temp.end(); it++) {
			// If we've hit the terminal character
			if (*it == ch_in) {
				// If we have some characters accumulated
				if (!m_next.empty()) {
					// Add them to the lowercase result vector
					v_result.push_back(m_next);
					m_next.clear();
				}
			}
			else {
				// Accumulate the next character into the sequence
				m_next += *it;
			}
		}
		if (!m_next.empty())
			v_result.push_back(m_next);
		
		for (int i = 0; i < v_result.size(); i++) {
			v_result.at(i).at(0) = toupper(v_result.at(i).at(0));
		}


		std::string m_outgoingString;
		for (int i = 0; i < v_result.size(); i++) {
			m_outgoingString.append(v_result.at(i));
			if (i != v_result.size() - 1)
				m_outgoingString.append(" ");
		}


		return m_outgoingString;
	}
};