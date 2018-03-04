#include "Player.h"

Player::Player(std::string name_in) {
	c_healthFloat = 100.0f;
	c_nameString = name_in;
	c_theme = "empty";

	c_hostilityInt = 0;
	c_recentPleasantryInt = 0;
	c_interactionsInt = 0;
	c_totalInteractionWordsInt = 0;

	c_positionInt2d.s_firstInt = 16777216;
	c_positionInt2d.s_secondInt = 16777126;
	
	c_attireHeadString = "Empty";
	c_attireTorsoString = "Empty";
	c_equipmentString = "Empty";

}

Player::~Player() {
	
}

bool Player::addItem(inventoryItem&  item_in) {
	if (v_inventoryItems.size() < 16) {
		for (inventoryItem l_item : v_inventoryItems) {
			if (l_item.s_bodyString == item_in.s_bodyString)
				return true;
		}
		v_inventoryItems.push_back(item_in);
		return true;
	}
	else {
		return false;
	}
}
inventoryItem Player::getItem(std::string& title_in) {
	for (inventoryItem l_item : v_inventoryItems) {
		if (l_item.s_titleString == title_in)
			return l_item;
	}
	return inventoryItem("false", "false", "false", "false");
}
bool Player::removeItem(std::string& title_in) {
	for (int i = 0; i < v_inventoryItems.size(); i++) {
		if (v_inventoryItems.at(i).s_titleString == title_in) {
			v_inventoryItems.erase(v_inventoryItems.begin() + i);
			return true;
		}
	}
	return false;
}

bool Player::equipItem(std::string& title_in) {
	if (v_inventoryItems.size() > 0) {
		for (inventoryItem l_item : v_inventoryItems) {
			if (l_item.s_titleString == title_in && l_item.s_nameString == "attire_head" && l_item.s_qualityString != "Damaged") {
				c_attireHeadString = l_item.s_titleString;
				return true;
			}
			else if (l_item.s_titleString == title_in && l_item.s_nameString == "attire_torso" && l_item.s_qualityString != "Damaged") {
				c_attireTorsoString = l_item.s_titleString;
				return true;
			}
			else if (l_item.s_titleString == title_in && l_item.s_nameString == "equipment" && l_item.s_qualityString != "Damaged") {
				c_equipmentString = l_item.s_titleString;
				return true;
			}
		}
	}
	else {
		return false;
	}
}
bool Player::unequipItem(std::string& title_in) {
	if (c_attireHeadString == title_in) {
		c_attireHeadString = "Empty";
		return true;
	}
	else if (c_attireTorsoString == title_in) {
		c_attireTorsoString = "Empty";
		return true;
	}

	else if (c_equipmentString == title_in) {
		c_equipmentString = "Empty";
		return true;
	}
	else if (title_in == "all" || title_in == "All") {
		c_attireHeadString = "Empty";
		c_attireTorsoString = "Empty";
		c_equipmentString = "Empty";
	}
	return false;
}