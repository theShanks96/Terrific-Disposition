#pragma once

#include <vector>
#include <string>

#include "DataStructs.h"

#include "Behaviour.h"


//! In-game entities that the player may interact with for benefit
class Interactable {
private:
	std::string c_nameString;
	std::string c_descriptionString;
	std::string c_storedInformation;
	std::string c_sharedInformation;

	std::vector<std::string> v_semanticFieldStrings;

public:
	Interactable();
	~Interactable();

	bool c_sapienceBool;
	Behaviour* ptr_behaviour;


	std::string getInformation();
	void setInformation(std::string information_in[]);


	std::string getName();
	void setName(std::string name_in);
	std::string getDescription();


};