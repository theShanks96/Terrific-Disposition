#pragma once

#include <vector>
#include <string>

#include "DataStructs.h"

#include "Behaviour.h"


//! In-game entities that the player may interact with for benefit
class Interactable {
public:
	bool c_sapienceBool;
	Behaviour* ptr_behaviour;	

private:	
	std::string c_nameString;
	std::string c_descriptionString;

public:
	Interactable();
	~Interactable();
		
	std::string getName();
	void setName(std::string name_in);
	std::string getDescription();


};