#pragma once

#include "Tile.h"

//! This tile is deadly to the player, should they ignore all warnings
class DeadlyTile : public Tile {
public:
	DeadlyTile();
	DeadlyTile(std::string description_in);
	~DeadlyTile();


	bool populateInteractables(int2d nextPlotPoint_in, int honestReliable_in, int honestUnreliable_in, int dishonestReliable_in, int play_in, int aggressiveness_in) override;
	std::string getTileInformation() override;
	bool getInteractablePresence(std::string text_in) override;

private:

};