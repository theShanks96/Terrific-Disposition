#include "Player.h"

Player::Player(std::string name_in) {
	c_health = 100.0f;
	c_name = name_in;

	c_position.s_first = 16777216;
	c_position.s_second = 16777126;
	
	c_attireHead = "Empty";
	c_attireTorso = "Empty";
	c_equipment = "Empty";

}

bool Player::addItem(inventoryItem&  item_in) {
	if (v_inventory.size() < 16) {
		for (inventoryItem l_item : v_inventory) {
			if (l_item.s_body == item_in.s_body)
				return true;
		}
		v_inventory.push_back(item_in);
		return true;
	}
	else {
		return false;
	}
}
inventoryItem Player::getItem(std::string& title_in) {
	for (inventoryItem l_item : v_inventory) {
		if (l_item.s_title == title_in)
			return l_item;
	}
	return inventoryItem("false", "false", "false", "false");
}
bool Player::removeItem(std::string& title_in) {
	for (int i = 0; i < v_inventory.size(); i++) {
		if (v_inventory.at(i).s_title == title_in) {
			v_inventory.erase(v_inventory.begin() + i);
			return true;
		}
	}
	return false;
}

bool Player::equipItem(std::string& title_in) {
	if (v_inventory.size() > 0) {
		for (inventoryItem l_item : v_inventory) {
			if (l_item.s_title == title_in && l_item.s_name == "attire_head" && l_item.s_quality != "Damaged") {
				c_attireHead = l_item.s_title;
				return true;
			}
			else if (l_item.s_title == title_in && l_item.s_name == "attire_torso" && l_item.s_quality != "Damaged") {
				c_attireTorso = l_item.s_title;
				return true;
			}
			else if (l_item.s_title == title_in && l_item.s_name == "equipment" && l_item.s_quality != "Damaged") {
				c_equipment = l_item.s_title;
				return true;
			}
		}
	}
	else {
		return false;
	}
}
bool Player::unequipItem(std::string& title_in) {
	if (c_attireHead == title_in) {
		c_attireHead = "Empty";
		return true;
	}
	else if (c_attireTorso == title_in) {
		c_attireTorso = "Empty";
		return true;
	}

	else if (c_equipment == title_in) {
		c_equipment = "Empty";
		return true;
	}
	else if (title_in == "all" || title_in == "All") {
		c_attireHead = "Empty";
		c_attireTorso = "Empty";
		c_equipment = "Empty";
	}
	return false;
}