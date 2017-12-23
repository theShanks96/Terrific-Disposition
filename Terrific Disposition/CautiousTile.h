#pragma once

#include "Tile.h"

//! A tile that delineates that danger is nearby, and should keep the player's wits about them
class CautiousTile : public Tile {
public:
	CautiousTile();
	CautiousTile(std::string description_in);
	~CautiousTile();

	Interactable* c_interactable;
private:

};