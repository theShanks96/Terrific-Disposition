#pragma once

#include <vector>
#include <string>

#include "Behaviour.h"


//! In-game entities that the player may interact with for benefit
class Interactable {
protected:
	bool c_sapience;

	Behaviour* c_behaviour;

	std::string c_name;
	std::string c_storedInformation;
	std::string c_sharedInformation;

	std::vector<std::string> v_semanticField;

public:
	Interactable();
	~Interactable();

	bool* getSapience();
	void setSapience(bool& sapience_in);

	std::string* getInformation();
	void setInformation(std::string information_in[]);

};