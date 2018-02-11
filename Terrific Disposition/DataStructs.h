#pragma once

#include <string>

//! A struct holding two strings
struct namedString {
	std::string s_nameString;
	std::string s_string;

	namedString(std::string name_in, std::string string_in) {
		s_nameString = name_in;
		s_string = string_in;
	}
};

//! A struct holding three strings
struct namedDoubleString {
	std::string s_nameString;
	std::string s_firstString;
	std::string s_secondString;

	namedDoubleString(std::string name_in, std::string one_in, std::string two_in) {
		s_nameString = name_in;
		s_firstString = one_in;
		s_secondString = two_in;
	}
};

//! A struct holding four strings; a name, a title, the quality, and a body of text
struct inventoryItem {
	std::string s_nameString;
	std::string s_titleString;
	std::string s_qualityString;
	std::string s_bodyString;

	inventoryItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in) {
		s_nameString = name_in;
		s_titleString = title_in;
		s_qualityString = quality_in;
		s_bodyString = body_in;
	}
};

//! A struct holding two floats
struct float2d {
	float s_firstFloat;
	float s_secondFloat;

	float2d() {
		s_firstFloat = 0.0f;
		s_secondFloat = 0.0f;
	}
	float2d(float first_in, float second_in) {
		s_firstFloat = first_in;
		s_secondFloat = second_in;
	}
};


//! A struct holding two ints
struct int2d {
	int s_firstInt;
	int s_secondInt;

	int2d() {
		s_firstInt = 0.0f;
		s_secondInt = 0.0f;
	}
	int2d(int first_in, int second_in) {
		s_firstInt = first_in;
		s_secondInt = second_in;
	}
};

//! A struct holding three ints
struct int3d {
	int s_firstInt;
	int s_secondInt;
	int s_thirdInt;

	int3d() {
		s_firstInt = 0.0f;
		s_secondInt = 0.0f;
		s_thirdInt = 0.0f;
	}
	int3d(int first_in, int second_in, int third_in) {
		s_firstInt = first_in;
		s_secondInt = second_in;
		s_thirdInt = third_in;
	}
};




//! A struct designed to be returned upon nltk processing is complete
struct commandProfile {
	int s_hostilityInt;
	int s_pleasantryInt;
	int s_processedWordsInt;

	int s_adjectivesInt;
	int s_nounsInt;
	int s_verbsInt;

	commandProfile() {
		s_hostilityInt = 0;
		s_pleasantryInt = 0;
		s_processedWordsInt = 0;

		s_adjectivesInt = 0;
		s_nounsInt = 0;
		s_verbsInt = 0;
	}

	commandProfile(int hostility_in, int pleasantry_in, int words_in, int adjectives_in, int nouns_in, int verbs_in) {
		s_hostilityInt = hostility_in;
		s_pleasantryInt = pleasantry_in;
		s_processedWordsInt = words_in;

		s_adjectivesInt = adjectives_in;
		s_nounsInt = nouns_in;
		s_verbsInt = verbs_in;
	}
};

//! An extensive struct designed to hold player and world information for saving/loading
struct saveProfile {
	std::string s_playerName;

	int2d s_playerCurrentLocation;
	int2d s_playerStartLocation;

	std::vector<inventoryItem> v_playerInventory;
	std::string s_playerHeadAttire;
	std::string s_playerTorsoAttire;
	std::string s_playerEquipment;
		
	int s_mapSize;
	std::string s_worldTheme;
	
	std::vector<int2d> v_plotPoints;
	std::vector<int2d> v_acceptableTileLocations;
	std::vector<int2d> v_cautiousTileLocations;
	std::vector<int2d> v_deadlyTileLocations;
};


