#pragma once

#include "Behaviour.h"

//! An implementation of Behaviour with a straight forward nature
class SimpleBehaviour : public Behaviour {
public:
	SimpleBehaviour();
	~SimpleBehaviour();

	std::string interactionProcess(std::string userText_in) override;
private:
	void addInteractionLog(std::string& userText_in) override;
};