#pragma once

#include <vector>
#include <string>

#include "DataStructs.h"

class Player {
public:
	//!	Constructor for the Player object
	//! @param name_in Pseudonym to assign to the player character
	Player(std::string name_in);
	~Player();

	std::string c_name;
	std::vector<inventoryItem> v_inventory;

	float c_health;
	std::string c_attireHead;
	std::string c_attireTorso;
	std::string c_equipment;

	int2d c_position;

	bool addItem(inventoryItem& item_in);
	inventoryItem getItem(std::string& title_in);
	bool removeItem(std::string& title_in);
	
	bool equipItem(std::string& title_in);
	bool unequipItem(std::string& title_in);

};