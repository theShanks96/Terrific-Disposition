#pragma once


#include <string>
#include <vector>

#include "DataStructs.h"


//! The basis for Behaviour of in-game entities
class Behaviour {
protected:
	std::vector<std::string> v_playerStrings;
	std::string c_baseInformation;
	std::string c_flavourString;
	
	virtual void addInteractionLog(std::string& userText_in) = 0;
public:
	Behaviour();
	~Behaviour();

	int2d c_nextPlotPoint;

	virtual std::string interactionProcess(std::string userText_in) = 0;

};