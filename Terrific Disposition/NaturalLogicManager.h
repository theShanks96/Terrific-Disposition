#pragma once

#include <Python.h>
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

#include <pybind11\embed.h>
#include <pybind11\pybind11.h>

#include "ResourceManager.h"
#include "DataStructs.h"



class NaturalLogicManager {
public:
	ResourceManager * ptr_resourceManager;

	pybind11::object c_globals;

	std::vector<std::string> v_entryStrings;
	std::vector<std::string> v_resultStrings;

	std::vector<std::string> v_processingWordStrings;
	std::vector<std::string> v_processingPOSStrings;

	pybind11::scoped_interpreter* ptr_scopedInterpreter;
	pybind11::module c_nltkModule;
	pybind11::module c_pydictionaryModule;

	int c_vectorCapacityInt;
	//! NaturalLogicManager's contructor
	//! @param resource_in A pointer to the utilised ResourceManager
	NaturalLogicManager(ResourceManager* resource_in) {
		//	Link the resource manager, as its information will be necessary
		ptr_resourceManager = resource_in;
		
		c_vectorCapacityInt = 16;

		//	Prepare the vectors
		v_entryStrings.reserve(c_vectorCapacityInt);
		v_resultStrings.reserve(c_vectorCapacityInt);

		//pybind11::scoped_interpreter guard{}; // start the interpreter and keep it alive
		ptr_scopedInterpreter = new pybind11::scoped_interpreter;

		c_nltkModule = pybind11::module::import("nltk");
		c_pydictionaryModule = pybind11::module::import("PyDictionary");
		
	}

	~NaturalLogicManager() {
	}

	//! This will identify the definition of the given entry, if any exists
	//! @param entry_in The entry to be defined
	//! @param type_in The part-of-speech that the entry has been identified as being
	//! @return The definition given by the pydictionary modules
	std::string PyDictionaryDefinition(std::string entry_in, std::string type_in) {
		try {
			pybind11::dict m_localEnv;

			pybind11::object m_dictionary = c_pydictionaryModule.attr("PyDictionary")();
			pybind11::object m_meaning = m_dictionary.attr("meaning")(entry_in);
			m_localEnv["meaning_in"] = m_meaning;

			if (type_in == "adjective" || type_in == "Adjective"
				|| type_in.find("JJ") != std::string::npos
				|| type_in.find("jj") != std::string::npos) {
				pybind11::exec(
					"definition = []\n"
					"meanings = meaning_in\n"
					"final = meanings['Adjective'][0]\n"
					, pybind11::globals(), m_localEnv);
			}

			else if (type_in == "noun" || type_in == "Noun"
				|| type_in.find("NN") != std::string::npos
				|| type_in.find("nn") != std::string::npos) {
				pybind11::exec(
					"definition = []\n"
					"meanings = meaning_in\n"
					"final = meanings['Noun'][0]\n"
					, pybind11::globals(), m_localEnv);
			}

			else if (type_in == "verb" || type_in == "Verb"
				|| type_in.find("VB") != std::string::npos
				|| type_in.find("vb") != std::string::npos) {
				pybind11::exec(
					"definition = []\n"
					"meanings = meaning_in\n"
					"final = meanings['Verb'][0]\n"
					, pybind11::globals(), m_localEnv);
			}
			else {
				return "error, not defined.";
			}

			std::cout << m_localEnv["final"].cast<std::string>() << std::endl;

			return m_localEnv["final"].cast<std::string>();

		}
		catch (const pybind11::error_already_set&) {
			std::cerr << ">>> Error! Uncaught exception:\n";
			PyErr_Print();
			return "error, not defined.";
		}
	}

	//!	This will simply identify the part-of-speech for each word in the entry
	//! @param entry_in The entry to be processed
	void nltkGenericProcessing(std::string entry_in) {
		pybind11::dict m_localEnv;

		pybind11::object tokens = c_nltkModule.attr("word_tokenize")(entry_in);
		pybind11::object tagged = c_nltkModule.attr("pos_tag")(tokens);

		m_localEnv["entry_in"] = tagged;
		pybind11::exec(
			"pos = []\n"
			"words = []\n"
			"final = []\n"
			"entry = entry_in\n"
			"final = entry\n"
			"for i in range(0, len(final)):\n"
			"    pos.append(final[i][1])\n"
			"    words.append(final[i][0])\n"
			, pybind11::globals(), m_localEnv);

		pybind11::exec(
			"final_pos = []\n"
			"final_words = []\n"
			"final_pos = ';'.join(pos)\n"
			"final_words = ';'.join(words)\n"
			, pybind11::globals(), m_localEnv);

		std::cout << m_localEnv["final_pos"].cast<std::string>() << std::endl;
		std::cout << m_localEnv["final_words"].cast<std::string>() << std::endl;

		entryPushBack(m_localEnv["final_words"].cast<std::string>());
		resultPushBack(m_localEnv["final_pos"].cast<std::string>());
	}
	
	//! Process the entry, primarily with the use of nltk
	//! @param entry_in The entry to be processed
	//! @result The command profile, with the different statistics on the given entry
	commandProfile nltkEntryProcessing(std::string entry_in) {
		
		nltkGenericProcessing(entry_in);

		return bigThreeEntryProcessing();

	}

