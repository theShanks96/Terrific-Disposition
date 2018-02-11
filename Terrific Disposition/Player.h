#pragma once

#include <vector>
#include <string>

#include "DataStructs.h"

//! The player and all its relevant information
class Player {
public:
	//!	Constructor for the Player object
	//! @param name_in Pseudonym to assign to the player character
	Player(std::string name_in);
	~Player();

	std::string c_nameString;
	std::vector<inventoryItem> v_inventoryItems;

	int c_interactionsInt;
	int c_hostilityInt;
	int c_recentPleasantryInt;
	int c_totalInteractionWordsInt;

	float c_playStyle;

	float c_healthFloat;
	std::string c_attireHeadString;
	std::string c_attireTorsoString;
	std::string c_equipmentString;

	int2d c_positionInt2d;

	bool addItem(inventoryItem& item_in);
	inventoryItem getItem(std::string& title_in);
	bool removeItem(std::string& title_in);
	
	bool equipItem(std::string& title_in);
	bool unequipItem(std::string& title_in);

};