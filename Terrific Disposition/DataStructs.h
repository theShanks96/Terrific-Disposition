#pragma once

#include <string>

struct namedString {
	std::string s_name;
	std::string s_string;

	namedString(std::string name_in, std::string string_in) {
		s_name = name_in;
		s_string = string_in;
	}
};

struct namedDoubleString {
	std::string s_name;
	std::string s_one;
	std::string s_two;

	namedDoubleString(std::string name_in, std::string one_in, std::string two_in) {
		s_name = name_in;
		s_one = one_in;
		s_two = two_in;
	}
};

struct inventoryItem {
	std::string s_name;
	std::string s_title;
	std::string s_quality;
	std::string s_body;

	inventoryItem(std::string name_in, std::string title_in, std::string quality_in, std::string body_in) {
		s_name = name_in;
		s_title = title_in;
		s_quality = quality_in;
		s_body = body_in;
	}
};


struct float2d {
	float s_first;
	float s_second;

	float2d() {
		s_first = 0.0f;
		s_second = 0.0f;
	}
	float2d(float first_in, float second_in) {
		s_first = first_in;
		s_second = second_in;
	}
};

struct int2d {
	int s_first;
	int s_second;

	int2d() {
		s_first = 0.0f;
		s_second = 0.0f;
	}
	int2d(int first_in, int second_in) {
		s_first = first_in;
		s_second = second_in;
	}
};

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