	//! Designed to use nltk and pydictionary to define words for the user
	//! @param entry_in The word to be defined by the python scripts
	//! @return The definition of the given entry
	std::string nltkDictionaryDefinition(std::string entry_in) {
		std::string m_entry = "";
		std::vector<std::string> v_definitions;
		if (entry_in.find("define") != std::string::npos)
			m_entry = entry_in.substr(6, entry_in.size());
		else
			m_entry = entry_in;

		nltkGenericProcessing(m_entry);

		v_processingWordStrings.clear();
		v_processingWordStrings = explode(v_entryStrings.back(), ';');
		v_definitions.reserve(v_processingWordStrings.size());

		v_processingPOSStrings.clear();
		v_processingPOSStrings = explode(v_resultStrings.back(), ';');

		for (int i = 0; i < v_processingPOSStrings.size(); i++) {
			bool m_wordProcessed = false;
			//	ADJECTIVES
			//	Check to see if the word is a negative thematic adjective
			for (namedString l_negativeAdjective : ptr_resourceManager->v_thematicNegativeAdjectives) {
				if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_negativeAdjective.s_nameString) != std::string::npos) {
					v_definitions.push_back(l_negativeAdjective.s_string);
					m_wordProcessed = true;
				}
			}
			//	Check to see if the word is a positive thematic adjective
			if (!m_wordProcessed) {
				for (namedString l_positiveAdjective : ptr_resourceManager->v_thematicPositiveAdjectives) {
					if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_positiveAdjective.s_nameString) != std::string::npos) {
						v_definitions.push_back(l_positiveAdjective.s_string);
						m_wordProcessed = true;
					}
				}
			}
			//	NOUNS
			//	Check to see if the word is a negative thematic object noun
			for (namedString l_negativeObjectNoun : ptr_resourceManager->v_thematicNegativeObjectNouns) {
				if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_negativeObjectNoun.s_nameString) != std::string::npos) {
					v_definitions.push_back(l_negativeObjectNoun.s_string);
					m_wordProcessed = true;
				}
			}
			//	Check to see if the word is a positive thematic object noun
			if (!m_wordProcessed) {
				for (namedString l_positiveObjectNoun : ptr_resourceManager->v_thematicPositiveObjectNouns) {
					if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_positiveObjectNoun.s_nameString) != std::string::npos) {
						v_definitions.push_back(l_positiveObjectNoun.s_string);
						m_wordProcessed = true;
					}
				}
			}
			//	Check to see if the word is a negative thematic person noun
			if (!m_wordProcessed) {
				for (namedString l_negativePersonNoun : ptr_resourceManager->v_thematicNegativePersonNouns) {
					if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_negativePersonNoun.s_nameString) != std::string::npos) {
						v_definitions.push_back(l_negativePersonNoun.s_string);
						m_wordProcessed = true;
					}
				}
			}
			//	Check to see if the word is a positive thematic person noun
			if (!m_wordProcessed) {
				for (namedString l_positivePersonNoun : ptr_resourceManager->v_thematicPositivePersonNouns) {
					if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_positivePersonNoun.s_nameString) != std::string::npos) {
						v_definitions.push_back(l_positivePersonNoun.s_string);
						m_wordProcessed = true;
					}
				}
			}
			//	VERBS
			//	Check to see if the word is a negative thematic verb
			for (namedString l_negativeVerb : ptr_resourceManager->v_thematicNegativeVerbs) {
				if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_negativeVerb.s_nameString) != std::string::npos) {
					v_definitions.push_back(l_negativeVerb.s_string);
					m_wordProcessed = true;
				}
			}
			//	Check to see if the word is a positive thematic verb
			if (!m_wordProcessed) {
				for (namedString l_positiveVerb : ptr_resourceManager->v_thematicPositiveVerbs) {
					if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_positiveVerb.s_nameString) != std::string::npos) {
						v_definitions.push_back(l_positiveVerb.s_string);
						m_wordProcessed = true;
					}
				}
			}
			
			//	JJ, JJR, JJS are all adjectives
			if (!m_wordProcessed && (v_processingPOSStrings.at(i).find("JJ") != std::string::npos ||
				v_processingPOSStrings.at(i).find("jj") != std::string::npos)) {
								
				//	Check to see if PyAdjective has an available definition
				v_definitions.push_back(PyDictionaryDefinition(v_processingWordStrings.at(i), "Adjective"));
				m_wordProcessed = true;
			}
			//	NN, NNS, NNP, NNPS are all nouns
			else if (!m_wordProcessed && (v_processingPOSStrings.at(i).find("NN") != std::string::npos ||
				v_processingPOSStrings.at(i).find("nn") != std::string::npos)) {
								
				//	Check to see if PyAdjective has an available definition
				v_definitions.push_back(PyDictionaryDefinition(v_processingWordStrings.at(i), "Noun"));
				m_wordProcessed = true;
			}
			//	VB, VBD, VBG, VBN, VBP, VBZ are all adjectives
			else if (!m_wordProcessed && (v_processingPOSStrings.at(i).find("VB") != std::string::npos ||
				v_processingPOSStrings.at(i).find("vb") != std::string::npos)) {
								
				//	Check to see if PyAdjective has an available definition
				v_definitions.push_back(PyDictionaryDefinition(v_processingWordStrings.at(i), "Verb"));
				m_wordProcessed = true;
			}

			//	No definition was found
			if (!m_wordProcessed) {
				v_definitions.push_back("error, not defined");
			}
		}


		std::vector<std::string> v_temp;
		std::string m_temp = "";

		v_temp.reserve(v_definitions.size());
		for (int i = 0; i < v_definitions.size(); i++) {
			m_temp.append(v_processingWordStrings.at(i));
			m_temp.append(": ");
			m_temp.append(v_definitions.at(i));

			v_temp.push_back(m_temp);
			m_temp = "";
		}
		if (v_temp.size() == 1)
			return v_temp.at(0);
		else
			return implode(v_temp, ';');

	}

	//! Process the fuzzybehaviour boards
	//! @param behaviour_in The fuzzybehaviour profile
	//! @param magnitude_in The magnitude of the fuzzybehaviour profile
	//! @param plot_in The next plot point that the player is headed towards
	//! @param player_in The player's current position
	//! @return The processed board ready for viewing by the user
	std::string fuzzyBehaviourBoardProcessing(int behaviour_in, int magnitude_in, int2d plot_in, int2d player_in) {

		int m_boardSizeInt = 0;		

		if (behaviour_in >= 0 && behaviour_in < 30)
			m_boardSizeInt = ptr_resourceManager->v_honestUnreliableBoards.size();
		else if (behaviour_in >= 30 && behaviour_in < 60)
			m_boardSizeInt = ptr_resourceManager->v_honestReliableBoards.size();
		else if (behaviour_in >= 60 && behaviour_in < 90)
			m_boardSizeInt = ptr_resourceManager->v_dishonestReliableBoards.size();

		std::random_device m_randomDevice;
		std::mt19937 m_mt(m_randomDevice());
		std::uniform_int_distribution<int> m_boardDist(0, m_boardSizeInt - 1);

		std::string m_temporaryBoardString = "  ";
		if (behaviour_in >= 0 && behaviour_in < 30) {

			int m_tempInt = m_boardDist(m_mt);
			if (m_tempInt >= ptr_resourceManager->v_honestUnreliableBoards.size())
				m_tempInt = ptr_resourceManager->v_honestUnreliableBoards.size();

			if (magnitude_in >= 0 && magnitude_in < 30)
				m_temporaryBoardString = ptr_resourceManager->v_honestUnreliableBoards.at(m_tempInt).s_nameString;
			else if (magnitude_in >= 30 && magnitude_in < 60)
				m_temporaryBoardString = ptr_resourceManager->v_honestUnreliableBoards.at(m_tempInt).s_firstString;
			else if (magnitude_in >= 60 && magnitude_in < 90)
				m_temporaryBoardString = ptr_resourceManager->v_honestUnreliableBoards.at(m_tempInt).s_secondString;
		}
		else if (behaviour_in >= 30 && behaviour_in < 60) {

			int m_tempInt = m_boardDist(m_mt);
			if (m_tempInt >= ptr_resourceManager->v_honestReliableBoards.size())
				m_tempInt = ptr_resourceManager->v_honestReliableBoards.size();

			if (magnitude_in >= 0 && magnitude_in < 30)
				m_temporaryBoardString = ptr_resourceManager->v_honestReliableBoards.at(m_tempInt).s_nameString;
			else if (magnitude_in >= 30 && magnitude_in < 60)
				m_temporaryBoardString = ptr_resourceManager->v_honestReliableBoards.at(m_tempInt).s_firstString;
			else if (magnitude_in >= 60 && magnitude_in < 90)
				m_temporaryBoardString = ptr_resourceManager->v_honestReliableBoards.at(m_tempInt).s_secondString;
		}
		else if (behaviour_in >= 60 && behaviour_in < 90) {

			int m_tempInt = m_boardDist(m_mt);
			if (m_tempInt >= ptr_resourceManager->v_dishonestReliableBoards.size())
				m_tempInt = ptr_resourceManager->v_dishonestReliableBoards.size();

			if (magnitude_in >= 0 && magnitude_in < 30)
				m_temporaryBoardString = ptr_resourceManager->v_dishonestReliableBoards.at(m_tempInt).s_nameString;
			else if (magnitude_in >= 30 && magnitude_in < 60)
				m_temporaryBoardString = ptr_resourceManager->v_dishonestReliableBoards.at(m_tempInt).s_firstString;
			else if (magnitude_in >= 60 && magnitude_in < 90)
				m_temporaryBoardString = ptr_resourceManager->v_dishonestReliableBoards.at(m_tempInt).s_secondString;

		}
		

		v_processingWordStrings.clear();
		v_processingWordStrings = explode(m_temporaryBoardString, ' ');


		//	These operate very similar to the tile boards, in the way that they give the player some lore or flavour text
		if (behaviour_in >= 0 && behaviour_in < 30) {
			std::random_device m_randomDevicePOS;
			std::mt19937 m_mtPOS(m_randomDevicePOS());
			std::uniform_int_distribution<int> m_negativeAdjectiveDist(0, ptr_resourceManager->v_thematicNegativeAdjectives.size() - 1);
			std::uniform_int_distribution<int> m_positiveAdjectiveDist(0, ptr_resourceManager->v_thematicPositiveAdjectives.size() - 1);
			std::uniform_int_distribution<int> m_negativeVerbDist(0, ptr_resourceManager->v_thematicNegativeVerbs.size() - 1);
			std::uniform_int_distribution<int> m_positiveVerbDist(0, ptr_resourceManager->v_thematicPositiveVerbs.size() - 1);
			std::uniform_int_distribution<int> m_negativeObjectNounDist(0, ptr_resourceManager->v_thematicNegativeObjectNouns.size() - 1);
			std::uniform_int_distribution<int> m_positiveObjectNounDist(0, ptr_resourceManager->v_thematicPositiveObjectNouns.size() - 1);
			std::uniform_int_distribution<int> m_negativePersonNounDist(0, ptr_resourceManager->v_thematicNegativePersonNouns.size() - 1);
			std::uniform_int_distribution<int> m_positivePersonNounDist(0, ptr_resourceManager->v_thematicPositivePersonNouns.size() - 1);

			int m_negAdjInt = m_negativeAdjectiveDist(m_mtPOS);
			int m_posAdjInt = m_positiveAdjectiveDist(m_mtPOS);

			int m_negVerInt = m_negativeVerbDist(m_mtPOS);
			int m_posVerInt = m_positiveVerbDist(m_mtPOS);

			int m_negObjInt = m_negativeObjectNounDist(m_mtPOS);
			int m_posObjInt = m_positiveObjectNounDist(m_mtPOS);
			int m_negPerInt = m_negativePersonNounDist(m_mtPOS);
			int m_posPerInt = m_positivePersonNounDist(m_mtPOS);


			for (int i = 0; i < v_processingWordStrings.size(); i++) {
				if (v_processingWordStrings.at(i).find("[negative_adjective]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_adjective]", ptr_resourceManager->v_thematicNegativeAdjectives.at(m_negAdjInt).s_nameString);
				}
				else if (v_processingWordStrings.at(i).find("[positive_adjective]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_adjective]", ptr_resourceManager->v_thematicPositiveAdjectives.at(m_posAdjInt).s_nameString);
				}

				else if (v_processingWordStrings.at(i).find("[negative_verb]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_verb]", ptr_resourceManager->v_thematicNegativeVerbs.at(m_negVerInt).s_nameString);

				}
				else if (v_processingWordStrings.at(i).find("[positive_verb]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_verb]", ptr_resourceManager->v_thematicPositiveVerbs.at(m_posVerInt).s_nameString);
				}

				else if (v_processingWordStrings.at(i).find("[negative_object]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_object]", ptr_resourceManager->v_thematicNegativeObjectNouns.at(m_negObjInt).s_nameString);
				}
				else if (v_processingWordStrings.at(i).find("[positive_object]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_object]", ptr_resourceManager->v_thematicPositiveObjectNouns.at(m_posObjInt).s_nameString);
				}
				else if (v_processingWordStrings.at(i).find("[negative_person]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_person]", ptr_resourceManager->v_thematicNegativePersonNouns.at(m_negPerInt).s_nameString);
				}
				else if (v_processingWordStrings.at(i).find("[positive_person]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_person]", ptr_resourceManager->v_thematicPositivePersonNouns.at(m_posPerInt).s_nameString);
				}
			}

			m_temporaryBoardString = implode(v_processingWordStrings, " ");
		}
		else {

			namedString m_direction = namedString("same", "same");
			int2d m_tiles = int2d(0, 0);
			int2d m_add = int2d(0, 0);
			
			std::random_device m_randomDeviceBinary;
			std::mt19937 m_mtBinary(m_randomDeviceBinary());
			std::uniform_int_distribution<int> m_binaryDist(0, 1);
			int m_result = m_binaryDist(m_mtBinary);

			m_tiles = int2d(plot_in.s_firstInt - player_in.s_firstInt, plot_in.s_secondInt - player_in.s_secondInt);				
			//	X_axis
			if (m_tiles.s_firstInt > 0) {
				m_direction.s_nameString = "east";
				m_add.s_firstInt = 1;
			}
			else if (m_tiles.s_firstInt < 0) {
				m_direction.s_nameString = "west";
				m_add.s_firstInt = -1;
			}

			//	Y-axis
			if (m_tiles.s_secondInt > 0) {
				m_direction.s_string = "north";
				m_add.s_secondInt = 1;
			}
			else if (m_tiles.s_secondInt < 0) {
				m_direction.s_string = "south";
				m_add.s_secondInt = -1;
			}
			
			for (int i = 0; i < v_processingWordStrings.size(); i++) {
				//	These will be effective for the honest reliable
				if (v_processingWordStrings.at(i).find("[tiles]") != std::string::npos) {
					if (m_result == 0 && m_tiles.s_firstInt != 0) {
						v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[tiles]", "" + m_tiles.s_firstInt);
					}
					else {
						v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[tiles]", "" + m_tiles.s_secondInt);

					}
				}
				if (v_processingWordStrings.at(i).find("[direction]") != std::string::npos) {
					if (m_result == 0 && m_direction.s_nameString != "same") {
						v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[direction]", m_direction.s_nameString);
					}
					else {
						v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[direction]", m_direction.s_string);
					}
				}
				if (v_processingWordStrings.at(i).find("[x-tiles]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[x-tiles]", ""+(m_tiles.s_firstInt));
				}
				else if (v_processingWordStrings.at(i).find("[x-tiles-high]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[x-tiles-high]", "" + (m_tiles.s_firstInt + m_add.s_firstInt));
				}
				else if (v_processingWordStrings.at(i).find("[y-tiles]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[y-tiles]", "" + (m_tiles.s_secondInt));
				}
				else if (v_processingWordStrings.at(i).find("[y-tiles-high]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[y-tiles-high]", "" + (m_tiles.s_secondInt + m_add.s_secondInt));
				}
				else if (v_processingWordStrings.at(i).find("[x-direction]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[x-direction]", m_direction.s_nameString);
				}
				else if (v_processingWordStrings.at(i).find("[x-direction-swch]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[x-direction-swch]", m_direction.s_string);
				}
				else if (v_processingWordStrings.at(i).find("[y-direction]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[y-direction]", m_direction.s_string);
				}
				else if (v_processingWordStrings.at(i).find("[y-direction-swch]") != std::string::npos) {
					v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[y-direction-swch]", m_direction.s_nameString);
				}

				
			}

			m_temporaryBoardString = implode(v_processingWordStrings, " ");
			

		}

		

		return m_temporaryBoardString;

	}


	//! Process the tile boards by inserting the relevant thematic words
	//! @param tile_in The tile's classification
	//! @return The processed board, ready for viewing by the user
	std::string tileBoardProcessing(std::string tile_in) {
		
		int m_boardSizeInt = 0;
		if (tile_in == "acceptable")
			m_boardSizeInt = ptr_resourceManager->v_acceptableTileBoards.size();
		else if (tile_in == "cautious")
			m_boardSizeInt = ptr_resourceManager->v_cautiousTileBoards.size();
		else if (tile_in == "deadly")
			m_boardSizeInt = ptr_resourceManager->v_deadlyTileBoards.size();

		std::random_device m_randomDevice;
		std::mt19937 m_mt(m_randomDevice());
		std::uniform_int_distribution<int> m_boardDist(0, m_boardSizeInt - 1);

		std::string m_temporaryBoardString = "  ";
		if (tile_in == "acceptable")
			m_temporaryBoardString = ptr_resourceManager->v_acceptableTileBoards.at(m_boardDist(m_mt)).s_string;
		else if (tile_in == "cautious")
			m_temporaryBoardString = ptr_resourceManager->v_cautiousTileBoards.at(m_boardDist(m_mt)).s_string;
		else if (tile_in == "deadly")
			m_temporaryBoardString = ptr_resourceManager->v_deadlyTileBoards.at(m_boardDist(m_mt)).s_string;
		
		v_processingWordStrings.clear();
		v_processingWordStrings = explode(m_temporaryBoardString, ' ');

		std::random_device m_randomDevicePOS;
		std::mt19937 m_mtPOS(m_randomDevicePOS());
		std::uniform_int_distribution<int> m_negativeAdjectiveDist(0, ptr_resourceManager->v_thematicNegativeAdjectives.size() - 1);
		std::uniform_int_distribution<int> m_positiveAdjectiveDist(0, ptr_resourceManager->v_thematicPositiveAdjectives.size() - 1);
		std::uniform_int_distribution<int> m_negativeVerbDist(0, ptr_resourceManager->v_thematicNegativeVerbs.size() - 1);
		std::uniform_int_distribution<int> m_positiveVerbDist(0, ptr_resourceManager->v_thematicPositiveVerbs.size() - 1);
		std::uniform_int_distribution<int> m_negativeObjectNounDist(0, ptr_resourceManager->v_thematicNegativeObjectNouns.size() - 1);
		std::uniform_int_distribution<int> m_positiveObjectNounDist(0, ptr_resourceManager->v_thematicPositiveObjectNouns.size() - 1);
		std::uniform_int_distribution<int> m_negativePersonNounDist(0, ptr_resourceManager->v_thematicNegativePersonNouns.size() - 1);
		std::uniform_int_distribution<int> m_positivePersonNounDist(0, ptr_resourceManager->v_thematicPositivePersonNouns.size() - 1);

		int m_negAdjInt = m_negativeAdjectiveDist(m_mtPOS);
		int m_posAdjInt = m_positiveAdjectiveDist(m_mtPOS);

		int m_negVerInt = m_negativeVerbDist(m_mtPOS); 
		int m_posVerInt = m_positiveVerbDist(m_mtPOS);
		
		int m_negObjInt = m_negativeObjectNounDist(m_mtPOS);
		int m_posObjInt = m_positiveObjectNounDist(m_mtPOS);
		int m_negPerInt = m_negativePersonNounDist(m_mtPOS);
		int m_posPerInt = m_positivePersonNounDist(m_mtPOS);
	

		for (int i = 0; i < v_processingWordStrings.size(); i++) {
			if (v_processingWordStrings.at(i).find("[negative_adjective]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_adjective]", ptr_resourceManager->v_thematicNegativeAdjectives.at(m_negAdjInt).s_nameString);
			}
			else if (v_processingWordStrings.at(i).find("[positive_adjective]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_adjective]", ptr_resourceManager->v_thematicPositiveAdjectives.at(m_posAdjInt).s_nameString);
			}
			
			else if (v_processingWordStrings.at(i).find("[negative_verb]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_verb]", ptr_resourceManager->v_thematicNegativeVerbs.at(m_negVerInt).s_nameString);
				
			}
			else if (v_processingWordStrings.at(i).find("[positive_verb]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_verb]", ptr_resourceManager->v_thematicPositiveVerbs.at(m_posVerInt).s_nameString);
			}

			else if (v_processingWordStrings.at(i).find("[negative_object]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_object]", ptr_resourceManager->v_thematicNegativeObjectNouns.at(m_negObjInt).s_nameString);
			}
			else if (v_processingWordStrings.at(i).find("[positive_object]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_object]", ptr_resourceManager->v_thematicPositiveObjectNouns.at(m_posObjInt).s_nameString);
			}
			else if (v_processingWordStrings.at(i).find("[negative_person]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_person]", ptr_resourceManager->v_thematicNegativePersonNouns.at(m_negPerInt).s_nameString);
			}
			else if (v_processingWordStrings.at(i).find("[positive_person]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_person]", ptr_resourceManager->v_thematicPositivePersonNouns.at(m_posPerInt).s_nameString);
			}
		}

		m_temporaryBoardString = implode(v_processingWordStrings, " ");

		return m_temporaryBoardString;

	}
	//! Process the simple behaviour boards by inserting the relevant thematic words
	//! @return The processed board, ready for viewing by the user
	std::string simpleBehaviourBoardProcessing() {
		std::random_device m_randomDevice;
		std::mt19937 m_mt(m_randomDevice());
		std::uniform_int_distribution<int> m_boardDist(0, ptr_resourceManager->v_simpleBehaviourBoards.size() - 1);
		std::string m_temporaryBoardString = ptr_resourceManager->v_simpleBehaviourBoards.at(m_boardDist(m_mt)).s_string;

		v_processingWordStrings.clear();
		v_processingWordStrings = explode(m_temporaryBoardString, ' ');
		
		for (int i = 0; i < v_processingWordStrings.size(); i++) {
			//	Now come the theme-specific plot keywords
			if (v_processingWordStrings.at(i).find("[primary_villain]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[primary_villain]", ptr_resourceManager->getPlotKeyword("primary_villain"));
			}
			else if (v_processingWordStrings.at(i).find("[secondary_villain]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[secondary_villain]", ptr_resourceManager->getPlotKeyword("secondary_villain"));
			}
			else if (v_processingWordStrings.at(i).find("[tertiary_villain]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[tertiary_villain]", ptr_resourceManager->getPlotKeyword("tertiary_villain"));
			}
			else if (v_processingWordStrings.at(i).find("[primary_ally]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[primary_ally]", ptr_resourceManager->getPlotKeyword("primary_ally"));
			}
			else if (v_processingWordStrings.at(i).find("[primary_macguffin]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[primary_macguffin]", ptr_resourceManager->getPlotKeyword("primary_macguffin"));
			}
			else if (v_processingWordStrings.at(i).find("[secondary_macguffin]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[secondary_macguffin]", ptr_resourceManager->getPlotKeyword("secondary_macguffin"));
			}
			else if (v_processingWordStrings.at(i).find("[tertiary_macguffin]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[tertiary_macguffin]", ptr_resourceManager->getPlotKeyword("tertiary_macguffin"));
			}
		}

		m_temporaryBoardString = implode(v_processingWordStrings, " ");

		return m_temporaryBoardString;

	}

	//! Process the tile boards by inserting the relevant thematic words
	//! @param tile_in The tile's classification
	//! @return The processed board, ready for viewing by the user
	std::string plotBoardProcessing(int plotIndex_in, int plotMax_in) {
		int m_primaryAllyIndexInt = (int)(plotMax_in * 0.25f) - 1;
		int m_tertiaryVillainIndexInt = (int)(plotMax_in * 0.5f) - 1;
		int m_secondaryVillainIndexInt = (int)(plotMax_in * 0.75f) - 1;
		int m_primaryVillainIndexInt = plotMax_in - 1;

		std::string m_temporaryBoardString = "";

		//	First we have to determine which part of the plot the player finds themselves
		if (plotIndex_in >= 0 && plotIndex_in < m_primaryAllyIndexInt)
			m_temporaryBoardString = ptr_resourceManager->getFirstStageBoard();
		else if (plotIndex_in == m_primaryAllyIndexInt)
			m_temporaryBoardString = ptr_resourceManager->getPrimaryAllyBoard();
		else if (plotIndex_in > m_primaryAllyIndexInt && plotIndex_in < m_tertiaryVillainIndexInt)
			m_temporaryBoardString = ptr_resourceManager->getSecondStageBoard();
		else if (plotIndex_in == m_tertiaryVillainIndexInt)
			m_temporaryBoardString = ptr_resourceManager->getTertiaryVillainBoard();
		else if (plotIndex_in > m_tertiaryVillainIndexInt && plotIndex_in < m_secondaryVillainIndexInt)
			m_temporaryBoardString = ptr_resourceManager->getThirdStageBoard();
		else if (plotIndex_in == m_secondaryVillainIndexInt)
			m_temporaryBoardString = ptr_resourceManager->getSecondaryVillainBoard();
		else if (plotIndex_in > m_secondaryVillainIndexInt && plotIndex_in < m_primaryVillainIndexInt)
			m_temporaryBoardString = ptr_resourceManager->getFourthStageBoard();
		else if (plotIndex_in == m_primaryVillainIndexInt)
			m_temporaryBoardString = ptr_resourceManager->getPrimaryVillainBoard();
				
		v_processingWordStrings.clear();
		v_processingWordStrings = explode(m_temporaryBoardString, ' ');


		//	Create the randomisation system that will be used when picking the part-of-speech components
		std::random_device m_randomDevicePOS;
		std::mt19937 m_mtPOS(m_randomDevicePOS());
		std::uniform_int_distribution<int> m_negativeAdjectiveDist(0, ptr_resourceManager->v_thematicNegativeAdjectives.size() - 1);
		std::uniform_int_distribution<int> m_positiveAdjectiveDist(0, ptr_resourceManager->v_thematicPositiveAdjectives.size() - 1);
		std::uniform_int_distribution<int> m_negativeVerbDist(0, ptr_resourceManager->v_thematicNegativeVerbs.size() - 1);
		std::uniform_int_distribution<int> m_positiveVerbDist(0, ptr_resourceManager->v_thematicPositiveVerbs.size() - 1);
		std::uniform_int_distribution<int> m_negativeObjectNounDist(0, ptr_resourceManager->v_thematicNegativeObjectNouns.size() - 1);
		std::uniform_int_distribution<int> m_positiveObjectNounDist(0, ptr_resourceManager->v_thematicPositiveObjectNouns.size() - 1);
		std::uniform_int_distribution<int> m_negativePersonNounDist(0, ptr_resourceManager->v_thematicNegativePersonNouns.size() - 1);
		std::uniform_int_distribution<int> m_positivePersonNounDist(0, ptr_resourceManager->v_thematicPositivePersonNouns.size() - 1);
		
		//	This ensures that the same part_of_speech component is reused within the same board
		int m_negAdjInt = m_negativeAdjectiveDist(m_mtPOS);
		int m_posAdjInt = m_positiveAdjectiveDist(m_mtPOS);

		int m_negVerInt = m_negativeVerbDist(m_mtPOS);
		int m_posVerInt = m_positiveVerbDist(m_mtPOS);

		int m_negObjInt = m_negativeObjectNounDist(m_mtPOS);
		int m_posObjInt = m_positiveObjectNounDist(m_mtPOS);
		int m_negPerInt = m_negativePersonNounDist(m_mtPOS);
		int m_posPerInt = m_positivePersonNounDist(m_mtPOS);


		for (int i = 0; i < v_processingWordStrings.size(); i++) {
			//	First come the adjectives
			if (v_processingWordStrings.at(i).find("[negative_adjective]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_adjective]", ptr_resourceManager->v_thematicNegativeAdjectives.at(m_negAdjInt).s_nameString);
			}
			else if (v_processingWordStrings.at(i).find("[positive_adjective]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_adjective]", ptr_resourceManager->v_thematicPositiveAdjectives.at(m_posAdjInt).s_nameString);
			}

			//	Then come the verbs
			else if (v_processingWordStrings.at(i).find("[negative_verb]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_verb]", ptr_resourceManager->v_thematicNegativeVerbs.at(m_negVerInt).s_nameString);

			}
			else if (v_processingWordStrings.at(i).find("[positive_verb]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_verb]", ptr_resourceManager->v_thematicPositiveVerbs.at(m_posVerInt).s_nameString);
			}

			//	Then come the nouns, split as object or person
			else if (v_processingWordStrings.at(i).find("[negative_object]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_object]", ptr_resourceManager->v_thematicNegativeObjectNouns.at(m_negObjInt).s_nameString);
			}
			else if (v_processingWordStrings.at(i).find("[positive_object]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_object]", ptr_resourceManager->v_thematicPositiveObjectNouns.at(m_posObjInt).s_nameString);
			}
			else if (v_processingWordStrings.at(i).find("[negative_person]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[negative_person]", ptr_resourceManager->v_thematicNegativePersonNouns.at(m_negPerInt).s_nameString);
			}
			else if (v_processingWordStrings.at(i).find("[positive_person]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[positive_person]", ptr_resourceManager->v_thematicPositivePersonNouns.at(m_posPerInt).s_nameString);
			}

			//	Now come the theme-specific plot keywords
			else if (v_processingWordStrings.at(i).find("[primary_villain]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[primary_villain]", ptr_resourceManager->getPlotKeyword("primary_villain"));
			}
			else if (v_processingWordStrings.at(i).find("[secondary_villain]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[secondary_villain]", ptr_resourceManager->getPlotKeyword("secondary_villain"));
			}
			else if (v_processingWordStrings.at(i).find("[tertiary_villain]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[tertiary_villain]", ptr_resourceManager->getPlotKeyword("tertiary_villain"));
			}
			else if (v_processingWordStrings.at(i).find("[primary_ally]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[primary_ally]", ptr_resourceManager->getPlotKeyword("primary_ally"));
			}
			else if (v_processingWordStrings.at(i).find("[primary_macguffin]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[primary_macguffin]", ptr_resourceManager->getPlotKeyword("primary_macguffin"));
			}
			else if (v_processingWordStrings.at(i).find("[secondary_macguffin]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[secondary_macguffin]", ptr_resourceManager->getPlotKeyword("secondary_macguffin"));
			}
			else if (v_processingWordStrings.at(i).find("[tertiary_macguffin]") != std::string::npos) {
				v_processingWordStrings.at(i) = replace(v_processingWordStrings.at(i), "[tertiary_macguffin]", ptr_resourceManager->getPlotKeyword("tertiary_macguffin"));
			}
		}

		m_temporaryBoardString = implode(v_processingWordStrings, " ");

		return m_temporaryBoardString;

	}

	//!	Process the entry/command for adjectives, nouns, and verbs
	//! @return A profile of the given command, that denotes the types of words present and their prevelance
	commandProfile bigThreeEntryProcessing() {

		int m_hostilityInt = 0;
		int m_pleasantInt = 0;

		int m_adjectivesInt = 0;
		int m_nounsInt = 0;
		int m_verbsInt = 0;

		v_processingWordStrings.clear();
		v_processingWordStrings = explode(v_entryStrings.back(), ';');
		
		v_processingPOSStrings.clear();
		v_processingPOSStrings = explode(v_resultStrings.back(), ';');

		for (int i = 0; i < v_processingPOSStrings.size(); i++) {

			bool m_wordProcessed = false;
			//	JJ, JJR, JJS are all adjectives
			if (v_processingPOSStrings.at(i).find("JJ") != std::string::npos ||
				v_processingPOSStrings.at(i).find("jj") != std::string::npos) {
				m_adjectivesInt++;

				//	Check to see if the word is a vulgarity
				for (std::string l_vulgarity : ptr_resourceManager->v_vulgarities) {
					if (!m_wordProcessed && v_processingWordStrings.at(i).find( l_vulgarity ) != std::string::npos) {
						m_hostilityInt++;
						m_wordProcessed = true;
					}
				}
				//	Check to see if the word is a hostile adjective
				if (!m_wordProcessed) {
					for (std::string l_hostileAdjective : ptr_resourceManager->v_hostileAdjectives) {
						if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_hostileAdjective) != std::string::npos) {
							m_hostilityInt++;
							m_wordProcessed = true;
						}
					}
				}
				//	Check to see if the word is a pleasant adjective
				if (!m_wordProcessed) {
					for (std::string l_pleasantAdjective : ptr_resourceManager->v_pleasantAdjectives) {
						if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_pleasantAdjective) != std::string::npos) {
							m_pleasantInt++;
							m_wordProcessed = true;
						}
					}
				}

			}
			//	NN, NNS, NNP, NNPS are all nouns
			else if (v_processingPOSStrings.at(i).find("NN") != std::string::npos ||
				v_processingPOSStrings.at(i).find("nn") != std::string::npos) {
				m_nounsInt++;

				//	Check to see if the word is a vulgarity
				for (std::string l_vulgarity : ptr_resourceManager->v_vulgarities) {
					if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_vulgarity) != std::string::npos) {
						m_hostilityInt++;
						m_wordProcessed = true;
					}
				}
				//	Check to see if the word is a hostile noun
				if (!m_wordProcessed) {
					for (std::string l_hostileNoun : ptr_resourceManager->v_hostileNouns) {
						if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_hostileNoun) != std::string::npos) {
							m_hostilityInt++;
							m_wordProcessed = true;
						}
					}
				}
				//	Check to see if the word is a pleasant noun
				if (!m_wordProcessed) {
					for (std::string l_pleasantNoun : ptr_resourceManager->v_pleasantNouns) {
						if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_pleasantNoun) != std::string::npos) {
							m_pleasantInt++;
							m_wordProcessed = true;
						}
					}
				}
			}
			//	VB, VBD, VBG, VBN, VBP, VBZ are all adjectives
			else if (v_processingPOSStrings.at(i).find("VB") != std::string::npos ||
				v_processingPOSStrings.at(i).find("vb") != std::string::npos) {
				m_verbsInt++;

				//	Check to see if the word is a vulgarity
				for (std::string l_vulgarity : ptr_resourceManager->v_vulgarities) {
					if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_vulgarity) != std::string::npos) {
						m_hostilityInt++;
						m_wordProcessed = true;
					}
				}
				//	Check to see if the word is a hostile verb
				if (!m_wordProcessed) {
					for (std::string l_hostileVerb : ptr_resourceManager->v_hostileVerbs) {
						if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_hostileVerb) != std::string::npos) {
							m_hostilityInt++;
							m_wordProcessed = true;
						}
					}
				}
				//	Check to see if the word is a pleasant verb
				if (!m_wordProcessed) {
					for (std::string l_pleasantVerb : ptr_resourceManager->v_pleasantVerbs) {
						if (!m_wordProcessed && v_processingWordStrings.at(i).find(l_pleasantVerb) != std::string::npos) {
							m_pleasantInt++;
							m_wordProcessed = true;
						}
					}
				}
			}
		}

		return commandProfile(m_hostilityInt, m_pleasantInt, v_processingWordStrings.size(), m_adjectivesInt, m_nounsInt, m_verbsInt);
		
	}


	//	Replace one portion of a string with another
	std::string replace(std::string str, std::string from, std::string to) {
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return str;
	}


	//	A mimicry of the php method of the same name, this will join a string vector into a string
	std::string implode(std::vector<std::string> str_in, char ch_in) {
		std::string m_result = "";
		std::string m_delim = ""+ch_in;
		std::vector<std::string> v_temp = str_in;

		for (int i = 0; i < v_temp.size(); i++) {
			m_result.append(v_temp.at(i));
			m_result.append(m_delim);
		}
		return m_result;
	}

	std::string implode(std::vector<std::string> str_in, std::string delim_in) {
		std::string m_result = "";
		std::string m_delim = delim_in;
		std::vector<std::string> v_temp = str_in;

		for (int i = 0; i < v_temp.size(); i++) {
			m_result.append(v_temp.at(i));
			m_result.append(m_delim);
		}
		return m_result;
	}


	//	A mimicry of the php method of the same name, this will split a string into a vector of strings
	std::vector<std::string> explode(std::string str_in, char ch_in) {
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
		return v_result;
	}

	//	Adding a new entry to the vector
	void entryPushBack(std::string entry_in) {
		if (v_entryStrings.size() == c_vectorCapacityInt) {
			v_entryStrings.erase(v_entryStrings.begin());
		}

		v_entryStrings.push_back(entry_in);
	}

	//	Adding a new result to the vector
	void resultPushBack(std::string result_in) {
		if (v_resultStrings.size() == c_vectorCapacityInt) {
			v_resultStrings.erase(v_resultStrings.begin());
		}

		v_resultStrings.push_back(result_in);
	}

};
