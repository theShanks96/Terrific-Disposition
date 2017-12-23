#pragma once

#include <string>
#include <vector>


//! The basis for Behaviour of in-game entities
class Behaviour {
protected:
	std::vector<std::string> v_playerInteraction;
	std::string c_baseInformation;
	std::string c_flavourText;
	
	virtual void addInteractionLog(std::string& userText_in) = 0;
public:
	Behaviour();
	~Behaviour();

};