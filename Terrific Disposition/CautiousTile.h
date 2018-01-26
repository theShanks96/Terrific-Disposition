#pragma once

#include "Tile.h"

//! A tile that delineates that danger is nearby, and should keep the player's wits about them
class CautiousTile : public Tile {
public:
	CautiousTile();
	CautiousTile(std::string description_in);
	CautiousTile(bool hideoutTile_in);
	~CautiousTile();

	Interactable* c_interactable;

	bool populateInteractables(int2d nextPlotPoint_in, int honestReliable_in, int honestUnreliable_in, int dishonestReliable_in, int play_in, int aggressiveness_in) override;
	std::string getTileInformation() override;
	bool getInteractablePresence(std::string text_in) override;

};