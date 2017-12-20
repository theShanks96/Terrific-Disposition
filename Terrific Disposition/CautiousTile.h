#pragma once

#include "Tile.h"

class CautiousTile : public Tile {
public:
	CautiousTile();
	CautiousTile(std::string description_in);
	~CautiousTile();

	Interactable* c_interactable;
private:

};