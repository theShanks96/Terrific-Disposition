#pragma once


#include <string>
#include <vector>

#include "DataStructs.h"
#include "ResourceManager.h"
#include "NaturalLogicManager.h"


//! The basis for Behaviour of in-game entities
class Behaviour {
protected:
	std::vector<std::string> v_playerStrings;
	std::string c_baseInformation;
	std::string c_flavourString;

	//! ptr_resourceManager Pointer to the resourcemanager used by the game
	ResourceManager* ptr_resourceManager;
	//! ptr_naturalLogicManager Pointer to the pythonmanager used by the game
	NaturalLogicManager* ptr_naturalLogicManager;
	
	virtual void addInteractionLog(std::string& userText_in) = 0;
public:
	Behaviour();
	~Behaviour();

	int2d c_nextPlotPoint;
	int2d c_currentLocation;

	void linkResourceManager(ResourceManager* resource_in);	
	void linkNaturalLogicManager(NaturalLogicManager* python_in);

	virtual std::string interactionProcess(std::string userText_in) = 0;

};