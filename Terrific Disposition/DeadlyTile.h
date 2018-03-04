#pragma once

#include "Tile.h"

//! This tile is deadly to the player, should they ignore all warnings
class DeadlyTile : public Tile {
public:
	DeadlyTile();
	DeadlyTile(std::string description_in);
	~DeadlyTile();


	bool populateInteractables(int2d nextPlotPoint_in, int2d location_in, int storyHonesty_in, int play_in, int hostility_in, ResourceManager* resource_in, NaturalLogicManager* python_in) override;
	std::string getTileInformation() override;
	bool getInteractablePresence(std::string text_in) override;
	std::string interactByName(std::string entry_in) override;
private:

};