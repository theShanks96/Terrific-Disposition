#pragma once

#include "Tile.h"

//! A tile deemed fairly safe for the player to find themselves
class AcceptableTile : public Tile{
public:
	AcceptableTile();
	AcceptableTile(std::string description_in);
	~AcceptableTile();

	bool populateInteractables(int2d nextPlotPoint_in, int2d location_in,int storyHonesty_in, int play_in, int hostility_in, ResourceManager* resource_in, NaturalLogicManager* python_in) override;
	std::string getTileInformation() override;
	bool getInteractablePresence(std::string text_in) override;
	std::string interactByName(std::string entry_in) override;

	std::vector<Interactable*> v_interactables;
	int c_maximumInteractables;
private:

};