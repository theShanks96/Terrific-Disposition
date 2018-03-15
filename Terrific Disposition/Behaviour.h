#pragma once


#include <string>
#include <vector>

#include "DataStructs.h"
#include "ResourceManager.h"
#include "NaturalLogicManager.h"


//! The basis for Behaviour of in-game entities
class Behaviour {
public:
	int2d c_nextPlotPoint;
	int2d c_currentLocation;

protected:
	std::vector<std::string> v_playerStrings;

	//! ptr_resourceManager Pointer to the resourcemanager used by the game
	ResourceManager* ptr_resourceManager;
	//! ptr_naturalLogicManager Pointer to the pythonmanager used by the game
	NaturalLogicManager* ptr_naturalLogicManager;
	
public:
	Behaviour();
	~Behaviour();	

	void linkResourceManager(ResourceManager* resource_in);	
	void linkNaturalLogicManager(NaturalLogicManager* natural_in);

	virtual std::string interactionProcess(std::string userText_in) = 0;
	
protected:
	virtual void addInteractionLog(std::string& userText_in) = 0;
};