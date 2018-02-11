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



class PythonManager {
public:
	ResourceManager * ptr_resourceManager;

	pybind11::object c_mainModule;
	pybind11::object c_globals;
	pybind11::object c_spacyModule;
	pybind11::object c_spacyProcessor;
	pybind11::object c_utilisedSpacyProcessor;

	std::vector<std::string> v_entryStrings;
	std::vector<std::string> v_resultStrings;

	std::vector<std::string> v_processingWordStrings;
	std::vector<std::string> v_processingPOSStrings;

	pybind11::scoped_interpreter* ptr_guard;
	pybind11::module c_nltk;

	int c_vectorCapacityInt;

	PythonManager(ResourceManager* resource_in) {
		//	Link the resource manager, as its information will be necessary
		ptr_resourceManager = resource_in;
		
		c_vectorCapacityInt = 16;

		//	Prepare the vectors
		v_entryStrings.reserve(c_vectorCapacityInt);
		v_resultStrings.reserve(c_vectorCapacityInt);

		//pybind11::scoped_interpreter guard{}; // start the interpreter and keep it alive
		
		ptr_guard = new pybind11::scoped_interpreter;

		c_nltk = pybind11::module::import("nltk");
	
		
	}

	~PythonManager() {
		pybind11::finalize_interpreter();
	}

	void nltkGenericProcessing(std::string entry_in) {
		pybind11::dict m_localEnv;

		pybind11::object tokens = c_nltk.attr("word_tokenize")(entry_in);
		pybind11::object tagged = c_nltk.attr("pos_tag")(tokens);

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

		pybind11::print(m_localEnv["final_pos"]);
		pybind11::print(m_localEnv["final_words"]);

		entryPushBack(m_localEnv["final_words"].cast<std::string>());
		resultPushBack(m_localEnv["final_pos"].cast<std::string>());
	}
	

	commandProfile nltkEntryProcessing(std::string entry_in) {
		
		nltkGenericProcessing(entry_in);

		return bigThreeEntryProcessing();

	}


	//! Process the thematic boards
	std::string nltkBoardProcessing(std::string tile_in) {
		
		int m_boardSizeInt = 0;
		if (tile_in == "acceptable")
			m_boardSizeInt = ptr_resourceManager->v_acceptableBoards.size();
		else if (tile_in == "cautious")
			m_boardSizeInt = ptr_resourceManager->v_cautiousBoards.size();
		else if (tile_in == "deadly")
			m_boardSizeInt = ptr_resourceManager->v_deadlyBoards.size();

		std::random_device m_randomDevice;
		std::mt19937 m_mt(m_randomDevice());
		std::uniform_int_distribution<int> m_boardDist(0, m_boardSizeInt);

		std::string m_temporaryBoardString = "  ";
		if (tile_in == "acceptable")
			m_temporaryBoardString = ptr_resourceManager->v_acceptableBoards.at(m_boardDist(m_mt));
		else if (tile_in == "cautious")
			m_temporaryBoardString = ptr_resourceManager->v_cautiousBoards.at(m_boardDist(m_mt));
		else if (tile_in == "deadly")
			m_temporaryBoardString = ptr_resourceManager->v_deadlyBoards.at(m_boardDist(m_mt));
		
		nltkGenericProcessing(m_temporaryBoardString);

		v_processingWordStrings.clear();
		v_processingWordStrings = explode(v_entryStrings.back(), ';');

		v_processingPOSStrings.clear();
		v_processingPOSStrings = explode(v_resultStrings.back(), ';');

		std::vector<int> v_adjectivesIndices;
		std::vector<int> v_nounsIndices;
		std::vector<int> v_verbsIndices;
		v_adjectivesIndices.reserve(v_processingWordStrings.size());
		v_nounsIndices.reserve(v_processingWordStrings.size());
		v_verbsIndices.reserve(v_processingWordStrings.size());


		for (int i = 0; i < v_processingPOSStrings.size(); i++) {

			bool m_wordProcessed = false;
			//	JJ, JJR, JJS are all adjectives
			if (v_processingPOSStrings.at(i).compare(0, 2, "jj")) {
				v_adjectivesIndices.push_back(i);

			}
			//	NN, NNS, NNP, NNPS are all nouns
			else if (v_processingPOSStrings.at(i).compare(0, 2, "nn")) {
				v_nounsIndices.push_back(i);

				
			}
			//	VB, VBD, VBG, VBN, VBP, VBZ are all adjectives
			else if (v_processingPOSStrings.at(i).compare(0, 2, "vb")) {
				v_verbsIndices.push_back(i);

			}
		}
		std::random_device m_randomDevicePOS;
		std::mt19937 m_mtPOS(m_randomDevice());
		std::uniform_int_distribution<int> m_adjectiveDist(0, ptr_resourceManager->v_thematicAdjectives.size());
		std::uniform_int_distribution<int> m_nounDist(0, ptr_resourceManager->v_thematicNouns.size());
		std::uniform_int_distribution<int> m_verbDist(0, ptr_resourceManager->v_thematicVerbs.size());

		for (int i = 0; i < v_adjectivesIndices.size(); i++) 
			v_processingWordStrings.at(v_adjectivesIndices.at(i)) = ptr_resourceManager->v_thematicAdjectives.at(m_adjectiveDist(m_mtPOS));
		
		for (int i = 0; i < v_nounsIndices.size(); i++) 
			v_processingWordStrings.at(v_adjectivesIndices.at(i)) = ptr_resourceManager->v_thematicNouns.at(m_nounDist(m_mtPOS));
		
		for (int i = 0; i < v_verbsIndices.size(); i++) 
			v_processingWordStrings.at(v_adjectivesIndices.at(i)) = ptr_resourceManager->v_thematicVerbs.at(m_verbDist(m_mtPOS));
		

		return "";

	}

	//!	Process the entry/command for adjectives, nouns, and verbs
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
