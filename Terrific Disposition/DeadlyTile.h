#pragma once

#include "Tile.h"

//! This tile is deadly to the player, should they ignore all warnings
class DeadlyTile : public Tile {
public:
	DeadlyTile();
	DeadlyTile(std::string description_in);
	~DeadlyTile();

private:

};