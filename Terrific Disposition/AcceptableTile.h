#pragma once

#include "Tile.h"

class AcceptableTile : public Tile{
public:
	AcceptableTile();
	AcceptableTile(std::string description_in);
	~AcceptableTile();

	std::vector<Interactable*> v_interactables;
	int c_maximumInteractables;
private:

};