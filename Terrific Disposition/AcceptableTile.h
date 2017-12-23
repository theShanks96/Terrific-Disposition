#pragma once

#include "Tile.h"

//! A tile deemed fairly safe for the player to find themselves
class AcceptableTile : public Tile{
public:
	AcceptableTile();
	AcceptableTile(std::string description_in);
	~AcceptableTile();

	std::vector<Interactable*> v_interactables;
	int c_maximumInteractables;
private:

};