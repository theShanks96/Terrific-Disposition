#pragma once

#include <vector>
#include <string>

#include "Interactable.h"

//! The basis for all the tiles in the world
class Tile{
public:
	Tile();
	Tile(std::string description_in);
	~Tile();

	std::string c_classification;
	bool c_availablePlot;

	std::string getDescription();
	void setDescription(std::string description_in);

	std::string getTypeFlavour();
	void setTypeFlavour(std::string flavour_in);
	
protected:
	std::string c_description;
	std::string c_typeFlavour;

};