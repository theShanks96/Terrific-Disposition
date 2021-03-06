#pragma once

#include "Tile.h"

//! A tile that delineates that danger is nearby, and should keep the player's wits about them
class CautiousTile : public Tile {
public:
	Interactable* c_interactable;

public:
	CautiousTile();
	CautiousTile(std::string description_in);
	CautiousTile(bool hideoutTile_in);
	~CautiousTile();


	bool populateInteractables(int2d nextPlotPoint_in, int2d location_in, int storyHonesty_in, int play_in, int hostility_in, ResourceManager* resource_in, NaturalLogicManager* natural_in) override;
	std::string getTileInformation() override;
	bool getInteractablePresence(std::string text_in) override;
	std::string interactByName(std::string entry_in) override;

};