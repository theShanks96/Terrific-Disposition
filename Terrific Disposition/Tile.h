#pragma once

#include <vector>
#include <string>


#include "DataStructs.h"

#include "Interactable.h"
#include "SimpleBehaviour.h"
#include "FuzzyBehaviour.h"

//! The basis for all the tiles in the world
class Tile{
public:
	Tile();
	Tile(std::string description_in);
	~Tile();

	std::string c_classificationString;
	bool c_availablePlotPosBool;

	std::string getDescription();
	void setDescription(std::string description_in);

	std::string getTypeFlavour();
	void setTypeFlavour(std::string flavour_in);

	virtual bool populateInteractables(int2d nextPlotPoint_in, int storyHonesty_in, int play_in, int hostility_in) = 0;
	virtual std::string getTileInformation() = 0;
	virtual bool getInteractablePresence(std::string text_in) = 0;
	
protected:
	std::string c_descriptionString;
	std::string c_typeFlavourString;

};